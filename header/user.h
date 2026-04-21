#ifndef USERFUNCTION_H
#define USERFUNCTION_H

#include <string>
using namespace std;

// Function declarations (prototypes only)
string userLogin();
void userUI(user userData);
void checkAppStatus(user userObj);
void checkTransHistory(string username);
void userProfile(string username);  //creative feature
void applyPass(user userData);

#endif