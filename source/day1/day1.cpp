/*
given an input of multiline string, each line will be a substring that will have numbers in them. take only the first and last number digit to form a two-digit number (in the case of one number, the number is formed by repeating that digit)

so sha2aj3ajk4naks will be 24

after each line, take the sum of all the numbers formed
*/

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <cassert>
#include <stdio.h>

void solve1(std::string input)
{
	std::vector<std::string> tokens;
	
	// split input into
	{
		std::string delim = "\n";
		size_t pos;

		while (pos != input.npos)
		{
			pos = input.find(delim);

			auto token = input.substr(0, pos); // pos = 5
			tokens.push_back(token);
			input.erase(0, pos + delim.length());
		}
		
		for (const auto& s : tokens)
			std::cout << s << "\n";
	}

	auto sum = 0;

	// parse each token and retrieve the first and last digit
	{
		for (const auto& token : tokens)
		{
			auto first = *std::find_if(token.begin(), token.end(), isdigit);
			auto last = *std::find_if(token.rbegin(), token.rend(), isdigit);
			std::stringstream buffer;
			buffer << first << last;
			auto num = std::stoi(buffer.str());
			sum += num;
		}
	}

	std::cout << sum << "\n";
}

static const std::unordered_map<std::string, int> table = {
	{"zero", 0},
	{"one", 1},
	{"two", 2},
	{"three", 3},
	{"four", 4},
	{"five", 5},
	{"six", 6},
	{"seven", 7},
	{"eight", 8},
	{"nine", 9}
};

using IteratorAndIntegerPairType = std::pair<int, int>;

void solve2(std::string input)
{
	/*
	auto lookupTable = [](std::string _input) 
	{
		static const std::unordered_map<std::string, int> table = {
			{"zero", 0},
			{"one", 1},
			{"two", 2},
			{"three", 3},
			{"four", 4},
			{"five", 5},
			{"six", 6},
			{"seven", 7},
			{"eight", 8},
			{"nine", 9}
		};

		auto it = table.find(_input);
		if (it != table.end()) {
			return it->second;
		}
		return -1;
	};
	*/

	std::vector<std::string> tokens;
	// split input into
	{
		std::string delim = "\n";
		size_t pos;

		while (pos != input.npos)
		{
			pos = input.find(delim);

			auto token = input.substr(0, pos); // pos = 5
			tokens.push_back(token);
			input.erase(0, pos + delim.length());
		}
		
		// for (const auto& s : tokens)
			// std::cout << s << "\n";
	}
	
	auto sum = 0;
	{
		for (const auto& token : tokens)
		{
			// obtain first and last digit of a token
			IteratorAndIntegerPairType IFirst(-1, -1);
			IteratorAndIntegerPairType ILast(-1, -1);
			IteratorAndIntegerPairType SFirst(INT_MAX, -1);
			IteratorAndIntegerPairType SLast(-1, -1);

			auto it = std::find_if(token.begin(), token.end(), isdigit);
			auto rit = std::find_if(token.rbegin(), token.rend(), isdigit);
			IFirst.first = it - token.begin(); // 3
			IFirst.second = *it - 48; // 1
			ILast.first = token.rend() - rit - 1; // 3
			ILast.second = *rit - 48; // 1
		
			for (const auto& [snum, inum] : table)
			{
				int tokenFindIterator = token.find(snum);
				// std::cout << std::boolalpha << snum << ": " << inum << " (" << tokenFindIterator << ")" << (tokenFindIterator != token.npos && static_cast<int>(tokenFindIterator) > SLast.first) << "\n";
				if (tokenFindIterator != token.npos && tokenFindIterator < SFirst.first)
				{
					SFirst.first = tokenFindIterator;
					SFirst.second = inum;
				}
			}
			
			for (const auto& [snum, inum] : table)
			{	
				int tokenFindIterator = token.rfind(snum);
				if (tokenFindIterator != token.npos && tokenFindIterator > SLast.first)
				{
					SLast.first = tokenFindIterator;
					SLast.second = inum;
				}
			}

			std::vector<IteratorAndIntegerPairType> iteratorList;
			for (const auto& pair : {IFirst, ILast, SFirst, SLast})
			{
				// printf("<%d, %d>\n", pair.first, pair.second);
				if (pair.first >= 0 && pair.first < token.length()) iteratorList.push_back(pair);
			}
			// printf("iterator list length: %d\n", iteratorList.size());
			IteratorAndIntegerPairType leastPair = iteratorList[0];
			IteratorAndIntegerPairType mostPair = iteratorList[0];
			for (const auto& element : iteratorList) 
			{
				// printf("<%d, %d>, ", element.first, element.second);
				if (leastPair.first > element.first) leastPair = element;
				if (mostPair.first < element.first) mostPair = element;
			}
			std::stringstream buffer;
			buffer << leastPair.second << mostPair.second;
			auto num = std::stoi(buffer.str());
			sum += num;
			std::cout << num << "\n";
		}
	}

	printf("result: %d", sum);
}