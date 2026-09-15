#include "../include/Reservation.h"

Reservation::Reservation(int ID, string studentID, string studentName, string resourceID, string date) {
    this->ID = ID;
    this->studentID = studentID;
    this->studentName = studentName;
    this->resourceID = resourceID;
    this->date = date;
}