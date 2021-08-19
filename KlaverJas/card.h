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
        constexpr auto operator>(const card_t& card) const noexcept
        {
            if (card.suit != suit) return card.suit == g_trump;
            return to_value() > card.to_value();
        }
        
        struct accumulate_value
        {
            constexpr auto operator()(const value_t& value, const card_t* card) const noexcept -> value_t
            {
                return value + card->to_value();
            }
        };

        struct is_suit
        {
            constexpr auto operator()(const card_t* card) const noexcept -> bool
            {
                return  card->suit == this->suit;
            }

            constexpr auto operator==(const card_t* card) const noexcept -> bool
            {
                return  card->suit == this->suit;
            }

            suit_t suit;
        };

        struct is_greater
        {
            constexpr auto operator()(card_t* const lhs, card_t* const rhs) const noexcept -> card_t* const
            {
                return *lhs > *rhs ? lhs : rhs;
            }
        };

        struct is_greater_and_same_suit
        {
            constexpr auto operator()(const card_t* card) const noexcept -> bool
            {
                return *card > *(this->card) && card->suit == this->card->suit;
            }

            card_t* card;
        };

        constexpr auto to_value() const noexcept -> value_t
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

        constexpr operator value_t() const noexcept { return to_value(); }

        rank_t rank = rank_t::ace;
        suit_t suit = suit_t::spades;
        bool played = false;
    };

}

