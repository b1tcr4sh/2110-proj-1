#include "../include/ResourceManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

void ResourceManager::PrintList() { // print the list of resources
    cout << endl << "Resources: " << endl << endl;

    for (unsigned int i = 0; i < existingResources.size(); i++) { // iterate through the list
        Resource e = existingResources.at(i);

        cout << e.id << " | " << e.name << " | " << ResourceTypeToString(e.type) << " | " << (e.available ? "available" : "unavailable") << endl;
    }
}

bool ResourceManager::Sort() {
    if (existingResources.empty()) {
        return false;

    }
    
    MergeSort(0, existingResources.size() - 1);
    return true;

}

void ResourceManager::MergeSort(int left, int right) {
    if (left >= right) {
        return;

    }
    int middle = left + (right - left) / 2;
    MergeSort(left, middle);
    MergeSort(middle + 1, right);

    Merge(left, middle, right);

}

void ResourceManager::Merge(int left, int middle, int right) {
    vector<Resource> temp;

    int i = left;
    int j = middle + 1;
    

    while (i <= middle && j <= right) {
        if (existingResources.at(i).name <= existingResources.at(j).name) {
            temp.push_back(existingResources.at(i));
            i++;

        }

        else {
            temp.push_back(existingResources.at(j));
            j++;

        }
    }

    while (i <= middle) {
        temp.push_back(existingResources.at(i));
        i++;

    }

    while (j <= right) {
        temp.push_back(existingResources.at(j));
        j++;

    }

    for (unsigned int k = 0; k < temp.size(); k++) {
        existingResources.at(left + k) = temp.at(k);

    }
}

void ResourceManager::LoadFromFile() { // load from file
    ifstream file("data/resources.txt"); // create file stream


    while (!file.eof()) {        
        string line;
        getline(file, line); // read 1 line from file


        // split line into tokens
        stringstream stream(line);

        string id;
        getline(stream, id, '|'); // get id of resource; delimited by "|"

        string name;
        getline(stream, name, '|'); // get name of resource; delimited by "|"

        string typeString;
        getline(stream, typeString, '|'); // get type of resource; delimited by "|"

        string availability;
        getline(stream, availability, '|'); // get availability of resource; delimited by "|"

        ResourceType type;
        if (typeString == "Study Room") type = Study_Room;
        else if (typeString == "Laptop") type = Laptop;
        else if (typeString == "Calculator") type = Calculator;
        else if (typeString == "Lab Equipment") type = Lab_Equipment;
        else if (typeString == "Tutoring Appointment") type = Tutoring_Appointment;
        else {
            cout << "Was unable to read type ( " << typeString << " ) for " << id << endl;
        }


        // handle parsing availability into bool
        bool available;
        if (availability == "Available") { 
            available = true;
        } else if (availability == "Unavailable") { 
            available = false;
        } else {
            cout << "Was unable to read availability ( " << availability << " ) for " << id << endl;
        }

        Resource resource(id, name, type, available); // create a new resource object

        existingResources.push_back(resource); // push it into the vector

    }
}

Resource* ResourceManager::FindByID(string ID) { // find a resource in the vector by it's ID
    for (unsigned int i = 0; i < existingResources.size(); i++) { // iterate through vector
        if (existingResources.at(i).id == ID) { 
            return &existingResources.at(i); // if ID matches, return it
        }
    }

    return NULL; // if we were unable to find it, return null; for error handling
}

void ResourceManager::GenerateReport() {
    cout << endl << "==== SYSTEM REPORTS ====" << endl;

    // resource utilization section:
    // the resource and the how many reservations the item has

    cout << endl << "==== Resource Utillization ==== " << endl;
    

    for (unsigned int i = 0; i < existingResources.size(); i++) {
        cout << existingResources.at(i).name << " has " << existingResources.at(i).reservationCount << " reservations." << endl;
    }

        // the most requested resoruces: 
        // focused on which resource has the most reservations / requests

    cout << endl << "==== The most Requested Resources ==== " << endl;

    int maxReservations = 0;
    string mostRequestedResource = "";

    for (unsigned int i = 0; i < existingResources.size(); i++) {
        if (existingResources.at(i).reservationCount > maxReservations) {
            maxReservations = existingResources.at(i).reservationCount;
        }
    }
    cout << endl << "Most Requested Resource(s) with " << maxReservations << " reservations:" << endl;
    for (unsigned int i = 0; i < existingResources.size(); i++) { // in case there are multiple with the same greatest number 
        if (existingResources.at(i).reservationCount >= maxReservations) {
            cout << "   " << existingResources.at(i).name << endl;
        }
    }

    // waiting-list stats section:
    // number of stutdents waiting for the resoruce given
    // report needs to be gernerated by using the wait listing data already given
    cout << endl << "==== Waiting List Stats: ====" << endl;
    for (unsigned int i = 0; i < existingResources.size(); i++) {
        cout << existingResources.at(i).name << ": " << existingResources.at(i).waitingListLength << " students waiting." << endl;
    }
}

Resource ResourceManager::FindByName(string name) { // find a single resource by it's nameout
    if (existingResources.size() < 1) { // if it's empty
        return Resource("none", "none", ResourceType::Study_Room, false); // list is empty, so return a blank
    }

    for (unsigned int i = 0; i < existingResources.size(); i++) { // iterate through until found or not
        if (existingResources.at(i).name == name) { // if name matches,
            return existingResources.at(i); //  then return it
        }
    }

    return Resource("none", "none", ResourceType::Study_Room, false); // otherwise, it wasn't found, so return a blank
}

void ResourceManager::ListAllByType(ResourceType type) {// find all resources of a type
    if (existingResources.size() < 1) { // if it's empty
        cout << endl << "List of resources is empty" << endl;
        return;
    }

    cout << endl << "==== All Resources of Type " << ResourceTypeToString(type) << " ====" << endl << endl;

    for (unsigned int i = 0; i < existingResources.size(); i++) { // iterate through 
        if (existingResources.at(i).type == type) {
            cout << existingResources.at(i).id << " | " << existingResources.at(i).name << " | " << ResourceTypeToString(existingResources.at(i).type) << " | " << (existingResources.at(i).available ? "available" : "unavailable") << endl;
        }
    }
}
void ResourceManager::ListAllByAvailability(bool available) { // find all available or unavailable resources
    if (existingResources.size() < 1) { // if it's empty
        cout << endl << "List of resources is empty" << endl;
        return;
    }

    if (available) cout << endl << "==== All Available Resources ====" << endl << endl;
    else cout << endl << "==== All Unavailable Resources ====" << endl << endl;

    for (unsigned int i = 0; i < existingResources.size(); i++) { // iterate through 
        if (existingResources.at(i).available == available) {
            cout << existingResources.at(i).id << " | " << existingResources.at(i).name << " | " << ResourceTypeToString(existingResources.at(i).type) << " | " << (existingResources.at(i).available ? "available" : "unavailable") << endl;
        }
    }
}

string ResourceManager::ResourceTypeToString(ResourceType type) {
    switch (type) {
        case Study_Room:
        return "Study Room";
        case Laptop:
        return "Laptop";
        case Calculator:
        return "Calculator";
        case Lab_Equipment:
        return "Lab Equipment";
        case Tutoring_Appointment:
        return "Tutoring Appointment";
        default:
        return "Unkown";
    }
}
