#include "../include/ReservationManager.h"
#include "../include/ResourceManager.h"

#include <fstream>
#include <sstream>
#include <string>



void ReservationManager::LoadFromFile(ResourceManager manager) { // loads reservation data line-by-line and creates new queue reservations
    ifstream file("data/reservations.txt");
    
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

        Create(stoi(id), studentID, studentName, resourceID, date, manager);
    }
}

void ReservationManager::PrintList() {
    list<Reservation>::iterator it = reservations.begin();

    cout << "Reservation List: " << endl;

    // step through list
    for (it = reservations.begin(); it != reservations.end(); it++) {
        cout << it->ID << ": " << it->date << endl;
        cout << " Resource: " << it->resourceID << endl;
        cout << " Student: " << it->studentName << " | " << it->studentID << endl;
    }
}

void ReservationManager::Create(int ID, string studentID, string studentName, string resourceID, string date, ResourceManager resourceManager) { // creates a new reservation and enqueues it
    Reservation res(ID, studentID, studentName, resourceID, date); // create new reservation

    Resource* resource = resourceManager.FindByID(resourceID);  // find the resource

    if (resource->available) { 
        resource->available = false; // if available, mark unavailable
    } else {
        resource->addToWaitingList(studentID); //  if available, mark unavailable
    }

    mostRecentID = ID;

    reservations.push_back(res);
    cout << "added reservation for " << studentName << " with ID " <<  ID << endl;
}

void ReservationManager::Create(string studentID, string studentName, string resourceID, string date, ResourceManager manager) { // creates a new reservation and enqueues it
    Create(mostRecentID + 1, studentID, studentName, resourceID, date, manager); // sets id to 1 + whatever the last ID was so IDs count up
}

Reservation ReservationManager::Search(int ID) {
    list<Reservation>::iterator it = reservations.begin();

    // step through list
    for (it = reservations.begin(); it != reservations.end(); it++) {
        if (it->ID == ID) {
            return *it;
        }
    }

    return *new Reservation(-1, "null", "null", "null", "null");
}

void ReservationManager::Cancel(int ID) { // find the reservation in the list, remove it from the list, and push it onto the stack
    Reservation res = Search(ID);


    canceled.push(&res);
    reservations.remove(res);
} 

void ReservationManager::Restore() { // pop top of stack and add to the end of list
    Reservation* restored = canceled.top(); // get the element on top
    
    reservations.push_back(*restored); // append the element to the end of the list

    canceled.pop(); // pop it off the top of the cancelled stack
} 
