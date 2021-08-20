#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <execution>
#include <memory>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <numeric>
#include <iterator>
#include <random>
#include <vector>
#include <ranges>
#include <cmath>

#include "constants.h"

namespace klaverjas
{
	namespace ranges = std::ranges;

	enum class suit_t : unsigned short;
	static suit_t g_trump = static_cast<suit_t>(2); // clubs

	typedef int value_t;
	typedef int team_t;

	static std::random_device device;
	static std::mt19937 engine{ device() };
	static std::uniform_int_distribution<> suit_distribution(0, c_suits);
}