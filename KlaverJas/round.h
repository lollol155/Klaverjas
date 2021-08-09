#pragma once

#include "common.h"
#include "trick.h"

namespace klaverjas
{
	struct round_t : public std::array<trick_t, c_tricks>
	{
		constexpr auto score(const short player) const noexcept -> score_t
		{
			return std::accumulate(cbegin(), cend(), 0, [&](const score_t lhs, const trick_t rhs) { return player == rhs.player ? lhs + rhs.score() : lhs; });
		};
	};
}