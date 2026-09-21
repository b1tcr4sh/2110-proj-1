#ifndef _RESERVATION_MANAGER_
#define _RESERVATION_MANAGER_

#include <queue>
#include <stack>
#include <iostream>
#include "Reservation.h"
#include "ResourceManager.h"
#include <list>


class ReservationManager {
    public:
         ReservationManager(ResourceManager* manager);

        void LoadFromFile(); // load reservations from file and place on queue
        void PrintList(); // print out the queue
        
        void Create(int ID, string studentID, string studentName, string resourceID, string date); // creates a new reservation and adds to queue
        void Create(string studentID, string studentName, string resourceID, string date); // creates a new reservation and generates ID; adds to queue
        Reservation Search(int ID); // find position in queue of reservation with ID
        void Cancel(int ID); // finds reservation with ID and adds it to canceled stack
        void Restore(); // pops top reservation off stack and restores it to the **back of the queue** ; returns ID of restored reservation
        // int FindByID(int ID);
    private:
        list<Reservation> reservations; // linked list that stores all reservations
        stack<Reservation*> canceled; // stack of canceled reservations -- most recent cancellation is on top (only the most recent can be restored/popped)

        int mostRecentID; // ID of most recent reservation; used for generating new IDs for reservations when they are created

        ResourceManager* resourceManager; // reference to the resource manager so we can grab and edit resources
};


#endif