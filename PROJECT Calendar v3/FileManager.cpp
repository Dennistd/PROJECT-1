//
//  FileManager.cpp
//  PROJECT Calendar v3
//
//  Created by Dennis Dimitrov on 18.05.20.
//  Copyright © 2020 Dennis Dimitrov. All rights reserved.
//

#include "FileManager.hpp"

void FileManager:: Copyfrom(const FileManager& other){
    SetFileName(other.fileName);
    calendar=other.calendar;
}
void FileManager:: Free(){
    delete [] fileName;
}



FileManager:: FileManager(const FileManager& other){
    Copyfrom(other);
}
FileManager& FileManager:: operator=(const FileManager& other){
    if(this != &other){
        Free();
        Copyfrom(other);
    }
    return *this;
}
FileManager:: ~FileManager(){
    Free();
}


void FileManager:: SetFileName(const char* name){
    this->len=strlen(name);
    this->fileName=new char[len+1];
    strcpy(fileName,name);
}

FileManager:: FileManager(const char* name,const Calendar& c){
    SetFileName(name);
    this->calendar=c;
}

void FileManager:: read(){
    
    std::ifstream iFile(fileName, std::ios::in);
    
    if(iFile.fail()){
        std::cout<<"Error while opening this file"<<std::endl;
        return;
    }
    
    Calendar buffer;
    iFile>>buffer;
    this->calendar=buffer;
    
}
void FileManager:: write(){
    
    std::ofstream oFile(fileName, std::ios::out );
    
    if(oFile.fail()){
        std::cout<<"Error while opening this file"<<std::endl;
        return;
    }
    
    oFile<<this->calendar;
}

void FileManager:: writeTo(const char* otherName){
    std::ofstream other(otherName);
    other<<this->calendar;
}
