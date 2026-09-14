#include "../include/Resource.h"

Resource::Resource(string id, string name, ResourceType type, bool available) {
    this->id = id;
    this->name = name;
    this->type = type;
    this->available = available;
}