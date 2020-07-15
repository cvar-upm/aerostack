//////////////////////////////////////////////////////
//  code_tests.cpp
//
//  Created on: Dec 11, 2013
//      Author: jespestana
//
//  Last modification on: Dec 11, 2013
//      Author: jespestana
//
//////////////////////////////////////////////////////

#include <iostream>
//#include <math.h>
//#include <cstdlib>
//#include <unistd.h>

#include "dronelogfileswritter.h"

#include <list>
#include <iostream>
#include <vector>

#include "debugstringstacker.h"
#include "stringstacker.h"

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/stat.h>
#include <fstream>
#include <string.h>

#include <list>

class Box
{
    // http://stackoverflow.com/questions/16501419/creating-a-class-with-a-static-member-container-holding-all-instances-of-said-cl
private:
    std::list <Box*>::iterator iter;
public:
    static std::list <Box*> List;
    Box() {
        List.push_front(this);
        iter = List.begin();
        std::cout << "Constructing box." << std::endl;
    }
    ~Box() {
        std::cout << "Trashing box." << std::endl;
        List.erase(iter);
    }
    void lookInside() {
        std::cout << "It's empty." << std::endl;
    };

    // JVC: added next two overloads:
    Box &operator=(Box const &src) {
        // don't assign anything.
        return *this;
    }
    Box(Box const &other) {
        List.push_front(this);
        iter = List.begin();
        std::cout << "Copy constructing box.\n";
    }
};

std::list <Box*> Box::List;

void my_handler(int s){
           printf("Caught signal %d\n",s);
           exit(1);

}

int main(int argc,char **argv) {
//        std::string stack_location_str(std::getenv("DRONE_STACK"));
//        stack_location_str += "/";
//        std::cout << "Your DRONE_STACK is located in: " << stack_location_str << std::endl;
//        DroneLogfilesWritter drone_logfile_writter(stack_location_str);
//        drone_logfile_writter.writeString2Logfile("Hola\nAdios\n"); // this works

    /* Prueba iteradores*/ {
//        {
//            Box Box_1;
//            Box Box_2;
//            {
//                Box Box_3;

//                Box_3 = Box_1; // No longer causes problem!

//                for (auto iter : Box::List) {
//                    iter->lookInside();
//                }
//                std::cout << "The list contains " << Box::List.size() << " boxes." << std::endl;
//            }

//            for (auto iter : Box::List) {
//                iter->lookInside();
//            }
//            std::cout << "The list contains " << Box::List.size() << " boxes." << std::endl;
//        }

//        for (auto iter : Box::List) {
//            iter->lookInside();
//        }
//        std::cout << "The list contains " << Box::List.size() << " boxes." << std::endl;

//        std::vector<int> v(10);
//        std::vector<int>::iterator it = v.begin() + 5;
//        std::insert_iterator<std::vector<int> > it_ins(v, it);

//        for (unsigned n = 20; n > 0; --n)
//            *it_ins++ = rand();
    }

    /* PRUEBA DebugStringStacker */
    {
//        std::string all_my_debug_strings;
//        bool priority_flag = false;
//        {
//            DebugStringStacker debug_string_stacker1;
//            all_my_debug_strings = DebugStringStacker::getAllStackedDebugStrings( priority_flag, false);
//            std::cout << "PRUEBA DebugStringStacker" << std::endl;
//            std::cout << all_my_debug_strings << "priority_flag:" << priority_flag << std::endl << std::endl;
//        }
//        DebugStringStacker debug_string_stacker2(1);
//        DebugStringStacker debug_string_stacker3;

//        {
//            DebugStringStacker debug_string_stacker4;
//            DebugStringStacker debug_string_stacker5;

//            //    debug_string_stacker1 << "prueba 1" << std::endl;
//            debug_string_stacker2 << "prueba 2, important data" << std::endl; debug_string_stacker2.setPriorityFlag();
//            debug_string_stacker3 << "prueba 3" << std::endl;
//            debug_string_stacker4 << "prueba 4" << std::endl;
//            debug_string_stacker5 << "prueba 5" << std::endl;

//            all_my_debug_strings = DebugStringStacker::getAllStackedDebugStrings( priority_flag, false);
//            std::cout << "PRUEBA DebugStringStacker" << std::endl;
//            std::cout << all_my_debug_strings << "priority_flag:" << priority_flag << std::endl << std::endl;

//            //    debug_string_stacker1 << "end prueba 1" << std::endl;
//            debug_string_stacker2 << "end prueba 2" << std::endl;
//            debug_string_stacker3 << "end prueba 3" << std::endl;
//            debug_string_stacker4 << "end prueba 4, important data" << std::endl; debug_string_stacker4.setPriorityFlag();
//            debug_string_stacker5 << "end prueba 5" << std::endl;
//            all_my_debug_strings = DebugStringStacker::getAllStackedDebugStrings( priority_flag, false);
//            std::cout << "PRUEBA DebugStringStacker" << std::endl;
//            std::cout << all_my_debug_strings << "priority_flag:" << priority_flag << std::endl << std::endl;
//        }

//        all_my_debug_strings = DebugStringStacker::getAllStackedDebugStrings(priority_flag);
//        std::cout << "PRUEBA DebugStringStacker" << std::endl;
//        std::cout << all_my_debug_strings << "priority_flag:" << priority_flag << std::endl << std::endl;

//        all_my_debug_strings = DebugStringStacker::getAllStackedDebugStrings(priority_flag, true, 1);
//        std::cout << "PRUEBA DebugStringStacker" << std::endl;
//        std::cout << all_my_debug_strings << "priority_flag:" << priority_flag << std::endl << std::endl;
    }

    /* PRUEBA ¿...? */ {
    StringStacker string_stacker;
    string_stacker << std::string("Esto es una prueba") << std::endl;
    string_stacker << std::string("Esto es una prueba otra vez") << std::endl;

    std::cout << string_stacker.getStackedString();

    string_stacker << std::string("Esto es una prueba 2") << std::endl;
    string_stacker << std::string("Esto es una prueba otra vez 2") << std::endl;

    std::cout << string_stacker.getStackedString();

    string_stacker << std::string("Esto es una prueba") << std::endl;
    string_stacker << std::string("Esto es una prueba otra vez") << std::endl;
    string_stacker << std::string("Esto es una prueba 2") << std::endl;
    string_stacker << std::string("Esto es una prueba otra vez 2") << std::endl;
    std::string line;
    for (int i=0; i<4; i++) {
        std::cout << std::string("Inside while loop") << std::endl;
        std::getline( string_stacker, line, '\n');
        std::cout << line << std::endl;
    }

    string_stacker << std::string("Esto es una prueba") << std::endl;
    string_stacker << std::string("Esto es una prueba otra vez") << std::endl;
    string_stacker << std::string("Esto es una prueba 2") << std::endl;
    string_stacker << std::string("Esto es una prueba otra vez 2") << std::endl;
    for (int i=0; i<4; i++) {
        std::cout << std::string("Inside while loop") << std::endl;
        std::getline( string_stacker, line, '\n');
        std::cout << line << std::endl;
    }

//    std::cout << "Using Boost "
//              << BOOST_VERSION / 100000     << "."  // major version
//              << BOOST_VERSION / 100 % 1000 << "."  // minior version
//              << BOOST_VERSION % 100                // patch level
//              << std::endl;

//    struct sigaction sigIntHandler;

//    sigIntHandler.sa_handler = my_handler;
//    sigemptyset(&sigIntHandler.sa_mask);
//    sigIntHandler.sa_flags = 0;

//    sigaction(SIGINT, &sigIntHandler, NULL);

//    pause();
    }

    /* PRUEBA substitute boost is_directory, time_t, and ofstream */ {
//        // http://stackoverflow.com/questions/3512434/using-struct-stat
//        struct stat st;
//        if(stat("/home/jespestana/no_existo",&st) == 0)
//            printf(" /home/jespestana/no_existo is present\n");
//        else
//            printf(" /home/jespestana/no_existo is NOT present\n");

//        if(stat("/tmp",&st) == 0)
//            printf(" /tmp is present\n");
//        else
//            printf(" /tmp is NOT present\n");

//        if(cvg_is_directory("/home/jespestana/no_existo"))
//            printf(" /home/jespestana/no_existo is present\n");
//        else
//            printf(" /home/jespestana/no_existo is NOT present\n");

//        if (cvg_is_directory("/tmp"))
//            printf(" /tmp is present\n");
//        else
//            printf(" /tmp is NOT present\n");

////        std::cout << "cvg_create_directory(\"/home/jespestana/no_existo\"):" << cvg_create_directory("/home/jespestana/no_existo") << std::endl;

//        time_t rawtime;
//        struct tm * timeinfo;
//        char data_buffer [30];
//        char time_buffer [30];

//        time (&rawtime);
//        timeinfo = localtime(&rawtime);

//        // date_y2014m03d21
//        // time_11:35:47.428712
//        strftime ( data_buffer, 30, "date_y%Ym%md%d", timeinfo);
//        strftime ( time_buffer, 30, "time_%H:%M:%S", timeinfo);
//        std::cout << data_buffer << std::endl;
//        std::cout << time_buffer << std::endl;

//        //
//        std::ofstream ofs;
//        ofs.open("/home/jespestana/no_existo/test.txt", std::ofstream::out);
//        ofs << "lorem ipsum" << std::endl;
//        ofs << "lorem ipsum" << std::endl;
//        ofs << "lorem ipsum" << std::endl;
//        ofs << "lorem ipsum" << std::endl;
//        ofs.close();
    }

    /* Pruebas atoi */ {
//        int idDrone = 2;
//        std::cout << std::string("/home/jespestana/")+"configs/drone"+ itoa(idDrone) +"/drone_logger_config.xml" << std::endl;
    }

    /* std::vector of string initializer list */{
       std::string input_parameter = "trajectory_controller_config:state_machine:checkpoint_clearance_radius";
       char str[1024];
       strcpy(str, input_parameter.c_str());
       char * pch; char *saveptr;
       printf ("Splitting string \"%s\" into tokens:\n",str);
       std::vector<std::string> result_str_vector;
       pch = strtok_r( str, ":", &saveptr);
       while (pch != NULL)
       {
         std::cout << pch << std::endl;
         result_str_vector.push_back(pch);
         pch = strtok_r( NULL,":", &saveptr);
       }
       for ( std::vector<std::string>::iterator it = result_str_vector.begin(); it != result_str_vector.end(); ++it) {
           std::cout << (*it) << std::endl;
       }
    }

    {
        int ctrl = int(0b1010);

        std::cout << "ctrl & 0b1000:" << (bool)(ctrl & 0b1000) << std::endl;
        std::cout << "ctrl & 0b0100:" << (bool)(ctrl & 0b0100) << std::endl;
        std::cout << "ctrl & 0b0010:" << (bool)(ctrl & 0b0010) << std::endl;
        std::cout << "ctrl & 0b0001:" << (bool)(ctrl & 0b0001) << std::endl;
    }

    {
        std::list<int> my_list;
        for (int i=0; i<10; i++)
            my_list.push_back(i);

        {
            std::list<int>::iterator it = my_list.begin();
            int n = 5;
            for (int i=0; i<n; i++)
                it++;
            std::cout << "my_list[" << n <<"]=" << (*it) << std::endl;
            {
            std::list<int>::iterator it2 = it;
            it2++;
            my_list.erase(it);
            it = it2;
            }
            std::cout << "my_list[" << n+1 <<"]=" << (*it) << std::endl;
            for (;it != my_list.end(); it++)
                std::cout << "my_list[i]=" << (*it) << std::endl;
        }

        for (std::list<int>::iterator it = my_list.begin(); it != my_list.end(); it++)
            std::cout << "my_list[i]=" << (*it) << std::endl;
    }
    return 0;
}
