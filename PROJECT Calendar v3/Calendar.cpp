//
//  Calendar.cpp
//  PROJECT Calendar v3
//
//  Created by Dennis Dimitrov on 15.05.20.
//  Copyright © 2020 Dennis Dimitrov. All rights reserved.
//

#include "Calendar.hpp"

void Calendar:: CopyFrom(const Calendar& other){
    this->size=other.size;
    this->capacity=other.capacity;
    
    this->calendar=new Date[other.capacity];
    for(int i=0;i<other.size;i++){
        calendar[i]=other.calendar[i];
    }
}
void Calendar:: Free(){
    size=capacity=0;
    delete[] calendar;
}
void Calendar::resize(){
    Date* temp=new Date[capacity*2];
    for(int i=0;i<size;i++){
        temp[i]=calendar[i];
    }
    delete[] calendar;
    calendar=temp;
}
void Calendar:: sortByDate()const{
    for(int i=0;i<size-1;i++){
        if(calendar[i]>calendar[i+1]){
            swapDate(calendar[i],calendar[i+1]);
        }
    }
}



int Calendar:: getIndex(const Date& date)const{
    for(int i=0;i<size;i++){
        if(calendar[i]==date)
            return i;
    }
    return -1;
}
int Calendar:: GetDateIndex(const Date& date)const{ //we don't actally need this function its just an additio 
    return getIndex(date);
}

int Calendar::GetDateIndex(int year,int month,int day){
    for(int i=0;i<size;i++){
        if(calendar[i].GetYear()==year && calendar[i].GetMonth()==month && calendar[i].GetDay()==day){
            return i;
        }
    }
    return -1;
}

Date Calendar:: at(int index)const{
    if(index>=0&&index<size){
        return calendar[index];
    }
    return Date();
}
Date& Calendar:: at(int index){
    return calendar[index];
}

Calendar:: Calendar(){
    size=0;
    capacity=8;
    calendar=new Date[capacity];
}
Calendar::Calendar(const Calendar& other){
    CopyFrom(other);
}
Calendar& Calendar:: operator=(const Calendar& other){
    if(this != &other){
        Free();
        CopyFrom(other);
    }
    return *this;
}
Calendar:: ~Calendar(){
    Free();
}

int Calendar:: GetSize()const{
    return size;
}

void Calendar:: book(const Date& date,const Meeting& meet){
    int index=getIndex(date);
    if(date.GetIsWorkday()&&index!=-1){
        calendar[index].addMeeting(meet);
    }
    
}
void Calendar:: addDate(int year,int month,int day, bool workday){
    if(size==capacity){
        resize();
    }
    
    Date dateToAdd(year,month,day,workday);
    calendar[size]=dateToAdd;
    size++;
    
}


void Calendar:: unbook(const Date& date,const Time& start,const Time& finish){
    int index=getIndex(date);
    
    if(index==-1)
        calendar[index].removeMeeting(start,finish);
}
void Calendar:: agenda(const Date& date){
    int index=getIndex(date);
    
    if(index != -1){
        calendar[index].sortByTime();
        calendar[index].printDate();
    }
}
void Calendar:: changeStart(Date& date, Time& start,const Time& newstart){
    int indexDate=getIndex(date);
    calendar[indexDate].GetMeeting(start).SetStart(newstart); //fix
}
void Calendar:: changeDate(Date& date, Time& start,const Date& newdate){
    int indexDate=getIndex(date);
    Meeting meet=calendar[indexDate].GetMeeting(start);
    calendar[indexDate].removeMeeting(meet.GetStart(), meet.GetFinish());
    
    int newDateIndex=getIndex(newdate);
    calendar[newDateIndex].addMeeting(meet);
}
void Calendar:: changeFinish(Date& date, Time& start,const Time& newEnd){
    int indexDate=getIndex(date);
    calendar[indexDate].GetMeeting(start).SetFinish(newEnd);
}
void Calendar:: changeName(Date& date, Time& start,const char* newName){
    int indexdate=getIndex(date);
    calendar[indexdate].GetMeeting(start).SetName(newName);
}
void Calendar:: changeNote(Date& date, Time& start,const char* newNote){
    int indexdate=getIndex(date);
    calendar[indexdate].GetMeeting(start).SetNote(newNote);
}

bool Calendar:: find(const char* ptr){
    for(int i=0;i<size;i++){
        if(calendar[i].searchFor(ptr)){
            calendar[i].printDate();
            return true;
        }
    }
    return false;
}

void Calendar:: busydays(const Date& from,const Date& to){ //TODO test
    sortByDate();
    int start=getIndex(from);
    int end=GetDateIndex(to);
    int helpersize=end-start;
    Date* helper= new Date[helpersize];
    for(int i=start;i<end;i++){
        helper[i]=calendar[i];
    }
    
    helper->sortByBusyness();
    for(int i=0;i<helpersize;i++){
        if(helper[i].GetIsWorkday()){
            helper[i].printDate();
        }
    }
    delete[] helper;
}

Date Calendar:: findslot(const Date& date,const Time& duration)const{
    int index=getIndex(date);
    for(int i=index;i<size;i++){
        if(calendar[i].hasSpace(duration))
            return calendar[i];
    }
    return Date();
}


Date Calendar:: findslotwith(const Date& date,const Time& duration,const Calendar& other)const{ //maybe not here
    
    if(findslot(date,duration)==other.findslot(date,duration)){
        return findslot(date,duration);
    }
    return Date();
}

void Calendar:: merge (const Calendar& other){
    
    sortByDate();
    other.sortByDate();
    
    for(int i=0;i<other.GetSize();i++){
        if(calendar[i]==other.at(i)){
            
            for(int j=0;j<other.at(i).GetSize();j++){
                if(!at(i).GetMeetingAt(j).hasConflict(other.at(i).GetMeetingAt(j))){
                    at(i).addMeeting(other.at(i).GetMeetingAt(j));
                }
                std::cout<<"Chose which meeting to be kept or replaced: "<<std::endl;
                
                Meeting problemCal=at(i).GetMeetingAt(j);
                Meeting problemOther=other.at(i).GetMeetingAt(j);
                char command[10];
                std::cin>>command;
                
                if(strcmp(command,"keep")==0){
                    other.at(i).removeMeeting(problemOther);
                    
                    std::cout<<"Enter new date and new time for the meeting: "<<std::endl;
                    
                    int newYear;
                    std::cin>>newYear;
                    int newMonth;
                    std::cin>>newMonth;
                    int newDay;
                    std::cin>>newDay;
                    
                    Time newStart=timeInit();
                    Time duration= problemOther.GetDuration();
                    Time newFinish= newStart+duration;
                    
                    Meeting newMeeting=problemOther;
                    newMeeting.SetStart(newStart);
                    newMeeting.SetFinish(newFinish);
                    
                    //int index = other.GetDateIndex(newYear,newMonth,newDay);
                    Date newdate(newYear,newMonth,newDay,false);
                    
                    int index= other.getIndex(newdate);
                    
                    other.at(index).addMeeting(newMeeting);
                    
                    at(i).addMeeting(problemOther);
                    
                }
                
                if(strcmp(command,"replace")==0){
                    at(i).removeMeeting(problemCal);
                    
                    std::cout<<"Enter new date and new time for the meeting: "<<std::endl;
                    
                    int newYear;
                    std::cin>>newYear;
                    int newMonth;
                    std::cin>>newMonth;
                    int newDay;
                    std::cin>>newDay;
                    
                    Time newStart=timeInit();
                    Time duration=problemCal.GetDuration();
                    Time newFinish= newStart+duration;
                    
                    Meeting newMeeting=problemCal;
                    newMeeting.SetStart(newStart);
                    newMeeting.SetFinish(newFinish);
                    
                    int index=GetDateIndex(newYear,newMonth,newDay);
                    
                    at(index).addMeeting(newMeeting);
                    other.at(i).addMeeting(problemCal);
                }
                
                std::cout<<"Enter a valid command"<<std::endl;
            }
        }
    }
}

Date Calendar:: PopBack(){
    Date el=calendar[size-1];
    
    if(size){
        size--;
    }
    else{
        std::cout<<"It's empty"<<std::endl;
    }
    
    return el;
    
}

void Calendar:: addDate( Date& date){
    if(size==capacity){
        resize();
    }
    
    calendar[size++]=date;
}

void Calendar:: InssrtAt(int index, Date& date){
    addDate(date);
    
    if(index>=size)
        return;
    
    for(int i=size-1;i>index;i--){
        swapDate(calendar[i],calendar[i-1]);
    }
}
void Calendar:: RemoveAt(int index){
    
    if(index>=size||size==1){
        PopBack();
        return;
    }
    for(int i=index;i<size;i++){
        swapDate(calendar[i],calendar[i+1]);
        PopBack();
    }
    
}

std::ostream& operator<<(std::ostream& os,Calendar& c){
    Calendar copy=c;
    int size=c.GetSize();
    os<< size<<std::endl;
    for(int i=0;i<size;i++){
        os<<copy.PopBack()<<std::endl;
    }
    return os;
}
std::istream& operator>>(std::istream& is,Calendar& c){
    int size;
    is>>size;
    Date date;
    for(int i=0;i<size;i++){
        is>>date;
        c.addDate(date);
    }
    return is;
}



void Calendar:: print()const{
    std::cout<<"CALENDAR INFORMATION:" <<std::endl;
    for(int i=0;i<GetSize();i++){
        calendar[i].PrintDaily();
    }
}
