#ifndef checkanalytics_H
#define checkanalytics_H

#include "txtDB.h"

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

void checkAnalytics();

#endif