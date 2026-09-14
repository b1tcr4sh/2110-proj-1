#ifndef _RESOURCE_MANAGER_
#define _RESOURCE_MANAGER_

#include "Resource.h";
#include <vector>


class ResourceManager { // manages loading and storing the list of available resouces.
    public:
        Resource* GetResouceAt(int i);
        Resource* GetAll();
        bool Sort();
        void LoadFromFile();
    private:
        vector<Resource> existingResources;
};
#endif