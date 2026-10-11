#ifndef _RESOURCE_
#define _RESOURCE_

#include <queue>
#include "Student.h"

using namespace std;

class Resource {
public:
  string id; // id of resource
  string name; // name of resource
  string type; // type of resource
  bool available; // if it is available or not
  int reservationCount; // number of reservations for this resource
  int waitingListLength = 0; // length of waiting list
  
  void addToWaitingList(string studentName, string studentID); // add

  void removeFromWaitingList(); // remove

  void displayWaitingList(); // display

  Resource(string id, string name, string type, bool available); // constructor

private:
   queue<string> WaitingList; // queue that holds waiting list for this resource
   Student* waitingListFront = NULL; // head of waiting list (front of queue)
   Student* waitingListBack = NULL; // tail of waiting list (back of queue)
};
#endif