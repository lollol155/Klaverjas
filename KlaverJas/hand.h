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

        constexpr auto highest(const suit_t& suit) const noexcept -> const value_t
        {
            std::vector<card_t*> cards = playable_cards(suit);
            return 0; //**ranges::max_element(cards);
        }

        constexpr auto playable_cards() const noexcept -> const std::vector<card_t*>
        {
            std::vector<card_t*> cards(size());
            std::copy(begin(), end(), cards.begin());
            return cards;
        }

        constexpr auto playable_cards(const suit_t& suit) const noexcept -> const std::vector<card_t*>
        {
            std::vector<card_t*> cards(size());
            std::copy_if(begin(), end(), cards.begin(), card_t::is_suit(suit));
            return cards;
        }

        constexpr auto playable_trumps(card_t* const trick_card) const noexcept -> const std::vector<card_t*>
        {
            std::vector<card_t*> cards(size());
            std::copy_if(begin(), end(), cards.begin(), card_t::is_greater_and_same_suit(trick_card));
            return cards;
        }

        auto playable_hand(const trick_t& trick) const noexcept -> const std::vector<card_t*>
        {
            if (trick.started())
            {
                if (find(trick.suit())) return playable_cards(trick.suit());
                if (find(g_trump)) return playable_trumps(trick.highest());
            }
            return playable_cards();
        }

        constexpr auto to_value() const noexcept -> value_t
        {
            return std::accumulate(cbegin(), cend(), 0, card_t::accumulate_value());
        }

        operator const value_t() const noexcept { return to_value(); }
    };
}
