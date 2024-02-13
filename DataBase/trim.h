#pragma once
#include <string>
#include <algorithm>

namespace myTrim {
	void trim(std::string& _s);

	void ltrim(std::string& _s);

	void rtrim(std::string& _s);

	std::string trim_copy(const std::string& _s_copy);
	std::string ltrim_copy(const std::string& _s_copy);
	std::string rtrim_copy(const std::string& _s_copy);
}

