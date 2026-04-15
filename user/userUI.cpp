//tested no problem
#include <iostream>
#include <string>
#include <fstream>
#include <limits>

#include "../header/txtDB.h"
#include "../header/txtPath.h"
#include "../header/user.h"

using namespace std;


string userLogin(){
    bool loggedIn = false;
    string username, pwd;

    while(loggedIn==false){
        
        cout << "Username: ";
        getline(cin, username);
        username = trim(username);

        cout << "Password: ";
        getline(cin, pwd);
        pwd = trim(pwd);

        fstream userFile(USER_FILE, ios::in);
        if (!userFile.is_open()){
            cout << "file can't open...";
            exit;
        }
        
        user tempUser;
        int lineNum = 0;
        RESULT result;
        bool validUser = false;
        
        while(true){
            result = getUser(userFile, tempUser, lineNum);
            
            if (result == END_OF_FILE){
                break;
            }
            if (result == INVALID_RECORD){
                lineNum++;
                continue;
            }
            if (result == VALID_RECORD){
                if(trim(tempUser.name) == username && trim(tempUser.pwd) == pwd){
                    validUser = true;
                    break;
                }
            }
            lineNum++;
        }
        
        userFile.close();
        
        if(validUser){
            cout << "\nLogin successful!" << endl;
            cout << "Welcome, " << username << "!\n" << endl;
            loggedIn = true;
        }else{
            cout << "\nInvalid username or password." << endl;
            
            char tryAgain;
            cout << "Enter 'y' to try again: ";
            cin >> tryAgain;
            cin.ignore();
            cout << endl;
            
            if(tryAgain != 'y' && tryAgain != 'Y'){
                cout << "Exiting program..." << endl;
                break;
            }
        }
    }
    return username;
}

void userUI(string username){
    bool running = true;

    while(running){
        char choice, mainMenu;
        
        cout<<"--------user Menu Choice--------"<<endl;
        cout<<"1. Apply"<<endl;
        cout<<"2. Check Application Status"<<endl;
        cout<<"3. Check Transaction History"<<endl;
        cout<<"4. Profile"<<endl;   //creative feature
        cout<<"5. Logout\n"<<endl;
        cout<<"Choose: ";
        cin>>choice;

        switch (choice){
            case '1': 
                cout<<"\nAPPLICATION:"<<endl;
                cout<<"Apply done"<<endl;   //apply function here
                cout<<"\n.....Returning to main menu.....\n"<<endl;
                break;
            case '2': 
                cout<<"\nAPPLICATION STATUS:"<<endl;
                checkAppStatus(username);
                cout<<"\n.....Returning to main menu...\n"<<endl;
                break;
            case '3':
                cout<<"\nTRANSACTION HISTORY:"<<endl;
                checkTransHistory(username);
                cout<<"\n.....Returning to main menu...\n"<<endl;
                break;
            case '4':
                cout<<"\nPROFILE:"<<endl;
                userProfile(username);
                cout<<"\n.....Returning to main menu...\n"<<endl;
                break;
            case '5':
                cout<<"...Logging out...";
                running = false;
                break;
        }
    }
}

//test function
int main(){
    string username = userLogin();

    user userObj;

    fstream userFile(USER_FILE);

    getUser(userFile,userObj, 0);

    userUI(username);
    return 0;
}