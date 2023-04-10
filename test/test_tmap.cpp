#include <gtest.h>
#include "TMap.h"

typedef TMap<char, int> TMap_test;

TEST(TMap_test, can_create_map_with_positive_length)
{
  ASSERT_NO_THROW(TMap_test m1(1));
}

TEST(TMap_test, cannot_create_map_with_negative_length)
{
  ASSERT_ANY_THROW(TMap_test m1(-1));
}

TEST(TMap_test, created_map_has_correct_size)
{
  TMap_test m1(1);
  EXPECT_EQ(m1.GetSize(), 1);
  EXPECT_EQ(m1.GetCount(), 0);
}

TEST(TMap_test, can_add_values)
{
  TMap_test m1(1);
  m1.Add('a', 1);
  EXPECT_EQ(m1.GetValue('a'), 1);
  EXPECT_EQ(m1['a'], 1);
}

TEST(TMap_test, can_del_values)
{
  TMap_test m1(1);
  m1.Add('a', 1);
  m1.Del('a');
  ASSERT_ANY_THROW(m1.GetValue('a'));
  EXPECT_EQ(m1.GetSize(), 1);
  EXPECT_EQ(m1.GetCount(), 0);
}

TEST(TMap_test, can_copy_map)
{
  TMap_test m1(1);
  m1.Add('a', 1);
  ASSERT_NO_THROW(TMap_test m2(m1));
  TMap_test m2(m1);
  EXPECT_EQ(m1.GetSize(), m2.GetSize());
  EXPECT_EQ(m1.GetValue('a'), m2.GetValue('a'));
}