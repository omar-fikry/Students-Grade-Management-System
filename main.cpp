#include <iostream>
#include <string>
#include <fstream>   // NEW: allows file input/output
using namespace std;

const int MAX_STUDENTS = 100;
const int MAX_COURSES = 10;

struct Course {
    string name;
    double grade;
};

struct Student {
    int id;
    string name;
    Course courses[MAX_COURSES];
    int numCourses;
};

// ---------------- FILE SAVE FUNCTION ----------------
void saveStudents(Student students[], int count) {   // NEW: function to save students
    ofstream file("students.txt");                    // NEW: open file for writing

    for (int i = 0; i < count; i++) {                 // NEW: loop through students
        file << students[i].id << "|";                // NEW: save ID
        file << students[i].name << "|";              // NEW: save name
        file << students[i].numCourses;               // NEW: save number of courses

        for (int j = 0; j < students[i].numCourses; j++) {   // NEW: loop courses
            file << "|"                               // NEW: separator
                 << students[i].courses[j].name      // NEW: course name
                 << ","                               // NEW: separator
                 << students[i].courses[j].grade;    // NEW: course grade
        }

        file << endl;                                 // NEW: new line per student
    }

    file.close();                                     // NEW: close file
}

// ---------------- GPA ----------------
double calculateGPA(Student student) {
    if (student.numCourses == 0) return 0.0;

    double total = 0;
    for (int i = 0; i < student.numCourses; i++) {
        total += student.courses[i].grade;
    }

    double average = total / student.numCourses;
    return average / 25.0;
}

void showStudent(Student student) {
    cout << "ID: " << student.id << endl;
    cout << "Name: " << student.name << endl;
    cout << "GPA: " << calculateGPA(student) << endl;
}

int findStudent(Student students[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            return i;
        }
    }
    return -1;
}

// ---------------- ADD STUDENT ----------------
void addStudent(Student students[], int &count) {
    if (count >= MAX_STUDENTS) {
        cout << "Cannot add more students!" << endl;
        return;
    }

    Student newStudent;

    cout << "Enter student ID: ";
    cin >> newStudent.id;

    cout << "Enter student name: ";
    cin.ignore();
    getline(cin, newStudent.name);

    cout << "How many courses? ";
    cin >> newStudent.numCourses;

    for (int i = 0; i < newStudent.numCourses; i++) {
        cout << "Course " << (i + 1) << " name: ";
        cin >> newStudent.courses[i].name;

        cout << "Course " << (i + 1) << " grade out of 100: ";
        cin >> newStudent.courses[i].grade;
    }

    students[count] = newStudent;
    count++;

    saveStudents(students, count);   // NEW: save after adding

    cout << "Student added successfully!" << endl;
}

// ---------------- UPDATE STUDENT ----------------
void updateStudent(Student students[], int count) {
    int id;
    cout << "Enter student ID to update: ";
    cin >> id;

    int index = findStudent(students, count, id);

    if (index == -1) {
        cout << "Student not found!" << endl;
        return;
    }

    cout << "Enter new name: ";
    cin.ignore();
    getline(cin, students[index].name);

    saveStudents(students, count);   // NEW: save after updating

    cout << "Name updated!" << endl;
}

// ---------------- REMOVE STUDENT ----------------
void removeStudent(Student students[], int &count) {
    int id;
    cout << "Enter student ID to remove: ";
    cin >> id;

    int index = findStudent(students, count, id);

    if (index == -1) {
        cout << "Student not found!" << endl;
        return;
    }

    for (int i = index; i < count - 1; i++) {
        students[i] = students[i + 1];
    }

    count--;

    saveStudents(students, count);   // NEW: save after deleting

    cout << "Student removed!" << endl;
}

// ---------------- SEARCH ----------------
void searchStudent(Student students[], int count) {
    int id;
    cout << "Enter student ID to search: ";
    cin >> id;

    int index = findStudent(students, count, id);

    if (index == -1) {
        cout << "Student not found!" << endl;
    } else {
        showStudent(students[index]);
    }
}

// ---------------- SORTING ----------------
void sortById(Student students[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].id > students[j + 1].id) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    cout << "Sorted by ID!" << endl;
}

void sortByName(Student students[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].name > students[j + 1].name) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    cout << "Sorted by name!" << endl;
}

// ---------------- LOW GPA ----------------
void showLowGPA(Student students[], int count) {
    bool found = false;

    cout << "Students with GPA below 2.0:" << endl;
    for (int i = 0; i < count; i++) {
        double gpa = calculateGPA(students[i]);
        if (gpa < 2.0) {
            cout << students[i].id << " - " << students[i].name;
            cout << " (GPA: " << gpa << ")" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No students with GPA below 2.0" << endl;
    }
}

// ---------------- MAIN ----------------
int main() {
    Student students[MAX_STUDENTS];
    int studentCount = 0;
    int choice;

    do {
        cout << "\n--- Main Menu ---" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Update Student" << endl;
        cout << "3. Delete Student" << endl;
        cout << "4. Search Student" << endl;
        cout << "5. Sort by ID" << endl;
        cout << "6. Sort by Name" << endl;
        cout << "7. Low GPA Report" << endl;
        cout << "8. Exit" << endl;
        cout << "\nYour choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(students, studentCount); break;
            case 2: updateStudent(students, studentCount); break;
            case 3: removeStudent(students, studentCount); break;
            case 4: searchStudent(students, studentCount); break;
            case 5: sortById(students, studentCount); break;
            case 6: sortByName(students, studentCount); break;
            case 7: showLowGPA(students, studentCount); break;
            case 8: cout << "Program ended.\n"; break;
            default: cout << "Error: Please choose a choice from 1 to 8\n";
        }

    } while (choice != 8);

    return 0;
}


