#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include "../header/txtDB.h"
#include "../header/txtPath.h"

using namespace std;

void displayApplicationDetails(application applicationDetail) {
    tm appliedPassTM;
    char appliedPassStr[50];
    appliedPassTM.tm_year = applicationDetail.pass_application / 100 - 1900;
    appliedPassTM.tm_mon = applicationDetail.pass_application % 100 -1;
    strftime(appliedPassStr, 50, "%b %Y", &appliedPassTM);

    cout << endl;
    cout<<left<<setw(20)<<"Name"<<": "<<trim(applicationDetail.username)<<endl;
    cout<<left<<setw(20)<<"Status"<<": "<<trim(applicationDetail.status)<<endl;
    cout<<left<<setw(20)<<"Pass Applied"<<": "<<appliedPassStr<<endl;
    cout<<left<<setw(20)<<"Car plate applied"<<": "<<trim(applicationDetail.car_plate)<<endl;
}

void approveApplication() {
    fstream applicationFile(APPLICATION_FILE);
    fstream userFile(USER_FILE);

    int lineNum = 0;
    application applicationObj;
    while(applicationFile) {
        RESULT fetchResult = getApplication(applicationFile, applicationObj, lineNum);
        lineNum++;

        cout << lineNum << '\t';

        if (fetchResult == INVALID_RECORD) {
            continue;
        }

        if(fetchResult == END_OF_FILE) {
            cout << "END OF FILE";
            break;
        }

        if (applicationObj.status == appStatusPND) {
            cout << endl << "THERE ARE STILL PENDING APPLICATIONS TO BE APPROVED!!!" << endl;
            return;
        }

        user userPlaceholder;
        if (!searchUser(userPlaceholder, applicationObj.username)) {
            cout << '[' <<applicationObj.username << ']';
            cout << endl << "THERE IS A UNKNOWN USER AMONG THE APPLICANTS" << endl;
            return;
        }

    }

    applicationFile.clear();
    applicationFile.seekp(0, fstream::beg);

    application applicationList[lineNum-1];

    for (int i = 0; i < lineNum-1; i++) {
        if(getApplication(applicationFile, applicationList[i], i) == INVALID_RECORD) {
            applicationList[i].status = appStatusRJT;
        }
    }

    for (int i =0; i < lineNum-1; i++) {
        user userObj;

        if (
            searchUser(userObj, applicationList[i].username) && 
            applicationList[i].status == appStatusAPV
        ) {
            string passStr = strLengthEnforcer(to_string(applicationList[i].pass_application), applicationList[i].pass_application_Attr.size);

            edit(userFile, userObj.line, userObj.lineSize, userObj.car_plate_Attr, applicationList[i].car_plate);
            edit(userFile, userObj.line, userObj.lineSize, userObj.pass_Attr, passStr);
        } 
    }

    applicationFile.close();
    applicationFile.open(APPLICATION_FILE, std::ios::out | std::ios::trunc);

    applicationFile.write(strLengthEnforcer("", applicationObj.lineSize-2).c_str(), applicationObj.lineSize -2);

    cout << endl << "APPROVED APPLICATIONS HAVE BEEN APPLIED" << endl;
}



int main () {
    approveApplication();
}