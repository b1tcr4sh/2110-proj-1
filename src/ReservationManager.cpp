#include "../include/ReservationManager.h"
#include "../include/ResourceManager.h"

#include <fstream>
#include <sstream>
#include <string>

ReservationManager::ReservationManager(ResourceManager* manager) {
    resourceManager = manager;
}

void ReservationManager::LoadFromFile() { // loads reservation data line-by-line and creates new queue reservations
    ifstream file("data/reservations.txt");
    
    while (!file.eof()) {
        string line;
        getline(file, line); // read 1 line from file

        //split line into tokens
        stringstream stream(line);

        string id;
        getline(stream, id, '|'); // get id; using "|" as delimiter

        string studentID;
        getline(stream, studentID, '|'); // get student id; using "|" as delimiter

        string studentName;
        getline(stream, studentName, '|'); // get student's name; using "|" as delimiter 

        string resourceID;
        getline(stream, resourceID, '|'); // get resource ID; using "|" as delimiter

        string date;
        getline(stream, date, '|'); // get date; using "|" as delimiter

        Create(stoi(id), studentID, studentName, resourceID, date); // pass all of this info to create a new reservation
    }
}

void ReservationManager::PrintList() { // iterate through the list and print out every element
    list<Reservation>::iterator it = reservations.begin();

    cout << "Reservation List: " << endl;

    // step through list
    for (it = reservations.begin(); it != reservations.end(); it++) {
        cout << it->ID << ": " << it->date << endl;
        cout << " Resource: " << it->resourceID << endl;
        cout << " Student: " << it->studentName << " | " << it->studentID << endl;
    }
}

void ReservationManager::Create(int ID, string studentID, string studentName, string resourceID, string date) { // creates a new reservation and enqueues it
    Reservation res(ID, studentID, studentName, resourceID, date); // create new reservation

    Resource* resource = resourceManager->FindByID(resourceID);  // find the resource

    if (resource->available) { 
        resource->available = false; // if available, mark unavailable
    } else {
        resource->addToWaitingList(studentID); //  if unavailable, add the student's ID to the waiting list of the resource they are requesting
    }

    mostRecentID = ID; // this ID is now the most recent

    reservations.push_back(res); // append to list of reservations
    cout << "added reservation for " << studentName << " with ID " <<  ID << endl;
}

void ReservationManager::Create(string studentID, string studentName, string resourceID, string date) { // creates a new reservation if we don't already have an ID
    Create(mostRecentID + 1, studentID, studentName, resourceID, date); // sets id to 1 + whatever the last ID was so IDs count up
}

Reservation ReservationManager::Search(int ID) { // search for a reservation by it's ID
    list<Reservation>::iterator it = reservations.begin();

    // step through list
    for (it = reservations.begin(); it != reservations.end(); it++) {
        if (it->ID == ID) {
            return *it; // if ID matches, then return it
        }
    }

    return *new Reservation(-1, "null", "null", "null", "null"); // if not, then return an empty reservation; this can be used for error handling
}

void ReservationManager::Cancel(int ID) { // find the reservation in the list, remove it from the list, and push it onto the stack
    Reservation res = Search(ID); // find the reservation

    canceled.push(&res); // push it onto the stack for cancelled reservations
    reservations.remove(res); // remove it from the list of reservations
} 

void ReservationManager::Restore() { // pop top of stack and add to the end of list
    Reservation* restored = canceled.top(); // get the element on top
    
    reservations.push_back(*restored); // append the element to the end of the list

    canceled.pop(); // pop it off the top of the cancelled stack
} 
