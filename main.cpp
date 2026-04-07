// *main*
// Start loop 
// 	OUTPUT menu choice: 1. User / 2. Admin / 3. Register / 4. Close program
// 	Switch choice 
// 		Case 1 → userLogin function
// 		Case 2 → adminLogin function 
// 		Case 3 → register function 
// 		Case 4 → exit
// End loop
////compile include user.cpp, admin.cpp, register.cpp

////tested : cannot compile file

#include <iostream>
#include <string>
#include <limits>
#include "header/txtDB.h"
#include "header/txtPath.h"
#include "header/user.h"

using namespace std;

int main (){
    char choice;
    cout<<"Menu choice: 1. User"<<endl;
    cin>>choice;
    cin.ignore();

    switch (choice){
        case '1': 
            string username = userLogin();
            userUI(username);
            break;
    }
}