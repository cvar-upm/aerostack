#ifndef DEBUGSTRINGSTACKER_H
#define DEBUGSTRINGSTACKER_H

#include <iostream>
#include <sstream>
#include <list>

// Class Description:
//  - Each rosnode/process may have several components that need to stack log data,
//    each of them will have an instance of the class DebugStringStacker.
//  - The node can gather all the debug information using the static function
//    getAllStackedDebugStrings() that uses a handle to access all the instances.
//    Note that this functions should only be called once in each rosnode/process,
//    as it automatically empties all the debugstrings of each component.
//  - Priority_flag specifies that the current string contains data that MUST be logged.
//    The use is that rostopics are usually used to broadcast logdata, however some
//    information can be given to DroneLogger in a rosservice. For now, however, this
//    functionality will not be used.
// To see why std::list is used for this class, check the iterator invalidation rules:
//  http://stackoverflow.com/questions/6438086/iterator-invalidation-rules
//  inspired from: http://stackoverflow.com/questions/16501419/creating-a-class-with-a-static-member-container-holding-all-instances-of-said-cl

class DebugStringStacker : public std::stringstream {
private:
    bool priority_flag;
    int  stacker_channel;

public:
    DebugStringStacker(int  stacker_channel_in = 0);
    ~DebugStringStacker();
    inline int getStackerChannel() { return stacker_channel; }
private:
    DebugStringStacker( const DebugStringStacker& src);
    const DebugStringStacker& operator=( const DebugStringStacker& src);

public:
    inline void setPriorityFlag() { priority_flag = true; }
private:
    // (*this) = std::ostringstream events_string_stream;
    std::list<DebugStringStacker*>::iterator iter;
    void getStackedDebugString(std::string &str_in, bool &priority_flag_out, bool empty_string_stream = true);
    std::string getStackedDebugString( bool &priority_flag_out, bool empty_string_stream = true);

// Static variables
private:
    static std::list<DebugStringStacker*> container_of_p2all_stackers;
public:
    static void getAllStackedDebugStrings(std::string &str_in, bool &priority_flag_out, bool empty_string_streams = true, int  stacker_channel_in = 0);
    static std::string getAllStackedDebugStrings( bool &priority_flag_out, bool empty_string_streams = true, int  stacker_channel_in = 0);
};

#endif // DEBUGSTRINGSTACKER_H
