#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <iomanip>
#include <ctime>
#include "../header/txtDB.h"
#include "../header/txtPath.h"
#include "../header/user.h"

void checkAppStatus(user userObj){
    fstream appFile(APPLICATION_FILE, ios::in);
    if (!appFile.is_open()){
        cout << "file can't open...";
        exit;
    }
    RESULT result;
    application tempApp;
    int lineNum = 0;

    bool validRecord = false;

    while(true){
        result = getApplication(appFile, tempApp, lineNum);
        
        if(result==INVALID_RECORD){
            continue;
        }
        if(result==END_OF_FILE){
            cout<<"Can't find application";
            break;
        }
        if(result==VALID_RECORD){
            if(trim(tempApp.username)==trim(userObj.name)){

                string type, status;
                if(tempApp.type=="RNW"){
                    type="Renew";
                }else if(tempApp.type=="BUY"){
                    type="Buy";
                }

                if(tempApp.status=="PND"){
                    status="Pending";
                }else if(tempApp.status=="APV"){
                    status="Approved";
                }else if(tempApp.status=="RJT"){
                    status="Rejected";
                }

                tm curPassTM;
                char curPassStr[50];
                curPassTM.tm_year = userObj.pass/100 - 1900;
                curPassTM.tm_mon = userObj.pass % 100 -1;
                strftime(curPassStr, 50, "%b %Y", &curPassTM);
                
                tm appliedPassTM;
                char appliedPassStr[50];
                appliedPassTM.tm_year = tempApp.pass_application / 100 - 1900;
                appliedPassTM.tm_mon = tempApp.pass_application % 100 -1;
                strftime(appliedPassStr, 50, "%b %Y", &appliedPassTM);

                tm applyDateTM;
                char applyDateStr[50];
                applyDateTM.tm_year = tempApp.date / 10000 + 100;
                applyDateTM.tm_mon = (tempApp.date / 100) % 100 - 1;
                applyDateTM.tm_mday = tempApp.date % 100 - 1;
                strftime(applyDateStr, 50, "%d/%m/%Y", &applyDateTM);
                
                cout<<left<<setw(20)<<"Name"<<": "<<trim(tempApp.username)<<endl;
                cout<<left<<setw(20)<<"Current Pass"<<": "<<curPassStr<<endl;
                cout<<left<<setw(20)<<"Pass Applied"<<": "<<appliedPassStr<<endl;
                cout<<left<<setw(20)<<"Car plate applied"<<": "<<trim(tempApp.car_plate)<<endl;
                cout<<left<<setw(20)<<"Type"<<": "<<type<<endl;
                cout<<left<<setw(20)<<"Status"<<": "<<status<<endl;
                cout<<left<<setw(20)<<"Apply date"<<": "<< applyDateStr <<endl;

                validRecord = true;
                break;
            }

        }
        lineNum++;
    }
    appFile.close();
    if(!validRecord){
        cout<<"Record not found.";
    }

    cout << endl <<  "Enter to return to User Menu";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
}
