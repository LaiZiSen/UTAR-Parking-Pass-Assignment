//tested no problem
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include "../header/txtDB.h"
#include "../header/txtPath.h"

using namespace std;

string userLogin();
void userUI(string username);

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
        char choice;
        
        cout<<"Menu Choice";
        cin>>choice;

        switch (choice){
            case '1': cout<<"1"<<endl;
            case '2': running=false;
        }
    }
}

//test only
// int main(){
//     userUI(userLogin());
//     return 0;
// }