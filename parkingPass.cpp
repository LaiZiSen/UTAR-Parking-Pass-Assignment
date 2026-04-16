#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include "header/generalFunc.h"
#include "header/txtDB.h"
#include "header/login.h"
#include "header/register.h"

using namespace std;

void printGeneralMenu() {
    cout << endl;
    cout << "General Menu" << endl;
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
                    cout << "ENTER USER UI AS " << userObj.name << endl;
                } 
                break;
            case '2':
                if (loginAdmin(adminObj)) {
                    cout << "ENTER ADMIN UI AS " << adminObj.name << endl;
                }
                break;
            case '3':
                registerUser();
                break;
            case '4':
                // check parking Pass
                break;
            case '5':
                cout << endl << "Exiting Parking Pass program";
                progRunning = false;
                break;
            default:
                cout << "Invalid option, enter anotehr number" << endl;
                break;
        }
    }
}