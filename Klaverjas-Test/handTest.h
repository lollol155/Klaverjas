#pragma once

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

	card_t trick_card{ rank_t::seven, suit_t::diamonds };

	std::vector<card_t*> cards = hand.playable_trumps(&trick_card);
	hand.erase(hand.begin());

	EXPECT_EQ(cards, hand);

	trick_card.rank = rank_t::nine;

	cards = hand.playable_trumps(&trick_card);
	hand.erase(hand.begin());

	EXPECT_EQ(cards, hand);
}

TEST(highest_card, hand) {
	hand_t hand;
	hand.emplace_back(new card_t{ rank_t::ace, suit_t::clubs });
	hand.emplace_back(new card_t{ rank_t::ten, suit_t::diamonds });
	hand.emplace_back(new card_t{ rank_t::jack, suit_t::diamonds });

	g_trump = suit_t::clubs;
	card_t highest_card{ rank_t::ten, suit_t::diamonds };

	EXPECT_EQ(highest_card.to_value(), hand.highest(suit_t::diamonds)->to_value());

	highest_card.rank = rank_t::jack;
	g_trump = suit_t::diamonds;

	EXPECT_EQ(highest_card.to_value(), hand.highest(suit_t::diamonds)->to_value());
}