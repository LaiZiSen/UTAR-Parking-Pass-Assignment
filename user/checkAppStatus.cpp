#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <iomanip>
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
            cout<<"Invalid record";
            continue;
        }
        if(result==END_OF_FILE){
            cout<<"Can't find application";
            break;
        }
        if(result==VALID_RECORD){
            if(trim(tempApp.username)==userObj.name){

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

                cout<<left<<setw(20)<<"Name"<<": "<<trim(tempApp.username)<<endl;
                cout<<left<<setw(20)<<"Pass until"<<": "<<trim(to_string(tempApp.pass_application))<<endl;
                cout<<left<<setw(20)<<"Car plate applied"<<": "<<trim(tempApp.car_plate)<<endl;
                cout<<left<<setw(20)<<"Type"<<": "<<type<<endl;
                cout<<left<<setw(20)<<"Status"<<": "<<status<<endl;
                cout<<left<<setw(20)<<"Apply date"<<": "<<trim(to_string(tempApp.date))<<endl;

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
}
