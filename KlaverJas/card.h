#pragma once

#include "common.h"

namespace klaverjas
{
    enum class rank_t : unsigned short
    {
        ace, seven, eight, nine,
        ten, jack, queen, king
    };

    enum class suit_t : unsigned short
    {
        hearts, diamonds, clubs, spades
    };

    struct card_t
    {        
        constexpr auto to_value() const noexcept -> int
        {
            switch (rank)
            {
            case rank_t::nine:  return g_trump == suit ? 14 : 0;
            case rank_t::ace:   return 11;
            case rank_t::ten:   return 10;
            case rank_t::jack:  return g_trump == suit ? 20 : 2;
            case rank_t::queen: return 3;
            case rank_t::king:  return 4;
            default:            return 0;
            }
        }

        rank_t rank = rank_t::ace;
        suit_t suit = suit_t::spades;
        bool played = false;

        operator int() const noexcept { return to_value(); }
    };
}

