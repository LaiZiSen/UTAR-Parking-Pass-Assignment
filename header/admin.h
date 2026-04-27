#ifndef admin_H
#define admin_H

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
void approveAPP();
void applyApplications();
void adminUI(admin adminData);

#endif