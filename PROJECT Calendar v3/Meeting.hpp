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
#include "Time.hpp"

/// Class for meeting
///
///The daily calendar will be working with these meetings
class Meeting{
    
    char* name; //The name of the meeting
    size_t lenName;
    
    char* note; //Additional information about the meeting
    size_t lenNote;
    
    ///The period in which the meeting will take place
    Time start;
    Time finish;
    
    
    void Free();
    void CopyFrom(const Meeting& other);
    
public:
    
    Meeting();
    Meeting(const char* name,const char* note,const Time& start,const Time& finish);
    Meeting(const char* name,const char* note,int StartHours,int StartMinutes,int StartSeconds,int FinishHours,int FinishMinutes,int FinishSeconds); 
    Meeting(const Meeting& other);
    Meeting& operator=(const Meeting& other);
    ~Meeting();
    

    const char* GetName()const;
    const char* GetNote()const;
    const Time& GetStart()const;
    const Time& GetFinish()const;
    const Time& GetDuration()const; //finds how long the meeting will continue
    

    void SetName(const char* name);
    void SetNote(const char* note);
    void SetStart(const Time& start);
    void SetFinish(const Time& end);
    void SetPeriod(const Time& start,const Time& end);
    
    bool IsValid(); //checks if the end is not before the start of the meeting
    bool hasConflict(const Meeting& other); //checks if the period of the given meeting does not cross with another one
    
    
    void printMeeting()const; //Prints the meeting with additional stylisation
    
    /// Operators for working with a file
    friend std::ostream& operator<<(std::ostream& os,const Meeting& meet);
    friend std::istream& operator>>(std::ostream& is, Meeting& meet);
    ///Operator which checks if the meetings are identical
    friend bool operator==(const Meeting& lhs,const Meeting& rhs);
};

void swapMeet(Meeting& a,Meeting& b);

#endif /* Meeting_hpp */
