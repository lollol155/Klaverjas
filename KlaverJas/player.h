#pragma once

#include "common.h"
#include "hand.h"
#include "trick.h"
#include "cards.h"

namespace klaverjas
{
	class player_t {
	public:
		auto set_hand(hand_t hand) noexcept -> void { m_hand = hand; };

		virtual auto play_hand() const noexcept -> bool
		{
			return (count_trumps() * 10) + m_hand.to_value() > c_threshold_play;
		}

		virtual auto play_card(const trick_t* trick, const cards_t* cards, const int& postition) const noexcept -> card_t*
		{
		}

	private:

		auto count_trumps() const noexcept -> short
		{
			return (short) std::count_if(m_hand.cbegin(), m_hand.cend(), [](const card_t& card) { return card.suit == g_trump; });
		}

		hand_t m_hand;
	};
}