#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "../header/txtDB.h"

using namespace std;

const attribute admin::name_Attr(0,8);
const attribute admin::pwd_Attr(admin::name_Attr.pos + admin::name_Attr.size, 8);
const int admin::lineSize(admin::pwd_Attr.pos + admin::pwd_Attr.size + 2);

const attribute user::name_Attr(0, 20);
const attribute user::pwd_Attr(user::name_Attr.pos + user::name_Attr.size, 8);
const attribute user::id_Attr(user::pwd_Attr.pos + user::pwd_Attr.size, 7);
const attribute user::faculty_Attr(user::id_Attr.pos + user::id_Attr.size, 6);
const attribute user::pass_Attr(user::faculty_Attr.pos + user::faculty_Attr.size, 6);
const attribute user::car_plate_Attr(user::pass_Attr.pos + user::pass_Attr.size, 10);
const int user::lineSize(user::car_plate_Attr.pos + user::car_plate_Attr.size + 2);

const attribute application::username_Attr(0, 20);
const attribute application::pass_application_Attr(application::username_Attr.pos + application::username_Attr.size, 6);
const attribute application::car_plate_Attr(application::pass_application_Attr.pos + application::pass_application_Attr.size, 10);
const attribute application::type_Attr(application::car_plate_Attr.pos + application::car_plate_Attr.size, 3);
const attribute application::status_Attr(application::type_Attr.pos + application::type_Attr.size, 3);
const attribute application::date_Attr(application::status_Attr.pos + application::status_Attr.size, 6);
const int application::lineSize(application::date_Attr.pos + application::date_Attr.size + 2);

const attribute transaction::username_Attr(0,20);
const attribute transaction::trans_type_Attr(transaction::username_Attr.pos + transaction::username_Attr.size, 3);
const attribute transaction::date_Attr(transaction::trans_type_Attr.pos + transaction::trans_type_Attr.size, 6);
const attribute transaction::amount_Attr(transaction::date_Attr.pos + transaction::date_Attr.size, 6);
const int transaction::lineSize(transaction::amount_Attr.pos + transaction::amount_Attr.size + 2);

const attribute analytic::month_Attr(0, 6);
const attribute analytic::new_user_count_Attr(analytic::month_Attr.pos + analytic::month_Attr.size, 3);
const attribute analytic::new_application_count_Attr(analytic::new_user_count_Attr.pos + analytic::new_user_count_Attr.size, 3);
const attribute analytic::extension_count_Attr(analytic::new_application_count_Attr.pos + analytic::new_application_count_Attr.size, 3);
const attribute analytic::pass_price_Attr(analytic::extension_count_Attr.pos + analytic::extension_count_Attr.size, 5);
const attribute analytic::income_Attr(analytic::pass_price_Attr.pos + analytic::pass_price_Attr.size, 8);
const int analytic::lineSize(analytic::income_Attr.pos + analytic::income_Attr.size + 2);

void writeAdmin(fstream &file, admin input) {
    string writeLine = "\n";
    writeLine.append(strLengthEnforcer(input.name, input.name_Attr.size));
    writeLine.append(strLengthEnforcer(input.pwd, input.pwd_Attr.size));

    file.seekp(0, fstream::end);
    file.write(writeLine.c_str(), input.lineSize-1);
}

void writeUser(fstream &file, user input) {
    string writeLine = "\n";
    writeLine.append(strLengthEnforcer(input.name, input.name_Attr.size));
    writeLine.append(strLengthEnforcer(input.pwd, input.pwd_Attr.size));
    writeLine.append(strLengthEnforcer(input.faculty, input.faculty_Attr.size));
    writeLine.append(strLengthEnforcer(to_string(input.pass), input.pass_Attr.size));
    writeLine.append(strLengthEnforcer(input.car_plate, input.car_plate_Attr.size));

    file.seekp(0, fstream::end);
    file.write(writeLine.c_str(), input.lineSize-1);
}

void writeApplication(fstream &file, application input) {
    string writeLine = "\n";
    writeLine.append(strLengthEnforcer(input.username, input.username_Attr.size));
    writeLine.append(strLengthEnforcer(to_string(input.pass_application), input.pass_application_Attr.size));
    writeLine.append(strLengthEnforcer(input.car_plate, input.car_plate_Attr.size));
    writeLine.append(strLengthEnforcer(input.type, input.type_Attr.size));
    writeLine.append(strLengthEnforcer(input.status, input.status_Attr.size));
    writeLine.append(strLengthEnforcer(to_string(input.date), input.date_Attr.size));

    file.seekp(0, fstream::end);
    file.write(writeLine.c_str(), input.lineSize-1);
}

void writeTransaction(fstream &file, transaction input) {
    string writeLine = "\n";
    writeLine.append(strLengthEnforcer(input.username, input.username_Attr.size));
    writeLine.append(strLengthEnforcer(input.trans_type, input.trans_type_Attr.size));
    writeLine.append(strLengthEnforcer(to_string(input.date), input.date_Attr.size));
    writeLine.append(strLengthEnforcer(to_string(input.amount), input.amount_Attr.size));

    file.seekp(0, fstream::end);
    file.write(writeLine.c_str(), input.lineSize-1);
}

void writeAnalytic(fstream &file, analytic input) {
    string writeLine = "\n";
    writeLine.append(strLengthEnforcer(to_string(input.month), input.month_Attr.size));
    writeLine.append(strLengthEnforcer(to_string(input.new_user_count), input.new_user_count_Attr.size));
    writeLine.append(strLengthEnforcer(to_string(input.new_application_count), input.new_application_count_Attr.size));
    writeLine.append(strLengthEnforcer(to_string(input.extension_count), input.extension_count_Attr.size));
    writeLine.append(strLengthEnforcer(to_string(input.pass_price), input.pass_price_Attr.size));
    writeLine.append(strLengthEnforcer(to_string(input.income), input.income_Attr.size));

    file.seekp(0, fstream::end);
    file.write(writeLine.c_str(), input.lineSize-1);
}

RESULT getAdmin(fstream &file, admin &output, int lineNum) {
    string line;

    if(getline(file, line)){
        if(line[0] == ' ') {
            return INVALID_RECORD;
        } 
        
        output.name = line.substr(output.name_Attr.pos,output.name_Attr.size);
        output.pwd = line.substr(output.pwd_Attr.pos,output.pwd_Attr.size);
        output.line = lineNum;

        return VALID_RECORD;
        
    } else {return END_OF_FILE;}
}

RESULT getUser(fstream &file, user &output, int lineNum) {
    string line;

    if(getline(file, line)) {
        if(line[0] == ' ') {
            return INVALID_RECORD;
        }
        
        output.name = line.substr(output.name_Attr.pos, output.name_Attr.size);
        output.pwd = line.substr(output.pwd_Attr.pos,output.pwd_Attr.size);
        output.faculty = line.substr(output.faculty_Attr.pos, output.faculty_Attr.size);
        output.pass = stoi(line.substr(output.pass_Attr.pos,output.pass_Attr.size));
        output.car_plate = line.substr(output.car_plate_Attr.pos,output.car_plate_Attr.size);
        output.line = lineNum;

        return VALID_RECORD;
        
    } else {return END_OF_FILE;}
}

RESULT getApplication(fstream &file, application &output, int lineNum) {
    string line;

    if(getline(file, line)) {
        if(line[0] == ' ') {
            return INVALID_RECORD;
        }
        
        output.username = line.substr(output.username_Attr.pos, output.username_Attr.size);
        output.pass_application = stoi(line.substr(output.pass_application_Attr.pos,output.pass_application_Attr.size));
        output.car_plate = line.substr(output.car_plate_Attr.pos,output.car_plate_Attr.size);
        output.type = line.substr(output.type_Attr.pos, output.type_Attr.size);
        output.status = line.substr(output.status_Attr.pos,output.status_Attr.size);
        output.date = stoi(line.substr(output.date_Attr.pos, output.date_Attr.size));
        output.line = lineNum;

        return VALID_RECORD;
        
    } else {return END_OF_FILE;}
}

RESULT getTransaction(fstream &file, transaction &output, int lineNum) {
    string line;

    if(getline(file, line)) {
        if(line[0] == ' ') {
            return INVALID_RECORD;
        }
        
        output.username = line.substr(output.username_Attr.pos, output.username_Attr.size);
        output.trans_type =line.substr(output.trans_type_Attr.pos,output.trans_type_Attr.size);
        output.date = stoi(line.substr(output.date_Attr.pos, output.date_Attr.size));
        output.amount = stof(line.substr(output.amount_Attr.pos,output.amount_Attr.size));
        output.line = lineNum;

        return VALID_RECORD;
        
    } else {return END_OF_FILE;}
}

RESULT getAnalytic(fstream &file, analytic &output, int lineNum) {
    string line;

    if(getline(file, line)) {
        if(line[0] == ' ') {
            return INVALID_RECORD;
        }
        
        output.month = stoi(line.substr(output.month_Attr.pos, output.month_Attr.size));
        output.new_user_count = stoi(line.substr(output.new_user_count_Attr.pos, output.new_user_count_Attr.size));
        output.new_application_count = stoi(line.substr(output.new_application_count_Attr.pos, output.new_application_count_Attr.size));
        output.extension_count = stoi(line.substr(output.extension_count_Attr.pos, output.extension_count_Attr.size));
        output.pass_price = stof(line.substr(output.pass_price_Attr.pos, output.pass_price_Attr.size));
        output.income = stof(line.substr(output.income_Attr.pos, output.income_Attr.size));
        output.line = lineNum;

        return VALID_RECORD;
        
    } else {return END_OF_FILE;}
}

bool edit (fstream &file, int line, int lineSize, attribute editAttribute, string editValue) {
    
    int editPosition = line * lineSize + editAttribute.pos;

    file.seekp(editPosition, fstream::beg);

    if (file.tellg() == -1) {
        return false;
    }

    editValue = strLengthEnforcer(editValue, editAttribute.size);
    file.write(editValue.c_str(), editAttribute.size);

    return true;
}

bool removeRecord(fstream &file, int line, int lineSize) {
    int removeLinePosition = line * lineSize;

    string fillString = strLengthEnforcer("", lineSize-2);

    file.seekp(removeLinePosition, fstream::beg);

    if (file.tellp() == -1) {
        return false;
    }

    file.write(fillString.c_str(), lineSize-2);

    return true;
}

string  strLengthEnforcer(string targetStr, int fillSize) {
    if (fillSize <= 0) {return "";}

    if (targetStr.length() > static_cast<size_t>(fillSize)) {
        // Truncate the string
        targetStr = targetStr.substr(0, fillSize);
    } else if (targetStr.length() < static_cast<size_t>(fillSize)) {
        // Pad with spaces
        targetStr.append(fillSize - targetStr.length(), ' ');
    }

    return targetStr;
}

//function to remove spaces in txt data
string trim(const string& input){
    size_t startPos = input.find_first_not_of(' ');
    if (startPos == string::npos){
        return "";
    }
    size_t endPos = input.find_last_not_of(' ');

    return input.substr(startPos, endPos-startPos+1);
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

    return resultInYearMonth;
}

int getCurrYYMMDD(){
    time_t rawtime; 
    time(&rawtime); 
    struct tm* timeinfo; 
    timeinfo = localtime(&rawtime); 

    int yearNow = timeinfo->tm_year - 100; 
    int monthNow = timeinfo->tm_mon + 1; 
    int dayNow = timeinfo->tm_mday;

    int resultInYearMonthDay = yearNow * 10000 + monthNow * 100 + dayNow;

    return resultInYearMonthDay;
}

int getCurrDay(){
    time_t rawtime;
    time(&rawtime);
    struct tm* timeinfo;
    timeinfo = localtime(&rawtime);

    return timeinfo -> tm_mday;
}