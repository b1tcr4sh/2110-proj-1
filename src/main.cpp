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

using namespace std;

bool handleInput(int input) {
  switch (input) {
  case 1:
    return true;
  case 2:
    return true;
  case 3:
    return true;
  case 4:
    return true;
  case 5:
    return true;
  case 6:
    return true;
  case 7:
    return true;
  case 8:
    return true;
  case 9:
    return false; // return false to escape input loop
  default:
    return true;
  }
}

int main() {

  int input;

  do {
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

    cin >> input;

  } while (handleInput(input));

  cout << "bye bye..." << endl;
}
