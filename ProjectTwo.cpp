// ProjectTwo.cpp
// CS 300
// Aleksandr Donovan

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>    // for transform and sort
#include <cctype>       // for toupper
using namespace std;

// Struct to store course information
struct Course {
    string number;                     // Course number (e.g., CSCI300, etc)
    string title;                      // Course title
    vector<string> prerequisites;      // List of prerequisite course numbers
};

// Global hash table to store the courses
unordered_map<string, Course> courseTable;

// Function to convert a string to uppercase (used for course numbers and prerequisites to make it user friendly) 
string toUpperCase(const string& str) {
    string upperStr = str;
    transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
    return upperStr;
}

// Function to load courses from the file into the global hash table
void loadCoursesFromFile() {
    const string fileName = "CS 300 ABCU_Advising_Program_Input.csv";

    ifstream file(fileName);  // Opens the file for reading

    // Checks if the file failed to open
    if (!file.is_open()) {
        cout << "Error: Unable to open file " << fileName << endl;   // Error message
        return;
    }

    unordered_map<string, Course> tempTable;  // Temporary table to validate prerequisites
    vector<string> allCourseNumbers;          // List of course numbers for validation

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;  // Skips the blank lines

        stringstream ss(line);
        string token;
        vector<string> tokens;

        // Splits the line into tokens using ',' as the delimiter
        while (getline(ss, token, ',')) {
            if (!token.empty()) {
                tokens.push_back(token);
            }
        }

        // Basic validation: must have at least a course number and the title
        if (tokens.size() < 2) {
            cout << "Error: Invalid line format: " << line << endl;
            continue;
        }

        // Extract course number and the title
        string courseNumber = toUpperCase(tokens[0]);  // Normalize case
        string courseTitle = tokens[1];

        Course course;
        course.number = courseNumber;
        course.title = courseTitle;

        // Add prerequisites if there are any
        for (size_t i = 2; i < tokens.size(); ++i) {
            course.prerequisites.push_back(toUpperCase(tokens[i]));
        }

        // Add course to the temporary table
        tempTable[courseNumber] = course;
        allCourseNumbers.push_back(courseNumber);
    }

    // Validate that all prerequisites exist in the course list
    for (const auto& pair : tempTable) {
        const Course& course = pair.second;

        for (const string& prereq : course.prerequisites) {
            if (tempTable.find(prereq) == tempTable.end()) {
                // Output a warning for missing prerequisites and a not critical error
                cout << "Warning: Prerequisite " << prereq
                    << " for course " << course.number << " not found in file." << endl;
            }
        }
    }

    // Assigns the validated data to the global hash table
    courseTable = tempTable;

    cout << "Data loaded successfully.\n";

    file.close();  // Closes the file
}

// Function to print all courses in alphanumeric order by course number
void printCourseList() {
    if (courseTable.empty()) {
        cout << "Course list is empty. Please load data first.\n";
        return;
    }

    vector<Course> courseList;

    // Copy all courses from the hash table to a vector
    for (const auto& pair : courseTable) {
        courseList.push_back(pair.second);
    }

    // Sort the vector based on course number (e.g., CSCI100 < CSCI200)
    sort(courseList.begin(), courseList.end(), [](const Course& a, const Course& b) {
        return a.number < b.number;
        });

    // Print the sorted course list
    cout << "\nHere is a sample schedule:\n";
    for (const Course& course : courseList) {
        cout << course.number << ", " << course.title << "\n";
    }
}

// Function to print detailed information for a specific course
void searchCourse(const string& inputNumber) {
    string courseNumber = toUpperCase(inputNumber);  // Normalizes the input to uppercase

    // Search for course in hash table
    auto it = courseTable.find(courseNumber);
    if (it == courseTable.end()) {
        cout << "Course " << inputNumber << " not found.\n";  
        return;
    }

    const Course& course = it->second;

    // Prints the course details
    cout << course.number << ", " << course.title << "\n";

    // Prints the prerequisites
    // If there are no prerequisites
    if (course.prerequisites.empty()) {
        cout << "Prerequisites: None\n";
    }
    // Else prints them
    else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1) {
                cout << ", ";
            }
        }
        cout << "\n";
    }
}

// Function to display the main menu to the user
void displayMenu() {
    cout << "\n====== ABCU Course Planner ======\n";
    cout << "1. Load Data Structure\n";
    cout << "2. Print Course List\n";
    cout << "3. Print Course\n";
    cout << "9. Exit\n";
    cout << "What would you like to do? ";
}

// Main loop that handles user interaction with the menu
void runProgram() {
    int userChoice = 0;
    string courseNumber;

    while (true) {
        displayMenu();           // Show menu options
        string input;
        getline(cin, input);     // Get the full line for input
        stringstream ss(input);
        ss >> userChoice;        // Converts to int


        switch (userChoice) {
        case 1:
            // Load the hardcoded input file into the hash table
            loadCoursesFromFile();
            break;

        case 2:
            // print all courses in alphanumeric order by course number
            printCourseList();
            break;

        case 3:
            // prints detailed information for a specific course
            cout << "Enter course number: ";
            getline(cin, courseNumber);
            searchCourse(courseNumber);
            break;

        case 9:
            // Exit the program
            cout << "Thank you for using the course planner!\n";
            return;

        default:
            // Handle invalid menu input
            cout << userChoice << " is not a valid option.\n";
            break;
        }
    }
}

int main() {
    runProgram();  // Start the program by launching the menu loop
    return 0;
}
