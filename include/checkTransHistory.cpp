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
        cout << "file can't open..." << endl;
        exit;
    }
    RESULT result;
    transaction tempTrans;
    int lineNum = 0;

    bool validRecord = false;

    cout<<left<<setw(20)<<"DATE"<<"AMOUNT"<<endl;

    while(true){
        result = getTransaction(transFile, tempTrans, lineNum);
        
        if(result==INVALID_RECORD){
            continue;
        }
        if(result==END_OF_FILE){
            cout<<"End of record" << endl;
            break;
        }
        if(result==VALID_RECORD){
            validRecord = true;
            if(trim(tempTrans.username)==trim(username)){

                string trans_type;
                if(tempTrans.trans_type=="INC"){
                    trans_type="+ RM";
                }else if(tempTrans.trans_type=="RFD"){
                    trans_type="- RM";
                }
                cout<<left<<setw(20)<<trim(to_string(tempTrans.date))<<fixed<<setprecision(2)<<trans_type<<(tempTrans.amount)<<endl;
            }
        }
        lineNum++;
    }
    transFile.close();
    if(!validRecord){
        cout<<"Record not found." << endl;
    }
    
    cout << endl <<  "Enter to return to User Menu";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
}
