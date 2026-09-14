/*
must include:
Resource ID
Resource Name
Resource Type
Availability Status

types:
Study Rooms
Laptops
Calculators
Lab Equipment
Tutoring appointments
*/

#include <string>

using namespace std;

enum ResourceType {
  study_room,
  laptop,
  calculator,
  lab_equipment,
  tutoring_appt
};

class Resource {
public:
  int id;
  string name;
  ResourceType type;
  bool available;

private:
};