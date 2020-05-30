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

///Клас отговарящ за работа с файлове
///
///Той представялява връзката ни с фаила и се грижи единствено за него, без да се интересъва от информацията 
class FileManager{
    
    char* fileName; //Пазим името на файла
    int len;
    Calendar calendar; //Обект от тип клас с който да боравим
    
    
    void Copyfrom(const FileManager& other);
    void Free();
public:
    
    FileManager(const char* name,const Calendar& c);
    FileManager(const FileManager& other);
    FileManager& operator=(const FileManager& other);
    ~FileManager();
    
    void SetFileName(const char* name); //задава името на работния файл
    
    void read(); //отваря файла и чете от него, като инициализира календара
    void write(); //записва настоящия календар във файла
    void writeTo(const char* other); //записва настоящия календар във файл със зададено име
    
};

#endif /* FileManager_hpp */
