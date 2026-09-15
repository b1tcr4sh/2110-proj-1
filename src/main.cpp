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

bool handleInput(int input, ResourceManager resourceManager) {
  switch (input) {
    case 1: // View Resources
        resourceManager.PrintList();
      return true;
    case 2: // Create Reservation
      return true;
    case 3: // Cancel Reservation
      return true;
    case 4: // View Waiting Lists
      return true;
    case 5: // Undo Cancellation
      return true;
    case 6: // Search Reservations
      return true;
    case 7: // Sort Resources
      return true;
    case 8: // Generate Report
      return true;
    case 9:
      return false; // return false to escape input loop
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
  // ReservationManager reservationManager;

  resourceManager.LoadFromFile(); // make sure to load all the resources

  printMenu();

  int input;
  bool cont = true;
  while (cont) {
        cin >> input;
        cont = handleInput(input, resourceManager);
  }

  cout << "bye bye..." << endl;
  return 0;
}
