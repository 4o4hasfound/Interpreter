#pragma once
#include <regex>
#include <string>

#include "GenerateRegex.hpp"

class WhiteSpace {
public:
	static bool eat(std::wstring::const_iterator& start, std::wstring::const_iterator& end);
private:
	static std::wregex s_regex;
};