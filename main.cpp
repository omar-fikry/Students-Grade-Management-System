#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
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


string toLower(string s) {
    for (int i = 0; i < s.length(); i++) {
        s[i] = tolower(s[i]);
    }
    return s;
}


void saveStudents(Student students[], int count) {
    ofstream file("students.txt");

    for (int i = 0; i < count; i++) {
        file << students[i].id << "|"
             << students[i].name << "|"
             << students[i].numCourses;

        for (int j = 0; j < students[i].numCourses; j++) {
            file << "|" << students[i].courses[j].name
                 << "," << students[i].courses[j].grade;
        }
        file << endl;
    }

    file.close();
}


double calculateGPA(Student s) {
    if (s.numCourses == 0) return 0.0;

    double total = 0;
    for (int i = 0; i < s.numCourses; i++) {
        total += s.courses[i].grade;
    }

    return (total / s.numCourses) / 25.0;
}


void showStudent(Student s) {
    cout << "\nID: " << s.id << endl;
    cout << "Name: " << s.name << endl;
    cout << "GPA: " << calculateGPA(s) << endl;
}


int findStudentById(Student students[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id)
            return i;
    }
    return -1;
}


void addStudent(Student students[], int &count) {
    if (count >= MAX_STUDENTS) {
        cout << "Cannot add more students!\n";
        return;
    }

    Student s;

    cout << "Enter student ID: ";
    cin >> s.id;

    cout << "Enter student name: ";
    cin.ignore();
    getline(cin, s.name);

    cout << "How many courses? ";
    cin >> s.numCourses;

    for (int i = 0; i < s.numCourses; i++) {
        cout << "Course " << i + 1 << " name: ";
        cin >> s.courses[i].name;

        cout << "Course " << i + 1 << " grade: ";
        cin >> s.courses[i].grade;
    }

    students[count++] = s;
    saveStudents(students, count);

    cout << "Student added successfully!\n";
}


void updateStudent(Student students[], int count) {
    int id;
    cout << "Enter student ID to update: ";
    cin >> id;

    int index = findStudentById(students, count, id);

    if (index == -1) {
        cout << "Student not found!\n";
        return;
    }

    cout << "Enter new name: ";
    cin.ignore();
    getline(cin, students[index].name);

    saveStudents(students, count);
    cout << "Student updated!\n";
}


void removeStudent(Student students[], int &count) {
    int id;
    cout << "Enter student ID to remove: ";
    cin >> id;

    int index = findStudentById(students, count, id);

    if (index == -1) {
        cout << "Student not found!\n";
        return;
    }

    for (int i = index; i < count - 1; i++) {
        students[i] = students[i + 1];
    }

    count--;
    saveStudents(students, count);

    cout << "Student removed!\n";
}


void searchById(Student students[], int count) {
    int id;
    cout << "Enter student ID: ";
    cin >> id;

    int index = findStudentById(students, count, id);

    if (index == -1)
        cout << "Student not found!\n";
    else
        showStudent(students[index]);
}


void searchByName(Student students[], int count) {
    string name;
    cout << "Enter student name: ";
    cin.ignore();
    getline(cin, name);

    string searchName = toLower(name);
    bool found = false;

    for (int i = 0; i < count; i++) {
        if (toLower(students[i].name) == searchName) {
            showStudent(students[i]);
            found = true;
        }
    }

    if (!found)
        cout << "Student not found!\n";
}


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
    cout << "Sorted by ID!\n";
}

void sortByName(Student students[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (toLower(students[j].name) > toLower(students[j + 1].name)) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    cout << "Sorted by name!\n";
}


void showLowGPA(Student students[], int count) {
    bool found = false;

    cout << "\nStudents with GPA below 2.0:\n";
    for (int i = 0; i < count; i++) {
        double gpa = calculateGPA(students[i]);
        if (gpa < 2.0) {
            cout << students[i].id << " - "
                 << students[i].name
                 << " (GPA: " << gpa << ")\n";
            found = true;
        }
    }

    if (!found)
        cout << "No students found.\n";
}


int main() {
    Student students[MAX_STUDENTS];
    int studentCount = 0;
    int choice;

    do {
        cout << "\n--- MAIN MENU ---\n";
        cout << "1. Add Student\n";
        cout << "2. Update Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Search by ID\n";
        cout << "5. Search by Name\n";
        cout << "6. Sort by ID\n";
        cout << "7. Sort by Name\n";
        cout << "8. Low GPA Report\n";
        cout << "9. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(students, studentCount); break;
            case 2: updateStudent(students, studentCount); break;
            case 3: removeStudent(students, studentCount); break;
            case 4: searchById(students, studentCount); break;
            case 5: searchByName(students, studentCount); break;
            case 6: sortById(students, studentCount); break;
            case 7: sortByName(students, studentCount); break;
            case 8: showLowGPA(students, studentCount); break;
            case 9: cout << "Program ended.\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 9);

    return 0;
}


