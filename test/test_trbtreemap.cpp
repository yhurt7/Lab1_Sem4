#include <gtest.h>
#include "TRBTreeMap.h"

typedef TRBTreeMap<char, int> TRBTreeMap_test;

TEST(TRBTreeMap_test, can_create_rb_tree_map)
{
  ASSERT_NO_THROW(TRBTreeMap_test m1());
}