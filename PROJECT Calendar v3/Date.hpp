//
//  Date.hpp
//  PROJECT Calendar v3
//
//  Created by Dennis Dimitrov on 15.05.20.
//  Copyright © 2020 Dennis Dimitrov. All rights reserved.
//


#ifndef Date_hpp
#define Date_hpp

//#include <stdio.h>
//#include "Meeting.cpp"
#include "Meeting.hpp"
const int DEFAULT_SIZE=8;

///Клас за днесвна заетосе
///
///Описва дата, съпровождащите я събития, ако е работна

class Date{
    ///Член данни във формата (годинна : месец : ден)
    int year;
    int month;
    int day;
    
    
    bool IsWorkday; //променлива която отразява дали датата е работна
    
    //масив от срещите на датата
    Meeting* schedule;
    int size; //описват го размер и капацитет
    int capacity;
    
    void CopyFrom(const Date& other);
    void Free();
    
    void Resize(); //Функция за разширение на масива от срещи
    
    //Връща индекса на срещата в масива
    int getMeetingIndex(const Time& start,const Time& end);
    int getMeetingIndex(int startHours, int startMin, int startSec, int endHours, int endMin, int endSec);
    int  getMeetingIndex(const Meeting& meet);

    bool IsLeapYear(); //прверява дали годината е високосна
    
    
public:
    Date(); //коструктор по подразбиране
    Date(int,int,int,bool); //конструктор с бълева променлива
    Date(int,int,int);
    
    
    Date(const Date& other);
    Date& operator=(const Date& other);
    ~Date();
    
    void makeHoliday(); //Датата се обяввява за неработна
    
    // Мутатори за промяна на датата
    void SetYear(int year);
    void SetMonth(int month);
    void SetDay(int day);
    void SetDate(int, int, int);
    
    //Селектори
    int GetYear()const;
    int GetMonth()const;
    int GetDay()const;
    bool GetIsWorkday()const;
    int GetSize()const;
    Meeting GetMeetingAt(int index)const; //връща стещата на дадена позиция
    
    Meeting PopBack(); //връща срещата на последна позиция

    ///Функции за добавяне на срещи, приемащи параметри от различен тип
    bool addMeeting(const char* name,const char* note, int startHours, int startMin, int startSec, int endHours, int endMin, int endSec);
    bool addMeeting(const char* name,const char* note, Time start,Time end);
    bool addMeeting(const Meeting& meeting);
    
    ///Функции за премахване на среща
    void removeMeeting(Time start,Time end);
    void removeMeeting(int startHours, int startMin, int startSec, int endHours, int endMin, int endSec);
    void removeMeeting(const Meeting& meet);
    
    //сортировка на масива от срещи по време
    void sortByTime();
    
    
    Meeting GetMeeting(const Time& start); //намира среща с опеределено начално време
    bool Isvalid()const;
    
    bool IsFree(const Time& start);
    bool searchFor(const char* ptr); //Търси низ в описанието или името на срещите
    Time& busyness(); //намира натовареността, като сбор от работни часове
    bool hasSpace(const Time& needed);
    bool hasConflict(Date& other);
 
    

    void sortByBusyness(); //сортировака по натовареност
    void printDate()const; //fix 0s
    
    ///Оператори за сравнение
    friend bool operator>(const Date& lhs,const Date& rhs);
    friend bool operator<(const Date& lhs,const Date& rhs);
    friend bool operator==(const Date& lhs,const Date& rhs);
    //Оператори за работа на дата с файл
    friend std::ostream& operator<<(std::ostream& os,const Date& date);
    friend std::istream& operator>>(std::istream& is,Date& date);
    
    
};
void swapDate(Date&,Date&);
#endif /* Date_hpp */
