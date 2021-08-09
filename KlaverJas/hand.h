#pragma once

#include "common.h"
#include "card.h"

namespace klaverjas
{
    struct hand_t
    {
        card_t* card;

        constexpr auto to_value() const noexcept -> int 
        {
            return std::accumulate(card, card + c_hand_size, 0);
        }

        operator int() const noexcept { return to_value(); }

        auto cbegin() const noexcept -> card_t const* { return card; }

        auto cend() const noexcept -> card_t const* { return card + c_hand_size; }
    };
}
