// hewo
// hi meooowwww
// gay faggot gay

/*
View Resources
Create Reservation
Cancel Reservation
View Waiting Lists
Undo Cancellation
Search Reservations
Sort Resources
Generate Report
Exit
*/

#include <iostream>
#include "../include/ResourceManager.h"
#include "../include/ReservationManager.h"

using namespace std;

void viewWaitingLists(ResourceManager manager) {
  string id;
  cout << "ID of resource to view? > ";
  cin >> id;

  Resource* res = manager.FindByID(id);
  res->displayWaitingList();
}

void createReservationFromUser(ReservationManager manager, ResourceManager resourceManager) {
  
  string resourceID;
  cout << "ID of resource to book > ";
  cin >> resourceID;

  string studentName;
  cout << "Who is booking? (Student Name): " << endl;
  getline(cin, studentName);

  string studentID;
  cout << "What is " << studentName << "'s ID? > ";
  cin >> studentID;

  string date;
  cout << "What is today's date? (MM/DD/YYYY) > ";
  cin >> date;

  manager.Create(studentID, studentName, resourceID, date, resourceManager);

  cout << "Done!" << endl;
}

void cancelReservationFromUser(ReservationManager& manager) {
  int ID;
  cout << "ID of reservation to cancel > ";
  cin >> ID;

  manager.Cancel(ID);

  cout << "Cancelled reservation." << endl << "Added to cancellation history." << endl;
}

void searchReservationFromUser(ReservationManager& manager) {
  int ID;
  cout << "ID of reservation you are looking for > ";
  cin >> ID;

  Reservation res = manager.Search(ID);

  cout << res.ID << ": " << res.date << endl;
  cout << " Resource: " << res.resourceID << endl;
  cout << " Student: " << res.studentName << " | " << res.studentID;
}

bool handleInput(int input, ResourceManager& resourceManager, ReservationManager& reservationManager) {
  switch (input) {
    case 1: // View Resources
        resourceManager.PrintList();
      return true;
    case 2: // Create Reservation
        createReservationFromUser(reservationManager, resourceManager);
      return true;
    case 3: // Cancel Reservation
        cancelReservationFromUser(reservationManager);
      return true;
    case 4: // View Waiting Lists
      viewWaitingLists(resourceManager);
      return true;
    case 5: // Undo Cancellation
      cout << "Restored reservation " << endl;
      return true;
    case 6: // Search Reservations
      searchReservationFromUser(reservationManager);
      return true;
    case 7: // Sort Resources
      resourceManager.Sort();
      resourceManager.PrintList();
      return true;
    case 8: // Generate Report
      return true;
    case 9:
      return false; // return false to escape input loop (exit program)
    case 10:
      reservationManager.PrintList();
      return true;
    default:
        cout << "Input not recognized!!" << endl;
      return true; // return true to loop again
  }
}

void printMenu() {
  cout << "===== Campus Resource Reservation System =====" << endl;
  cout << "1. View Resources" << endl;
  cout << "2. Create Reservation" << endl;
  cout << "3. Cancel Reservation" << endl;
  cout << "4. View Waiting Lists" << endl;
  cout << "5. Undo Cancellation" << endl;
  cout << "6. Search Reservations" << endl;
  cout << "7. Sort Resources" << endl;
  cout << "8. Generate Report" << endl;
  cout << "9. Exit" << endl;
  cout << endl << "Selection > ";
}

int main() {
  ResourceManager resourceManager;
  ReservationManager reservationManager;

  resourceManager.LoadFromFile(); // make sure to load all the resources
  reservationManager.LoadFromFile(resourceManager); // load reservations and handle them....

  int input;
  bool cont = true;
  while (cont) {
    cout << endl;
    printMenu();
    cin >> input;
    cont = handleInput(input, resourceManager, reservationManager);
  }

  cout << "bye bye..." << endl;
  return 0;
}
