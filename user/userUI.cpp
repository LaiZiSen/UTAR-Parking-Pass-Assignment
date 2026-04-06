#include <iostream>
#include <ctime> //for time function
#include <string>
#include <sstream>
#include "../header/txtDB.h"
#include "../header/txtPath.h"

using namespace std;

int getCurrYearMonth();
int getCurrDate();

int main(){
    fstream userFile(USER_FILE, ios::in);
    
    if (!userFile.is_open()) {
        cout<<"Error: file is at "<<USER_FILE<<endl;
        return 1;
    }

    bool valid = true;

    while(valid){
        string username, pwd;

        cout<<"Username: "<<endl;
        cin>>username;
        cout<<"Password: "<<endl;
        cin>>pwd;
        
        user tempUser;
        int lineNum = 0;
        RESULT result;

        result = getUser(userFile, tempUser, lineNum);
        if (result == VALID_RECORD){
            //start finding username and psw
            if (trim(tempUser.name)==username && trim(tempUser.pwd)==pwd){
                cout<<"Login successful!";
            } else {
                cout<<"Invalid username or password"<<endl;

                char tryAgain;
                cout<<"Enter 'y' if you want to try again."<<endl;
                cin>>tryAgain;
                if(tryAgain != 'y' && tryAgain != 'Y'){
                    valid = false;
                }
            }
        }else{
            cout<<"Invalid record OR no match found"<<endl;
            break;
        }
    }
}

//function to track time now
int getCurrYearMonth(){
    time_t rawtime; 
    time(&rawtime); 
    struct tm* timeinfo; 
    timeinfo = localtime(&rawtime); 

    int yearNow = timeinfo->tm_year + 1900; 
    int monthNow = timeinfo->tm_mon + 1; 

    int resultInYearMonth = yearNow * 100 + monthNow;

    //separate year and month
    int year = resultInYearMonth/100;
    int month = resultInYearMonth%100;

    //handle overflow
    while (month>12){
        month -= 12;
        year ++;
    }
    
    while (month<1){
        month += 12;
        year --;
    }

    return year * 100 + month;
}

int getCurrDate(){
    time_t rawtime;
    time(&rawtime);
    struct tm* timeinfo;
    timeinfo = localtime(&rawtime);

    return timeinfo -> tm_mday;
}