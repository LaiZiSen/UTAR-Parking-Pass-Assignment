#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <iomanip>
#include "../header/txtDB.h"
#include "../header/txtPath.h"
#include "../header/user.h"

void checkStatus(string username){
    fstream appFile(APPLICATION_FILE, ios::in);
    if (!appFile.is_open()){
        cout << "file can't open...";
        exit;
    }
    RESULT result;
    application tempApp;
    int lineNum = 0;

    bool validRecord = false;

    while(true){
        result = getApplication(appFile, tempApp, lineNum);
        
        if(result==INVALID_RECORD){
            cout<<"Invalid record";
            continue;
        }
        if(result==END_OF_FILE){
            cout<<"Can't find application";
            break;
        }
        if(result==VALID_RECORD){
            if(trim(tempApp.username)==username){

                string type, status;
                if(tempApp.type=="RNW"){
                    type="Renew";
                }else if(tempApp.type=="BUY"){
                    type="Buy";
                }

                if(tempApp.status=="PND"){
                    status="Pending";
                }else if(tempApp.status=="APV"){
                    status="Approved";
                }else if(tempApp.status=="RJT"){
                    status="Rejected";
                }

                cout<<left<<setw(20)<<"Name"<<": "<<trim(tempApp.username)<<endl;
                cout<<left<<setw(20)<<"Pass until"<<": "<<trim(to_string(tempApp.pass_application))<<endl;
                cout<<left<<setw(20)<<"Car plate applied"<<": "<<trim(tempApp.car_plate)<<endl;
                cout<<left<<setw(20)<<"Type"<<": "<<type<<endl;
                cout<<left<<setw(20)<<"Status"<<": "<<status<<endl;
                cout<<left<<setw(20)<<"Apply date"<<": "<<trim(to_string(tempApp.date))<<endl;

                validRecord = true;
                break;
            }

        }
        lineNum++;
    }
    appFile.close();
    if(!validRecord){
        cout<<"Record not found.";
    }
}

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

//test function
// int main(){
//     string username = userLogin();
//     char choice;
//     cout<<"1. check status\n";
//     cin>>choice;
//     if(choice='1'){
//         checkStatus(username);
//     }
//     return 0;
// }