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
	for (const auto& token : tokens)
	{
		auto first = *std::find_if(token.begin(), token.end(), isdigit);
		auto last = *std::find_if(token.rbegin(), token.rend(), isdigit);
		std::stringstream buffer;
		buffer << first << last;
		auto num = std::stoi(buffer.str());
		sum += num;
	}

	std::cout << sum << "\n";
}