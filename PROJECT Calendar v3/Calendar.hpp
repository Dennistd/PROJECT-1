//
//  Calendar.hpp
//  PROJECT Calendar v3
//
//  Created by Dennis Dimitrov on 15.05.20.
//  Copyright © 2020 Dennis Dimitrov. All rights reserved.
//


#ifndef Calendar_hpp
#define Calendar_hpp

//#include <stdio.h>
//#include "Date.cpp"
#include "Date.hpp"

/// Основния ни клас каледндар
///
/// представлява масив от дати
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
    
    Calendar();
    Calendar(const Calendar& other);
    Calendar& operator=(const Calendar& calendar);
    ~Calendar();
    
    void InssrtAt(int index, Date& date);
    void RemoveAt(int index);
    
    int GetDateIndex(const Date& date); //намира индекс по дадена дата
    int GetDateIndex(int year,int month,int day);
    Date at(int index)const; //дата на позиция
    int GetSize()const; //намира размера
    
    
    void addDate(int,int,int, bool); //добавя дата към календара
    void addDate(Date& date);
    Date PopBack(); //връща дата на последна позиция
    
    void book(const Date& date,const Meeting& meet); //добавя нова среща към датата
    void unbook(const Date& date,const Time& start,const Time& finish); //премахва срещата по дадени часове
    void agenda(const Date& date); // печата хронологичен списък
    
    /// Променя избран компонент от среща
    void changeStart(Date& date, Time& start,const Time& newstart);
    void changeDate(Date& date, Time& start,const Date& newdate);
    void changeFinish(Date& date, Time& start,const Time& newEnd);
    void changeName(Date& date, Time& start,const char* newName);
    void changeNote(Date& date, Time& start,const char* newNote);
    
    
    bool find(const char* ptr); //търси подниз
   // void holiday(const Date& date);
        
    
    void busydays(const Date& from,const Date& to); 
    Date findslot(const Date& date,const Time& duration)const; //намира свободно място за среща
  
    Date findslotwith(const Date& date,const Time& duration,const Calendar& other)const;
    
    
    void merge (const Calendar& other);
   // void rearrange(Meeting& lhs,Meeting& rhs);
    
    friend std::ostream& operator<<(std::ostream& os,Calendar& c);
    friend std::istream& operator>>(std::istream& is,Calendar& c);
};
#endif /* Calendar_hpp */
