#ifndef txtDB_H
#define txtDB_H

#include <string>
#include <fstream>

enum RESULT {
    VALID_RECORD,
    INVALID_RECORD,
    END_OF_FILE
};

struct attribute
{
    int pos;
    int size;

    attribute(int pos, int size) : pos(pos), size(size) {};
};

struct admin {
    static const attribute name_Attr;
    static const attribute pwd_Attr;
    static const int lineSize;
    
    int line;
    std::string name;
    std::string pwd;
};

struct user {
    static const attribute name_Attr;
    static const attribute pwd_Attr;
    static const attribute faculty_Attr;
    static const attribute pass_Attr;
    static const attribute car_plate_Attr;
    static const int lineSize;

    int line;
    std::string name;
    std::string pwd;
    std::string faculty;
    int pass;
    std::string car_plate;
};

struct application {
    static const attribute username_Attr;
    static const attribute pass_application_Attr;
    static const attribute car_plate_Attr;
    static const attribute type_Attr;
    static const attribute status_Attr;
    static const attribute date_Attr;
    static const int lineSize;

    int line;
    std::string username;
    int pass_application;
    std::string car_plate;
    std::string type;
    std::string status;
    int date;
};

struct transaction {
    static const attribute username_Attr;
    static const attribute trans_type_Attr;
    static const attribute date_Attr;
    static const attribute amount_Attr;
    static const int lineSize;

    int line;
    std::string username;
    std::string trans_type;
    int date;
    float amount;
};

struct analytic {
    static const attribute month_Attr;
    static const attribute new_user_count_Attr;
    static const attribute new_application_count_Attr;
    static const attribute extension_count_Attr;
    static const attribute pass_price_Attr;
    static const attribute income_Attr;
    static const int lineSize;

    int line;
    int month;
    int new_user_count;
    int new_application_count;
    int extension_count;
    float pass_price;
    float income;
};

void writeAdmin(std::fstream &file, admin input);
void writeUser(std::fstream &file, user input);
void writeApplication(std::fstream &file, application input);
void writeTransaction(std::fstream &file, transaction input);
void writeAnalytic(std::fstream &file, analytic input);

RESULT getAdmin(std::fstream&, admin&, int);
RESULT getUser(std::fstream&, user&, int);
RESULT getApplication(std::fstream&, application&, int);
RESULT getTransaction(std::fstream&, transaction&, int);
RESULT getAnalytic(std::fstream&, analytic&, int);

bool edit (std::fstream &file, int line, int lineSize, attribute editAttribute, std::string editValue);
bool removeRecord(std::fstream &file, int line, int lineSize);

std::string  strLengthEnforcer(std::string targetStr, int fillSize);
std::string trim(const std::string& input);

#endif