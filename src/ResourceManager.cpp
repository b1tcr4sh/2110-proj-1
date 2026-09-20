#include "../include/ResourceManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

Resource* ResourceManager::ResourceByID(string id) {return 0;}

void ResourceManager::PrintList() {
    cout << "Resources: " << endl << endl;

    for (unsigned int i = 0; i < existingResources.size(); i++) {
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

bool ResourceManager::Sort() {return 0;}

void ResourceManager::LoadFromFile() {
    ifstream file("data/resources.txt");


    while (!file.eof()) {
        string line;
        getline(file, line); // read 1 line from file


        // split line into tokens
        stringstream stream(line);

        string id;
        getline(stream, id, '|');
        // cout << id << endl;

        string name;
        getline(stream, name, '|');
        // cout << name << endl;

        string typeString;
        getline(stream, typeString, '|');
        // cout << typeString << endl;

        string availability;
        getline(stream, availability, '|');
        // cout << availability << endl;

        ResourceType type;
        if (typeString == "Study Room") type = study_room;
        else if (typeString == "Laptop") type = laptop;
        else if (typeString == "Calculator") type = calculator;
        else if (typeString == "Lab Equipment") type = lab_equipment;
        else if (typeString == "Tutoring Appointment") type = tutoring_appt;
        else {
            cout << "Was unable to read resource type ( " << type << " ) for " << id << endl;
        }

        bool available;
        if (availability == "Available") { 
            available = true;
        } else if (availability == "Unavailable") { 
            available = false;
        } else {
            cout << "Was unable to read availability ( " << availability << " ) for " << id << endl;
        }

        Resource resource(id, name, type, available);

        existingResources.push_back(resource);

    }
}

Resource* ResourceManager::FindByID(string ID) {
    for (unsigned int i = 0; i < existingResources.size(); i++) {
        if (existingResources.at(i).id == ID) {
            return &existingResources.at(i);
        }
    }

    cout << "Was unabe to find resource " << ID << endl;
    return nullptr;
}