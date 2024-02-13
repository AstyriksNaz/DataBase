#include "trim.h"

namespace myTrim {
	void trim(std::string& _s) {
		ltrim(_s);
		rtrim(_s);
	}

	void ltrim(std::string& _s) {
		_s.erase(_s.begin(), std::find_if(_s.begin(), _s.end(), [](const unsigned char& ch)  -> bool {
			return !std::isspace(ch); }));
	}

	void rtrim(std::string& _s) {
		_s.erase(std::find_if(_s.rbegin(), _s.rend(), [](const unsigned char& ch)->bool {return !std::isspace(ch); }).base(), _s.end());
	}

	std::string trim_copy(const std::string& _s_copy) {
		return rtrim_copy(ltrim_copy(_s_copy));
	}

	std::string ltrim_copy(const std::string& _s_copy) {
		std::string _s = _s_copy;
		_s.erase(_s.begin(), std::find_if(_s.begin(), _s.end(), [](const unsigned char& ch)  -> bool {
			return !std::isspace(ch); }));
		return _s;
	}

	std::string rtrim_copy(const std::string& _s_copy) {
		std::string _s = _s_copy;
		_s.erase(std::find_if(_s.rbegin(), _s.rend(), [](const unsigned char& ch)->bool {return !std::isspace(ch); }).base(), _s.end());
		return _s;
	}
}