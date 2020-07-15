#include "cvgException.h"

cvgException::cvgException() {
}

cvgException::cvgException(const char *msg) {
	message = msg;
}

cvgException::cvgException(const std::string &msg) {
	message = msg;
}

cvgException::cvgException(const cvgException &e) {
	message = e.message;
}

cvgException::cvgException(const std::exception &e) {
	message = std::string("C++ exception: ") + e.what();
}

cvgException::~cvgException() {
}

