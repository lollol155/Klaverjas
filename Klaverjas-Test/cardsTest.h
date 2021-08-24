#pragma once

#include <cards.h>
using namespace klaverjas;

TEST(shuffle, cards) {
	cards_t cards;
	card_t card = *cards[0];

	EXPECT_EQ(card, *cards[0]);
	cards.shuffle();
	EXPECT_NE(card, *cards[0]);
}
