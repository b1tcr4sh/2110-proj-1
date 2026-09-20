#ifndef _RESERVATION_
#define _RESERVATION_

#include <string>

using namespace std;

class Reservation {
    public:
        int ID;
        string studentID;
        string studentName;
        string resourceID;
        string date;

        Reservation(int ID, string studentID, string studentName, string resourceID, string date);
        bool operator==(const Reservation& res);
};

#endif