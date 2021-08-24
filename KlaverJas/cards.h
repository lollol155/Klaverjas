#pragma once

#include "common.h"
#include "card.h"

namespace klaverjas
{
    struct cards_t : public std::array<card_t*, c_deck_size>
    {
        cards_t()
        {
            ranges::generate(_Elems, [n = 0]() mutable { return new card_t { std::make_pair(static_cast<suit_t>(n / c_ranks), static_cast<rank_t>(n++ % c_ranks)) }; });
        }

        auto shuffle() noexcept-> void { ranges::shuffle(_Elems, engine); }
    };
}