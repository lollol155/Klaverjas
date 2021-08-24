#pragma once

#include "common.h"
#include "trick.h"

namespace klaverjas
{
	struct round_t : public std::array<trick_t, c_tricks>
	{
		constexpr auto to_value(const short player) const noexcept -> value_t
		{
			return std::accumulate(cbegin(), cend(), 0, [&](const value_t& lhs, const trick_t& rhs) { return player == rhs.who_started() ? lhs + rhs.to_value() : lhs; });
		};
	};
}