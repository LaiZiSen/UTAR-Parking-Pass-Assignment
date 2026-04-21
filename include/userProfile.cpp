#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <iomanip>
#include "../header/txtDB.h"
#include "../header/txtPath.h"
#include "../header/user.h"

void userProfile(string username){
    fstream userFile(USER_FILE, ios::in);
    if (!userFile.is_open()){
        cout << "file can't open...";
        exit;
    }
    RESULT result;
    user tempUser;
    int lineNum = 0;

    bool validRecord = false;

    while(true){
        result = getUser(userFile, tempUser, lineNum);
        
        if(result==INVALID_RECORD){
            cout<<"Invalid record";
            continue;
        }
        if(result==END_OF_FILE){
            cout<<"Can't find application";
            break;
        }
        if(result==VALID_RECORD){
            if(trim(tempUser.name)==trim(username)){

                cout<<left<<setw(20)<<"Name"<<": "<<trim(tempUser.name)<<endl;
                cout<<left<<setw(20)<<"Student ID"<<": "<<trim(to_string(tempUser.id))<<endl;
                cout<<left<<setw(20)<<"Faculty"<<": "<<trim(tempUser.faculty)<<endl;
                cout<<left<<setw(20)<<"Pass active until"<<": "<<trim(to_string(tempUser.pass))<<endl;
                cout<<left<<setw(20)<<"Car plate"<<": "<<trim(tempUser.car_plate)<<endl;

                validRecord = true;
                break;
            }

        }
        lineNum++;
    }
    userFile.close();
    if(!validRecord){
        cout<<"Record not found.";
    }
    
    cout << endl <<  "Enter to return to User Menu";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
}
