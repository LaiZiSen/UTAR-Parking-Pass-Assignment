#include <iostream>
#include <string>
#include <fstream>
#include <limits>

#include "../header/txtDB.h"
#include "../header/txtPath.h"
#include "../header/user.h"

using namespace std;

void usePopup(user userData) {
    int currYearMonth = getCurrYearMonth();
    // cout << userData.pass<< "   " << getCurrYearMonth();

    fstream applicationFile(APPLICATION_FILE);
    
    if (searchApplication(applicationFile, userData.name)) {
        return;
    }

    if (userData.pass == 0) {
        cout << endl << "!!!! APPLY FOR YOUR FIRST PASS NOW !!!!" << endl << endl;
    } else if (userData.pass < currYearMonth) {
        cout << endl << "!!!! APPLY FOR ANOTHER PASS NOW !!!!" << endl << endl;
    } else if (userData.pass == currYearMonth && getCurrDay() > 20) {
        cout << endl << "!!!! YOUR PASS WILL EXPIRE SOON | APPLY FOR EXTENSION NOW !!!!" << endl << endl;
    }
    cout<<"--------------------------------"<<endl;
    return;
}

void userUI(user userData){
    bool running = true;

    while(running){
        char choice, mainMenu;
        
        cout<<"--------User Menu Choice--------"<<endl;

        usePopup(userData);

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
                cout<< endl << "...Logging out...";
                running = false;
                break;
        }
    }
}

// //test function
// int main(){
    
//     user userObj;

//     fstream userFile(USER_FILE);

//     getUser(userFile,userObj, 0);

//     userUI(userObj);
//     return 0;
// }