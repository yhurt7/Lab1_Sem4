#include <gtest.h>
#include "THMap.h"

typedef THMap<char, int> THMap_test;

TEST(THMap_test, can_create_hash_map_with_positive_length)
{
  ASSERT_NO_THROW(THMap_test m1(1));
}

TEST(THMap_test, cannot_create_hash_map_with_negative_length)
{
  ASSERT_ANY_THROW(THMap_test m1(-1));
}

TEST(THMap_test, can_add_item_to_hash_map)
{
  THMap_test m1(10);
  m1.Add('a', 1);
  EXPECT_EQ(m1.GetValue('a'), 1);
}

TEST(THMap_test, cannot_add_item_to_full_hash_map)
{
  THMap_test m1(1);
  m1.Add('a', 1);
  ASSERT_ANY_THROW(m1.Add('b', 2));
}

TEST(THMap_test, can_del_item_from_hash_map)
{
  THMap_test m1(10);
  m1.Add('a', 1);
  m1.Del('a');
  ASSERT_ANY_THROW(m1.GetValue('a'));
}

TEST(THMap_test, cannot_del_inexistent_item_from_hash_map)
{
  THMap_test m1(10);
  m1.Add('a', 1);
  ASSERT_ANY_THROW(m1.Del('b'));
}