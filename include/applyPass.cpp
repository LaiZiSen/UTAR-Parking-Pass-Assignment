#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <limits>
#include <bits/stdc++.h>
#include "../header/txtDB.h"
#include "../header/txtPath.h"
#include "../header/generalFunc.h"
#include "../header/settings.h"


bool decideCarPlate(application &applicationDetail, user &userData, int curYYYYMM) {
    char choice;

    cout << "Do you want to RENEW PASS for [" << trim(userData.car_plate) << "]?" << endl << endl;
    
    bool decided = false;
    while (!decided) {
        string action = (userData.pass == 0) ? "APPLY" : "RENEW";

        cout << "(1) " << action <<" FOR [" << trim(userData.car_plate) << ']' <<  endl;
        cout << "(2) APPLY PASS for new carplate" << endl << endl;
        choice = getChoice();
        string newCarPlate = "";

        switch (choice) {
            case '1':
                applicationDetail.car_plate = userData.car_plate;

                if (userData.pass < curYYYYMM) {
                    applicationDetail.type = appTypeAPL;
                } else applicationDetail.type = appTypeRNW;

                if ((userData.pass) >= (curYYYYMM+3)) {
                    return false;
                }

                return true;

            case '2':
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                while(newCarPlate.length() == 0) {
                    cout << endl << "Enter a new carplate:  ";

                    newCarPlate = trim(getLineInput(userData.car_plate_Attr));
                    transform(newCarPlate.begin(), newCarPlate.end(), newCarPlate.begin(), ::toupper);
                    newCarPlate = strLengthEnforcer(newCarPlate, userData.car_plate_Attr.size);


                    if (newCarPlate.length() > 0) {
                        if (!searchCarPlate(newCarPlate)) {
                            applicationDetail.car_plate = newCarPlate;
                            break;
                        } else {
                            cout << endl << "CAR PLATE REGISTER IN ANOTHER USER, ENTER AGAIN" << endl;
                            newCarPlate = "";
                        }

                    } else {
                        cout << "INVALID CARPLATE, ENTER AGAIN" << endl; 
                    };
                }
                applicationDetail.type = appTypeAPL;

                return true;
        }
    }
}

void displayApplicationDetails(application applicationDetail, user userData) {
    tm curPassTM;
    char curPassStr[50];
    curPassTM.tm_year = userData.pass/100 - 1900;
    curPassTM.tm_mon = userData.pass % 100 -1;
    strftime(curPassStr, 50, "%b %Y", &curPassTM);
    
    tm appliedPassTM;
    char appliedPassStr[50];
    appliedPassTM.tm_year = applicationDetail.pass_application / 100 - 1900;
    appliedPassTM.tm_mon = applicationDetail.pass_application % 100 -1;
    strftime(appliedPassStr, 50, "%b %Y", &appliedPassTM);

    cout << endl;
    cout<<left<<setw(20)<<"Name"<<": "<<trim(applicationDetail.username)<<endl;
    cout<<left<<setw(20)<<"Current Pass"<<": "<<curPassStr<<endl;
    cout<<left<<setw(20)<<"Pass Applied"<<": "<<appliedPassStr<<endl;
    cout<<left<<setw(20)<<"Car plate applied"<<": "<<trim(applicationDetail.car_plate)<<endl;
}

bool confirmPayment(transaction applicationTransaction) {
    cout << "Total amount is [" << applicationTransaction.amount << ']' << endl;
    cout << "(1) Pay" << endl;
    cout << "(2) Cancel application" << endl;

    char choice;

    while (true) {
        choice = getChoice();

        switch (choice)
        {
        case '1':
            return true;
        
        case '2':
            return false;

        }
    }

}

void endProgram() {
    cout << endl <<  "Enter to return to User Menu";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();

    return;
}

void APPLUpdateAnalytics (int monthsApplied, string applicationType, float amount) {
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

    string extension_count_STR = to_string(curMonAnalytics.extension_count + monthsApplied);
    string income_STR = floatToStr(curMonAnalytics.income + amount);

    string new_application_STR = to_string(curMonAnalytics.new_application_count + (applicationType.compare(appTypeAPL) == 0));


    cout << extension_count_STR + income_STR + new_application_STR << endl;

    fstream analyticFile(ANALYTICS_FILE);

    edit(analyticFile, curMonAnalytics.line, curMonAnalytics.lineSize, curMonAnalytics.extension_count_Attr, extension_count_STR);
    edit(analyticFile, curMonAnalytics.line, curMonAnalytics.lineSize, curMonAnalytics.income_Attr, income_STR);
    edit(analyticFile, curMonAnalytics.line, curMonAnalytics.lineSize, curMonAnalytics.new_application_count_Attr, new_application_STR);

    analyticFile.close();
}

void applyPass(user userData) {
    application applicationDetail;
    transaction applicationTransaction;
    fstream applicationFile(APPLICATION_FILE);
    fstream transactionFile(TRANSACTION_FILE);

    /*
    
    information needs = [
        std::string username;
        int pass_application;
        std::string car_plate;
        std::string type;
        std::string status;
        int date;
    ]

    Add 
        username
        date
        status

    Car Plate
        ask if apply with old car plate or new car plate
            if new car plate, ask for car plate and declare TYPE as APLICATION
        else use old car plate

    Apply month
        if carPlate new or Pass < cur month, 
            declare TYPE as APPLICATION
            allowed to apply for 3 months
        if pass >= cur month + 3
            declare vehichal has applied for maximum number of pass and 
            application attempt is voided, 
            return to main menu
        Tell user how many months they can apply for
        Get the months they want to apply for

    Ask for payment, calculating the amount required
    if user pays, 
        add amount to transaction and add application info to application.txt
    if not
        declare application voided and return to main menu


    declare application succeeded and return to main menu
    
    */

    applicationDetail.username = userData.name;
    applicationDetail.date = getCurrYYMMDD();
    applicationDetail.status = appStatusPND;

    int curYYYYMM = getCurrYearMonth();

    if(searchApplication(applicationFile, userData.name)) {
        cout << endl << "YOU HAVE ALREADY SUBMITTED AN APPLICATION, GO TO CHECK APPLICATION" << endl;
        
        cout << endl <<  "Enter to return to User Menu";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();

        return;
    }
    applicationFile.clear();

    if (!decideCarPlate(applicationDetail, userData, curYYYYMM)) {
        cout << endl << "YOUR CAR PLATE ALREADY HAS THE MAXIMUM PASS LENGTH, APPLICATION VOIDED" << endl;
        
        cout << endl <<  "Enter to return to User Menu";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();

        return;

    }

    int appliedMonths = 0;
    int monthsAllowed;

    if (applicationDetail.type.compare(appTypeAPL) == 0) {
        monthsAllowed = 3;
    } else {
        monthsAllowed = curYYYYMM + 3 - userData.pass;
    }

    while (true){
        cout << endl << "Enter the amount of months of parking pass you would like to purchase:  ";
        cin >> appliedMonths;

        if (appliedMonths <= 0 || appliedMonths > monthsAllowed) {
            cout << endl << "INVALID AMOUNT OF PARKING PASS, ENTER AGAIN" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else break;
    }

    applicationDetail.pass_application = (applicationDetail.type == appTypeAPL) 
        ? curYYYYMM + appliedMonths 
        : userData.pass + appliedMonths;
    applicationTransaction.date = getCurrYYMMDD();
    applicationTransaction.username = userData.name;
    applicationTransaction.trans_type = transTypeINC;
    applicationTransaction.amount = round(appliedMonths * parkingPassPrice * 10) / 10.0;


    displayApplicationDetails(applicationDetail, userData);

    if (confirmPayment(applicationTransaction)) {
        writeTransaction(transactionFile, applicationTransaction);
        writeApplication(applicationFile, applicationDetail);

        APPLUpdateAnalytics(appliedMonths, applicationDetail.type, applicationTransaction.amount);

        cout << endl << "TRANSACTION SUCCEED, APPLICATION SUBMITTED" << endl;
    } else {
        cout << endl <<  "TRANSACTION FAILED, APPLICATION VOIDED" << endl;
    }
    
    cout << endl <<  "Enter to return to User Menu";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
}

// int main () {

//     fstream userFile(USER_FILE);
//     user userobj;

//     getUser(userFile, userobj, 0);

//     applyPass(userobj);
// }