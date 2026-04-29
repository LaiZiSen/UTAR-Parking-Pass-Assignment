#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <bits/stdc++.h>
#include "../header/txtDB.h"
#include "../header/txtPath.h"
#include "../header/generalFunc.h"

using namespace std;

bool searchStudentId(int studentId) {
    fstream userFile(USER_FILE);
    user userObj;

    bool foundId = false;
    while(!userFile.eof() && !foundId) {
        RESULT result = getUser(userFile, userObj, 0);\

        if(result != VALID_RECORD) continue;
        
        if(userObj.id ==  studentId) {
            userFile.close();
            return true;
        } else {
            continue;
        };
    }
    return false;

    userFile.close();
}

void getRegisterName(user &userObj) {
    user placeholderUser;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while(true) {
        cout << "Enter a Username (up to 20 letters):  ";
        userObj.name = getLineInput(userObj.name_Attr);
        transform(userObj.name.begin(), userObj.name.end(), userObj.name.begin(), ::toupper);

        if (searchUser(placeholderUser, userObj.name) || userObj.name[0] == ' ') {
            cout << "USERNAME ALREADY EXIST OR INVALID!" << endl << endl;
        } else {
            return;
        }
    }
}

void getRegisterPassword(user &userObj) {
    while (true) {
        cout << endl <<"Enter Password (8 letters long):  ";
        cin >> userObj.pwd;
        userObj.pwd = removeSpaces(userObj.pwd);

        if (userObj.pwd.length() < userObj.pwd_Attr.size) {
            cout << "INVALID PASSWORD" << endl;
        } else {break;}
    }


    while(true) {
        string confirmPwd;
        
        cout << endl <<"Confirm Password:  ";
        cin >> confirmPwd;
        
        if (confirmPwd.compare(userObj.pwd) == 0) {
            return;
        } else {
            cout << "INVALID PASSWORD" << endl;
        }
    }
}

void getRegisterId(user &userObj) {
    string studentIdStr;
    int studentIdInt;

    while (true) {
        cout << endl << "Enter Your Student ID:  ";
        cin >>  studentIdStr;

        studentIdInt = atoi(studentIdStr.c_str());

        if(studentIdInt > 1000000 && studentIdInt <= 9999999 && !searchStudentId(studentIdInt)) {
            userObj.id = studentIdInt;
            return;
        } else {
            cout << endl << "INVALID STUDENT ID OR STUDENT ID EXIST! ENTER AGAIN!" << endl;
        }
    }
}

void getRegisterFaculty(user &userObj) {
    string faculty;
    char choice;

    bool loopDone = false;
    while (!loopDone) {
        cout << endl << "Enter your faculty" << endl;
        cout << "1. IIE" << endl;
        cout << "2. CFS" << endl;
        cout << "3. FAM" << endl;
        cout << "4. FCI" << endl;
        cout << "5. FICT" << endl;
        cout << "6. LKCFES" << endl;
        cout << "7. MKFMHS" << endl;
        
        choice = getChoice();

        switch (choice) {
            case '1':
                userObj.faculty = "IIE";
                loopDone = true;
                break;
            case '2':
                userObj.faculty = "CFS";
                loopDone = true;
                break;
            case '3':
                userObj.faculty = "FAM";
                loopDone = true;
                break;
            case '4':
                userObj.faculty = "FCI";
                loopDone = true;
                break;
            case '5':
                userObj.faculty = "FICT";
                loopDone = true;
                break;
            case '6':
                userObj.faculty = "LKCFES";
                loopDone = true;
                break;
            case '7':
                userObj.faculty = "MKFMHS";
                loopDone = true;
                break;
            default:
                cout << endl << "Invalid choice. Please try again." << endl;
                break;
        }       
    }
}

void getRegisterCarPlate(user &userObj) {
    string carPlate;

    while (true) {
        cout <<  endl <<"Enter Your Car Plate:  ";
        cin >> carPlate;
        
        transform(carPlate.begin(), carPlate.end(), carPlate.begin(), ::toupper);
    
        carPlate = removeSpaces(carPlate);
        carPlate = strLengthEnforcer(carPlate, userObj.car_plate_Attr.size);
    
        if (carPlate[0] != ' ' & !searchCarPlate(carPlate)) {
            userObj.car_plate = carPlate;
            break;
        } else {
            cout << endl << "INVALID CAR PLATE OR CAR PLATE ALREADY EXIST! ENTER AGAIN" << endl;
        }
    }

}

void REGUpdateAnalytics () {
    analytic curMonAnalytics;
    int nextLine = 0;

    if (!searchAnalytics(curMonAnalytics, getCurrYearMonth(), nextLine)) {
        curMonAnalytics.month = getCurrYearMonth();
        curMonAnalytics.extension_count = 0;
        curMonAnalytics.income = 0;
        curMonAnalytics.new_application_count = 0;
        curMonAnalytics.new_user_count = 0;
        curMonAnalytics.line = nextLine;
        
        fstream analyticFile(ANALYTICS_FILE);
        writeAnalytic(analyticFile, curMonAnalytics);

        analyticFile.close();
    }

    string newUserCountStr = to_string(curMonAnalytics.new_user_count + 1);

    fstream analyticFile(ANALYTICS_FILE);

    edit(analyticFile, curMonAnalytics.line, curMonAnalytics.lineSize, curMonAnalytics.new_user_count_Attr, newUserCountStr);

    analyticFile.close();
}

bool confirmRegister(user registerUser) {
    
    cout << endl << "CONFIRM INFO YOUR INFORMATION" << endl;
    cout << "USERNAME: [" << trim(registerUser.name) << "]" << endl;
    cout << "PASSWORD: [" << trim(registerUser.pwd) << "]" << endl;
    cout << "STUDENT ID: [" << trim(to_string(registerUser.id)) << "]" << endl;
    cout << "FACULTY: [" << trim(registerUser.faculty) << "]" << endl;
    cout << "CAR PLATE: [" << trim(registerUser.car_plate) << "]" << endl;

    while (true) {
        cout << endl << "Is all of your information correct?" << endl;
        cout << "Yes (1)" << endl;
        cout << "No (2)" << endl;

        char choice = getChoice();
        cout << endl;

        switch (choice)
        {
        case '1':
            return true;
            break;
        
        case '2':
            return false;
            break;
        }

    }
}


void registerUser() {
    /*
    
    Get username
    Check if valid
    Get password
    Confirm password

    Get student id
    Check if valid

    Get faculty

    Get car plate
    
    Get confirmation of information
    if confirm proceed
    not confirm exit

    */

    user userObj;
    user placeholderUser;

    cout << endl << "REGISTER NEW USER" << endl << endl;

    getRegisterName(userObj);
    getRegisterPassword(userObj);
    getRegisterId(userObj);
    getRegisterFaculty(userObj);
    getRegisterCarPlate(userObj);
    userObj.pass = 0;

    if (confirmRegister(userObj)) {
        fstream userFile(USER_FILE);

        writeUser(userFile, userObj);
        REGUpdateAnalytics();
        userFile.close();

        cout << "REGISTERED USER - " << userObj.name << endl;
    } else {
        cout << "FAILED TO REGISTER USER, EXITING TO MAIN MENU" << endl;
    }
}