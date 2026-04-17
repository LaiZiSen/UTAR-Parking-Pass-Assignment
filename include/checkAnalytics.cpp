#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iomanip>
#include <ctime>
#include "../header/txtDB.h"
#include "../header/txtPath.h"
#include "../header/generalFunc.h"

struct analyticNode {
    analytic analyticObj;
    analyticNode* nextNode;
    analyticNode* prevNode;
};

struct analyticList
{
    analyticNode* headNode;
    analyticNode* tailNode;
    analyticNode* curNode;
};


analyticNode* getAnalyticNode(fstream &file) {
    analytic analyticObj;
    getAnalytic(file, analyticObj, 0);

    analyticNode* newNode = new analyticNode;

    newNode->analyticObj = analyticObj;
    newNode->nextNode = nullptr;

    return newNode;
}

void getAnalyticList(analyticList &list) {
    fstream analyticFile(ANALYTICS_FILE);
    
    while (!analyticFile.eof()) {
        analyticNode* newNode = getAnalyticNode(analyticFile);
    
        if (list.headNode == nullptr) {
            list.headNode = newNode;
            list.tailNode = newNode;
            list.curNode = newNode;
        } else {
            newNode->prevNode = list.tailNode;
            list.tailNode->nextNode = newNode;
            list.tailNode = newNode;
        }
    }

    list.curNode = list.tailNode;
}

void printAnalysis(analytic analyticData) {

    char monthString[50];

    tm analyticDataMonth;
    analyticDataMonth.tm_year = analyticData.month / 100 -1900;
    analyticDataMonth.tm_mon = analyticData.month % 100 -1;

    strftime(monthString, 50, "%Y %b", &analyticDataMonth);

    cout << endl;
    cout << "===== Month: " << monthString << " =====" << endl;
    cout << "New User Count: " << analyticData.new_user_count << endl;
    cout << "New Application Count: " << analyticData.new_application_count << endl;
    cout << "Extension Count: " << analyticData.extension_count << endl;
    cout << "Income: " << fixed << setprecision(2) << analyticData.income << endl;
    cout << endl;

}

void checkAnalytics() {
    /*
    
    Get analytics data into double linked list

    output current month analytics

    option, next, previous, choose month, exit check analytics

    */

    analyticList analyticListObj;
    analyticListObj.curNode = nullptr;
    analyticListObj.headNode = nullptr;
    analyticListObj.tailNode = nullptr;

    fstream analyticFile(ANALYTICS_FILE);

    getAnalyticList(analyticListObj);

    char choice;
    bool done = false;
    while(!done) {
        //output analytics
        printAnalysis(analyticListObj.curNode->analyticObj);


        cout << "(1) Previous Month Record" << endl;
        cout << "(2) Next Month Record" << endl;
        cout << "(3) Quit Check Analysis" << endl << endl;

        
        bool choiceDone = false;
        while(!choiceDone) {
            choice = getChoice();
            switch (choice)
            {
            case '1':
                if (analyticListObj.curNode->prevNode != nullptr) {
                    analyticListObj.curNode = analyticListObj.curNode->prevNode;
                    choiceDone = true;
                } else {
                    cout << "There is no record for the previous month" << endl;
                }
                break;
            
            case '2':
                if (analyticListObj.curNode->nextNode != nullptr) {
                    analyticListObj.curNode = analyticListObj.curNode->nextNode;
                    choiceDone = true;
                } else {
                    cout << endl << "There is no record for the next month!!!" << endl << endl;
                }
                break;
    
            case '3':
                cout << endl << "Quiting Check Analysis" << endl << endl;
                choiceDone = true;
                done = true;
                break;
            }
        }



        // get choice
        // 1 go to previous record
        // 2 go to next record
        // 3 quit
    }
}

int main () {
    checkAnalytics();
}