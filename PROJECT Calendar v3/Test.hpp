//
//  Test.hpp
//  PROJECT Calendar v3
//
//  Created by Dennis Dimitrov on 18.05.20.
//  Copyright © 2020 Dennis Dimitrov. All rights reserved.
//


#ifndef Test_hpp
#define Test_hpp

#include <stdio.h>
//#include "FileManager.cpp"
#include "FileManager.hpp"
const int LENGTH=1024;
const int COMMAND_MAX_SIZE=30;

///Class which accepta command from the user via console (user interface)
///
///  Works with a file given by the user and its input
/// Applies the given command to the calendar
class Test{
    char* command; //user command
    size_t len;
    
    Calendar c;
    
    void CopyFrom(const Test& other);
    void Free();
    
public:
    void SetCommand(const char* command);
    
    Test(const Calendar& calendar,const char* command);
    Test(const Test& other);
    Test& operator=(const Test& other);
    ~Test();
    
    void Command(); //does the given command for the calendar
    void FileCommand(); //does the given command for the file
    
};

#endif /* Test_hpp */
