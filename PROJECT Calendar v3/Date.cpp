//
//  Date.cpp
//  PROJECT Calendar v3
//
//  Created by Dennis Dimitrov on 15.05.20.
//  Copyright © 2020 Dennis Dimitrov. All rights reserved.
//

#include "Date.hpp"

void Date::CopyFrom(const Date& other){
    SetYear(other.year);
    SetMonth(other.month);
    SetDay(other.day);
       
    this->IsWorkday=other.IsWorkday;
       
    this->size=other.size;
    this->capacity=other.capacity;
    schedule=new Meeting[other.capacity];
    for(int i=0;i<other.size;i++){
        
        schedule[i]=other.schedule[i];
    }
       
       
}
void Date:: Free(){

    delete [] this->schedule;
}

void Date:: Resize(){
    Meeting* temp=new Meeting[capacity*=2];
    for(int i=0;i<size;i++){
        temp[i]=schedule[i];
    }
    delete[] schedule;
    schedule=temp;
    
}
void Date::SetMonth(int month){
    if(month>=1&&month<=12){
        this->month=month;
    }
    else{
        std::cout<<"Enter a valid month number"<<std::endl;
    }
}
bool Date:: IsLeapYear(){
    if(year%4==0){
        if(year%100==0){
            if(year%400==0){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return true;
        }
    }
    return false;
}
void Date::SetDay(int day){
    if(this->month==4 || this->month==6 || this->month==9 ||this->month==11){
        if(day>=1 && day<=30){
            this->day=day;
           }
        else{
            throw "This month does not have 31 days";
        }
    }

   else if(month==2){
        if(IsLeapYear()){
            if(day>=1&&day<=29){
                this->day=day;
            }
        }
        if(day>=1&&day<=28){
            this->day=day;
        }
        std::cout<<"Invalid date for February"<<std::endl;
    }
   else{
       if(day>=1 && day<=31){
           this->day=day;
       }
       else{
           throw "Invalid day";
       }
   }
}
void Date:: SetYear(int year){
    if(year>=1970){
        this->year=year;
    }
    else{
    std::cout<<"Enter a valid year"<<std::endl;
    }
}

int Date::  GetYear()const{
    return this->year;
}
int Date::GetMonth()const{
    return this->month;
}
int Date::GetDay()const{
    return this->day;
}


Date::Date(){
    SetYear(1970);
    
    SetMonth(1);
    SetDay(1);
    size=0;
    capacity=DEFAULT_SIZE;
    schedule=new Meeting[capacity];
}
Date::Date(int year,int month,int day,bool IsWorkday){
    
    SetDay(day);
           SetMonth(month);
           SetYear(year);
    this->IsWorkday=IsWorkday;
    
    if(IsWorkday){
        
        
    size=0;
    capacity=DEFAULT_SIZE;
        this->schedule=new Meeting[capacity];
    }
    else{
        size=capacity=0;
        this->schedule=nullptr;
    }
    
}

Date:: Date(int year ,int month,int day){
    SetYear(year);
    SetMonth(month);
    SetDay(day);
    this->IsWorkday=true;
    
    size=0;
    capacity=DEFAULT_SIZE;
    schedule=new Meeting[capacity];
    
}
Date::Date(const Date& other){
    CopyFrom(other);
}
Date& Date:: operator=(const Date& other){
    if(this != &other){
        Free();
        CopyFrom(other);
    }
    return *this;
}
Date::~Date(){
    Free();
}
bool Date:: GetIsWorkday()const{
    return this->IsWorkday;
}

void Date:: makeHoliday(){
    IsWorkday=false;
    delete[]schedule;
    schedule=nullptr;
}



Meeting Date:: GetMeetingAt(int index)const{
    if(index>=0&&index<size){
        return schedule[index];
    }
    return Meeting();
}

int Date:: GetSize()const{
    return size;
}

int Date:: getMeetingIndex(const Time& start,const Time& end){
    for(int i=0;i<size;i++){
        if(schedule[i].GetStart()==start&&schedule[i].GetFinish()==end)
            return i;
    }
    return -1;
}

int Date:: getMeetingIndex(const Meeting& meet){
    
    for(int i=0;i<GetSize();i++){
        if(schedule[i]==meet){
            return i;
        }
    }
    return -1;
}

int Date:: getMeetingIndex(int startHours, int startMin, int startSec, int endHours, int endMin, int endSec){
    Time start(startHours,startMin,startSec);
    Time finish(endHours,endMin,endSec);
    return getMeetingIndex(start, finish);
}

void Date:: sortByTime(){
    for(int i=0;i<size;i++){
        if(schedule[i].GetStart()<schedule[i+1].GetStart())
            swapMeet(schedule[i],schedule[i+1]);
    }
}

void Date:: sortByBusyness(){
    for(int i=0;i<size;i++){
        if(schedule[i].GetDur()<schedule[i+1].GetDur())
            swapMeet(schedule[i],schedule[i+1]);
    }
}

Meeting Date:: PopBack(){
    
    if(size){
        size--;
    }
    
    return schedule[size];
}


bool Date:: addMeeting(const Meeting& meeting){
    for(int i=0;i<size;i++){
    
        if(schedule[i].hasConflict(meeting)){
            throw "You can't add this meeting because its time conflicts with the time of another!";
            
        }
        
    }
    
    if(IsWorkday){
       this->schedule[size]=meeting;
        this->size++;
        return true;
    }
    return false;
}

bool Date:: addMeeting(const char* name,const char* note, int startHours, int startMin, int startSec, int endHours, int endMin, int endSec){
    
    Meeting meet(name,note,startHours,startMin,startSec,endHours,endMin,endSec);
    addMeeting(meet);
    
    return addMeeting(meet);
}
bool Date:: addMeeting(const char* name,const char* note, Time start,Time end){
    Meeting meet(name,note,start,end);
    addMeeting(meet);
    return  addMeeting(meet);
}




void Date:: removeMeeting(Time start,Time end){
    int index=getMeetingIndex(start, end);
    
    if(index>=size||size==1){
        PopBack();
        return ;
    }
    for(int i=index;i<size-1;i++){
        swapMeet(schedule[i], schedule[i+1]);
        PopBack();
    }
    PopBack();
}

void Date:: removeMeeting(const Meeting& meet){
    int index=getMeetingIndex(meet);
    
    if(index>=size||size==1){
        PopBack();
        return ;
    }
    for(int i=index;i<size-1;i++){
        swapMeet(schedule[i], schedule[i+1]);
        PopBack();
    }
    PopBack();
}

void swapDate(Date& a,Date& b){ //разменя дадените дати
    Date temp=a;
    a=b;
    b=temp;
}

 Meeting Date:: GetMeeting(const Time& start){
     for(int i=0;i<size;i++){
         if(schedule[i].GetStart()==start){
             return schedule[i];
         }
     }
     return Meeting();
 }


void Date:: SetDate(int year, int month, int day){
    SetDay(day);
    SetMonth(month);
    SetYear(year);
}


bool contains(const char* str,const char* ptr){ //проверява дали е подниз
    
    return strstr(str,ptr) != nullptr;
}

bool Date:: searchFor(const char* ptr){
    for(int i=0;i<size;i++){
        if(contains(schedule[i].GetName(),ptr)||contains(schedule[i].GetNote(),ptr)){
            schedule[i].printMeeting();
            return true;
        }
    }
     return false;
}

bool Date:: hasSpace(const Time& needed){
    sortByTime();
    for(int i=0;i<size;i++){
        if(GetIsWorkday()&&((schedule[i+1].GetStart()-schedule[i].GetFinish())>=needed||(needed+Time(8,0,0)<=schedule[0].GetStart())||(schedule[size-1].GetFinish()+needed<Time(17,0,0)))){
            return true;
        }
    }
    return false;
}

//int Date:: ConflictIndex(const Meeting& other){
//    for(int i=0;i<size;i++){
//        if(schedule[i].hasConflict(other)){
//            return i;
//        }
//    }
//    return -1;
//}

//void Date:: mergeSchedules(const Date& other){
//    for(int i=0;i<other.GetSize();i++){
//        if((ConflictIndex(other.GetMeetingAt(i))==-1)&&GetIsWorkday()){
//             addMeeting(other.GetMeetingAt(i));
//        }
//        // else do something else
//        //rearrange
//        //int conf=ConflictIndex(other.GetMeetingAt(i));
//    }
//}

void Date:: printDate()const{

    std::cout<<GetYear()<<" : ";
    if(GetMonth()<10){
        std::cout<<0<<GetMonth()<<" : ";
    }
    else{
    std::cout<<month<<" : ";
    }
    if(GetDay()<10){
           std::cout<<0<<GetDay();
       }
    else{
        std::cout<<GetDay();
    }
    std::cout<<std::endl;
}
void Date:: PrintDaily()const{
    printDate();
    if(GetIsWorkday()){
        for(int i=0;i<GetSize();i++){
            schedule[i].printMeeting();
        }
    }
}
bool operator>(const Date& lhs,const Date& rhs){
    if(lhs.GetYear()>rhs.GetYear())
           return true;
       else if(lhs.GetYear()==rhs.GetYear()){
           
           if(lhs.GetMonth()>rhs.GetMonth())
               return true;
           else if(lhs.GetMonth()==rhs.GetMonth()){
               
               if(lhs.GetDay()>rhs.GetDay())
                   return true;
           }
       }
       return false;
}
bool operator<(const Date& lhs,const Date& rhs){
    if(lhs.GetYear()<rhs.GetYear())
        return true;
    else if(lhs.GetYear()==rhs.GetYear()){
        
        if(lhs.GetMonth()<rhs.GetMonth())
            return true;
        else if(lhs.GetMonth()==rhs.GetMonth()){
            
            if(lhs.GetDay()<rhs.GetDay())
                return true;
        }
    }
    return false;
    
}


bool operator==(const Date& lhs,const Date& rhs){
    return lhs.GetYear()==rhs.GetYear() && lhs.GetMonth()==rhs.GetMonth() && lhs.GetDay()==rhs.GetDay();
}

std::ostream& operator<<(std::ostream& os,const Date& date){
    os<<date.GetYear()<<':'<<date.GetMonth()<<':'<<date.GetDay()<<std::endl;
    if(date.GetIsWorkday()){
        os << "Schedule for today: ";
        for(int i=0;i<date.GetSize();i++){
            os << date.GetMeetingAt(i)<<' ';
        }
    }
    os<<std::endl;
    return os;
}
std::istream& operator>>(std::istream& is,Date& date){
    int newYear;
    int newMonth;
    int newDay;
    is>>newYear;
    date.SetYear(newYear);
    is>>newMonth;
    date.SetMonth(newMonth);
    is>>newDay;
    date.SetDay(newDay);
    if(date.GetIsWorkday()){
        for(int i=0;i<date.GetSize();i++){
            char name[1024];
            is>>name;
            char note[1024];
            is>>note;
            Time start;
            is>>start;
            Time end;
            is>>end;
            date.addMeeting(name, note, start, end);
        }
    }
    return is;
   
}



