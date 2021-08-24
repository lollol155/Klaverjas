#pragma once

#include <trick.h>
#include <hand.h>
using namespace klaverjas;

TEST(playable_cards, hand) {
	hand_t hand;
	hand.emplace_back(new card_t{ std::make_pair<suit_t, rank_t>(suit_t::clubs, rank_t::ace) });
	hand.emplace_back(new card_t{ std::make_pair<suit_t, rank_t>(suit_t::diamonds, rank_t::ace) });
	hand.emplace_back(new card_t{ std::make_pair<suit_t, rank_t>(suit_t::diamonds, rank_t::ten) });

	std::vector<card_t*> cards = hand.playable_cards();

	EXPECT_EQ(cards, hand);

	cards = hand.playable_cards(suit_t::diamonds);
	hand.erase(hand.begin());

	EXPECT_EQ(cards, hand);
}

TEST(playable_trumps, hand) {
	hand_t hand;
	hand.emplace_back(new card_t{ std::make_pair<suit_t, rank_t>(suit_t::clubs, rank_t::ace) });
	hand.emplace_back(new card_t{ std::make_pair<suit_t, rank_t>(suit_t::diamonds, rank_t::ten) });
	hand.emplace_back(new card_t{ std::make_pair<suit_t, rank_t>(suit_t::diamonds, rank_t::jack) });
	hand_t result;

	card_t trick_card{ std::make_pair<suit_t, rank_t>(suit_t::hearts, rank_t::seven) };
	g_trump = suit_t::spades;

	std::vector<card_t*> cards = hand.playable_trumps(&trick_card);
	EXPECT_EQ(cards, result);

	g_trump = suit_t::clubs;
	cards = hand.playable_trumps(&trick_card);
	result.emplace_back(hand[0]);
	EXPECT_EQ(cards, result);

	result = hand;
	g_trump = suit_t::diamonds;
	cards = hand.playable_trumps(&trick_card);
	result.erase(result.begin());
	EXPECT_EQ(cards, result);

	trick_card.first = suit_t::diamonds;
	cards = hand.playable_trumps(&trick_card);
	EXPECT_EQ(cards, result);

	trick_card.second = rank_t::nine;
	cards = hand.playable_trumps(&trick_card);
	result.erase(result.begin());
	EXPECT_EQ(cards, result);
}

TEST(playable_hand, hand) {
	hand_t hand;
}

TEST(highest_card, hand) {
	hand_t hand;
	hand.emplace_back(new card_t{ std::make_pair<suit_t, rank_t>(suit_t::clubs, rank_t::ace) });
	hand.emplace_back(new card_t{ std::make_pair<suit_t, rank_t>(suit_t::diamonds, rank_t::ten) });
	hand.emplace_back(new card_t{ std::make_pair<suit_t, rank_t>(suit_t::diamonds, rank_t::jack) });

	g_trump = suit_t::clubs;
	trick_t trick;

	std::vector<card_t*> cards = hand.playable_hand(trick);
	EXPECT_EQ(cards.size(), 3);

	trick.insert({ 1, new card_t{ std::make_pair<suit_t, rank_t>(suit_t::diamonds, rank_t::nine) } });

	cards = hand.playable_hand(trick);
	EXPECT_EQ(cards.size(), 2);

	g_trump = suit_t::diamonds;

	cards = hand.playable_hand(trick);
	EXPECT_EQ(cards.size(), 1);

	trick.erase(1);
	trick.insert({ 1, new card_t{ std::make_pair<suit_t, rank_t>(suit_t::hearts, rank_t::nine) } });

	cards = hand.playable_hand(trick);
	EXPECT_EQ(cards.size(), 2);
}