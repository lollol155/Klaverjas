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
        constexpr auto operator>(const card_t& card) const noexcept -> const bool
        {
            if (card.suit != suit) return card.suit != g_trump;
            return to_value() > card.to_value();
        }

        constexpr auto operator<(const card_t& card) const noexcept -> const bool
        {
            if (card.suit != suit) return suit == g_trump;
            return to_value() < card.to_value();
        }
        
        struct accumulate_value
        {
            constexpr auto operator()(const value_t& lhs, const card_t* const rhs) const noexcept -> const value_t
            {
                return lhs + rhs->to_value();
            }
            constexpr auto operator()(const value_t lhs, const std::pair<int, card_t*>& rhs) const noexcept -> const value_t
            {
                return lhs + rhs.second->to_value();
            }
        };

        struct is_suit
        {
            constexpr auto operator()(const card_t* const card) const noexcept -> const bool
            {
                return  card->suit == this->suit;
            }
            constexpr auto operator==(const card_t* const card) const noexcept -> const bool
            {
                return  card->suit == this->suit;
            }

            suit_t suit;
        };

        struct max
        {
            constexpr auto operator()(const card_t* const lhs, const card_t* const rhs) const noexcept -> const card_t* const
            {
                return *lhs > *rhs ? lhs : rhs;
            }
            constexpr auto operator()(card_t* const lhs, const std::pair<int, card_t*>& rhs) const noexcept -> card_t* const
            {
                return *lhs > *rhs.second ? lhs : rhs.second;
            }
        };

        struct is_less
        {
            constexpr auto operator()(const card_t* const lhs, const card_t* const rhs) const noexcept -> const bool
            {
                return *lhs < *rhs;
            }
        };

        struct is_greater_and_trump
        {
            constexpr auto operator()(const card_t* const card) const noexcept -> const bool
            {
                return *card > *(this->card) && card->suit == g_trump;
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

