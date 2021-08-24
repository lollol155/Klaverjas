#pragma once

#include <trick.h>

TEST(highest_card, trick) {
	trick_t trick;
	trick.emplace(1, new card_t{ std::make_pair<suit_t, rank_t>(suit_t::clubs, rank_t::ace) });
	trick.emplace(2, new card_t{ std::make_pair<suit_t, rank_t>(suit_t::diamonds, rank_t::ten) });
	trick.emplace(3, new card_t{ std::make_pair<suit_t, rank_t>(suit_t::diamonds, rank_t::jack) });

	g_trump = suit_t::clubs;
	card_t highest_card{ std::make_pair<suit_t, rank_t>(suit_t::clubs, rank_t::ace) };

	EXPECT_EQ(highest_card.first, trick.highest()->first);
	EXPECT_EQ(highest_card.second, trick.highest()->second);

	highest_card.first = suit_t::diamonds;
	highest_card.second = rank_t::jack;
	g_trump = suit_t::diamonds;

	EXPECT_EQ(highest_card.first, trick.highest()->first);
	EXPECT_EQ(highest_card.second, trick.highest()->second);
}

TEST(who_started, trick) {
	trick_t trick;
	trick.insert({ 1, new card_t{ std::make_pair<suit_t, rank_t>(suit_t::clubs, rank_t::ace) } });
	trick.insert({ 2, new card_t{ std::make_pair<suit_t, rank_t>(suit_t::diamonds, rank_t::ten) } });
	trick.insert({ 3, new card_t{ std::make_pair<suit_t, rank_t>(suit_t::diamonds, rank_t::jack) } });

	EXPECT_EQ(trick.who_started(), 1);

	trick_t trick2;
	trick2.insert({ 4, new card_t{ std::make_pair<suit_t, rank_t>(suit_t::clubs, rank_t::ace) } });
	trick2.insert({ 1, new card_t{ std::make_pair<suit_t, rank_t>(suit_t::clubs, rank_t::ten) } });

	EXPECT_EQ(trick2.who_started(), 4);
}

TEST(started, trick) {
	trick_t trick;
	trick.insert({ 1, new card_t{ std::make_pair<suit_t, rank_t>(suit_t::clubs, rank_t::ace) } });
	trick.insert({ 2, new card_t{ std::make_pair<suit_t, rank_t>(suit_t::diamonds, rank_t::ten) } });
	trick.insert({ 3, new card_t{ std::make_pair<suit_t, rank_t>(suit_t::diamonds, rank_t::jack) } });

	EXPECT_TRUE(trick.started());

	trick_t trick2;

	EXPECT_FALSE(trick2.started());
}

TEST(suit, trick) {
	g_trump = suit_t::clubs;
	trick_t trick;
	trick.insert({ 1, new card_t{ std::make_pair<suit_t, rank_t>(suit_t::clubs, rank_t::ace) } });
	trick.insert({ 2, new card_t{ std::make_pair<suit_t, rank_t>(suit_t::diamonds, rank_t::ten) } });
	trick.insert({ 3, new card_t{ std::make_pair<suit_t, rank_t>(suit_t::hearts, rank_t::jack) } });

	EXPECT_EQ(trick.suit(), suit_t::clubs);

	g_trump = suit_t::diamonds;

	EXPECT_EQ(trick.suit(), suit_t::clubs);
}