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
        void PrintActiveReservations(); // print the list of reservations

        int Create(int ID, string studentID, string studentName, string resourceID, string date); // creates a new reservation and adds to list
        int Create(string studentID, string studentName, string resourceID, string date); // creates a new reservation and generates ID; adds to list
        Reservation* Search(int ID); // find position in queue of reservation with ID
        // Reservation* FindByStudent(string studentID); // find all reservations from a student by ID and return an array

        bool Cancel(int ID); // finds reservation with ID in list and push it onto stack
        Reservation Restore(); // pops top reservation off stack and restores it to the **back of the queue** ; returns ID of restored reservation
        Reservation PeekMostRecentCancellation(); // peek the top of stack (returns a copy instead of a pointer so that it can't fuck up the stack)

        int listLength = 0;
        int canceledLength = 0;
    private:
        list<Reservation> reservations; // linked list that stores all reservations
        stack<Reservation> canceled; // stack of canceled reservations -- most recent cancellation is on top (only the most recent can be restored/popped)

        void addToList(Reservation* res); // helper function for appending to the linked list
        Reservation* removeFromList(Reservation* res); // helper function for removing an item from the linked list
        void pushCanceled(Reservation* res); // helper function for pushing onto stack
        Reservation* popCanceled(); // helper function for popping off the stack

        Reservation* head = NULL; // head of list of reservations
        Reservation* tail = NULL; // tail of list of reservations

        Reservation* canceledTop = NULL; // top of the canceled stack (head)
        Reservation* canceledBottom = NULL; // bottom of the canceled stack (tail)

        int mostRecentID; // ID of most recent reservation; used for generating new IDs for reservations when they are created

        ResourceManager* resourceManager; // reference to the resource manager so we can grab and edit resources
};


#endif