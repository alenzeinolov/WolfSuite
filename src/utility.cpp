#include "utility.h"

namespace wolfsuite {

	std::string eraseStringFromString(std::string s1, std::string s2) {
		std::string::size_type i = s1.find(s2);
		if (i != std::string::npos)
			s1.erase(i, s2.length());
		return s1;
	}

}