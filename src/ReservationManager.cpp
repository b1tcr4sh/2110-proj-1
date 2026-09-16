#include "../include/ReservationManager.h"
#include "../include/ResourceManager.h"

#include <fstream>
#include <sstream>
#include <string>


void ReservationManager::LoadFromFile(ResourceManager manager) { // loads reservation data line-by-line and creates new queue reservations
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

        this->Create(stoi(id), studentID, studentName, resourceID, date, manager);
    }
}

void ReservationManager::PrintList() {
    Reservation* current = head;

    // step through list
    while (current != tail) {
        cout << ""; // print reservation information
        current = current->next;
    }
}

void ReservationManager::Create(int ID, string studentID, string studentName, string resourceID, string date, ResourceManager manager) { // creates a new reservation and enqueues it
    Reservation res(ID, studentID, studentName, resourceID, date); // create new reservation


    Resource* resource = manager.FindByID(resourceID);  // find the resource

    if (resource->available) { 
        resource->available = false; // if available, mark unavailable
    } else {
        resource->addToWaitingList(studentID); //  if available, mark unavailable ;  awaiting maddie
    }


    mostRecentID = ID;

    Append(&res); // append to end of list
}

void ReservationManager::Create(string studentID, string studentName, string resourceID, string date, ResourceManager manager) { // creates a new reservation and enqueues it
    Create(mostRecentID + 1, studentID, studentID, resourceID, date, manager); // sets id to 1 + whatever the last ID was so IDs count up
}

void ReservationManager::Cancel(int ID) { // find the reservation in the list, remove it from the list, and push it onto the stack
    int pos = FindByID(ID);
    
    int i = 0;
    Reservation* current = head;
    while (current->ID != ID) { // get element with matching id
        current = current->next;
    }

    canceled.push(current);

} 

void ReservationManager::Restore() { // pop top of stack and add to the end of list
    Reservation* restored = canceled.top(); // get the element on top
    
    Append(restored); // append the element to the end of the list

    canceled.pop(); // pop it off the top of the cancelled stack
} 

int ReservationManager::FindByID(int id) { // traverse list until element is found; return -1 if not found
    Reservation* current = head;
    int i = 0;

    while (current != tail) {
        if (current->ID == id) {
            return i; // found; return position in list
        }
        current = current->next;
        i++;
    }
    return -1; // not found
}

void ReservationManager::Append(Reservation* res) {
    tail->next = res; // point last element to this one
    tail = res; // point tail at this one
}
