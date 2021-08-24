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
			for (;;)
			{
				play_round();
			}
		}

	private:
		auto init_players() noexcept -> void
		{
			m_starting_player = 0;
			for (auto player = 0; player < c_players; player++)
			{
				hand_t hand;
				hand.resize(c_hand_size);
				std::copy(m_cards.begin() + player * c_hand_size, m_cards.begin() + player * c_hand_size + c_hand_size, hand.begin());
				m_players[player].set_hand(hand);
			}
		}

		virtual auto play_round() noexcept -> const round_t
		{
			round_t round;
			shuffle();
			for (;;)
			{
				play_trick(round);
				next_starting_player();
			}
			flip();
		}

		virtual auto play_trick(const round_t& round) noexcept -> const trick_t
		{
			//auto playing_player = who_plays();
			trick_t trick;
			for (auto counter = 0, player = m_starting_player; counter < c_players; counter++, player = counter % c_players)
			{
				auto played_card = m_players[player].play_card(trick, round, m_cards) + player * c_hand_size;
				//trick.emplace(player, &played_card);
				//played_card->played = true;
			}


			// calculate score


			return trick;
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

		auto shuffle() noexcept -> void	{ m_cards.shuffle(); }

		auto flip() noexcept -> void { g_trump = static_cast<suit_t>(suit_distribution(engine)); }

		inline auto next_starting_player() noexcept -> void { m_starting_player = (m_starting_player) % c_players; }

		rounds_t m_rounds;
		cards_t m_cards;
		player_t m_players[c_players];
		int m_starting_player;
	};
}