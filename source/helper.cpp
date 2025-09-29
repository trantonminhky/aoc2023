#include "helper.hpp"

std::vector<std::string> split(std::string input, std::string delim) {
	std::vector<std::string> tokens;
	size_t pos;

	while (pos != input.npos)
	{
		pos = input.find(delim);

		auto token = input.substr(0, pos); // pos = 5
		tokens.push_back(token);
		input.erase(0, pos + delim.length());
	}
	return tokens;
}

// std::vector<std::string> splitMultipleDelims(std::string input);