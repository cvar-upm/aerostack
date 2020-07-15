#include "stringstacker.h"

StringStacker::StringStacker()
{
    this->str(std::string());
}

StringStacker::StringStacker( const StringStacker& src) :
    std::basic_ios<char>(),
    std::stringstream()
{
    this->str(std::string());
    (*this) << src.str();
}

const StringStacker& StringStacker::operator=( const StringStacker& src) {
    this->str(std::string());
    (*this) << src.str();

    return (*this);
}

std::string StringStacker::getStackedString(bool empty_string_stream) {
    std::string string_out = this->str();
    if (empty_string_stream)
        this->str(std::string());
    return string_out;
}

