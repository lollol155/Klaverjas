#pragma once

#include "common.h"
#include "card.h"

namespace klaverjas
{
    struct cards_t : public std::array<card_t, c_deck_size>
    {
        cards_t()
        {
            std::ranges::generate(_Elems, [n = 0]() mutable { return card_t{ static_cast<rank_t>(n % c_ranks), static_cast<suit_t>(n++ / c_ranks) }; });
        }

        auto shuffle() noexcept-> void { std::ranges::shuffle(_Elems, engine); }

        auto reset() noexcept-> void { }//std::ranges::for_each(_Elems, [](auto& played) { played = false;  }, & card_t::played); }
    };
}