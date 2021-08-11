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
		auto started() const noexcept -> const bool { return !empty(); }
		auto suit() const noexcept -> const suit_t
		{ 
			assert(started()); 
			return cbegin()->second->suit;
		}
		auto highest() const noexcept -> card_t* const
		{ 
			assert(started());
			//return std::transform_reduce(begin() + 1, end(),*begin(), card_t::greater_card(), [](const std::pair<int, card_t*>& pair) { return pair.second; });
			return cbegin()->second;
		}
		constexpr auto score() const noexcept -> const value_t { return std::accumulate(cbegin(), cend(), 0, [](value_t value, const std::unordered_map<int, card_t*>::value_type& card) { return value + card.second->to_value(); }); }
		constexpr auto roem() const noexcept -> value_t { return 0; } // TODO
	};
}