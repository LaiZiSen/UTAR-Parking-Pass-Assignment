#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void printGeneralMenu() {
    cout << endl;
    cout << "General Menu" << endl;
    cout << "1. Description" << endl;
    cout << "2. Login as User" << endl;
    cout << "3. Login as Admin" << endl;
    cout << "4. Register" << endl; 
    cout << "5. Exit Program" << endl;
}

char getChoice(){
    cout << "Enter a number for your option:  ";
    
    char output;
    cin >> output;

    return output;
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

        switch (choice) {
            case '1':
                printDescription();
                break;
            case '2':
                // Login as User
                break;
            case '3':
                // Login as Admin
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