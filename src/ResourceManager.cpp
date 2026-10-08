#include "../include/ResourceManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

Resource* ResourceManager::ResourceByID(string id) {return 0;} // not implemented yet

void ResourceManager::PrintList() { // print the list of resources
    cout << "Resources: " << endl << endl;

    for (unsigned int i = 0; i < existingResources.size(); i++) { // iterate through the list
        Resource e = existingResources.at(i);

        string type;
        switch (e.type) {
            case study_room:
                type = "Study Room";
                break;
            case laptop:
                type = "Laptop";
                break;
            case calculator:
                type = "Calculator";
                break;
            case lab_equipment:
                type = "Lab Equipment";
                break;
            case tutoring_appt:
                type = "Tutoring Appointment";
                break;
        }

        cout << e.id << " | " << e.name << " | " << type << " | " << (e.available ? "available" : "unavailable") << endl;
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

    for (int k = 0; k < temp.size(); k++) {
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

        // handle parsing the type into the enum
        ResourceType type; 
        if (typeString == "Study Room") type = study_room;
        else if (typeString == "Laptop") type = laptop;
        else if (typeString == "Calculator") type = calculator;
        else if (typeString == "Lab Equipment") type = lab_equipment;
        else if (typeString == "Tutoring Appointment") type = tutoring_appt;
        else {
            cout << "Was unable to read resource type ( " << type << " ) for " << id << endl;
        }

        // handle parsing availability into bool
        bool available;
        if (availability == "Available") { 
            available = true;
        } else if (availability == "Unavailable") { 
            available = false;
        } else {
            // cout << "Was unable to read availability ( " << availability << " ) for " << id << endl;
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

    cout << "Was unabe to find resource " << ID << endl; 
    return nullptr; // if we were unable to find it, return null; for error handling
}