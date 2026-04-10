#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <iomanip>
#include "../header/txtDB.h"
#include "../header/txtPath.h"
#include "../header/user.h"

void checkTransHistory(string username){
    fstream transFile(TRANSACTION_FILE, ios::in);
    if (!transFile.is_open()){
        cout << "file can't open...";
        exit;
    }
    RESULT result;
    transaction tempTrans;
    int lineNum = 0;

    bool validRecord = false;

    while(true){
        result = getTransaction(transFile, tempTrans, lineNum);
        
        if(result==INVALID_RECORD){
            cout<<"Invalid record";
            continue;
        }
        if(result==END_OF_FILE){
            cout<<"Can't find application";
            break;
        }
        if(result==VALID_RECORD){
            if(trim(tempTrans.username)==username){

                string trans_type;
                if(tempTrans.trans_type=="INC"){
                    trans_type="+";
                }else if(tempTrans.trans_type=="RFD"){
                    trans_type="-";
                }

                cout<<left<<setw(20)<<"Name"<<": "<<trim(tempTrans.username)<<endl;
                cout<<left<<setw(20)<<"Amount"<<": "<<fixed<<setprecision(2)<<trans_type<<(tempTrans.amount)<<endl;
                cout<<left<<setw(20)<<"Date"<<": "<<trim(to_string(tempTrans.date))<<endl;

                validRecord = true;
                break;
            }

        }
        lineNum++;
    }
    transFile.close();
    if(!validRecord){
        cout<<"Record not found.";
    }
}