#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <bits/stdc++.h>
#include "../header/txtDB.h"
#include "../header/txtPath.h"
#include "../header/generalFunc.h"

using namespace std;

bool loginUser(user &);

bool loginAdmin(admin &);

bool loginUser(user &outputUser){
    string inputName;
    user userObj;

    cout << endl << "USER LOGIN" << endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    bool userNameExist = false;
    while(!userNameExist) {
        cout << "Enter your Username:  ";
        inputName = getLineInput(userObj.name_Attr);

        userNameExist = searchUser(userObj, inputName);
        if (!userNameExist) {
            cout << "Username not found" << endl;
        }
        cout << endl;
    }

    bool matchedPwd = false;
    string inputPwd;
    while (!matchedPwd) {
        cout << "Enter your Password:  ";
        inputPwd = getLineInput(userObj.pwd_Attr);

        if(userObj.pwd.compare(inputPwd) == 0) {
            outputUser = userObj;
            cout << endl;
            return true;
        } else {
            cout << "Wrong Password" << endl << endl;
        }
    }
}

bool loginAdmin(admin &outputAdmin){
    string inputName;
    admin adminObj;

    cout << endl << "ADMIN LOGIN" << endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    bool adminNameExist = false;
    while(!adminNameExist) {
        cout << "Enter your Admin Name:  ";
        inputName = getLineInput(adminObj.name_Attr);

        adminNameExist = searchAdmin(adminObj, inputName);
        if (!adminNameExist) {
            cout << "Admin Name not found" << endl;
        }
        cout << endl;
    }

    bool matchedPwd = false;
    string inputPwd;
    while (!matchedPwd) {
        cout << "Enter your Password:  ";
        inputPwd = getLineInput(adminObj.pwd_Attr);

        if(adminObj.pwd.compare(inputPwd) == 0) {
            outputAdmin = adminObj;
            cout << endl;
            return true;
        } else {
            cout << "Wrong Password" << endl << endl;
        }

    }
}