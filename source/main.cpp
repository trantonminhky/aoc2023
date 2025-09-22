#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include "header.hpp"

static constexpr std::string_view FILE_PREFIX = "../../source/";
static constexpr std::string_view DAY = "day2"; // change this for solution of a day

int main() {
	std::ifstream fin(std::string(FILE_PREFIX) + std::string(DAY) + "/input.txt");
	std::stringstream buffer;
	buffer << fin.rdbuf();
	Day1::solve1(buffer.str()); // change function name for first part solution and second part solution

	return 0;
}