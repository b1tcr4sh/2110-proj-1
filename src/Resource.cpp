#include "../include/Resource.h"

#include <iostream>

using namespace std;

Student::Student(string _name, string _id) {
    name = _name;
    id = _id;
}

Resource::Resource(string id, string name, ResourceType type, bool available) { // constructor to pass values
    this->id = id;
    this->name = name;
    this->type = type;
    this->available = available;
}

void Resource::addToWaitingList(string studentName, string studentID){ // append to the waiting list queue
    Student* stu = new Student(studentName, studentID); // create a new student

    if (waitingListFront != NULL) {// if there are already elements in the stack (stack is not empty and head/tail are initialized),
        // stu->next = waitingListTop; // then set the new student to point to the current head (prepend to front of list/top of stack)
        waitingListBack->next = stu; // set the last element (tail) to point to this new element
        waitingListBack = stu; // then set the new element as the tail

    } else { // if the stack is not initialized (head/tail are null),
        waitingListFront = stu; // then new element is the head
        waitingListBack = waitingListFront; // and the tail
    } 
    waitingListLength++; // regardless, the list is one larger
}

void Resource::removeFromWaitingList(){ // remove the person at the front of the waiting list
    Student* temp = waitingListFront; // store the front of the queue

    if (temp->next == NULL) { // if there is only 1 item in the list,
        waitingListFront = NULL; // set head to point to nothing
        waitingListBack = NULL; // and tail
        delete temp; // then we can safely delete the last element
        return; // and exit early
    }

    // if there are more elements in the list ....
    waitingListFront = temp->next; // then set head to the next element in the queue (the front's next)
    delete temp; // now we can get rid of the previous head
    waitingListLength--; // list is one smaller
}

void Resource::displayWaitingList() { // iterate through the list and print out every student in it
    if (waitingListFront == NULL) {
        cout << endl << "Waiting list is empty." << endl; // if the list is empty, there's nothing to do
        return;        
    }

    cout << endl << "Waiting List: " << endl;

    Student* temp = waitingListFront; // temporary student variable to hold the one we are currently looking at. Could say this is like an iterator.

    for (int i = 0; i < waitingListLength; i++) {
        cout << "   " << temp->name << ": " << temp->id << endl;
        if (temp != waitingListBack) {
            temp = temp->next; // iterate to the next element if it exists
        }
    }
}