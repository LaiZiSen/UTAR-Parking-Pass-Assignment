#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

enum RESULT {
    VALID_RECORD,
    INVALID_RECORD, 
    END_OF_FILE
};

struct attribute
{
    int pos;
    int size;

    attribute(int pos, int size) : pos(pos), size(size) {};
};

struct admin {
    static const attribute name_Attr;
    static const attribute pwd_Attr;
    static const int lineSize;
    
    int line;
    string name;
    string pwd;
};

const attribute admin::name_Attr(0,8);
const attribute admin::pwd_Attr(admin::name_Attr.pos + admin::name_Attr.size, 8);
const int admin::lineSize(admin::pwd_Attr.pos + admin::pwd_Attr.size + 2);

struct user {
    static const attribute name_Attr;
    static const attribute pwd_Attr;
    static const attribute pass_Attr;
    static const attribute car_plate_Attr;
    static const int lineSize;

    int line;
    string name;
    string pwd;
    int pass;
    string car_plate;
};


const attribute user::name_Attr(0, 20);
const attribute user::pwd_Attr(user::name_Attr.pos + user::name_Attr.size, 8);
const attribute user::pass_Attr(user::pwd_Attr.pos + user::pwd_Attr.size, 6);
const attribute user::car_plate_Attr(user::pass_Attr.pos + user::pass_Attr.size, 10);
const int user::lineSize(user::car_plate_Attr.pos + user::car_plate_Attr.size + 2);

struct application {
    static const attribute username_Attr;
    static const attribute pass_application_Attr;
    static const attribute car_plate_Attr;
    static const attribute status_Attr;
    static const int lineSize;

    int line;
    string username;
    int pass_application;
    string car_plate;
    string status;
};

const attribute application::username_Attr(0, 20);
const attribute application::pass_application_Attr(application::username_Attr.pos + application::username_Attr.size, 6);
const attribute application::car_plate_Attr(application::pass_application_Attr.pos + application::pass_application_Attr.size, 10);
const attribute application::status_Attr(application::car_plate_Attr.pos + application::car_plate_Attr.size, 3);
const int application::lineSize(application::status_Attr.pos + application::status_Attr.size + 2);

struct transaction {
    static const attribute username_Attr;
    static const attribute trans_type_Attr;
    static const attribute amount_Attr;
    static const int lineSize;

    int line;
    string username;
    string trans_type;
    float amount;
};

const attribute transaction::username_Attr(0,20);
const attribute transaction::trans_type_Attr(transaction::username_Attr.pos + transaction::username_Attr.size, 3);
const attribute transaction::amount_Attr(transaction::trans_type_Attr.pos + transaction::trans_type_Attr.size, 6);
const int transaction::lineSize(transaction::amount_Attr.pos + transaction::amount_Attr.size + 2);


void writeAdmin(fstream &file, admin input);
void writeUser(fstream &file, user input);
void writeApplication(fstream &file, application input);
void writeTransaction(fstream &file, transaction input);

RESULT getAdmin(fstream&, admin&, int);
RESULT getUser(fstream&, user&, int);
RESULT getApplication(fstream&, application&, int);
RESULT getTransaction(fstream&, transaction&, int);

bool edit (fstream &file, int line, int lineSize, attribute editAttribute, string editValue);
bool removeRecord(fstream &file, int line, int lineSize);

string  strLengthEnforcer(string targetStr, int fillSize);

void writeAdmin(fstream &file, admin input) {
    string writeLine = "";
    writeLine.append("\n").append(input.name).append(input.pwd);

    file.seekp(0, fstream::end);
    file.write(writeLine.c_str(), input.lineSize-1);
}

void writeUser(fstream &file, user input) {
    string writeLine = "";
    writeLine.append("\n").append(input.name).append(input.pwd).append(to_string(input.pass)).append(input.car_plate);

    file.seekp(0, fstream::end);
    file.write(writeLine.c_str(), input.lineSize-1);
}

void writeApplication(fstream &file, application input) {
    string writeLine = "";
    writeLine.append("\n").append(input.username).append(to_string(input.pass_application)).append(input.car_plate).append(input.status);

    file.seekp(0, fstream::end);
    file.write(writeLine.c_str(), input.lineSize-1);
}

void writeTransaction(fstream &file, transaction input) {
    string writeLine = "";
    writeLine.append("\n").append(input.username).append(input.trans_type).append(strLengthEnforcer(to_string(input.amount), input.amount_Attr.size));

    file.seekp(0, fstream::end);
    file.write(writeLine.c_str(), input.lineSize-1);
}

/*
Gets the admin record from the next line of admin.txt
*/
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
        output.status = line.substr(output.status_Attr.pos,output.status_Attr.size);
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
        output.trans_type = stoi(line.substr(output.trans_type_Attr.pos,output.trans_type_Attr.size));
        output.amount = stof(line.substr(output.amount_Attr.pos,output.amount_Attr.size));
        output.line = lineNum;

        return VALID_RECORD;
        
    } else {return END_OF_FILE;}
}

/*
Need to add function to fill in the string if not long enough to aovid garbage values
*/
bool edit (fstream &file, int line, int lineSize, attribute editAttribute, string editValue) {
    
    int editPosition = line * lineSize + editAttribute.pos;

    file.seekp(editPosition, fstream::beg);

    if (file.tellg() == -1) {
        return false;
    }

    file.write(editValue.c_str(), editAttribute.size);
    return true;
}

bool removeRecord(fstream &file, int line, int lineSize) {
    int removeLinePosition = line * lineSize;

    string fillString = strLengthEnforcer("", lineSize-2);

    file.seekg(removeLinePosition, fstream::beg);

    file.write(fillString.c_str(), lineSize-2);
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

int main () {

    fstream file("..\\db\\user.txt");
    user userObj;

    cout << endl << file.tellg() << endl;

    int line = 0;

    while(getUser(file, userObj, line) != END_OF_FILE) {
        line++;

        cout << "User Number:  " << line +1 << endl;
        cout << "Username : [" << userObj.name << "]" << endl;
        cout << "Password : [" << userObj.pwd << "]" << endl;
        cout << "Car Pass : [" << userObj.pass << "]" << endl;
        cout << "Car Plate: [" << userObj.car_plate << "]" << endl;
    }

    file.close();

    file.open("..\\db\\application.txt");
    application applicationObj;

    cout << endl << "Printing application.txt" << endl;

    line = 0;

    while(getApplication(file, applicationObj, line) != END_OF_FILE) {
        line++;

        cout << "Application number:  " << line << endl;
        cout << "Username : [" << applicationObj.username << "]" << endl;
        cout << "PassApli : [" << applicationObj.pass_application << "]" << endl;
        cout << "CarPlate : [" << applicationObj.car_plate << "]" << endl;
        cout << "Status   : [" << applicationObj.status << "]" << endl;
    }

    file.close();
}