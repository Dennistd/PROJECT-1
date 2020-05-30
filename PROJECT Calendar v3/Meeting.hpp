//
//  Meeting.hpp
//  PROJECT Calendar v3
//
//  Created by Dennis Dimitrov on 15.05.20.
//  Copyright © 2020 Dennis Dimitrov. All rights reserved.
//


#ifndef Meeting_hpp
#define Meeting_hpp

#include <stdio.h>
//#include "Time.cpp"
#include "Time.hpp"
#endif /* Meeting_hpp */

/// Клас за среща
///
///Дневният ни календар ще работи със тези събития
class Meeting{
    
    char* name; //Име на срещата
    int lenName;
    
    char* note; //Коментар към срещата
    int lenNote;
    
    Time start; //назално време
    Time finish;//крайно време
    
    
    void Free();
    void CopyFrom(const Meeting& other);
    
public:
    
    Meeting(); //Конструктор по подразбиране
    Meeting(const char* name,const char* note,const Time& start,const Time& finish); //конструктор с параметри обекти от тип Време
    Meeting(const char* name,const char* note,int StartHours,int StartMinutes,int StartSeconds,int FinishHours,int FinishMinutes,int FinishSeconds); // конструктор с основни типове
    Meeting(const Meeting& other);
    Meeting& operator=(const Meeting& other);
    ~Meeting();
    
    ///  Селектори
    const char* GetName()const;
    const char* GetNote()const;
    const Time& GetStart()const;
    const Time& GetFinish()const;
    const Time& GetDuration()const; //Функция за намиране продължителността на срещата
    
    ///Мутатори
    void SetName(const char* name);
    void SetNote(const char* note);
    void SetStart(const Time& start);
    void SetFinish(const Time& end);
    
    bool IsValid(); //проверява дали срещата е валидна
    Time& GetDur()const;
    bool hasConflict(const Meeting& other); //Проверява дали часът на дадената среща не се пресича с друга
    
    
    void printMeeting()const; //Функция за отпечатане на Среща върху конзолата
    
    /// Оператори за работа на срещата с файл
    friend std::ostream& operator<<(std::ostream& os,const Meeting& meet);
    friend std::istream& operator>>(std::ostream& is, Meeting& meet);
    ///Оператор, който проверява дали срещите са идентични
    friend bool operator==(const Meeting& lhs,const Meeting& rhs);
};

void swapMeet(Meeting& a,Meeting& b);
