#include "Tokens/WhiteSpace.hpp"

std::wregex WhiteSpace::s_regex = generateRegex({ LR"((//.*)?\s*)" }, 0);

bool WhiteSpace::eat(std::wstring::const_iterator& start, std::wstring::const_iterator& end) {
	std::wsmatch match;
	if (std::regex_search(start, end, match, s_regex)) {
		start = match.suffix().first;
		return true;
	}
	return false;
}
