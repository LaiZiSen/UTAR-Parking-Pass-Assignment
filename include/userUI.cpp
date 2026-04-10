//tested no problem
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include "../header/txtDB.h"
#include "../header/txtPath.h"
#include "../header/user.h"

using namespace std;

void userUI(string username){
    bool running = true;

    while(running){
        char choice;
        
        cout<<"Menu Choice"<<endl;
        cout<<"1. Apply"<<endl;
        cout<<"2. Check Application Status"<<endl;
        cout<<"3. Check Transaction History"<<endl;
        cout<<"4. Profile"<<endl;   //creative feature
        cout<<"5. Logout"<<endl;
        cin>>choice;

        switch (choice){
            case '1': 
                
            case '2': 
                running=false;
        }
    }
}

//test function
int main(){
    userUI(userLogin());
    return 0;
}