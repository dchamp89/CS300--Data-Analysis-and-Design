//============================================================================
// Name        : CourseListSortAndPrint.cpp
// Author      : Donald Champagne
// Course      : CS 300 - Data Structures and Algorithms: Analysis and Design
// Description : Portfolio excerpt from ProjectTwo.cpp — the ABCU Advising
//               Assistance Program.
//
//               This file isolates the piece of the program responsible for
//               sorting and printing the full Computer Science course list
//               in alphanumeric order (Menu Option 2). It's excerpted here
//               to showcase that specific algorithm; the full program also
//               includes file loading, a hash table with chaining for
//               storage, and a single-course lookup with prerequisites.
//
//               Because courses are stored in a hash table, there is no
//               inherent order to rely on — a hash table's bucket a course
//               lands in depends on a hash of its course number, not the
//               alphabet. So printCourseList() pulls every course back out
//               of the table into a plain vector via GetAllCourses(), sorts
//               that vector by course number, and only then prints it. This
//               keeps the hash table doing what it's fast at (O(1) average
//               lookups) while still meeting the "alphanumeric list"
//               requirement with a straightforward O(n log n) sort applied
//               only when this option is actually chosen.
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//============================================================================
// Course object (see the full ProjectTwo.cpp for the HashTable class this
// depends on — specifically its GetAllCourses() and IsEmpty() methods).
//============================================================================
struct Course {
    string courseNumber;               // e.g. "CSCI200"
    string courseName;                 // e.g. "Data Structures"
    vector<string> prerequisites;      // course numbers required before this course
};

// Forward declaration of the HashTable interface this function relies on.
// The full implementation (hashing, chaining, Insert, Search) lives in the
// complete ProjectTwo.cpp submission.
class HashTable {
public:
    bool IsEmpty() const;
    vector<Course> GetAllCourses() const;
};

//============================================================================
// printCourseList - Menu Option 2. Prints every course, sorted in
// alphanumeric order, as "COURSENUMBER, Course Name".
//============================================================================
void printCourseList(const HashTable& courseTable) {
    if (courseTable.IsEmpty()) {
        cout << "Error: course data has not been loaded yet. "
             << "Please choose option 1 first." << endl;
        return;
    }

    // Pull every course out of the hash table into a plain vector, since
    // the table itself keeps no order.
    vector<Course> courses = courseTable.GetAllCourses();

    // Sort that vector by course number, ascending, so the list prints in
    // alphanumeric order regardless of which bucket each course actually
    // landed in.
    sort(courses.begin(), courses.end(),
         [](const Course& a, const Course& b) {
             return a.courseNumber < b.courseNumber;
         });

    cout << endl << "Here is a sample schedule:" << endl << endl;
    for (const Course& course : courses) {
        cout << course.courseNumber << ", " << course.courseName << endl;
    }
    cout << endl;
}
