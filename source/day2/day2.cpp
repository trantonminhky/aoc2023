/*
given a bag of 12 red cubes, 13 green cubes, and 14 blue cubs. a game is played by randomly picking a set of cubes from the bag and then put back. this picking action can be performed multiple times per game, and the match's information is recorded as so:

	Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue

where the semicolon denotes each pick. determine if the game is possible, i.e. picked number of a cube's type must not exceed the true number of cubes in the bag
*/

#include <string>
#include <sstream>
#include <stdio.h>
#include "day2.hpp"
#include "helper.hpp"

static constexpr auto RED = 12;
static constexpr auto GREEN = 13;
static constexpr auto BLUE = 14;

bool checkIfMatchIsPossible(char c, int count)
{
	if (c == 'b')
	{
		if (count > BLUE) return false;
		return true;
	}
	else if (c == 'r')
	{
		if (count > RED) return false;
		return true;
	}
	else if (c == 'g')
	{
		if (count > GREEN) return false;
		return true;
	}
	return false;
}

void Day2::solve1(std::string input)
{
	auto tokens = split(input, "\n");
	// remove "Game xxx: " in each token
	for (int i = 0; i < tokens.size(); i++)
	{ // watch out for off-by-one
		auto it = tokens[i].find(":"); // 6
		tokens[i].erase(0, it + 2);
	}

	std::vector<std::vector<std::string>> _tokens;
	for (auto token : tokens)
	{
		_tokens.push_back(split(token, "; "));
	}

	auto sum = 0;
	for (int gameIdMinus1 = 0; gameIdMinus1 < tokens.size(); gameIdMinus1++) // 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
	{
		auto isGamePossible = true;
		for (auto match : _tokens[gameIdMinus1]) // 3 blue, 4 red
		{
			// printf("%s\n", match.c_str());
			std::stringstream buffer{};
			int cubeCount{};
			auto amidstColorFlag = false;
			auto isMatchPossible = true;

			for (auto c : match) // 3 ->  -> b -> l -> u -> e
			{
				if (isdigit(c)) buffer << c;
				else if (c == ' ')
				{
					// printf("CURRENT BUFFER: %s\n", buffer.str().c_str());
					cubeCount = std::stoi(buffer.str());
				}
				else if (c == ',')
				{
					buffer.str("");
					buffer.clear();
					buffer << '0';
					amidstColorFlag = false;
				}
				else if (!amidstColorFlag)
				{	
					// printf("currently processing %c\n", c);
					amidstColorFlag = true;
					if (!checkIfMatchIsPossible(c, cubeCount))
					{
						isMatchPossible = false;
						break;
					}
				}
			}

			if (!isMatchPossible)
			{
				isGamePossible = false;
				break;
			}
			// printf("MATCH %d POSSIBLE\n", gameIdMinus1 + 1);
		}

		if (isGamePossible) 
		{
			sum += gameIdMinus1 + 1;
			printf("GAME %d POSSIBLE\n", gameIdMinus1 + 1);
		}
		else
		{
			printf("GAME %d NOT POSSIBLE\n", gameIdMinus1 + 1);
		}
	}

	printf("result: %d\n", sum);
}

void Day2::solve2(std::string input)
{

}