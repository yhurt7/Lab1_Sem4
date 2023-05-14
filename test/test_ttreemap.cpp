#include <gtest.h>
#include "TTreeMap.h"

typedef TTreeMap<char, int> TTreeMap_test;

TEST(TTreeMap_test, can_create_tree_map)
{
  ASSERT_NO_THROW(TTreeMap_test m1('a', 1));
  TTreeMap_test m1('a', 1);
  EXPECT_EQ(m1.GetRootKey(), 'a');
  EXPECT_EQ(m1.GetValue('a'), 1);
}

TEST(TTreeMap_test, can_add_to_tree_map)
{
  TTreeMap_test m1('a', 1);
  m1.Add('b', 2);
  ASSERT_NO_THROW(m1.GetValue('b'));
  EXPECT_EQ(m1.GetValue('b'), 2);
}

TEST(TTreeMap_test, cannot_add_same_key_to_tree_map)
{
  TTreeMap_test m1('a', 1);
  m1.Add('b', 2);
  ASSERT_ANY_THROW(m1.Add('b', 2));
}

TEST(TTreeMap_test, can_not_get_value_from_incorrect_key_in_tree_map)
{
  TTreeMap_test m1('a', 1);
  ASSERT_ANY_THROW(m1.GetValue('b'));
}

TEST(TTreeMap_test, can_get_child_keys_from_tree_map)
{
  TTreeMap_test m1('b', 1);
  m1.Add('a', 2);
  m1.Add('c', 3);
  EXPECT_EQ(m1.GetLChildKey('b'), 'a');
  EXPECT_EQ(m1.GetRChildKey('b'), 'c');
}

TEST(TTreeMap_test, can_get_child_keys_from_incorrect_node_in_tree_map)
{
  TTreeMap_test m1('a', 1);
  ASSERT_ANY_THROW(m1.GetLChildKey('b'));
  ASSERT_ANY_THROW(m1.GetRChildKey('b'));
}

TEST(TTreeMap_test, can_del_from_tree_map)
{
  TTreeMap_test m1('a', 1);
  m1.Add('b', 2);
  ASSERT_NO_THROW(m1.Del('b'));
}

TEST(TTreeMap_test, cannot_del_incorrect_key_from_tree_map)
{
  TTreeMap_test m1('a', 1);
  m1.Add('b', 2);
  ASSERT_ANY_THROW(m1.Del('v'));
}
