#ifndef login_H
#define login_H

#include "txtDB.h"
#include <string>

bool loginUser(user&);
bool loginAdmin(admin&);
bool searchUser(user &outputUser, std::string inputName);
bool searchAdmin(admin &outputAdmin, std::string inputName);

#endif