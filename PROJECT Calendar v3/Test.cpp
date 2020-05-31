//
//  Test.cpp
//  PROJECT Calendar v3
//
//  Created by Dennis Dimitrov on 18.05.20.
//  Copyright © 2020 Dennis Dimitrov. All rights reserved.
//

#include "Test.hpp"

void Test:: CopyFrom(const Test& other){
    this->c=other.c;
    SetCommand(other.command);
}
void Test:: Free(){
    delete[] command;
}




Test:: Test(const Test& other){
    CopyFrom(other);
}
Test& Test:: operator=(const Test& other){
    if(this != &other){
        Free();
        CopyFrom(other);
    }
    return *this;
}
Test:: ~Test(){
    Free();
}



void Test:: SetCommand(const char* command){
    this->len=strlen(command);
    this->command=new char[len+1];
    strcpy(this->command,command);
}

Test:: Test(const Calendar& calendar,const char* command){
    SetCommand(command);
    this->c=calendar; //we have an operayor =
}

void Test:: Command(){
    
    
    
    if(strcmp(command,"book")==0){
        
        std::cout<<"Enter your date: "<<std::endl;
        
        int year;
        int month;
        int day;
        std::cin>>year;
        std::cin>>month;
        std::cin>>day;
        
        std::cout<<"Enter a name for the meeting "<<std::endl;
        char name[LENGTH];
        std::cin>>name;
        
        std::cout<<"Enter a note for the meeting  "<<std::endl;
        
        char note[LENGTH];
        std::cin>>note;
        
        std::cout<<"Enter the start of your meeting "<<std::endl;
        Time start=timeInit();
        
        std::cout<<"Enter the end of your meeting "<<std::endl;
        Time end=timeInit();
        
        
        int index= c.GetDateIndex(year, month, day);
        if (index !=-1){
            c.at(index).addMeeting(name, note, start, end);
        }
        
        
        if(c.at(index).addMeeting(name, note, start, end)){
            std::cout<<"Succesfully added!"<<std::endl;
        }
        else{
            std::cout<<"Error couldn't add"<<std::endl;
        }
    }
    
    
    else if(strcmp(command,"unbook")==0){
        
        std::cout<<"Enter your date: "<<std::endl;
        
        int year;
        int month;
        int day;
        std::cin>>year;
        std::cin>>month;
        std::cin>>day;
        
        std::cout<<"Enter the start of the meeting that's to be removed "<<std::endl;
        Time start=timeInit();
        
        std::cout<<"Enter the end of your meeting that's to be removed"<<std::endl;
        Time end=timeInit();
        
        int index= c.GetDateIndex(year, month, day);
        
        if(index!=-1){
            Date date=c.at(index);
            c.unbook(date, start, end);
        }
        else{
            std::cout<<"Error while unbooking!"<<std::endl;
        }
    }
    
    else if(strcmp(command,"agenda")==0){
        
        std::cout<<"Enter your date: "<<std::endl;
        
        int year;
        int month;
        int day;
        std::cin>>year;
        std::cin>>month;
        std::cin>>day;
        
        int index=c.GetDateIndex(year, month, day);
        Date date =c.at(index);
        
        c.agenda(date);
        //also fix this cuz it is a mess
    }
    
    else if(strcmp(command,"change")==0){
        
        std::cout<<"Enter your date: "<<std::endl;
        
        int year;
        int month;
        int day;
        std::cin>>year;
        std::cin>>month;
        std::cin>>day;
        
        int index=c.GetDateIndex(year, month, day);
        //if != -1
        Date date =c.at(index);
        
        std::cout<<"Enter the startting time"<<std::endl;
        Time start= timeInit();
        
        char option[COMMAND_MAX_SIZE];
        
        
        if(strcmp(option,"date")==0){
            std::cout<<"Enter your new date"<<std::endl;
            
            int year;
            int month;
            int day;
            std::cin>>year;
            std::cin>>month;
            std::cin>>day;
            
            Date newdate(year,month,day,false);
            //look into it
            c.changeDate(date, start, newdate);
        }
        
        else if(strcmp(option,"starttime")==0){
            std::cout<<"Enter your new start time"<<std::endl;
            Time newstart=timeInit();
            c.changeStart(date, start, newstart);
            //chek if correct
        }
        
        else if(strcmp(option,"endtime")==0){
            std::cout<<"Enter your new end time"<<std::endl;
            Time newend=timeInit();
            c.changeFinish(date, start, newend);
        }
        
        else if(strcmp(option,"name")==0){
            
            std::cout<<"Enter a new name: "<<std::endl;
            char newName[LENGTH];
            
            c.changeName(date, start, newName);
        }
        
        else if(strcmp(option,"note")==0){
            
            std::cout<<"Enter a new note: "<<std::endl;
            char newNote[LENGTH];
            std::cin>>newNote;
            
            c.changeName(date, start, newNote);
            
        }
        else{
            std::cout<<"Enter a falid option for change!"<<std::endl;
        }
    }
    
    else if(strcmp(command,"find")==0){
        char pattern[LENGTH];
        
        std::cout<<"Enter a pattern to be found "<<std::endl;
        std::cin>>pattern;
        
        c.find(pattern);
    }
    
    else if(strcmp(command,"holiday")==0){
        std::cout<<"Enter a holiday date"<<std::endl;
        int year;
        int month;
        int day;
        std::cin>>year;
        std::cin>>month;
        std::cin>>day;
        int index= c.GetDateIndex(year, month, day);
        c.at(index).makeHoliday();
        
    }
    
    else if(strcmp(command,"busydays")==0){
        std::cout<<"Enter a starting date"<<std::endl;
        int yearS;
        int monthS;
        int dayS;
        std::cin>>yearS;
        std::cin>>monthS;
        std::cin>>dayS;
        
        std::cout<<"Enter a ending date"<<std::endl;
              int yearE;
              int monthE;
              int dayE;
              std::cin>>yearE;
              std::cin>>monthE;
              std::cin>>dayE;
        
        Date start(yearS,monthS,dayS,false);
        Date end(yearE,monthE,dayE,false);
        c.busydays(start, end);
    }
    else if(strcmp(command,"findslot")==0){
        std::cout<<"Enter a starting date"<<std::endl;
               int year;
               int month;
               int day;
               std::cin>>year;
               std::cin>>month;
               std::cin>>day;
        Date date(year,month,day,false);
        
        std::cout<<"Enter the lenth of your meeting"<<std::endl;
        Time dur=timeInit();
        c.findslot(date, dur);
    }
    else if(strcmp(command,"findslotwith")==0){
        std::cout<<"Enter the name of your file and its path: "<<std::endl;
        char fileName[LENGTH];
        std::cin>>fileName;
        
        Calendar newC;
        FileManager f(fileName,newC);
        f.read();
        
        std::cout<<"Enter a starting date"<<std::endl;
                 int year;
                 int month;
                 int day;
                 std::cin>>year;
                 std::cin>>month;
                 std::cin>>day;
          Date date(year,month,day,false);
          
          std::cout<<"Enter the lenth of your meeting"<<std::endl;
          Time dur=timeInit();
        
        c.findslotwith(date, dur, newC);
        
    }
    else if(strcmp(command,"merge")==0){
        std::cout<<"Enter the name of your file and its path: "<<std::endl;
               char fileName[LENGTH];
               std::cin>>fileName;
               
               Calendar newC;
               FileManager f(fileName,newC);
               f.read();
        
        c.merge(newC);
    }
    else{
        std::cout<<"Error! Enter a valid command for this calendar!"<<std::endl;
    }
}

void Test:: FileCommand(){
    
    char fileName[LENGTH];
    std::cout<<"Enter the file name and its path: "<<std::endl;
    std::cin>>fileName;
    
    FileManager f(fileName,this->c);
    
    
    
    while (strcmp(this->command ,"exit")!=0){
        if(strcmp(command,"open")==0){
            f.read();
            
            
            char innerCommand[COMMAND_MAX_SIZE];
            std::cin>>innerCommand;
            
           
            SetCommand(innerCommand);
            while((strcmp(innerCommand, "save")==0)&&(strcmp(innerCommand, "saveas")==0)&&(strcmp(innerCommand, "close")==0)){
                
                Command();
                std::cin>>innerCommand;
            }
        }
        
        else if(strcmp(command,"close")==0){
            this->c=Calendar();
        }
        
        else if(strcmp(command,"save")==0){
            
            
            f.write();
        }
        
        else if(strcmp(command,"saveas")==0){
            char fileName[LENGTH];
            std::cout<<"Enter the file name and its path: "<<std::endl;
            std::cin>>fileName;
            f.writeTo(fileName);
        }
        else if(strcmp(command,"help")==0){
            std::cout<<"The following commands are supported:"<<std::endl;
            std::cout<<"open <file>    opens <file> "<<std::endl;
            std::cout<<"close            closes currently opened file "<<std::endl;
            std::cout<<"save            saves the currently open file "<<std::endl;
            std::cout<<"saveas <file>    saves the currently open file in <file> "<<std::endl;
            std::cout<<"help            prints this information "<<std::endl;
            
        }
        
        if(strcmp(command,"exit")==0){
            std::cout<<"Exiting program... "<<std::endl;
            return;
        }
        else{
            std::cout<<"Error! Enter a valid commad: "<<std::endl;
        }
        std::cin>>command;
        SetCommand(command);
    }
}

