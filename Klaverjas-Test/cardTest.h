#pragma once

#include <card.h>
using namespace klaverjas;

TEST(value, card) {
	card_t card;
	card.suit = suit_t::clubs;
	card.rank = rank_t::jack;

	g_trump = suit_t::clubs;
	EXPECT_EQ(card.to_value(), 20);
	EXPECT_EQ(card, 20);
	g_trump = suit_t::diamonds;
	EXPECT_EQ(card.to_value(), 2);
	EXPECT_EQ(card, 2);
}

TEST(larger, card) {
	card_t card;
	card.suit = suit_t::clubs;
	card.rank = rank_t::jack;

	card_t card2;
	card2.suit = suit_t::clubs;
	card2.rank = rank_t::ace;

	g_trump = suit_t::clubs;
	EXPECT_TRUE(card > card2);
	EXPECT_TRUE(card2 < card);
	g_trump = suit_t::diamonds;
	EXPECT_TRUE(card2 > card);
	EXPECT_TRUE(card < card2);
}