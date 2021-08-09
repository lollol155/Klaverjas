#pragma once

#include "common.h"
#include "card.h"

namespace klaverjas
{
	struct trick_t {
		score_t points;
		score_t roem;
		unsigned short player;
		card_t* played_cards[c_players];

		constexpr auto score() const noexcept -> score_t { return points + roem; }
	};
}