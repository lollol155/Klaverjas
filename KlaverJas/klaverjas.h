#pragma once

#include "common.h"
#include "cards.h"
#include "player.h"
#include "rounds.h"

namespace klaverjas
{
	class klaverjas
	{
	public:
		klaverjas()
		{
			init_players();
			for (auto& round : m_rounds)
			{
				shuffle();
				for (auto& trick : round)
				{
					play_trick(trick);
				}
				flip();
			}
		}

	private:
		auto init_players() noexcept -> void
		{
			m_starting_player = 0;
			for (auto player = 0; player < c_players; player++)
			{
				m_players[player].set_hand(hand_t{ &m_cards[player * c_hand_size] });
			}
		}

		virtual auto play_trick(trick_t& trick) noexcept -> void
		{
			auto playing_player = who_plays();
			for (auto player = 0, real_player = m_starting_player; player < c_players; player++, real_player = player % c_players)
			{
				trick.played_cards[real_player];
				// every player plays card

				//card_t* players[player % c_players].which_card(cards);
			}
			// calculate score


			next_starting_player();
		}

		virtual auto who_plays() noexcept -> int
		{
			while (true)
			{
				for (size_t player = m_starting_player; player - m_starting_player < c_players; player++)
					if (m_players[player % c_players].play_hand()) return (int)player;
				flip();
				for (size_t player = m_starting_player; player - m_starting_player < c_players; player++)
					if (m_players[player % c_players].play_hand()) return (int) player;
				shuffle();
			}
		}

		auto shuffle() noexcept -> void	{ m_cards.reset(); m_cards.shuffle(); }

		auto flip() noexcept -> void { g_trump = static_cast<suit_t>(suit_distribution(engine)); }

		inline auto next_starting_player() noexcept -> void { m_starting_player = (m_starting_player) % c_players; }

		rounds_t m_rounds;
		cards_t m_cards;
		player_t m_players[c_players];
		int m_starting_player;
	};
}