#pragma once

#include <trick.h>

TEST(highest_card, trick) {
	trick_t trick;
	trick.emplace(1, new card_t{ rank_t::ace, suit_t::clubs });
	trick.emplace(2, new card_t{ rank_t::ten, suit_t::diamonds });
	trick.emplace(3, new card_t{ rank_t::jack, suit_t::diamonds });

	g_trump = suit_t::clubs;
	card_t highest_card{ rank_t::ace, suit_t::clubs };

	EXPECT_EQ(highest_card.suit, trick.highest()->suit);
	EXPECT_EQ(highest_card.rank, trick.highest()->rank);

	highest_card.rank = rank_t::jack;
	highest_card.suit = suit_t::diamonds;
	g_trump = suit_t::diamonds;

	EXPECT_EQ(highest_card.suit, trick.highest()->suit);
	EXPECT_EQ(highest_card.rank, trick.highest()->rank);
}

TEST(who_started, trick) {
	trick_t trick;
	trick.insert({ 1, new card_t{ rank_t::ace, suit_t::clubs } });
	trick.insert({ 2, new card_t{ rank_t::ten, suit_t::diamonds } });
	trick.insert({ 3, new card_t{ rank_t::jack, suit_t::diamonds } });

	EXPECT_EQ(trick.who_started(), 1);

	trick_t trick2;
	trick2.insert({ 4, new card_t{ rank_t::ace, suit_t::clubs } });
	trick2.insert({ 1, new card_t{ rank_t::ten, suit_t::clubs } });

	EXPECT_EQ(trick2.who_started(), 4);
}

TEST(started, trick) {
	trick_t trick;
	trick.insert({ 1, new card_t{ rank_t::ace, suit_t::clubs } });
	trick.insert({ 2, new card_t{ rank_t::ten, suit_t::diamonds } });
	trick.insert({ 3, new card_t{ rank_t::jack, suit_t::diamonds } });

	EXPECT_TRUE(trick.started());

	trick_t trick2;

	EXPECT_FALSE(trick2.started());
}

TEST(suit, trick) {
	g_trump = suit_t::clubs;
	trick_t trick;
	trick.insert({ 1, new card_t{ rank_t::ace, suit_t::clubs } });
	trick.insert({ 2, new card_t{ rank_t::ten, suit_t::diamonds } });
	trick.insert({ 3, new card_t{ rank_t::jack, suit_t::hearts } });

	EXPECT_EQ(trick.suit(), suit_t::clubs);

	g_trump = suit_t::diamonds;

	EXPECT_EQ(trick.suit(), suit_t::clubs);
}