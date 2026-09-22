#include <iostream>
#include "../include/ResourceManager.h"
#include "../include/ReservationManager.h"

using namespace std;

void viewWaitingLists(ResourceManager* manager) {
  string id;
  cout << "ID of resource to view? > "; 
  cin >> id; // get ID of resource

  Resource* res = manager->FindByID(id); // find resource from ID
  res->displayWaitingList(); // print out the resource's waiting list
}

void createReservationFromUser(ReservationManager* manager, ResourceManager* resourceManager) {
  string resourceID;
  cout << "ID of resource to book > ";
  cin >> resourceID; // get resource ID from user

  cin.ignore();
  string studentName;
  cout << "Who is booking? (Student Name): " << endl;
  getline(cin, studentName); // get student name from user; handle names with multiple words!!

  string studentID;
  cout << "What is " << studentName << "'s ID? > ";
  cin >> studentID; // get ID from student

  string date;
  cout << "What is today's date? (MM/DD/YYYY) > ";
  cin >> date; // get date from user

  manager->Create(studentID, studentName, resourceID, date); // use all of these to create a reservation

  cout << "added reservation for " << studentName << endl;
}

void cancelReservationFromUser(ReservationManager* manager) {
  int ID;
  cout << "ID of reservation to cancel > ";
  cin >> ID; // get reservation ID

  manager->Cancel(ID); // cancel it

  cout << "Cancelled reservation." << endl << "Added to cancellation history." << endl;
}

void searchReservationFromUser(ReservationManager* manager) {
  int ID;
  cout << "ID of reservation you are looking for > ";
  cin >> ID; // get reservation ID

  Reservation res = manager->Search(ID); // find it by ID

  if (res.ID == -1) {
    cout << "Not found..." << endl;
    return;
  }

  cout << res.ID << ": " << res.date << endl; // print out the ID and date
  cout << " Resource: " << res.resourceID << endl; // print out the resource ID
  cout << " Student: " << res.studentName << " | " << res.studentID; // print out student info
}

bool handleInput(int input, ResourceManager* resourceManager, ReservationManager* reservationManager) {

  // switch to handle different inputs (numbers 1 - 10); also handles errors in case input is incorrect
  switch (input) {
    case 1: // View Resources
        resourceManager->PrintList(); // print the list or resources
      return true;
    case 2: // Create Reservation
        createReservationFromUser(reservationManager, resourceManager); // handle creating a reservation
      return true;
    case 3: // Cancel Reservation
        cancelReservationFromUser(reservationManager); // handle cancelling a reservation
      return true;
    case 4: // View Waiting Lists
      viewWaitingLists(resourceManager); // handle getting a resource and printing it's waiting list
      return true;
    case 5: // Undo Cancellation
      reservationManager->Restore();
      cout << "Restored reservation " << endl; // not implemented yet
      return true;
    case 6: // Search Reservations
      searchReservationFromUser(reservationManager); // handle searching for a reservation and printing it's info
      return true;
    case 7: // Sort Resources
      resourceManager->Sort(); // sort the resources; not yet implemented
      resourceManager->PrintList(); // print them out
      return true;
    case 8: // Generate Report; not yet implemented
      return true;
    case 9:
      reservationManager->PrintList(); // print all reservations
      return true;
    case 10: // exit program
      return false; // return false to escape input loop (exit program)
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
  cout << "9. View Active Reservations" << endl;
  cout << "10. Exit" << endl;
  cout << endl << "Selection > ";
}

int main() {
  ResourceManager resourceManager;
  ReservationManager reservationManager(&resourceManager);

  resourceManager.LoadFromFile(); // make sure to load all the resources
  reservationManager.LoadFromFile(); // load reservations and handle them....

  int input;
  bool cont = true;
  while (cont) { // loop until program end; makes sure that user gets prompted with a new menu after each operaiton
    cout << endl;
    printMenu(); // print the menu
    cin >> input;
    cont = handleInput(input, &resourceManager, &reservationManager); // take user input and do things with it
  }

  cout << "bye bye..." << endl;
  return 0;
}
