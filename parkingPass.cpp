#include <iostream>
#include <string>
#include <fstream>
#include "header/generalFunc.h"
#include "header/txtDB.h"
#include "header/login.h"

using namespace std;

void printGeneralMenu() {
    cout << endl;
    cout << "General Menu" << endl;
    cout << "1. Description" << endl;
    cout << "2. Login as User" << endl;
    cout << "3. Login as Admin" << endl;
    cout << "4. Register" << endl; 
    cout << "5. Exit Program" << endl << endl;
}

void printDescription() {
    cout << endl << "Description" << endl;
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
                printDescription();
                break;
            case '2':
                if (loginUser(userObj)) {
                    cout << "ENTER USER UI AS " << userObj.name << endl;
                } 
                break;
            case '3':
                if (loginAdmin(adminObj)) {
                    cout << "ENTER ADMIN UI AS " << adminObj.name << endl;
                }
                break;
            case '4':
                // Register user account
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