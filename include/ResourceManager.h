#ifndef _RESOURCE_MANAGER_
#define _RESOURCE_MANAGER_

#include "Resource.h"
#include <vector>


class ResourceManager { // manages loading and storing the list of available resouces.
    public:
        void PrintList(); // what it says
        bool Sort(); // sort by name
        void LoadFromFile(); // loads all the resources from the file into the vector
        void GenerateReport(); // generates a report of all resources
        Resource* FindByID(string ID); // finds the resource with ID and returns it
        Resource FindByName(string name); // find a single resource by it's name
        void ListAllByType(ResourceType type); // find all resources of a type
        void ListAllByAvailability(bool available); // find all available or unavailable resources
        string ResourceTypeToString(ResourceType type); // convert a type to a string
    private:
        vector<Resource> existingResources; // vector containing all existing resources

        void MergeSort(int left, int right);
        void Merge(int left, int middle, int right);
};
#endif