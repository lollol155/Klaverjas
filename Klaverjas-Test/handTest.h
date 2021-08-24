#pragma once

#include <trick.h>
#include <hand.h>
using namespace klaverjas;

TEST(playable_cards, hand) {
	hand_t hand;
	hand.emplace_back(new card_t{ rank_t::ace, suit_t::clubs });
	hand.emplace_back(new card_t{ rank_t::ace, suit_t::diamonds });
	hand.emplace_back(new card_t{ rank_t::ten, suit_t::diamonds });

	std::vector<card_t*> cards = hand.playable_cards();

	EXPECT_EQ(cards, hand);

	cards = hand.playable_cards(suit_t::diamonds);
	hand.erase(hand.begin());

	EXPECT_EQ(cards, hand);
}

TEST(playable_trumps, hand) {
	hand_t hand;
	hand.emplace_back(new card_t{ rank_t::ace, suit_t::clubs });
	hand.emplace_back(new card_t{ rank_t::ten, suit_t::diamonds });
	hand.emplace_back(new card_t{ rank_t::jack, suit_t::diamonds });
	hand_t result;

	card_t trick_card{ rank_t::seven, suit_t::hearts };
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

	trick_card.suit = suit_t::diamonds;
	cards = hand.playable_trumps(&trick_card);
	EXPECT_EQ(cards, result);

	trick_card.rank = rank_t::nine;
	cards = hand.playable_trumps(&trick_card);
	result.erase(result.begin());
	EXPECT_EQ(cards, result);
}

TEST(playable_hand, hand) {
	hand_t hand;
	hand.emplace_back(new card_t{ rank_t::ace, suit_t::clubs });
	hand.emplace_back(new card_t{ rank_t::ten, suit_t::diamonds });
	hand.emplace_back(new card_t{ rank_t::jack, suit_t::diamonds });
}

TEST(highest_card, hand) {
	hand_t hand;
	hand.emplace_back(new card_t{ rank_t::ace, suit_t::clubs });
	hand.emplace_back(new card_t{ rank_t::ten, suit_t::diamonds });
	hand.emplace_back(new card_t{ rank_t::jack, suit_t::diamonds });

	g_trump = suit_t::clubs;
	trick_t trick;

	std::vector<card_t*> cards = hand.playable_hand(trick);
	EXPECT_EQ(cards.size(), 3);

	trick.insert({ 1, new card_t{ rank_t::nine, suit_t::diamonds } });

	cards = hand.playable_hand(trick);
	EXPECT_EQ(cards.size(), 2);

	g_trump = suit_t::diamonds;

	cards = hand.playable_hand(trick);
	EXPECT_EQ(cards.size(), 1);

	trick.erase(1);
	trick.insert({ 1, new card_t{ rank_t::nine, suit_t::hearts } });

	cards = hand.playable_hand(trick);
	EXPECT_EQ(cards.size(), 2);
}