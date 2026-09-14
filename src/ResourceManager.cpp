#include "../include/ResourceManager.h"
#include <fstream>
#include <stdio.h>
#include <sstream>

Resource* ResourceManager::GetResouceAt(int i) {}

Resource* ResourceManager::GetAll() {}

bool ResourceManager Sort() {}

void ResourceManager::LoadFromFile() {
    ifstream file("resources.txt");


    while (!file.eof()) {
        string line;
        getline(line, file);

        stringstream stream(line);

        string id;
        getline(stream, id, "|");

        string name;
        getline(stream, name, "|");

        string typeString;
        getline(stream, typeString, "|");

        string availability;
        getline(stream, availability, "|");


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