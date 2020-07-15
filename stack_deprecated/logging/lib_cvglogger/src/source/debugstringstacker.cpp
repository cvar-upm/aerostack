#include "debugstringstacker.h"

std::list<DebugStringStacker*> DebugStringStacker::container_of_p2all_stackers;

DebugStringStacker::DebugStringStacker(int  stacker_channel_in) :
    priority_flag(false),
    stacker_channel(stacker_channel_in)
{
    this->str(std::string());

    container_of_p2all_stackers.push_front(this);
    iter = container_of_p2all_stackers.begin();
}

DebugStringStacker::~DebugStringStacker() {
    container_of_p2all_stackers.erase(iter);
}

const DebugStringStacker& DebugStringStacker::operator=( const DebugStringStacker& src) {
    this->str(std::string());
    (*this) << src.str();

//    this->iter = this->iter;
    return (*this);
}


DebugStringStacker::DebugStringStacker( const DebugStringStacker& src) :
    std::basic_ios<char>(),
    std::stringstream()
{
    this->str(std::string());
    (*this) << src.str();

    container_of_p2all_stackers.push_front(this);
    iter = container_of_p2all_stackers.begin();
}

void DebugStringStacker::getStackedDebugString(std::string &str_in, bool &priority_flag_out, bool empty_string_stream) {
    str_in = this->str();
    priority_flag_out = priority_flag;
    if (empty_string_stream) {
        this->str(std::string());
        priority_flag = false;
    }
}

std::string DebugStringStacker::getStackedDebugString( bool &priority_flag_out, bool empty_string_stream) {
    std::string str_out;
    getStackedDebugString(str_out, priority_flag_out, empty_string_stream);
    return str_out;
}


void DebugStringStacker::getAllStackedDebugStrings(std::string &str_in, bool &priority_flag_out, bool empty_string_streams, int  stacker_channel_in){
    str_in = std::string("");
    priority_flag_out = false;
    for (std::list<DebugStringStacker*>::iterator it = container_of_p2all_stackers.begin();
         it != container_of_p2all_stackers.end();
         ++it ) {
        if ((*it)->getStackerChannel() == stacker_channel_in) {
            bool aux_priority_flag_out = false;
            str_in += (*it)->getStackedDebugString( aux_priority_flag_out, empty_string_streams);
            priority_flag_out = priority_flag_out || aux_priority_flag_out;
        }
    }
    return;
}

std::string DebugStringStacker::getAllStackedDebugStrings( bool &priority_flag_out, bool empty_string_streams, int  stacker_channel_in) {
    std::string str_out;
    getAllStackedDebugStrings(str_out, priority_flag_out, empty_string_streams, stacker_channel_in);
    return str_out;
}
