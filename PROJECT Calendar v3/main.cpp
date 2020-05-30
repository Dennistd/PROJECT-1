//
//  main.cpp
//  PROJECT Calendar v3
//
//  Created by Dennis Dimitrov on 15.05.20.
//  Copyright © 2020 Dennis Dimitrov. All rights reserved.
//

#include <iostream>
#include "Test.hpp"
int main(int argc, const char * argv[]) {
    Calendar personalCal;
    
    std::cout<<"Enter a command for your file manager: "<<std::endl;
    char command[30];
    std::cin>>command;
    
    Date today(2020,3,13,true);
    Date tomorrow(2020,6,12);
    
    Meeting work("Working","Hard",9,30,0,14,30,0);
    tomorrow.addMeeting(work);
    today.addMeeting("Finish the project", "It is due today", 23, 0, 0, 0, 0, 0);
    personalCal.addDate(today);
    personalCal.addDate(tomorrow);

    FileManager f("Output.txt",personalCal);
   
    f.write();
//    
//    Calendar otherCal;
//    FileManager g("Input.txt",otherCal);
//    g.read();
    Date date(2020,12,25,true);
    date.addMeeting("Breakfast", "Eggs for breakfast", 7, 0, 0, 8, 30, 0);
    std::cout<<date.GetYear()<<':'<<date.GetMonth()<<':'<<date.GetDay()<<std::endl;
    if(date.GetIsWorkday()){
        std::cout << "Schedule for today: ";
        for(int i=0;i<date.GetSize();i++){
            std::cout << date.GetMeetingAt(i)<<' ';
        }
    }
    std::cout<<std::endl;

    Test t1(personalCal,command);

    t1.FileCommand();
    
//    while(true){
//        Time t;
//        Meeting m;
//        Date d;
//        d.addMeeting(m);
//        Calendar c;
//        c.addDate(d);
//        FileManager f("name", c);
//        Test ts(c,"command");
//    }
    
    return 0;
}
