//
//  main.cpp
//  PROJECT Calendar v3
//
//  Created by Dennis Dimitrov on 15.05.20.
//  Copyright © 2020 Dennis Dimitrov. All rights reserved.
//

#include <iostream>
#include "Test.hpp"
int main() {
    Calendar personalCal;
    
    std::cout<<"Enter a command for your file manager: "<<std::endl;
    char command[COMMAND_MAX_SIZE];
    std::cin>>command;
    
    Test UserTest(personalCal,command);
    
    return 0;
}
