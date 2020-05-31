//
//  Time.hpp
//  PROJECT Calendar v3
//
//  Created by Dennis Dimitrov on 15.05.20.
//  Copyright © 2020 Dennis Dimitrov. All rights reserved.
//

#ifndef Time_hpp
#define Time_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>

/// Class for time
///
/// In format hh:mm:ss

class Time {
    int hours;
    int minutes;
    int seconds;
    
public:
    /// Constructor with parameters
    ///
    /// that sets the default values
    Time(int hours=0,int minutes=0,int seconds=0);
    
    
    void SetHours(int);
    void SetMinutes(int);
    void SetSeconds(int);
    
   
    int GetHours()const;
    int GetMinutes()const;
    int GetSeconds()const;
    
    ///Prints the time in a formated way
    void printTime()const;
    
    ///operators for working with files
    friend std::istream& operator>>(std::istream& is,Time& time);
    friend std::ostream& operator<<(std::ostream& os,const Time& time);
    
    Time& operator-=(const Time& other);
    Time& operator+=(const Time& other);
    
    ///Operators for comparing times
    friend bool operator==(const Time& lhs,const Time& rhs);
    friend bool operator>(const Time& lhs,const Time& rhs);
    friend bool operator<(const Time& lhs,const Time& rhs);
    
    ///Operators for addition and subtraction
    friend Time&  operator-(const Time& lhs,const Time& rhs);
    friend Time&  operator+(const Time& lhs,const Time& rhs);
    
};

Time timeInit(); //initialises an objest from the console
 bool operator>=(const Time& lhs,const Time& rhs);
 bool operator<=(const Time& lhs,const Time& rhs);
#endif /* Time_hpp */
