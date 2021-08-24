#pragma once

#include "common.h"
#include "card.h"
#include "trick.h"

namespace klaverjas
{
    struct hand_t : public std::vector<card_t*>
    {
        constexpr auto count(const suit_t& suit) const noexcept -> const long long
        {
            return std::count_if(cbegin(), cend(), card_t::is_suit(suit));
        }

        constexpr auto find(const suit_t& suit) const noexcept -> const bool
        {
            return std::find(cbegin(), cend(), card_t::is_suit(suit)) != cend();
        }

        constexpr auto highest(const suit_t& suit) const noexcept -> const card_t*
        {
            std::vector<card_t*> cards = playable_cards(suit);
            return *ranges::max_element(cards, card_t::is_less());
        }

        constexpr auto playable_cards() const noexcept -> const std::vector<card_t*>
        {
            std::vector<card_t*> cards(size());
            std::copy(begin(), end(), cards.begin());
            return cards;
        }

        constexpr auto playable_cards(const suit_t& suit) const noexcept -> const std::vector<card_t*>
        {
            std::vector<card_t*> cards;
            std::copy_if(begin(), end(), std::back_inserter(cards), card_t::is_suit(suit));
            return cards;
        }

        constexpr auto playable_trumps(card_t* const trick_card) const noexcept -> const std::vector<card_t*>
        {
            std::vector<card_t*> cards;
            std::copy_if(begin(), end(), std::back_inserter(cards), card_t::is_greater_and_trump(trick_card));
            if (cards.empty())
            {
                cards = playable_cards(trick_card->suit);
            }
            return cards;
        }

        auto playable_hand(const trick_t& trick) const noexcept -> const std::vector<card_t*>
        {
            if (trick.started())
            {
                if (trick.suit() != g_trump && find(trick.suit())) return playable_cards(trick.suit());
                if (find(g_trump)) return playable_trumps(trick.highest());
            }
            return playable_cards();
        }

        constexpr auto to_value() const noexcept -> value_t
        {
            return std::accumulate(cbegin(), cend(), 0, card_t::accumulate_value());
        }

        constexpr operator const value_t() const noexcept { return to_value(); }
    };
}
