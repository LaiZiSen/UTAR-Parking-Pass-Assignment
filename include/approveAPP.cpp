#include <iostream>
#include <fstream>
#include <string>
#include "../header/txtDB.h"
#include "../header/txtPath.h"

using namespace std;

void displayAPP (application applicationObj) {
    cout << "Username    - " << applicationObj.username << endl;
    cout << "Application - " << applicationObj.pass_application << endl;
    cout << "Car Plate   - " << applicationObj.car_plate << endl;
    cout << "Appli type  - " << applicationObj.type << endl;
    cout << "Appli date  - " << applicationObj.date << endl;
}

void displayApvMenu() {
    cout << endl << "APPROVE OR REJECT?" << endl;
    cout << "(1) APV" << endl;
    cout << "(2) RJT" << endl;
}

void displayContApvMenu() {
    cout << endl << "NEXT APPLICATION or EXIT?" << endl;
    cout << "(1) NEXT" << endl;
    cout << "(2) EXIT" << endl;
}

float getRFDAmount(fstream &transFile, application applicationData) {

    transaction transactionObj;
    int lineNum;
    while (!transFile.eof())
    {
        getTransaction(transFile, transactionObj, lineNum);

        if (transactionObj.username.compare(applicationData.username) == 0) {
            return transactionObj.amount;
        }
    }
    return 0;
}

void approve(fstream &file, application applicationData) {
    edit(file, applicationData.line, applicationData.lineSize, applicationData.status_Attr, appStatusAPV);
}

void RFDUpdateAnalytics (float amount) {
    analytic curMonAnalytics;
    int nextLine = 0;

    if (!searchAnalytics(curMonAnalytics, 202604, nextLine)) {
        curMonAnalytics.month = 202604;
        curMonAnalytics.extension_count = 0;
        curMonAnalytics.income = 0;
        curMonAnalytics.new_application_count = 0;
        curMonAnalytics.new_user_count = 0;
        curMonAnalytics.line = nextLine;
        
        fstream analyticFile(ANALYTICS_FILE);
        writeAnalytic(analyticFile, curMonAnalytics);

        analyticFile.close();
    }

    string amountStr = floatToStr(curMonAnalytics.income - amount);

    fstream analyticFile(ANALYTICS_FILE);

    edit(analyticFile, curMonAnalytics.line, curMonAnalytics.lineSize, curMonAnalytics.income_Attr, amountStr);

    analyticFile.close();
}

void reject(fstream &file, application applicationData) {
    file.clear();
    edit(file, applicationData.line, applicationData.lineSize, applicationData.status_Attr, appStatusRJT);

    fstream transFile(TRANSACTION_FILE);

    transaction rfdTransaction;
    rfdTransaction.username = applicationData.username;
    rfdTransaction.amount = getRFDAmount(transFile, applicationData); //later
    rfdTransaction.date = getCurrYYMMDD();
    rfdTransaction.trans_type = transTypeRFD;

    writeTransaction(transFile, rfdTransaction);
    RFDUpdateAnalytics(rfdTransaction.amount);
    transFile.close();
}

void approveAPP() {
    cout << "Approve applications !" << endl;

    fstream applicationFile(APPLICATION_FILE);
    int lineNum = 0;
    application applicationObj;

    bool continueAPV = true;
    while(!applicationFile.eof() && continueAPV) {

        applicationFile.seekp(applicationObj.lineSize * lineNum);
        RESULT getAPPResult = getApplication(applicationFile, applicationObj, lineNum);
        lineNum++;

        bool isPND = (applicationObj.status.compare(appStatusPND) == 0) ? true : false;

        if (getAPPResult != VALID_RECORD || !isPND) {continue;}
        
        displayAPP(applicationObj);

        bool done = false;
        char choice;

        displayApvMenu();
        while (!done){
            cout << "Enter choice:  ";
            cin >> choice;
            switch (choice){
            case '1':
                //approve
                cout << "Approve " << applicationObj.username << endl;

                approve(applicationFile ,applicationObj);

                done = true; break;
            case '2':
                //reject
                cout << "Reject " << applicationObj.username << endl;
                
                reject(applicationFile, applicationObj);

                done = true; break;
            default:
                cout << "Invalid choice, enter another number!";
                break;
            }
        }

        done = false;
        displayContApvMenu();
        while (!done){
            cout << "Enter choice:  ";
            cin >> choice;

            switch (choice)
            {
            case '1':
                // Continue to approve application
                done = true;
                break;
            case '2':
                // Exit back to Admin UI
                done = true;
                continueAPV = false; 
                break;
            default:
                cout << "Invalid choice, enter another number!";
                break;
            }
        }
    }

    if (applicationFile.eof()) {
        cout << endl << "End of PENDING Applications" << endl;
    }

    cout << endl << "Exiting Application Approve" << endl;
    applicationFile.close();
}