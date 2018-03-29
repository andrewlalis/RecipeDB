#include "stringutils.h"

namespace StringUtils{

bool stringEndsWith(std::string const &fullString, std::string const &ending){
	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
	} else {
		return false;
	}
}

std::string toString(float val){
	float decimal = std::fmod(val, 1.0f);
	int places = 1;
	while (std::fmod(decimal * 10, 1.0f) > 0){
		decimal *= 10;
		places++;
	}
	char buffer[50];
	std::string arg = "%."+std::to_string(places)+"f";
	sprintf(buffer, arg.c_str(), val);
	std::string s = buffer;
	if (stringEndsWith(s, ".0")){
		while (s.find('.') != std::string::npos){
			s.pop_back();
		}
	}
	return s;
}

}
