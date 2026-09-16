#ifndef _RESOURCE_
#define _RESOURCE_
/*
must include:
Resource ID
Resource Name
Resource Type
Availability Status

types:
Study Rooms
Laptops
Calculators
Lab Equipment
Tutoring appointments
*/

#include <string>
#include <queue>

using namespace std;

enum ResourceType {
  study_room,
  laptop,
  calculator,
  lab_equipment,
  tutoring_appt
};

class Resource {
public:
  string id;
  string name;
  ResourceType type;
  bool available;

 queue<string> WaitingList;
 
 void addToWaitingList(string studentID); // add

 void removeFromWaitingList(); // remove

 void displayWaitingList(); // display

// some important methods can go in here. 

  Resource(string id, string name, ResourceType type, bool available);
private:
};
#endif