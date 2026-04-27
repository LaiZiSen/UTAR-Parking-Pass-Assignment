#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include "../header/txtDB.h"
#include "../header/txtPath.h"
#include "../header/generalFunc.h"

using namespace std;

struct carPlateNode
{
    string carPlate;
    carPlateNode* prevNode;
    carPlateNode* nextNode;
};

struct carPlateList {
    carPlateNode* headNode;
    carPlateNode* tailNode;
    carPlateNode* curNode;
};

void getCarPlateList(carPlateList &list) {
    fstream userFile(USER_FILE);

    int currentMonth = getCurrYearMonth();

    while(!userFile.eof()) {
        user userObj; 
        getUser(userFile, userObj, 0);

        if (userObj.pass < currentMonth) {
            continue;
        }

        carPlateNode* newNode = new carPlateNode;
        newNode->carPlate = userObj.car_plate;

        if (list.headNode == nullptr) {
            list.headNode = newNode;
            list.tailNode = newNode;
            list.curNode = newNode;
            newNode->prevNode = nullptr;
            newNode->nextNode = nullptr;
        } else {
            newNode->prevNode = list.tailNode;
            newNode->nextNode = nullptr;
            list.tailNode->nextNode = newNode;
            list.tailNode = newNode;
        }
    }
}

void checkPass() {

    /*
    
    get all valid pass into a list

    check what carplate to check
    check

    ask if continue

    */

    carPlateList validCarPlateList;
    validCarPlateList.headNode = nullptr;
    validCarPlateList.tailNode = nullptr;
    validCarPlateList.curNode = nullptr;
    getCarPlateList(validCarPlateList);

    user userSample;

    do{
        validCarPlateList.curNode = validCarPlateList.curNode->nextNode;
    } while(validCarPlateList.curNode != nullptr);

    cout<< endl << "--------Check Vehichal Pass--------"<<endl << endl;
    while (true)
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "ENTER CARPLATE:  ";
        string carPlate = getLineInput(userSample.car_plate_Attr);
        carPlate = removeSpaces(carPlate);
        carPlate = strLengthEnforcer(carPlate, userSample.car_plate_Attr.size);
        transform(carPlate.begin(), carPlate.end(), carPlate.begin(), ::toupper);

        bool isValidCarPlate = false;
        validCarPlateList.curNode = validCarPlateList.headNode;
        
        while(validCarPlateList.curNode != nullptr && !isValidCarPlate) {
            if (carPlate.compare(validCarPlateList.curNode->carPlate) == 0) {
                isValidCarPlate = true;
            }
            validCarPlateList.curNode = validCarPlateList.curNode->nextNode;
        }        

        if (isValidCarPlate) {
            cout << endl << "PASS IS ACTIVE FOR [" << carPlate << ']' << endl << endl;
        } else {cout << endl << "PASS IS NOT ACTIVE FOR [" << carPlate << ']' << endl << endl;}

        bool loopDone = false;
        
        while(!loopDone) {

            cout << "(1) Continue checking Carplates" << endl;
            cout << "(2) Quit check pass" << endl << endl;

            char choice = getChoice();
            
            switch (choice) {
                case '1':
                    cout << endl;
                    loopDone = true;
                    break;
                case '2':
                    cout << endl << "Quiting Check Pass" << endl;
                    return;
            }
        }
    }
}