//
//  Meeting.cpp
//  PROJECT Calendar v3
//
//  Created by Dennis Dimitrov on 15.05.20.
//  Copyright © 2020 Dennis Dimitrov. All rights reserved.
//

#include "Meeting.hpp"

void Meeting:: Free(){
    delete[] name;
    delete[] note;
}
void Meeting:: CopyFrom(const Meeting& other){
    this->SetName(other.name);
    // this->lenName=strlen(other.name);
    this->SetNote(other.note);
    // this->lenNote=strlen(other.note);
    this->SetStart(other.start);
    this->SetFinish(other.finish);
}
Meeting:: Meeting() :start(),finish(){
    const char* def="Unknown";
    lenNote=strlen(def);
    lenNote=strlen(def);
    SetName(def);
    SetNote(def);
    
    //IsInit=false;
}
Meeting:: Meeting(const char* name,const char* note,const Time& start,const Time& finish){
    if(IsValid()){
        this->lenName=strlen(name);
        this->SetName(name);
        this->lenNote=strlen(note);
        this->SetNote(note);
        this->SetStart(start);
        this->SetFinish(finish);
        
        //IsInit=true;
    }
    this->lenName=strlen(name);
    this->SetName(name);
    this->lenNote=strlen(note);
    this->SetNote(note);
    
    this->start=this->finish;
    
}
Meeting:: Meeting(const char* name,const char* note,int StartHours,int StartMinutes,int StartSeconds,int FinishHours,int FinishMinutes,int FinishSeconds):
start(StartHours,StartMinutes,StartSeconds),finish(FinishHours,FinishMinutes,FinishSeconds){
    if(IsValid()){
        this->lenName=strlen(name);
        this->lenNote=strlen(note);
        this->SetName(name);
        this->SetNote(note);
        
    }
    this->lenName=strlen(name);
    this->lenNote=strlen(note);
    this->SetName(name);
    this->SetNote(note);
    
}
Meeting:: Meeting(const Meeting& other){
    CopyFrom(other);
}
Meeting& Meeting:: operator=(const Meeting& other){
    if(this!=&other){
        Free();
        CopyFrom(other);
    }
    return *this;
}
Meeting::~Meeting(){
    Free();
}

const char* Meeting:: GetName()const{
    return this->name;
}
const char* Meeting:: GetNote()const{
    return this->note;
}
const Time& Meeting:: GetStart()const{
    return this->start;
}
const Time& Meeting:: GetFinish()const{
    return this->finish;
}


bool  Meeting:: IsValid(){
    return finish>start;
}
void Meeting:: SetName(const char* name){
    this->lenName=strlen(name);
    this->name=new char[lenName+1];
    strcpy(this->name,name);
}
void Meeting:: SetNote(const char* note){
    this->lenNote=strlen(note);
    this->note= new char[lenNote+1];
    strcpy(this->note,note);
    
}
void Meeting:: SetStart(const Time& start){
    if(start <= this->finish){
        this->start=start;
    }
    else{
        std::cout<<"Enter a valid start time, before the end"<<std::endl;
    }
}
void Meeting:: SetFinish(const Time& end){
    if(finish>=this->start){
        this->finish=end;
    }
    else{
        std::cout<<"Enter a valid end time, after the start"<<std::endl;
    }
}

void Meeting:: printMeeting()const{
    std::cout<<"Name: "<<name<<std::endl;
    
    std::cout<<"Start: ";
    std::cout<< start;
    std::cout<<" End: ";
    std::cout<<finish;
    std::cout<<"Notes: ";
    std::cout<<note;
    std::cout<<std::endl;
}
void swapMeet(Meeting& a,Meeting& b){
    Meeting temp=a;
    a=b;
    b=temp;
}
Time& Meeting:: GetDur()const{
    return GetStart()-GetFinish();
}

bool operator==(const Meeting& lhs,const Meeting& rhs){
    return (strcmp(lhs.GetName(),rhs.GetName())==0)&&(strcmp(lhs.GetNote(),rhs.GetNote())==0)&&lhs.GetStart()==rhs.GetStart()&&lhs.GetFinish()==rhs.GetFinish();
}


std::istream& operator>>(std::istream& is,Meeting& meet){
    //fix
    
    Time newStart;
    Time newFinish;
    
    is>>newStart;
    meet.SetStart(newStart);
    is>>newFinish;
    meet.SetFinish(newFinish);
    
    char buffName[1024];
    char buffNote[1024];
    is>>buffName;
    is>>buffNote;
    
    meet.SetNote(buffNote);
    meet.SetName(buffName);
    
    
    return is;
}

std::ostream& operator<<(std::ostream& os,const Meeting& meet){
    return os <<' '<< meet.GetName()<<' '<<meet.GetNote()<<' '<<meet.GetStart()<<' '<<meet.GetFinish()<<std::endl;
}

bool Meeting:: hasConflict(const Meeting& other){
    return !(this->GetStart()>=other.GetFinish()) || (this->GetFinish()<=other.GetStart());
}


const Time& Meeting:: GetDuration()const{
    return GetFinish()-GetStart();
}

