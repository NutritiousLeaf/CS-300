#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <limits>

using namespace std;

struct Course {
    string courseId;
    string courseTitle;
    vector<string> prerequisites;
};

class CoursePlanner {
private:
    vector<Course> courses;

public:
    void loadCourses(const string& fileName) {
        ifstream file(fileName);
        if (!file.is_open()) {
            cout << "? Could not open file: " << fileName << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            Course course;
            stringstream ss(line);
            string token;

            // Read course ID
            getline(ss, course.courseId, ',');

            // Read course title
            getline(ss, course.courseTitle, ',');

            // Read prerequisites
            while (getline(ss, token, ',')) {
                course.prerequisites.push_back(token);
            }

            courses.push_back(course);
        }

        file.close();
        cout << "? Courses successfully loaded.\n";
    }

    void printCourseList() const {
        if (courses.empty()) {
            cout << "?? No course data loaded.\n";
            return;
        }

        vector<Course> sortedCourses = courses;
        sort(sortedCourses.begin(), sortedCourses.end(), [](const Course& a, const Course& b) {
            return a.courseId < b.courseId;
            });

        for (const auto& course : sortedCourses) {
            cout << course.courseId << ", " << course.courseTitle << endl;
        }
    }

    void printCourseDetails(const string& courseId) const {
        for (const auto& course : courses) {
            if (course.courseId == courseId) {
                cout << course.courseId << ", " << course.courseTitle << endl;
                if (!course.prerequisites.empty()) {
                    cout << "Prerequisites: ";
                    for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                        cout << course.prerequisites[i];
                        if (i < course.prerequisites.size() - 1) cout << ", ";
                    }
                    cout << endl;
                }
                else {
                    cout << "Prerequisites: None\n";
                }
                return;
            }
        }
        cout << "? Course not found.\n";
    }
};

int main() {
    CoursePlanner planner;
    int choice = 0;

    while (true) {
        cout << "\nWelcome to the course planner.\n";
        cout << "  1. Load Data Structure\n";
        cout << "  2. Print Course List\n";
        cout << "  3. Print Course\n";
        cout << "  9. Exit\n";
        cout << "What would you like to do? ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "? Invalid input. Please enter a valid menu option.\n";
            continue;
        }

        cin.ignore();  // Clean newline from buffer

        if (choice == 1) {
            string fileName;
            cout << "Enter file name to load: ";
            getline(cin, fileName);
            planner.loadCourses(fileName);
        }
        else if (choice == 2) {
            planner.printCourseList();
        }
        else if (choice == 3) {
            string courseId;
            cout << "Enter course ID: ";
            getline(cin, courseId);
            planner.printCourseDetails(courseId);
        }
        else if (choice == 9) {
            cout << "?? Exiting Course Planner. Goodbye!\n";
            break;
        }
        else {
            cout << "? " << choice << " is not a valid option.\n";
        }
    }

    return 0;
}
