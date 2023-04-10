#include <gtest.h>
#include "TSMap.h"

typedef TSMap<char, int> TSMap_test;

TEST(TSMap_test, can_create_sorted_map_with_positive_length)
{
  ASSERT_NO_THROW(TSMap_test m1(1));
}

TEST(TSMap_test, cannot_create_sorted_map_with_positive_length)
{
  ASSERT_ANY_THROW(TSMap_test m1(-1));
}

TEST(TSMap_test, created_map_has_correct_size)
{
  TSMap_test m1(1);
  EXPECT_EQ(m1.GetSize(), 1);
  EXPECT_EQ(m1.GetCount(), 0);
}

TEST(TSMap_test, can_add_values)
{
  TSMap_test m1(1);
  m1.Add('a', 1);
  EXPECT_EQ(m1.GetValue('a'), 1);
}

TEST(TSMap_test, can_del_values)
{
  TSMap_test m1(1);
  m1.Add('a', 1);
  m1.Del('a');
  ASSERT_ANY_THROW(m1.GetValue('a'));
  EXPECT_EQ(m1.GetSize(), 1);
  EXPECT_EQ(m1.GetCount(), 0);
}

TEST(TSMap_test, can_copy_map)
{
  TSMap_test m1(1);
  m1.Add('a', 1);
  ASSERT_NO_THROW(TSMap_test m2(m1));
  TSMap_test m2(m1);
  EXPECT_EQ(m1.GetSize(), m2.GetSize());
  EXPECT_EQ(m1.GetValue('a'), m2.GetValue('a'));
}