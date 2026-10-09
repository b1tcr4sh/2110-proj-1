#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <string>

using namespace std;

class Student {
    public:
        Student(string name, string id);

        string id;
        string name;
        Student* next;
};

#endif