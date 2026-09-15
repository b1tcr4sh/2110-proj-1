#include "../include/ResourceManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

Resource* ResourceManager::ResourceByID(string id) {return 0;}

void ResourceManager::PrintList() {
    cout << "Resources: " << endl << endl;

    for (int i = 0; i < existingResources.size(); i++) {
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
    ifstream file("resources.txt");


    while (!file.eof()) {
        string line;
        getline(file, line); // read 1 line from file


        // split line into tokens
        stringstream stream(line);

        string id;
        getline(stream, id, '|');

        string name;
        getline(stream, name, '|');

        string typeString;
        getline(stream, typeString, '|');

        string availability;
        getline(stream, availability, '|');


        ResourceType type;
        if (typeString == "Study Room") type = study_room;
        else if (typeString == "Laptop") type = laptop;
        else if (typeString == "Calculator") type = calculator;
        else if (typeString == "Lab Equipment") type = lab_equipment;
        else if (typeString == "Tutoring Appointment") type = tutoring_appt;
        else {
            // handle error
        }

        bool available;
        if (availability == "Available") available = true;
        else if (availability == "Unavailable") available = false;
        else {
            // handle error
        }

        Resource resource(id, name, type, available);

        existingResources.push_back(resource);

    }
}