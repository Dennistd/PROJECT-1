//
//  Date.hpp
//  PROJECT Calendar v3
//
//  Created by Dennis Dimitrov on 15.05.20.
//  Copyright © 2020 Dennis Dimitrov. All rights reserved.
//


#ifndef Date_hpp
#define Date_hpp

#include <stdio.h>
#include "Meeting.hpp"
const int DEFAULT_SIZE=8;

///Class for daily obligations
///
///Describes the date in yyyy:mm:dd format and its supporting meetings

class Date{
    
    int year;
    int month;
    int day;
    
    
    bool IsWorkday; //describes if it is a workday, and can support meetings
    
   ///array of meetings which the given date carries
    Meeting* schedule;
    int size; //it is described by its size which is the currend number of meetings
    int capacity; //and the maximum number whish it can carry
    
    void CopyFrom(const Date& other);
    void Free();
    
    void Resize(); //function that doubles the capacity
    
    ///functions to find an index
    int getMeetingIndex(const Time& start,const Time& end);
    int getMeetingIndex(int startHours, int startMin, int startSec, int endHours, int endMin, int endSec);
    int  getMeetingIndex(const Meeting& meet);

    bool IsLeapYear();
    
    
public:
    Date();
    Date(int,int,int,bool);
    Date(int,int,int);
    
    
    Date(const Date& other);
    Date& operator=(const Date& other);
    ~Date();
    
    void makeHoliday(); //the date is set to not be a workday
    
   
    void SetYear(int year);
    void SetMonth(int month);
    void SetDay(int day);
    void SetDate(int, int, int);
    
 
    int GetYear()const;
    int GetMonth()const;
    int GetDay()const;
    bool GetIsWorkday()const;
    int GetSize()const;
    Meeting GetMeetingAt(int index)const; //returns the meeting on a given position
    Meeting PopBack(); //returns the meeting on the last position

    ///Functions for adding a new meeting to the array
    bool addMeeting(const char* name,const char* note, int startHours, int startMin, int startSec, int endHours, int endMin, int endSec);
    bool addMeeting(const char* name,const char* note, Time start,Time end);
    bool addMeeting(const Meeting& meeting);
    
    ///Functions for removing a meeting from the daily array
    void removeMeeting(Time start,Time end);
    void removeMeeting(int startHours, int startMin, int startSec, int endHours, int endMin, int endSec);
    void removeMeeting(const Meeting& meet);
    
    //sort the array by its start time
    void sortByTime();
    
    
    Meeting GetMeeting(const Time& start); //finds the meeting with given start time
    bool Isvalid()const;
    
    bool IsFree(const Time& start);
    bool searchFor(const char* ptr); //looks for a substring in the name or describtion
    Time& busyness(); //find the bussyness, in the form of a sum
    bool hasSpace(const Time& needed);
    bool hasConflict(Date& other);
 
    

    void sortByBusyness(); //sort by bussyness
    void printDate()const; //fix 0s
    void PrintDaily()const;
    
    ///Operator for comparison
    friend bool operator>(const Date& lhs,const Date& rhs);
    friend bool operator<(const Date& lhs,const Date& rhs);
    friend bool operator==(const Date& lhs,const Date& rhs);
    ///Operators for working with a file
    friend std::ostream& operator<<(std::ostream& os,const Date& date);
    friend std::istream& operator>>(std::istream& is,Date& date);
    
    
};
void swapDate(Date&,Date&);
#endif /* Date_hpp */
