#pragma once

#include "common.h"
#include "round.h"

namespace klaverjas
{
	struct rounds_t : public std::array<round_t, c_rounds>
	{
		constexpr auto to_value(const team_t team) const noexcept -> value_t
		{
			return std::accumulate(cbegin(), cend(), 0, [&](value_t lhs, round_t rhs) { return lhs + rhs.to_value(team); });
		};
	};
}