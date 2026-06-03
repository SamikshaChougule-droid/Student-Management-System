/*
------------------------------------------
Student Management System
Developed By : Samiksha Chougule
Language     : C++
Concepts Used:
- Object Oriented Programming
- File Handling
- Vectors
- Functions
- Menu Driven Programming
------------------------------------------
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Student
{
public:
    int rollNo;
    string name;
    int age;
    string course;

    void input()
    {
        cout << "\nEnter Roll Number: ";
        cin >> rollNo;

        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;

        cin.ignore();

        cout << "Enter Course: ";
        getline(cin, course);
    }

    void display()
    {
        cout << "\n------------------------";
        cout << "\nRoll Number : " << rollNo;
        cout << "\nName        : " << name;
        cout << "\nAge         : " << age;
        cout << "\nCourse      : " << course;
        cout << "\n------------------------";
    }
};

string filename = "students.txt";

void addStudent()
{
    Student s;
    s.input();

    ofstream file(filename, ios::app);

    file << s.rollNo << "|"
         << s.name << "|"
         << s.age << "|"
         << s.course << endl;

    file.close();

    cout << "\nStudent Added Successfully!\n";
}

void displayStudents()
{
    ifstream file(filename);

    string line;

    cout << "\n===== STUDENT RECORDS =====\n";

    while (getline(file, line))
    {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);

        cout << "\nRoll Number : "
             << line.substr(0, pos1);

        cout << "\nName        : "
             << line.substr(pos1 + 1, pos2 - pos1 - 1);

        cout << "\nAge         : "
             << line.substr(pos2 + 1, pos3 - pos2 - 1);

        cout << "\nCourse      : "
             << line.substr(pos3 + 1);

        cout << "\n------------------------";
    }

    file.close();
}

void searchStudent()
{
    int roll;
    cout << "\nEnter Roll Number to Search: ";
    cin >> roll;

    ifstream file(filename);

    string line;
    bool found = false;

    while (getline(file, line))
    {
        size_t pos1 = line.find('|');

        int storedRoll = stoi(line.substr(0, pos1));

        if (storedRoll == roll)
        {
            size_t pos2 = line.find('|', pos1 + 1);
            size_t pos3 = line.find('|', pos2 + 1);

            cout << "\nStudent Found!\n";

            cout << "\nRoll Number : "
                 << line.substr(0, pos1);

            cout << "\nName        : "
                 << line.substr(pos1 + 1, pos2 - pos1 - 1);

            cout << "\nAge         : "
                 << line.substr(pos2 + 1, pos3 - pos2 - 1);

            cout << "\nCourse      : "
                 << line.substr(pos3 + 1);

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\nStudent Not Found!\n";
    }

    file.close();
}

void updateStudent()
{
    int roll;
    cout << "\nEnter Roll Number to Update: ";
    cin >> roll;

    ifstream file(filename);
    vector<string> records;

    string line;
    bool found = false;

    while (getline(file, line))
    {
        size_t pos1 = line.find('|');

        int storedRoll = stoi(line.substr(0, pos1));

        if (storedRoll == roll)
        {
            Student s;

            cout << "\nEnter New Details:\n";
            s.rollNo = roll;

            cin.ignore();

            cout << "Enter Name: ";
            getline(cin, s.name);

            cout << "Enter Age: ";
            cin >> s.age;

            cin.ignore();

            cout << "Enter Course: ";
            getline(cin, s.course);

            string updatedRecord =
                to_string(s.rollNo) + "|" +
                s.name + "|" +
                to_string(s.age) + "|" +
                s.course;

            records.push_back(updatedRecord);

            found = true;
        }
        else
        {
            records.push_back(line);
        }
    }

    file.close();

    ofstream outFile(filename);

    for (string record : records)
    {
        outFile << record << endl;
    }

    outFile.close();

    if (found)
        cout << "\nStudent Updated Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

void deleteStudent()
{
    int roll;
    cout << "\nEnter Roll Number to Delete: ";
    cin >> roll;

    ifstream file(filename);

    vector<string> records;
    string line;

    bool found = false;

    while (getline(file, line))
    {
        size_t pos1 = line.find('|');

        int storedRoll = stoi(line.substr(0, pos1));

        if (storedRoll == roll)
        {
            found = true;
            continue;
        }

        records.push_back(line);
    }

    file.close();

    ofstream outFile(filename);

    for (string record : records)
    {
        outFile << record << endl;
    }

    outFile.close();

    if (found)
        cout << "\nStudent Deleted Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

int main()
{
    int choice;

    do
    {
        cout << "\n\n===== STUDENT MANAGEMENT SYSTEM =====";
        cout << "\n1. Add Student";
        cout << "\n2. Display Students";
        cout << "\n3. Search Student";
        cout << "\n4. Update Student";
        cout << "\n5. Delete Student";
        cout << "\n6. Exit";
        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}
