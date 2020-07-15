#include <string>

#ifndef CVG_EXCEPTION_INCLUDED__
#define CVG_EXCEPTION_INCLUDED__

class cvgException {
private:
    std::string message;

public:
	cvgException();
	cvgException(const cvgException &e);
    cvgException(const char *msg);
    cvgException(const std::string &msg);
	cvgException(const std::exception &e);

	virtual ~cvgException();

    inline std::string &getMessage() { return message; }
	inline cvgException &operator = (cvgException &e) { message = e.message; return *this; }
};

#endif
