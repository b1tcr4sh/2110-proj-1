#ifndef _RESOURCE_MANAGER_
#define _RESOURCE_MANAGER_

#include "Resource.h"
#include <vector>


class ResourceManager { // manages loading and storing the list of available resouces.
    public:
        Resource* ResourceByID(string id); // search for resource by id
        void PrintList(); // what it says
        bool Sort(); // sort by id??
        void LoadFromFile(); // loads all the resources from the file into the vector

        Resource* FindByID(string ID);
    private:
        vector<Resource> existingResources;
};
#endif