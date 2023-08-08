/*Name: Md Mubin Islam Alif
Roll:2107090*/


#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Course;
class Student;

class University;

class Menu {
public:
    static int displayMainMenu();
    static int displayStudentMenu();
    static int displayAuthorityMenu();
};

class University {
private:
    vector<Course> courses;
    vector<Student> students;

public:
    friend class Course;
    friend class Student;
    friend class Menu;

    void addCourse(int code, const string& name, int max, float min_cgpa);
    void enrollStudent(const string& student_name, float student_cgpa, int courseIndex);
    void displayEnrolledStudents() const;
    void displayCourses() const;
    void displayStudentInformation(const string& studentName) const;
    void displayAuthorityInformation() const;
};

class Course {
private:
    int coursecode;
    string coursename;
    int maxseats;
    int enrolledseats;
    float minimum_cgpa;

public:
    Course() : coursecode(0), coursename(""), maxseats(0), enrolledseats(0), minimum_cgpa(0.0) {}

    Course(int code, const string& name, int max, float min_cgpa)
        : coursecode(code), coursename(name), maxseats(max), enrolledseats(0), minimum_cgpa(min_cgpa) {}

    ~Course() {}

    friend void University::addCourse(int code, const string& name, int max, float min_cgpa);
    friend void University::enrollStudent(const string& student_name, float student_cgpa, int courseIndex);
    friend void University::displayCourses() const;
    friend void University::displayStudentInformation(const string& studentName) const;
    friend void University::displayAuthorityInformation() const;

    void displayInformation() const {
        cout << "Course Code: " << coursecode << endl;
        cout << "Course Name: " << coursename << endl;
        cout << "Enrolled Seats: " << enrolledseats << "/" << maxseats << endl;
        cout << "Minimum CGPA: " << minimum_cgpa << endl;
    }

    int getMaxSeats() const {
        return maxseats;
    }

    int getEnrolledSeats() const {
        return enrolledseats;
    }

    float getMinimumCGPA() const {
        return minimum_cgpa;
    }

    bool enrollStudent(float student_cgpa) {
        if (enrolledseats < maxseats && student_cgpa >= minimum_cgpa) {
            enrolledseats++;
            return true;
        }
        return false;
    }
};

class Student {
private:
    string name;
    float cgpa;
    vector<int> enrolledCourses;

public:
    Student() : name(""), cgpa(0.0) {}

    Student(const string& student_name, float student_cgpa)
        : name(student_name), cgpa(student_cgpa) {}

    const string& getName() const {
        return name;
    }

    float getCGPA() const {
        return cgpa;
    }

    friend class University;
};

void University::addCourse(int code, const string& name, int max, float min_cgpa) {
    courses.push_back(Course(code, name, max, min_cgpa));
}

void University::enrollStudent(const string& student_name, float student_cgpa, int courseIndex) {
    if (courseIndex >= 0 && courseIndex < courses.size()) {
        if (courses[courseIndex].enrollStudent(student_cgpa)) {
            students.push_back(Student(student_name, student_cgpa));
            students.back().enrolledCourses.push_back(courseIndex);
            cout << "Enrollment successful!" << endl;
        } else {
            cout << "Enrollment failed. The course is full or your CGPA is below the minimum required." << endl;
        }
    } else {
        cout << "Invalid course index. Please choose a valid course." << endl;
    }
}

void University::displayEnrolledStudents() const {
    if (students.empty()) {
        cout << "No students enrolled." << endl;
        return;
    }

    cout << "Enrolled Students Information" << endl;
    for (const Student& student : students) {
        cout << "Name: " << student.getName() << ", CGPA: " << student.getCGPA() << endl;
    }
}

void University::displayCourses() const {
    if (courses.empty()) {
        cout << "No courses available." << endl;
        return;
    }

    cout << "Courses Information" << endl;
    for (const Course& course : courses) {
        course.displayInformation();
        cout << endl;
    }
}

void University::displayStudentInformation(const string& studentName) const {
    bool found = false;
    for (const Student& student : students) {
        if (student.getName() == studentName) {
            cout << "Student Name: " << student.getName() << ", CGPA: " << student.getCGPA() << endl;
            cout << "Enrolled Courses: ";
            for (int courseIndex : student.enrolledCourses) {
                cout << courses[courseIndex].coursename << ", ";
            }
            cout << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Student not found." << endl;
    }
}

void University::displayAuthorityInformation() const {
    displayEnrolledStudents();
    displayCourses();
}

int Menu::displayMainMenu() {
    int choice;
    cout << "Main Menu" << endl;
    cout << "1. Student" << endl;
    cout << "2. Authority" << endl;
    cout << "3. Display Information" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

int Menu::displayStudentMenu() {
    int choice;
    cout << "Student Menu" << endl;
    cout << "1. Enroll in a Course" << endl;
    cout << "2. Display Enrolled Courses" << endl;
    cout << "3. Back" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

int Menu::displayAuthorityMenu() {
    int choice;
    cout << "Authority Menu" << endl;
    cout << "1. Add Course" << endl;
    cout << "2. Display Enrolled Students" << endl;
    cout << "3. Display Courses" << endl;
    cout << "4. Back" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

int main() {
    University myUniversity;

    while (true) {
        int mainChoice = Menu::displayMainMenu();

        switch (mainChoice) {
            case 1: { // Student
                string studentName;
                float studentCGPA;

                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, studentName);
                cout << "Enter your CGPA: ";
                cin >> studentCGPA;

                int studentChoice;
                while (true) {
                    studentChoice = Menu::displayStudentMenu();

                    switch (studentChoice) {
                        case 1: { // Enroll in a Course
                            myUniversity.displayCourses();
                            int chosenCourse;
                            cout << "Enter the course index you want to enroll in (-1 to go back): ";
                            cin >> chosenCourse;
                            if (chosenCourse != -1) {
                                myUniversity.enrollStudent(studentName, studentCGPA, chosenCourse);
                            }
                            break;
                        }
                        case 2: { // Display Enrolled Courses
                            myUniversity.displayStudentInformation(studentName);
                            break;
                        }
                        case 3:
                            break;
                        default:
                            cout << "Invalid choice. Please choose again." << endl;
                    }

                    if (studentChoice == 3) {
                        break;
                    }
                }
                break;
            }
            case 2: { // Authority
                int authorityChoice;
                while (true) {
                    authorityChoice = Menu::displayAuthorityMenu();

                    switch (authorityChoice) {
                        case 1: { // Add Course
                            int code, max;
                            float min_cgpa;
                            string name;

                            cout << "Enter course code: ";
                            cin >> code;
                            cout << "Enter course name: ";
                            cin.ignore();
                            getline(cin, name);
                            cout << "Enter maximum seats: ";
                            cin >> max;
                            cout << "Enter minimum CGPA: ";
                            cin >> min_cgpa;

                            myUniversity.addCourse(code, name, max, min_cgpa);
                            break;
                        }
                        case 2: // Display Enrolled Students
                            myUniversity.displayEnrolledStudents();
                            break;
                        case 3: // Display Courses
                            myUniversity.displayCourses();
                            break;
                        case 4:
                            break;
                        default:
                            cout << "Invalid choice. Please choose again." << endl;
                    }

                    if (authorityChoice == 4) {
                        break;
                    }
                }
                break;
            }
            case 3: // Display Information
                int infoChoice;
                cout << "1. Student" << endl;
                cout << "2. Authority" << endl;
                cout << "Enter your choice: ";
                cin >> infoChoice;

                if (infoChoice == 1) {
                    string studentName;
                    cout << "Enter student name: ";
                    cin.ignore();
                    getline(cin, studentName);
                    myUniversity.displayStudentInformation(studentName);
                } else if (infoChoice == 2) {
                    myUniversity.displayAuthorityInformation();
                } else {
                    cout << "Invalid choice." << endl;
                }
                break;
            case 4:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please choose again." << endl;
        }
    }

    return 0;
}





