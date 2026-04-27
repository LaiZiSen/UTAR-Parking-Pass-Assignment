#include <iostream>
#include <fstream>
#include "../header/txtDB.h"
#include "../header/txtPath.h"
#include "../header/generalFunc.h"
#include "../header/admin.h"

using namespace std;


void printAdminMenu() {
    cout << endl;
    cout<<"--------Admin Menu Choice--------"<<endl;
    cout << "1. Approve Applications" << endl;
    cout << "2. Apply Applications" << endl;
    cout << "3. Check Analytics" << endl;
    cout << "4. Logout" << endl << endl;
}

void adminUI(admin adminData) {
    cout << "WELCOME " << adminData.name << endl;

    bool loggedIn = true;
    while(loggedIn) {
        char choice;
        
        printAdminMenu();
        choice = getChoice();

        switch (choice) {
            case '1':
                approveAPP();
                break;
            case '2':
                applyApplications();
                break;
            case '3':
                checkAnalytics();
                break;
            case '4':
                cout << endl << "Logging out " << adminData.name << endl;
                loggedIn = false;
                break;
            default:
                cout << "Invalid option, enter another number" << endl;
                break;
        };
    }
}