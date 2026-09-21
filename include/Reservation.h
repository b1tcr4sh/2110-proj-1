#ifndef _RESERVATION_
#define _RESERVATION_

#include <string>

using namespace std;

class Reservation {
    public:
        int ID; // ID of reservation; they are ints so we can increment them each time a new reservation is created
        string studentID; // student id of student creating the reservation
        string studentName; // student's name
        string resourceID; // resource the reservation is requesting
        string date; // date of reservation creation

        Reservation(int ID, string studentID, string studentName, string resourceID, string date);
        bool operator==(const Reservation& res);
};

#endif