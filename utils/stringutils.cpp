#include "stringutils.h"

namespace StringUtils{

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
	return s;
}

}
