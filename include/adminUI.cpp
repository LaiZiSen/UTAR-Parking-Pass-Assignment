#include <iostream>
#include <fstream>
#include "../header/txtDB.h"
#include "../header/txtPath.h"
#include "../header/approveAPP.h"
#include "../header/checkAnalytics.h"

using namespace std;


void printAdminMenu() {
    cout << endl;
    cout << "Menu" << endl;
    cout << "1. Approve Applications" << endl;
    cout << "2. Apply Applications" << endl;
    cout << "3. Check Analytics" << endl;
    cout << "4. Logout" << endl << endl;
}

char getOption(){
    cout << "Enter a number for your option:  ";
    
    char output;
    cin >> output;

    return output;
}

void adminUI(admin adminData) {
    cout << endl << "WELCOME" << adminData.name << endl;

    bool loggedIn = true;
    while(loggedIn) {
        char option;
        
        printAdminMenu();
        option = getOption();

        switch (option) {
            case '1':
                approveAPP();
                break;
            case '2':
                cout << endl << "Apply Applications" << endl;
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

int main () {

    fstream adminFile(ADMIN_FILE);

    admin adminData;
    getAdmin(adminFile, adminData, 0);

    adminUI(adminData);

    return 0;
}