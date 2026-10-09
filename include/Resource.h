#ifndef _RESOURCE_
#define _RESOURCE_

#include <queue>
#include "Student.h"

using namespace std;

enum ResourceType { // enum for types of resources
  study_room,
  laptop,
  calculator,
  lab_equipment,
  tutoring_appt
};

class Resource {
public:
  string id; // id of resource
  string name; // name of resource
  ResourceType type; // type of resource
  bool available; // if it is available or not

 
  void addToWaitingList(string studentName, string studentID); // add

  void removeFromWaitingList(); // remove

  void displayWaitingList(); // display

  Resource(string id, string name, ResourceType type, bool available); // constructor

private:
   queue<string> WaitingList; // queue that holds waiting list for this resource
   Student* waitingListTop = NULL; // head of waiting list (top of stack)
   Student* waitingListBottom = NULL; // tail of waiting list (bottom of stack)
   int waitingListLength = 0;
};
#endif