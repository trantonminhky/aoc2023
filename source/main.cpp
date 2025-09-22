#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include "day1.hpp"

static constexpr std::string_view FILE_PREFIX = "../../source/";

int main() {
	std::ifstream fin(std::string(FILE_PREFIX) + "day1/input.txt");
	std::stringstream buffer;
	buffer << fin.rdbuf();
	solve2(buffer.str());

	return 0;
}