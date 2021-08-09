#pragma once

#include "common.h"
#include "round.h"

namespace klaverjas
{
	struct rounds_t : public std::array<round_t, c_rounds>
	{
		constexpr auto score(const team_t team) const noexcept -> score_t
		{
			return std::accumulate(cbegin(), cend(), 0, [&](score_t lhs, round_t rhs) { return lhs + rhs.score(team); });
		};
	};
}