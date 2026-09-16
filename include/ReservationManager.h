#ifndef _RESERVATION_MANAGER_
#define _RESERVATION_MANAGER_

#include <queue>
#include <stack>
#include <iostream>
#include "Reservation.h"

class ReservationManager {
    public:
        void LoadFromFile(); // load reservations from file and place on queue
        void PrintQueue(); // print out the queue
        
        void Create(int ID, string studentID, string studentName, string resourceID, string date); // creates a new reservation and adds to queue
        void Create(string studentID, string studentName, string resourceID, string date); // creates a new reservation and generates ID; adds to queue
        Reservation Search(int ID); // find position in queue of reservation with ID
        void Cancel(int ID); // finds reservation with ID and adds it to canceled stack
        int Restore(); // pops top reservation off stack and restores it to the **back of the queue** ; returns ID of restored reservation
    private:
        stack<Reservation> canceled; // stack of canceled reservation IDs -- most recent cancellation is on top (only the most recent can be restored/popped)
        queue<Reservation> reservations; // queue of reservations FIFO

        int mostRecentID;

};


#endif