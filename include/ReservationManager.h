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
        void PrintActiveReservations();
        void Create(int ID, string studentID, string studentName, string resourceID, string date); // creates a new reservation and adds to list
        void Create(string studentID, string studentName, string resourceID, string date); // creates a new reservation and generates ID; adds to list
        Reservation* Search(int ID); // find position in queue of reservation with ID
        void Cancel(int ID); // finds reservation with ID in list and push it onto stack
        void Restore(); // pops top reservation off stack and restores it to the **back of the queue** ; returns ID of restored reservation
        Reservation* FindByStudent(string studentID); // find all reservations from a student by ID and return an array
        int listLength = 0;
    private:
        list<Reservation> reservations; // linked list that stores all reservations
        stack<Reservation> canceled; // stack of canceled reservations -- most recent cancellation is on top (only the most recent can be restored/popped)

        void addToList(Reservation* res); // helper function
        Reservation* removeFromList(Reservation* res); // helper function

        Reservation* head = NULL; // head of list of reservations
        Reservation* tail = NULL; // tail of list of reservations

        Reservation* canceledTop = NULL; // top of the canceled stack (head)
        Reservation* canceledBottom = NULL; // bottom of the canceled stack (tail)

        int mostRecentID; // ID of most recent reservation; used for generating new IDs for reservations when they are created

        ResourceManager* resourceManager; // reference to the resource manager so we can grab and edit resources
};


#endif