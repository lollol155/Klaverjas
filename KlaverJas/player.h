#pragma once

#include "common.h"
#include "hand.h"
#include "trick.h"
#include "round.h"
#include "cards.h"

namespace klaverjas
{
	class player_t {
	public:
		auto set_hand(hand_t hand) noexcept -> void { m_hand = hand; };

		virtual constexpr auto play_hand() const noexcept -> const bool
		{
			return (m_hand.count(g_trump) * 10) + m_hand.to_value() > c_threshold_play;
		}

		virtual auto play_card(const trick_t& trick, const round_t& round, const cards_t& cards) const noexcept -> card_t* const
		{
			auto playable_cards = m_hand.playable_hand(trick);
			return playable_cards[0];
		}

	private:

		hand_t m_hand;
	};
}