#include "../include/Resource.h"

#include <iostream>

using namespace std;

Resource::Resource(string id, string name, ResourceType type, bool available) { // constructor to pass values
    this->id = id;
    this->name = name;
    this->type = type;
    this->available = available;
}

void Resource::addToWaitingList(string studentName){ // append to waiting list queue
        WaitingList.emplace(studentName);
}

void Resource::removeFromWaitingList(){ // remove the person at the front of the waiting list
    WaitingList.pop();
}

void Resource::displayWaitingList() { // iterate through the list and print out every student in it
    if (WaitingList.empty()) {
        cout << endl << "Waiting list is empty." << endl; // if the list is empty, there's nothing to do
        return;
    }

    queue<string> copy = WaitingList; // make a copy of the queue so we can iterate through it

    cout << endl << "Waiting List: " << endl;

    while (!copy.empty()) { // iterate through queue and print out everyone in it
        cout << copy.front() << endl;
        copy.pop();
    }
        cout << endl;
}