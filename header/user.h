#ifndef USERFUNCTION_H
#define USERFUNCTION_H

#include <string>
using namespace std;

// Function declarations (prototypes only)
string userLogin();
void userUI(string username);
void checkAppStatus(string username);
void checkTransHistory(string username);
void userProfile(string username);  //creative feature

#endif