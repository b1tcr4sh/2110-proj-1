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

void Resource::addToWaitingList(string studentName, string studentID){ // append to waiting list queue
    Student* stu = new Student(studentName, studentID); // create a new student

    if (waitingListTop != NULL) {// if there are already elements in the stack (stack is not empty and head/tail are initialized),
        cout << waitingListTop->name << " is at the top" << endl;

        cout << "adding " << stu->name << " to list" << endl;
        stu->next = waitingListTop; // then set the new student to point to the current head (prepend to front of list/top of stack)
        waitingListTop = stu; // then set the new student as the head

    } else { // if the stack is not initialized (head/tail are null),
        cout << "init list with " << stu->name << endl;
        waitingListTop = stu; // then new element is the head
        waitingListBottom = waitingListTop; // and the tail
    } 
    waitingListLength++; // regardless, the list is one larger
}

void Resource::removeFromWaitingList(){ // remove the person at the front of the waiting list
    Student* temp = waitingListTop; // store the top of the stack

    if (temp->next == NULL) { // if there is only 1 item in the list,
        waitingListTop = NULL; // set head to point to nothing
        waitingListBottom = NULL; // and tail
        delete temp; // then we can safely delete the last element
        return; // and exit early
    }

    // if there are more elements in the list ....
    waitingListTop = temp->next; // then set head to the next element in the stack (the top's next)
    delete temp; // now we can get rid of the previous top
    waitingListLength--; // list is one smaller
}

void Resource::displayWaitingList() { // iterate through the list and print out every student in it
    if (waitingListTop == NULL) {
        cout << endl << "Waiting list is empty." << endl; // if the list is empty, there's nothing to do
        return;        
    }

    cout << endl << "Waiting List: " << endl;

    Student* temp = waitingListTop; // temporary student variable to hold the one we are currently looking at. Could say this is like an iterator.

    for (int i = 0; i < waitingListLength; i++) {
        cout << "   " << temp->name << ": " << temp->id << endl;
        if (temp != waitingListBottom) {
            temp = temp->next; // iterate to the next element if it exists
        }
    }
}