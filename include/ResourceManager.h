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
    private:
        vector<Resource> existingResources; // vector containing all existing resources

        void MergeSort(int left, int right);
        void Merge(int left, int middle, int right);
};
#endif