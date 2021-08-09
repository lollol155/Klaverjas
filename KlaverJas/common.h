#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <memory>
#include <numeric>
#include <iterator>
#include <random>
#include <ranges>

#include "constants.h"

namespace klaverjas
{
	enum class suit_t : unsigned short;
	static suit_t g_trump = static_cast<suit_t>(2); // clubs

	typedef int score_t;
	typedef int team_t;

	static std::random_device device;
	static std::mt19937 engine{ device() };
	static std::uniform_int_distribution<> suit_distribution(0, c_suits);
}