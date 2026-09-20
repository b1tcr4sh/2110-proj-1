#include "../include/Reservation.h"

Reservation::Reservation(int ID, string studentID, string studentName, string resourceID, string date) {
    this->ID = ID;
    this->studentID = studentID;
    this->studentName = studentName;
    this->resourceID = resourceID;
    this->date = date;
}

// bool Reservation::operator==(const Reservation& l, const Reservation& r) {
//     if (l.ID == r.ID && l.studentID == r.studentID && l.studentName == r.studentID && l.resourceID == r.resourceID && l.date == r.date) {
//         return true;
//     } else {
//         return false;
//     }
// }