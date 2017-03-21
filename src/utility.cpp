#include "utility.h"

namespace wolfsuite {

	void deleteFile(std::string file) {
		std::remove(file.c_str());
	}

}