#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include "header/generalFunc.h"
#include "header/txtDB.h"
#include "header/login.h"
#include "header/register.h"
#include "header/checkPass.h"
#include "header/user.h"
#include "header/admin.h"

using namespace std;

void printGeneralMenu() {
    cout << endl;
    cout<<"--------Main Menu Choice--------"<<endl;
    cout << "1. Login as User" << endl;
    cout << "2. Login as Admin" << endl;
    cout << "3. Register" << endl; 
    cout << "4. Check Pass" << endl;
    cout << "5. Exit Program" << endl << endl;
}

int main () {    
    bool progRunning = true;

    char choice;
    while(progRunning) {
        printGeneralMenu();
        choice = getChoice();

        user userObj;
        admin adminObj;
        switch (choice) {
            case '1':
                if (loginUser(userObj)) {
                    cout << "ENTERING USER UI AS " << userObj.name << endl << endl;
                    userUI(userObj);
                } 
                break;
            case '2':
                if (loginAdmin(adminObj)) {
                    cout << "ENTERING ADMIN UI AS " << adminObj.name << endl << endl;
                    adminUI(adminObj);
                }
                break;
            case '3':
                registerUser();
                break;
            case '4':
                checkPass();
                break;
            case '5':
                cout << endl << "Exiting Parking Pass program";
                progRunning = false;
                break;
            default:
                cout << "Invalid option, enter another number" << endl;
                break;
        }
    }
    return 0;
}