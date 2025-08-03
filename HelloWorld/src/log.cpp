#include "log.h"

namespace Log {
	void Error(const char* message) {
		printf("ERROR:   %s", message);
		exit(-1);
	}
}