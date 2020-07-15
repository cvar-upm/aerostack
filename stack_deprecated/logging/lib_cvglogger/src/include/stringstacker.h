#ifndef STRINGSTACKER_H
#define STRINGSTACKER_H

#include <sstream>
#include <string>

class StringStacker : public std::stringstream {
public:
    StringStacker();
    StringStacker( const StringStacker& src);
    const StringStacker& operator=( const StringStacker& src);
    std::string getStackedString( bool empty_string_stream = true);
};

#endif // STRINGSTACKER_H
