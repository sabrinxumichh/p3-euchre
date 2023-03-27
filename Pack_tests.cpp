// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "Card.h"
#include "unit_test_framework.h"
#include <cassert>
#include <iostream>
#include <fstream>
using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}

TEST(test_reset) {
  Pack pack;
  pack.deal_one();
  pack.deal_one();
  pack.deal_one();
  pack.reset();
  Card first_card = pack.deal_one();
  ASSERT_EQUAL(first_card, Card(NINE, SPADES));

  Pack pack2;
  for (int i = 0; i < 23; ++i) {
    pack.deal_one();
  }
  pack.reset();
  Card c = pack.deal_one();
  ASSERT_EQUAL(c, Card(NINE, SPADES));
}

TEST(test_empty) {
    Pack pack;
    pack.deal_one();
    ASSERT_FALSE(pack.empty());
}

TEST(test_empty2) {
    Pack pack;
    for (int i = 0; i < 22; ++i) {
        pack.deal_one();
    }
    ASSERT_FALSE(pack.empty());

    pack.deal_one();
    pack.deal_one();

    ASSERT_TRUE(pack.empty());
}


TEST_MAIN()