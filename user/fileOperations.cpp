#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include "../include/txtPath.h"
#include "../include/txtDB.h"

//1. function to remove spaces in txt data
string trim(const string& input){
    //find first not space position
    size_t startPos = input.find_first_not_of(' ');
    if (startPos == string::npos){
        return "";
    }
    //find text end 
    size_t endPos = input.find_last_not_of(' ');

    //extract text (start with startPos, length)
    return input.substr(startPos, endPos-startPos+1);
}

//2. function to track time now
int getCurrYearMonth(){
    time_t rawtime; //variable to store raw time
    time(&rawtime); //get current time from system

    struct tm* timeinfo; //convert to YYYMMDD format
    timeinfo = localtime(&rawtime); //convert to localtime

    int yearNow = timeinfo->tm_year + 1900;  // tm_year counts from 1900
    int monthNow = timeinfo->tm_mon + 1;     // tm_mon is 0-11 (0=Jan, 11=Dec)

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

    //add back y and m together in YYYYMM format
    return year * 100 + month;
}

//3. function to get user's pass status
string getUserStatus(const string& username){
    int currentDate = getCurrYearMonth();

    //check file is open or not
    fstream appFile(APPLICATION_FILE, ios::in);
    if (!appFile.is_open()) {
        return "NO PASS";
    }

    application tempApp; //container to hold one record
    int lineNum = 0; //start at first line
    RESULT result; //result status of each read
    
    while (true) {
        //loop through all app record (push data into tempApp, result tells if read was successful)
        result = getApplication(appFile, tempApp, lineNum);
        
        //exit loop if finish reading every line in txt
        if (result == END_OF_FILE) break;
        
        if (result == VALID_RECORD) {
            string fileUsername = trim(tempApp.username);
            
            if (fileUsername == username) {
                if (tempApp.status == "APV") {
                    if (tempApp.pass_application < currentDate) {
                        return "EXPIRED";
                    } else if (tempApp.pass_application <= addMonths(currentDate, 1)) {
                        return "ALMOST_EXPIRED";
                    } else {
                        return "ACTIVE";
                    }
                } else if (tempApp.status == "PND") {
                    return "PENDING";
                }
            }
        }
        lineNum++;
    }
}