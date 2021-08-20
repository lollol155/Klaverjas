#pragma once

#include "common.h"
#include "card.h"

namespace klaverjas
{
	struct trick_t : public	std::unordered_map<int, card_t*>
	{
		auto who_started() const noexcept -> const int
		{
			assert(started());
			return cbegin()->first;
		}
		auto started() const noexcept -> const bool
		{
			return !empty(); 
		}
		auto suit() const noexcept -> const suit_t
		{ 
			assert(started()); 
			return cbegin()->second->suit;
		}
		auto highest() const noexcept -> card_t* const
		{ 
			assert(started());
			return std::reduce(begin(), end(), begin()->second, card_t::max());
		}
		constexpr auto to_value() const noexcept -> const value_t
		{
			return std::accumulate(cbegin(), cend(), 0, card_t::accumulate_value());
		}
		constexpr auto roem() const noexcept -> value_t { return 0; } // TODO

		constexpr operator value_t() const noexcept { return to_value(); }
	};
}