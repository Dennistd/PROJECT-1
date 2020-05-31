//
//  Calendar.hpp
//  PROJECT Calendar v3
//
//  Created by Dennis Dimitrov on 15.05.20.
//  Copyright © 2020 Dennis Dimitrov. All rights reserved.
//


#ifndef Calendar_hpp
#define Calendar_hpp

#include <stdio.h>
#include "Date.hpp"

/// The calendar manager
///
/// in the form of an array of dates
class Calendar{
    Date* calendar;
    int size;
    int capacity;
    
    void CopyFrom(const Calendar& other);
    void Free();
    void resize();
    void sortByDate()const;
    void sortByBusyness();
    int getIndex(const Date& date)const;
    
public:
    
    //BIG 4
    Calendar();
    Calendar(const Calendar& other);
    Calendar& operator=(const Calendar& calendar);
    ~Calendar();
    
    void InssrtAt(int index, Date& date);
    void RemoveAt(int index);
    
    int GetDateIndex(const Date& date)const; //returns the index of a given date
    int GetDateIndex(int year,int month,int day);
    Date at(int index)const; //date on the given position
    Date& at(int index);
    int GetSize()const;
    
    
    void addDate(int,int,int, bool); //adds a date to the calendar
    void addDate(Date& date);
    Date PopBack(); //returns the date on last position
    
    void book(const Date& date,const Meeting& meet); //adds a new meeting to the given date if it is possible
    void unbook(const Date& date,const Time& start,const Time& finish); //removes the meeting with the given period
    void agenda(const Date& date); // prints a list in chronological order
    
    /// Chenges a different component of the meeting on a given date
    void changeStart(Date& date, Time& start,const Time& newstart);
    void changeDate(Date& date, Time& start,const Date& newdate);
    void changeFinish(Date& date, Time& start,const Time& newEnd);
    void changeName(Date& date, Time& start,const char* newName);
    void changeNote(Date& date, Time& start,const char* newNote);
    
    
    bool find(const char* ptr); //looks for a substring

        
    
    void busydays(const Date& from,const Date& to); 
    Date findslot(const Date& date,const Time& duration)const; //finds a free space for a meeting with given duration
  
    Date findslotwith(const Date& date,const Time& duration,const Calendar& other)const;
    
    
    void merge (const Calendar& other);

    
    friend std::ostream& operator<<(std::ostream& os,Calendar& c);
    friend std::istream& operator>>(std::istream& is,Calendar& c);
    
    void print()const;// for testing
};
#endif /* Calendar_hpp */
