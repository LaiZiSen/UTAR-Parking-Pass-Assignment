#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <bits/stdc++.h>
#include "../header/txtDB.h"
#include "../header/txtPath.h"
#include "../header/generalFunc.h"

using namespace std;

void getRegisterName(user &userObj) {
    user placeholderUser;

    while(true) {
        cout << "Enter a Username:  ";
        // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        userObj.name = getLineInput(userObj.name_Attr);
        transform(userObj.name.begin(), userObj.name.end(), userObj.name.begin(), ::toupper);
    
        if (searchUser(placeholderUser, userObj.name)) {
            cout << "USERNAME ALREADY EXIST!" << endl;
        } else {
            return;
        }
    }
}

void getRegisterPassword(user &userObj) {
    cout << endl <<"Enter Password (8 letters long):  ";

    do {
        cin >> userObj.pwd;
    } while (userObj.pwd.length() < userObj.pwd_Attr.size);


    while(true) {
        string confirmPwd;
        
        cout << endl <<"Confirm Password:  ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        confirmPwd = getLineInput(userObj.pwd_Attr);
        
        if (confirmPwd.compare(userObj.pwd) == 0) {
            return;
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

        if(studentIdInt > 0 && studentIdInt <= 9999999) {
            userObj.id = studentIdInt;
            return;
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
                cout << "Invalid choice. Please try again." << endl;
                break;
        }       
    }
}

void getRegisterCarPlate(user &userObj) {
    string carPlate;

    while (true) {
        cout <<  endl <<"Enter Your Car Plate:  ";
        cin >> carPlate;
    
        carPlate = removeSpaces(carPlate);
        carPlate = strLengthEnforcer(carPlate, userObj.car_plate_Attr.size);
    
        if (carPlate[0] != ' ') {
            userObj.car_plate = carPlate;
            cout << "i got here"; // TODO: need to add check car plate
            break;
        }
    }

}

bool registerUser() {
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

    cout << "REGISTER INFO:   " << endl;
    cout << "USERNAME: [" << userObj.name << "]" << endl;
    cout << "PASSWORD: [" << userObj.pwd << "]" << endl;
    cout << "STUDENT ID: [" << userObj.id << "]" << endl;
    cout << "FACULTY: [" << userObj.faculty << "]" << endl;
    cout << "CAR PLATE: [" << userObj.car_plate << "]" << endl;

}

int main () {
    registerUser();
}