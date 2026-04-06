//tested corrected username&pwd, havent test wrong username/pwd yet

#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include "../header/txtDB.h"
#include "../header/txtPath.h"

using namespace std;

int main(){
    bool loggedIn = false;
    
    while(loggedIn==false){
        string username, pwd;
        
        cout << "Username: ";
        getline(cin, username);
        username = trim(username);

        cout << "Password: ";
        getline(cin, pwd);
        pwd = trim(pwd);

        fstream userFile(USER_FILE, ios::in);
        if (!userFile.is_open()){
            cout << "file can't open...";
            return 1;
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
            cout << "Welcome, " << username << "!" << endl;
            loggedIn = true;
        }else{
            cout << "\nInvalid username or password." << endl;
            
            char tryAgain;
            cout << "Enter 'y' to try again: ";
            cin >> tryAgain;
            
            if(tryAgain != 'y' && tryAgain != 'Y'){
                cout << "Exiting program..." << endl;
                break;
            }
        }
    }
    return 0;
}