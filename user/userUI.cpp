#include <iostream>
#include <string>
#include <fstream>
#include <limits>

#include "../header/txtDB.h"
#include "../header/txtPath.h"
#include "../header/user.h"

using namespace std;


void userUI(user userData){
    bool running = true;

    while(running){
        char choice, mainMenu;
        
        cout<<"--------User Menu Choice--------"<<endl;
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
                applyPass(userData);
                cout<<"\n.....Returning to main menu.....\n"<<endl;
                break;
            case '2': 
                cout<<"\nAPPLICATION STATUS:"<<endl;
                checkAppStatus(userData);
                cout<<"\n.....Returning to main menu...\n"<<endl;
                break;
            case '3':
                cout<<"\nTRANSACTION HISTORY:"<<endl;
                checkTransHistory(userData.name);
                cout<<"\n.....Returning to main menu...\n"<<endl;
                break;
            case '4':
                cout<<"\nPROFILE:"<<endl;
                userProfile(userData.name);
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
    
    user userObj;

    fstream userFile(USER_FILE);

    getUser(userFile,userObj, 0);

    userUI(userObj);
    return 0;
}