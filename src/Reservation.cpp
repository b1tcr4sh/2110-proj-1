#include "../include/Reservation.h"

Reservation::Reservation(int ID, string studentID, string studentName, string resourceID, string date) {
    this->ID = ID;
    this->studentID = studentID;
    this->studentName = studentName;
    this->resourceID = resourceID;
    this->date = date;
}

bool Reservation::operator==(const Reservation& r) { // == operator overlaod for list::remove()
    if (ID == r.ID && studentID == r.studentID && studentName == r.studentName && resourceID == r.resourceID && date == r.date) {
        return true; // if all values are the same, they are the same
    } else {
        return false;
    }
}