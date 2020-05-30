//
//  FileManager.hpp
//  PROJECT Calendar v3
//
//  Created by Dennis Dimitrov on 18.05.20.
//  Copyright © 2020 Dennis Dimitrov. All rights reserved.
//

#ifndef FileManager_hpp
#define FileManager_hpp

//#include <stdio.h>

//#include"Calendar.cpp"
//#include<fstream>
#include"Calendar.hpp"

///Class File Manager
///
///Links the data of a calendar with the data in a file
class FileManager{
    
    char* fileName; //This is the name and path for the working file
    int len;
    Calendar calendar; //Object of type calendar whith which the file will work
    
    
    void Copyfrom(const FileManager& other);
    void Free();
public:
    
    FileManager(const char* name,const Calendar& c);
    FileManager(const FileManager& other);
    FileManager& operator=(const FileManager& other);
    ~FileManager();
    
    void SetFileName(const char* name); //sets the name of the working file
    
    void read(); //opens the file, reads from it and initialises the calendar
    void write(); //saves the current calendar in the file
    void writeTo(const char* other); //saves the current calendar in a file with the given name and path
    
};

#endif /* FileManager_hpp */
