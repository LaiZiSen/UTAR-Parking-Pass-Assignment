#include <iostream>
#include <ctime> //for time function
#include <string>
#include <sstream>
#include "../header/txtDB.h"
#include "../header/txtPath.h"

using namespace std;

int getCurrYearMonth();
int getCurrDate();

int main(){
    fstream userFile(USER_FILE, ios::in);
    
    if (!userFile.is_open()) {
        cout<<"Error: file is at "<<USER_FILE<<endl;
        return 1;
    }

    bool valid = true;

    while(valid){
        string username, pwd;

        cout<<"Username: "<<endl;
        cin>>username;
        cout<<"Password: "<<endl;
        cin>>pwd;
        
        user tempUser;
        int lineNum = 0;
        RESULT result;

        result = getUser(userFile, tempUser, lineNum);
        if (result == VALID_RECORD){
            //start finding username and psw
            if (trim(tempUser.name)==username && trim(tempUser.pwd)==pwd){
                cout<<"Login successful!";
            } else {
                cout<<"Invalid username or password"<<endl;

                char tryAgain;
                cout<<"Enter 'y' if you want to try again."<<endl;
                cin>>tryAgain;
                if(tryAgain != 'y' && tryAgain != 'Y'){
                    valid = false;
                }
            }
        }else{
            cout<<"Invalid record OR no match found"<<endl;
            break;
        }
    }
}