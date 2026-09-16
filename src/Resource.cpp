#include "../include/Resource.h"

Resource::Resource(string id, string name, ResourceType type, bool available) {
    this->id = id;
    this->name = name;
    this->type = type;
    this->available = available;
}

void Resource::addToWaitingList(string studentId){
    WaitingList.push(studentId);
}

void Resource::removeFromWaitingList(){
    WaitingList.pop();
}

void Resource::displayWaitingList() {
    queue<string> copy = WaitingList;

    cout << "Waiting List: " << endl;

    while (!copy.empty()) {
        cout << copy.front() << endl;
        copy.pop();
    }
        cout << endl;
}