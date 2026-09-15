#include "../include/ReservationManager.h"

#include <fstream>
#include <sstream>
#include <string>


void ReservationManager::LoadFromFile() { // loads reservation data line-by-line and creates new queue reservations
    ifstream file("reservations.txt");
    
    while (!file.eof()) {
        string line;
        getline(file, line); // read 1 line from file

        //split line into tokens
        stringstream stream(line);

        string id;
        getline(stream, id, '|');

        string studentID;
        getline(stream, studentID, '|');

        string studentName;
        getline(stream, studentName, '|');

        string resourceID;
        getline(stream, resourceID, '|');

        string date;
        getline(stream, date, '|');

        this->Create(stoi(id), studentID, studentName, resourceID, date);
    }
}

void ReservationManager::PrintQueue() {

}

void ReservationManager::Create(int ID, string studentID, string studentName, string resourceID, string date) { // creates a new reservation and enqueues it
    Reservation res(ID, studentID, studentName, resourceID, date); // create new reservation

    mostRecentID = ID;

    reservations.push(res); // push it onto the queue
}

void ReservationManager::Create(string studentID, string studentName, string resourceID, string date) { // creates a new reservation and enqueues it
    Create(mostRecentID + 1, studentID, studentID, resourceID, date); // sets id to 1 + whatever the last ID was so IDs count up
}

void ReservationManager::Cancel(int ID) {} // 4 maddie

int ReservationManager::Restore() {return 0;} // 4 maddie