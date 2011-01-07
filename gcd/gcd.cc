#include "gtest/gtest.h"

#define SWAP(a,b) (a ^= b, b ^= a, a ^= b)

TEST(swap, swap1) { int a = 1, b = 2; SWAP(a, b); ASSERT_EQ(1, b); ASSERT_EQ(2, a); }
TEST(swap, swap2) { unsigned int a = 0xdeadbeaf, b = 0xcafecafe; SWAP(a, b); ASSERT_EQ(0xcafecafe, a); ASSERT_EQ(0xdeadbeaf, b); }

template<typename type> type gcd(type a, type b) {
  return b < a ? gcd_aux(a, b) : gcd_aux(b, a);
}

template<typename type> type gcd_aux(type a, type b) {
  return b ? gcd_aux(b, a % b) : a;
}

TEST(gcd, gcd) { ASSERT_EQ(1, gcd(3, 2)); }
TEST(gcd, gcd_3_6_is_3) { ASSERT_EQ(3, gcd(3, 6)); }
TEST(gcd, gcd_256_8_is_8) { ASSERT_EQ(8, gcd(256, 8)); }

template<typename type> type lcm(type a, type b) {
  return a / gcd(a, b) * b;
}

TEST(lcm, lcm1) { ASSERT_EQ(12, lcm(3, 4)); }
TEST(lcm, lcm2) { ASSERT_EQ(28, lcm(4, 7)); }
TEST(lcm, lcm3) { ASSERT_EQ(30, lcm(5, 6)); }

