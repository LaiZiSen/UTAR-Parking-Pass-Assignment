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

    bool userNameExist = false;
    while(!userNameExist) {
        cout << "Enter your Username:  ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        inputName = getLineInput(userObj.name_Attr);

        userNameExist = searchUser(userObj, inputName);
        if (!userNameExist) {
            char choice;

            cout << "Username not found" << endl;
            cout << "Do you want to continue? (1) " << endl;
            cout << "Or Quit Login (2)" << endl;

            choice = getChoice();
            switch(choice) {
                case '1':
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                case '2':
                    return false;
            }   
        }
    }

    bool matchedPwd = false;
    string inputPwd;
    while (!matchedPwd) {
        cout << "Enter your Password:  ";
        inputPwd = getLineInput(userObj.pwd_Attr);

        if(userObj.pwd.compare(inputPwd) == 0) {
            outputUser = userObj;
            return true;
        } else {
            char choice;

            cout << "Wrong Password" << endl;
            cout << "Do you want to continue? (1) " << endl;
            cout << "Or Quit Login (2)" << endl;

            choice = getChoice();
            switch(choice) {
                case '1':
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                case '2':
                    return false;
            }   

        }

    }
}

bool loginAdmin(admin &outputAdmin){
    string inputName;
    admin adminObj;

    cout << endl << "ADMIN LOGIN" << endl;

    bool adminNameExist = false;
    while(!adminNameExist) {
        cout << "Enter your Admin Name:  ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        inputName = getLineInput(adminObj.name_Attr);

        adminNameExist = searchAdmin(adminObj, inputName);
        if (!adminNameExist) {
            char choice;

            cout << "Admin Name not found" << endl;
            cout << "Do you want to continue? (1) " << endl;
            cout << "Or Quit Login (2)" << endl;

            choice = getChoice();
            switch(choice) {
                case '1':
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                case '2':
                    return false;
            }   
        }
    }

    bool matchedPwd = false;
    string inputPwd;
    while (!matchedPwd) {
        cout << "Enter your Password:  ";
        inputPwd = getLineInput(adminObj.pwd_Attr);

        if(adminObj.pwd.compare(inputPwd) == 0) {
            outputAdmin = adminObj;
            return true;
        } else {
            char choice;

            cout << "Wrong Password" << endl;
            cout << "Do you want to continue? (1) " << endl;
            cout << "Or Quit Login (2)" << endl;

            choice = getChoice();
            switch(choice) {
                case '1':
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                case '2':
                    return false;
            }   
        }

    }
}