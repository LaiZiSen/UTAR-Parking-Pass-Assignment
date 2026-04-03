#include <iostream>
#include <ctime> //for time function
#include <string>
#include <sstream>
#include "include/txtDB.h"

using namespace std;

//file paths
const string USER_FILE = "db/user.txt";
const string ANALYTICS_FILE = "db/analytics.txt";
const string APPLICATION_FILE = "db/application.txt";
const string TRANSACTION_FILE = "db/transaction.txt";

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

int main(){
    cout<<"Current: ";
    cout<<getCurrYearMonth();
}