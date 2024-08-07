#pragma once
#include <regex>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

std::wregex generateRegex(const std::vector<std::wstring>& strings, bool replaceSpecialCharacter, const std::wstring& cannotEndsWith = L"");