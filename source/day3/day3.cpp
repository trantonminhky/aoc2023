/*
given the engine schematic, any neighboring number to a symbol must be added to a sum. calculate that sum
*/

#include "day3.hpp"
#include "helper.hpp"
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <stdio.h>

using pairOfCoordinatesXYType = std::pair<int, int>;
using pairOfCoordinatesAndWhetherTheyAppeared = std::pair<pairOfCoordinatesXYType, bool>;
using pairOfpartNumbersAndTheirCoordinatesType = std::pair<int, pairOfCoordinatesAndWhetherTheyAppeared>;

struct Neighbor
{
	pairOfCoordinatesXYType n;
	pairOfCoordinatesXYType ne;
	pairOfCoordinatesXYType e;
	pairOfCoordinatesXYType se;
	pairOfCoordinatesXYType s;
	pairOfCoordinatesXYType sw;
	pairOfCoordinatesXYType w;
	pairOfCoordinatesXYType nw;
};

int calculateNumberLength(int num)
{
	return floor(log10(num) + 1);
}

bool checkIfNeighborsContainNoNumbers(Neighbor neighbors, std::vector<std::string> tokens)
{
	return
	(
		isdigit(tokens[neighbors.n.second][neighbors.n.first]) &&
		isdigit(tokens[neighbors.ne.second][neighbors.ne.first]) &&
		isdigit(tokens[neighbors.e.second][neighbors.e.first]) &&
		isdigit(tokens[neighbors.se.second][neighbors.se.first]) &&
		isdigit(tokens[neighbors.s.second][neighbors.s.first]) &&
		isdigit(tokens[neighbors.sw.second][neighbors.sw.first]) &&
		isdigit(tokens[neighbors.w.second][neighbors.w.first]) &&
		isdigit(tokens[neighbors.nw.second][neighbors.nw.first])
	);
}

void Day3::solve1(std::string input)
{
	auto tokens = split(input, "\n");
	std::vector<pairOfpartNumbersAndTheirCoordinatesType> partNumbersAndTheirCoordinates;

	const int LENGTH_X = tokens[0].size();
	const int LENGTH_Y = tokens.size();

	// find all numbers and their coordinates
	for (auto y = 0; y < LENGTH_Y; y++)
	{
		auto token = tokens[y];
		std::stringstream buffer{};
		pairOfCoordinatesXYType coordinates(0, 0);
		buffer << '0';
		for (auto x = 0; x < LENGTH_X; x++)
		{
			auto c = token[x];
			if (isdigit(c) && std::stoi(buffer.str()) == 0)
			{
				coordinates = {x, y};
				buffer << c;
			}
			else if (isdigit(c) && std::stoi(buffer.str()) != 0)
			{
				buffer << c;
			}
			else if (!isdigit(c) && std::stoi(buffer.str()) != 0)
			{
				auto partNumber = std::stoi(buffer.str());
				pairOfCoordinatesAndWhetherTheyAppeared coorAndFlag = {coordinates, false};
				partNumbersAndTheirCoordinates.push_back(pairOfpartNumbersAndTheirCoordinatesType(partNumber, coorAndFlag));
				buffer.str("");
				buffer.clear();
				buffer << '0';
			}
		}
		if (std::stoi(buffer.str()) != 0)
		{
			auto partNumber = std::stoi(buffer.str());
			pairOfCoordinatesAndWhetherTheyAppeared coorAndFlag = {coordinates, false};
			partNumbersAndTheirCoordinates.push_back(pairOfpartNumbersAndTheirCoordinatesType(partNumber, coorAndFlag));
		}
	}

	// for (const auto& pair : partNumbersAndTheirCoordinates)
	// {
	// 	printf("<%d, %d>: %d\n", pair.second.first.first, pair.second.first.second, pair.first);
	// }

	for (auto y = 0; y < LENGTH_Y; y++)
	{
		auto token = tokens[y];
		for (auto x = 0; x < LENGTH_X; x++)
		{
			auto c = token[x];
			if (isdigit(c) || c == '.') continue;
			printf("found symbol %c at ln %d col %d\n", c, y + 1, x + 1);

			auto neighbors = Neighbor
			{
				pairOfCoordinatesXYType(x, std::max(y - 1, 0)),
				pairOfCoordinatesXYType(std::min(x + 1, LENGTH_X), std::max(y - 1, 0)),
				pairOfCoordinatesXYType(std::min(x + 1, LENGTH_X), y),
				pairOfCoordinatesXYType(std::min(x + 1, LENGTH_X), std::min(y + 1, LENGTH_Y)),
				pairOfCoordinatesXYType(x, std::min(y + 1, LENGTH_Y)),
				pairOfCoordinatesXYType(std::max(x - 1, 0), std::min(y + 1, LENGTH_Y)),
				pairOfCoordinatesXYType(std::max(x - 1, 0), y),
				pairOfCoordinatesXYType(std::max(x - 1, 0), std::max(y - 1, 0))
			};

			std::vector<pairOfCoordinatesXYType> neighborsVector{ neighbors.n, neighbors.ne, neighbors.e, neighbors.se, neighbors.s, neighbors.sw, neighbors.w, neighbors.nw };

			for (const auto& neighbor : neighborsVector)
			{
				char n_c = tokens[neighbor.second][neighbor.first];
				if (!isdigit(n_c)) continue;

				printf("valid neighbor found at ln %d col %d: %c\n", neighbor.second + 1, neighbor.first + 1, n_c);

				auto nearest = INT_MAX;
				for (const auto& pair : partNumbersAndTheirCoordinates)
				{
					// printf("comparing current (<%d, %d>) and pair (<%d, %d>)\n", neighbor.first, neighbor.second, pair.second.first.first, pair.second.first.second);
					if (neighbor.second != pair.second.first.second) continue;
					if (neighbor.first < pair.second.first.first) continue;
					if (nearest < neighbor.first - pair.second.first.first) continue;

					nearest = neighbor.first - pair.second.first.first;
					if (nearest == 0) break;
				}

				for (auto& pair : partNumbersAndTheirCoordinates)
				{
					if (pair.second.first == pairOfCoordinatesXYType(neighbor.first - nearest, neighbor.second))
					{
						pair.second.second = true;
					}
				}
				// printf("neighbor found at [%d, %d] has nearest value of %d\n", neighbor.first, neighbor.second, nearest);
			}
		}
	}

	// for (const auto& pair : partNumbersAndTheirCoordinates)
	// {
	// 	printf("<%d, %d>: %d\n", pair.second.first.first, pair.second.first.second, pair.first);
	// }

	auto sum = 0;
	for (const auto& pair : partNumbersAndTheirCoordinates)
	{
		if (pair.second.second) {
			sum += pair.first;
			// printf("%d\n", pair.first);
		}
	}
	printf("result: %d\n", sum);
}