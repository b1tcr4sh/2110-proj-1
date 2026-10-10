#include "../include/ReservationManager.h"
#include "../include/ResourceManager.h"

#include <cstddef>
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

void ReservationManager::PrintActiveReservations() {
    cout << "Active Reservations: " << endl;
    Reservation* temp = head; // get the top

    do {
        cout << temp->ID << ": " << temp->date << endl;
        cout << " Resource: " << temp->resourceID << endl;
        cout << " Student: " << temp->studentName << " | " << temp->studentID << endl;

        // if (temp->next == NULL) { // if the next element doesn't exist (this should be redundant), 
        //     return; // then exist early so we don't iterate
        // }
        temp = temp->next; // otherwise, step to the next element
    } while (temp != tail);

    cout << tail->ID << ": " << tail->date << endl;
        cout << " Resource: " << tail->resourceID << endl;
        cout << " Student: " << tail->studentName << " | " << tail->studentID << endl;
}

int ReservationManager::Create(int ID, string studentID, string studentName, string resourceID, string date) { // creates a new reservation and enqueues it    
    Reservation* res = new Reservation(ID, studentID, studentName, resourceID, date); // create new reservation
    // reservations.push_back(res); // append to list of reservations
    addToList(res); // append to the list of reservations
    
    Resource* resource = resourceManager->FindByID(resourceID);  // find the resource

    if (resource == NULL) { // if the resource wasn't found
        return -1; // then, exit early and abort
    }

    if (resource->available) { 
        resource->available = false; // if available, mark unavailable
    } else {
        resource->addToWaitingList(studentName, studentID); //  if unavailable, add the student's name to the waiting list of the resource they are requesting
    }

    mostRecentID = ID; // this ID is now the most recent
    return ID;
}

int ReservationManager::Create(string studentID, string studentName, string resourceID, string date) { // creates a new reservation if we don't already have an ID
    return Create(mostRecentID + 1, studentID, studentName, resourceID, date); // sets id to 1 + whatever the last ID was so IDs count up
}

Reservation* ReservationManager::Search(int ID) { // search for a reservation by it's ID
    Reservation* temp = head;

    while (temp != tail) { // until the correct element is found, or we reach the end
        if (temp->next->ID == ID) { // if the next element is the correct element,
            return temp->next; // then we can return it
        }

        temp = temp->next; // iterate through elements
    } 

    cout << ID << " not found in list..." << endl;
    return NULL;
}

void ReservationManager::Cancel(int ID) { // find the reservation in the list, remove it from the list, and push it onto the stack
    Reservation* res = Search(ID); // find the reservation
    cout << "found reservation " << res->ID << endl;

    res = removeFromList(res); // remove it from the list of reservations
    pushCanceled(res); // push it onto the stack for cancelled reservations
} 

Reservation ReservationManager::Restore() { // pop top of stack and add to the end of list
    if (canceledTop == NULL) {
        cout << "There are no canceled reservations to restore." << endl;
        return Reservation(-1, "", "", "", "");
    }

    Reservation* res = popCanceled(); // pop off the top of the cancelled stack
    addToList(res); // append it to the end of the list

    return *res;
} 

void ReservationManager::addToList(Reservation* res) {
        if (head != NULL) { // if list already has elements in it,
            tail->next = res; // then append the element to the end of list
            tail = res; // and make it the end of the list
        } else { // if the list is empty,
            head = res; // then make the new element the first in the list
            tail = head; // and last
        }
        listLength++; // list is one longer
}

Reservation* ReservationManager::removeFromList(Reservation* res) {
    Reservation* temp = head;

    if (temp == NULL) {
        // list is empty
        cout << "list is empty, cannot remove" << endl;
        return NULL;
    }
    
    if (temp->ID == res->ID) { // if the element we're looking to remove is the head,
        if (temp->next != NULL) { // and if the list is not only one element long,
            head = temp->next; // then, set the head to the predecessor of the element we're looking for
            temp->next = NULL; // and exclude it from the list
            return temp; // then we can return it
        } else { // otherwise, the head (and tail) is the only element in the list
            temp->next = NULL; // se we exclude it from the list
            head = NULL; // and deinitialize the list by making the head null
            tail = NULL;  // and the tail
            return temp; // then we can return the removed element
        }

    }

    while (temp != tail) { // Otherwise, loop until the correct element is found, or we reach the end
        if (temp->next->ID == res->ID) { // if the next element is the correct element,

            if (temp->next != tail) { // if the found element is not the tail,
                temp->next = temp->next->next; // then it has a predecessor, and we can repair the reference
            } 
            res->next = NULL; // and regardless, the found element should not point into the list
            return res; // then we can return it, so it can be pushed onto the stack
        }

        temp = temp->next; // iterate through elements
    } 

    cout << res->ID << " not found in list..." << endl;
    return NULL;
}

void ReservationManager::pushCanceled(Reservation* res) {
    if (canceledTop != NULL) {// if there are already elements in the stack (stack is not empty and head/tail are initialized),
        res->next = canceledTop; // then set the new element to point to the current head (prepend to front of list/top of stack)
        canceledTop = res; // then set the new element as the head

    } else { // if the stack is not initialized (head/tail are null),
        canceledTop = res; // then new element is the head
        canceledBottom = canceledTop; // and the tail
    } 
    canceledLength++; // regardless, the stack is one larger
}

Reservation* ReservationManager::popCanceled() {
    Reservation* temp = canceledTop; // store the top of the stack

    if (temp == NULL) {  // if the list is empty (not initiailized),
        cout << "The stack of cancellations is empty" << endl;
        return NULL;
    }

    if (temp->next == NULL) { // if there is only 1 item in the list,
        canceledTop = NULL; // deinitialize the stack by setting the head to point to nothing
        canceledBottom = NULL; // and tail
        return temp; // then exit early and return
    }

    // if there are more elements in the list ....
    canceledTop = temp->next; // then set head to the next element in the stack (the top's next)
    canceledLength--; // and make the list is one smaller

    temp->next = NULL; // exclude from the list 
    return temp; // and return it
}

Reservation ReservationManager::PeekMostRecentCancellation() {
    if (canceledTop == NULL) { // if the list is empty, return a false reservation
        return Reservation(-1, "none", "none", "none", "none"); 
    }

    return *canceledTop; // otherwise, just return a copy of the top of the stack
}