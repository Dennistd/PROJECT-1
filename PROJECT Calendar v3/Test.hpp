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

///Клас който приема информация от потребилтеля  (потребителски интерфейс)
///
///  Работи с потребителски вход от конзолата или с потребителски файл
/// Отговаря за изпълнението на командите свързани с календара или с файла
class Test{
    char* command; //потребителска команда
    int len;
    
    Calendar c; //обект от тип календар
    
    void CopyFrom(const Test& other);
    void Free();
    
public:
    void SetCommand(const char* command);
    
    Test(const Calendar& calendar,const char* command);
    Test(const Test& other);
    Test& operator=(const Test& other);
    ~Test();
    
    void Command(); //изпълнява подадена команда за календара
    void FileCommand(); //изпълнява подадена команда за файла
    
};

#endif /* Test_hpp */
