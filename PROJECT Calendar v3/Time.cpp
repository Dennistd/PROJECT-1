//
//  Time.cpp
//  PROJECT Calendar v3
//
//  Created by Dennis Dimitrov on 15.05.20.
//  Copyright © 2020 Dennis Dimitrov. All rights reserved.
//

#include "Time.hpp"


void Time:: SetHours(int hours){
    if(hours>=0 && hours<=23){
        this->hours=hours;
    }
    else{
        std::cout<<"Enter valid hours"<<std::endl;
    }
}
void Time:: SetMinutes(int minutes){
    if(minutes>=0 && minutes<=59){
        this->minutes=minutes;
    }
    else{
           std::cout<<"Enter valid minutes"<<std::endl;
       }
}
void Time:: SetSeconds(int seconds){
    if(seconds>=0 && seconds<=59){
        this->seconds=seconds;
    }
    else{
           std::cout<<"Enter valid seconds"<<std::endl;
       }
}
Time:: Time(int hours,int minutes,int seconds){
    this->SetHours(hours);
    this->SetMinutes(minutes);
    this->SetSeconds(seconds);
}

int Time::GetHours()const{
    return hours;
}
int Time::GetMinutes()const{
    return minutes;
}
int Time::GetSeconds()const{
    return seconds;
}


bool operator< (const Time& lhs,const Time& rhs){
    
    
    if(lhs.GetHours()<rhs.GetHours()){
        return true;
    }
    else if(lhs.GetHours()==rhs.GetHours()){
        
        if(lhs.GetMinutes()<rhs.GetMinutes()){
             return true;
        }
           
        
        else if(lhs.GetMinutes()==rhs.GetMinutes()){
            
            if(lhs.GetSeconds()<rhs.GetSeconds())
                return true;
        }
    }
    return false;
    
}


bool operator> (const Time& lhs,const Time& rhs){
    if(lhs.GetHours()>rhs.GetHours())
        return true;
    else if(lhs.GetHours()==rhs.GetHours()){
        
        if(lhs.GetMinutes()>rhs.GetMinutes())
            return true;
        
        else if(lhs.GetMinutes()==rhs.GetMinutes()){
            
            if(lhs.GetSeconds()>rhs.GetSeconds())
                return true;
        }
    }
    return false;
}

Time& Time:: operator-=(const Time& other){
    
    
    if(this->seconds < other.seconds){
        --this->minutes;
        this->seconds += 60;
    }
    
    this->seconds -= other.seconds;
    
    if(this->minutes < other.minutes){
        --this->hours;
        this->minutes += 60;
    }
    
    this->minutes -= other.minutes;
    this->hours -= other.hours;
    
    return *this;
}
Time&  operator-(const Time& lhs,const Time& rhs){
    Time copy(lhs);
   return  copy-=rhs;
}

Time& Time:: operator+=(const Time& other){
    
    this->seconds += other.seconds;
    this->minutes +=other.minutes;
    this->hours=other.hours;
    if (seconds >= 60){
        minutes += seconds/60;
        seconds %= 60;
        if (minutes >=60){
            hours = (hours + minutes/60) % 24;
            minutes %= 60;
        }
    }
    return *this;
}


Time& operator+(const Time& lhs,const Time& rhs){
    Time copy(lhs);
   return  copy+=rhs;
    
}
bool operator==(const Time& lhs,const Time& rhs){
    return lhs.GetHours()==rhs.GetHours()&& lhs.GetMinutes()==rhs.GetMinutes()&& lhs.GetSeconds()==rhs.GetSeconds();
}
bool operator>=(const Time& lhs,const Time& rhs){
    return lhs>rhs || lhs==rhs;
}
bool operator<=(const Time& lhs,const Time& rhs){
    return lhs<lhs || lhs==rhs;
}
std::istream& operator>>(std::istream& is,Time& time){
    int newHours;
    int newMinutes;
    int newSeconds;
    is>>newHours;
    time.SetHours(newHours);
    is>>newMinutes;
    time.SetMinutes(newMinutes);
    is>>newSeconds;
    time.SetSeconds(newSeconds);
    return is;
}
std::ostream& operator<<(std::ostream& os,const Time& time){
    os<<time.GetHours()<<" ";
    os<<time.GetMinutes()<<" ";
    os<<time.GetSeconds()<<std::endl;
    return os;
}

void Time:: printTime()const{
    if(hours<10){
        std::cout<<0<<hours<<":";
    }
    std::cout<<hours<<":";
    
    if(minutes<10){
        std::cout<<0<<minutes<<":";
    }
    std::cout<<minutes<<":";
    
    if(seconds<10){
        std::cout<<0<<seconds<<std::endl;
    }
    std::cout<<seconds<<std::endl;
    
}

///Function for initialising time from the console
Time timeInit(){
    int hours;
    std::cin>>hours;
    int minutes;
    std::cin>>minutes;
    int seconds;
    std::cin>>seconds;
    Time res(hours,minutes,seconds);
    return res;
}


