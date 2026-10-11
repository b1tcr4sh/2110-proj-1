#include <iostream>
#include "../include/ResourceManager.h"
#include "../include/ReservationManager.h"

using namespace std;

void viewWaitingLists(ResourceManager* manager) {
  string id;
  cout << endl << "ID of resource to view? > "; 
  cin >> id; // get ID of resource

  Resource* res = manager->FindByID(id); // find resource from ID

  if (res != NULL) { // if it's found..
    res->displayWaitingList(); // print out the resource's waiting list
  } else { // if not found
    cout << endl << "Was unabe to find resource " << id << endl; 
    cout << "aborting." << endl; // then abort 
  }
}

void createReservationFromUser(ReservationManager* manager, ResourceManager* resourceManager) {
  string resourceID;
  cout << endl << "ID of resource to book > ";
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

  int id = manager->Create(studentID, studentName, resourceID, date); // use all of these to create a reservation

  if (id != -1) {
    cout << endl << "added reservation for " << studentName << " with id " << id << endl;
  } else {
    cout << endl << resourceID << " not found in list..." << endl;
    cout << "reservation creation aborted." << endl;
  }
}

void cancelReservationFromUser(ReservationManager* manager) {
  int ID;
  cout << endl << "ID of reservation to cancel > ";
  cin >> ID; // get reservation ID

  bool success = manager->Cancel(ID); // cancel it

  if (success) {
    cout << endl << "Cancelled reservation " << ID << endl << "Added to cancellation history." << endl;
  } else {
    cout << endl << ID << " not found..." << endl << "Aborting." << endl;
  }

}

void searchReservationFromUser(ReservationManager* manager) {
  int ID;
  cout << endl << "ID of reservation you are looking for > ";
  cin >> ID; // get reservation ID

  Reservation* res = manager->Search(ID); // find it by ID

  if (res == NULL) {
    cout << endl << ID << " not found in list..." << endl;
    cout << "Aborting." << endl;
    return;
  }

  cout << endl << res->ID << ": " << res->date << endl; // print out the ID and date
  cout << " Resource: " << res->resourceID << endl; // print out the resource ID
  cout << " Student: " << res->studentName << " | " << res->studentID << endl; // print out student info
}

void peekCancellation(ReservationManager* man) {
  Reservation res = man->PeekMostRecentCancellation();

  if (res.ID == -1) {
    cout << endl << "There are no cancellations to view..." << endl;
    return;
  }

  cout << endl << "Reservation " << res.ID << " | " << res.date << endl;
  cout << " for: " << res.studentName << " | " << res.studentID << endl;
  cout << " requesting: " << res.resourceID << endl;
}

void restoreReservation(ReservationManager* man) {
  Reservation res = man->Restore();

  if (res.ID == -1) { // if the restore function could not find a reservation
    cout << endl << "There are no cancellations to restore..." << endl;
    return;
  }

  cout << "Restored reservation " << res.ID << endl; // not implemented yet
}

void searchResourceByID(ResourceManager* man) {
  cout << endl << "ID > ";
  string id;
  cin >> id;

  Resource* resource = man->FindByID(id);  // find the resource

  if (resource == NULL) { // if the resource wasn't found
      cout << endl << "Resource " << id << " could not be found. Aborting." << endl; // then, exit early and abort
      return;
  }

  cout << endl << resource->id << " | " << resource->name << " | " << man->ResourceTypeToString(resource->type) << " | " << (resource->available ? "available" : "unavailable") << endl;
}

void searchResourceByName(ResourceManager* man) {
  cout << endl << "Name:" << endl;
  string name;
  cin.ignore();
  getline(cin, name);

  Resource res = man->FindByName(name);

  if (res.name == "none") {
    cout << endl << "Resource " << name << " could not be found or list is empty. Aborting." << endl;
    return;
  }

  cout << endl << res.id << " | " << res.name << " | " << man->ResourceTypeToString(res.type) << " | " << (res.available ? "available" : "unavailable") << endl;
}

void listResourceByType(ResourceManager* man) {
  cout << "Select Type: " << endl << "  1. Study Room" << endl << "  2. Laptop" << endl << "  3. Calculator" << endl << "  4. Lab Equipment" << endl << "  5. Tutoring Appointment" << endl << endl;

  cout << endl << " > ";
  int type;
  cin >> type;

  if (type < 1 || type > 5) {
    cout << "Invalid Option. Aborting." << endl;
    return;
  }

  switch (type) {
    case 1:
      man->ListAllByType(ResourceType::Study_Room);
    return;
    case 2:
      man->ListAllByType(ResourceType::Laptop);
    return;
    case 3:
      man->ListAllByType(ResourceType::Calculator);
    return;
    case 4:
      man->ListAllByType(ResourceType::Lab_Equipment);
    return;
    case 5:
      man->ListAllByType(ResourceType::Tutoring_Appointment);
    return;
  }
}

void listResourceByAvailability(ResourceManager* man) {
  cout << endl << "Available? (y/n) > ";
  string available;
  cin >> available;

  if (available == "y") {
    man->ListAllByAvailability(true);
  } else if (available == "n") {
    man->ListAllByAvailability(false);
  } else {
    cout << endl << "Invalid response. Aborting." << endl;
    return;
  }
}
 
void searchResources(ResourceManager* man) {
  cout << endl << "Search by:" << endl;
  cout << "1. ID" << endl;
  cout << "2. Name" << endl;
  cout << "3. Type" << endl;
  cout << "4. Availability" << endl << endl;
  cout << " > ";

  int sel;
  cin >> sel;

  if (sel < 1 || sel > 5) {
    cout << endl << "Invalid selection. Aborting." << endl;
    return;
  }

  switch (sel) {
    case 1:
      searchResourceByID(man);
    return;
    case 2:
      searchResourceByName(man);
    return;
    case 3:
      listResourceByType(man);
    return;
    case 4:
      listResourceByAvailability(man);
    return;
  }
}

bool handleInput(int input, ResourceManager* resourceManager, ReservationManager* reservationManager) {

  // switch to handle different inputs (numbers 1 - 10); also handles errors in case input is incorrect
  switch (input) {
    case 1: // View Resources
        resourceManager->PrintList(); // print the list or resources
      return true;
    case 2: // search resources
        searchResources(resourceManager);
      return true;
    case 3: // Create Reservation
        createReservationFromUser(reservationManager, resourceManager); // handle creating a reservation
      return true;
    case 4: // Cancel Reservation
        cancelReservationFromUser(reservationManager); // handle cancelling a reservation
      return true;
    case 5: // View Waiting Lists
      viewWaitingLists(resourceManager); // handle getting a resource and printing it's waiting list
      return true;
    case 6: // Undo Cancellation
      restoreReservation(reservationManager);
      return true;
    case 7: // Search Reservations
      searchReservationFromUser(reservationManager); // handle searching for a reservation and printing it's info
      return true;
    case 8: // Sort Resources
      resourceManager->Sort(); // sort the resources; not yet implemented
      resourceManager->PrintList(); // print them out
      return true;
    case 9: // Generate Report
      resourceManager->GenerateReport(); // generate a report of all resources
      reservationManager->PrintActiveReservations(); // print active reservations
      return true;
    case 10:
      reservationManager->PrintActiveReservations(); // print active reservations
      return true;
    case 11: // see the most recent cancellation
      peekCancellation(reservationManager);
      return true;
    case 12: // exit program
      return false; // return false to escape input loop (exit program)
    default:
        cout << "Input not recognized!!" << endl;
      return true; // return true to loop again
  }
}

void printMenu() {
  cout << "===== Campus Resource Reservation System =====" << endl;
  cout << "1. View Resources" << endl;
  cout << "2. Search Resources" << endl;
  cout << "3. Create Reservation" << endl;
  cout << "4. Cancel Reservation" << endl;
  cout << "5. View Waiting Lists" << endl;
  cout << "6. Undo Cancellation" << endl;
  cout << "7. Search Reservations" << endl;
  cout << "8. Sort Resources" << endl;
  cout << "9. Generate Report" << endl;
  cout << "10. View Active Reservations" << endl;
  cout << "11. View Last Cancellation" << endl;
  cout << "12. Exit" << endl;
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
