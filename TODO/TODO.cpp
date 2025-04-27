#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Structure to hold task data
struct TODO
{
    int id;
    string task;
};

// Global variable to track the last ID
int ID = 0;

// Function declarations
void banner();
void addTask();
void showTask();
int searchTask();
void deleteTask();
void updateTask();
void loadLastID();  //  function to load last ID

int main()
{
    system("cls");  // Clear the screen at start
    loadLastID();   // Load last ID when program starts

    while (true)
    {
        banner();
        cout << "\n0. Exit";
        cout << "\n1. Add Task";
        cout << "\n2. Show Task";
        cout << "\n3. Search Task";
        cout << "\n4. Delete Task";
        cout << "\n5. Update Task";

        int choice;
        cout << "\n\nEnter Choice: ";
        cin >> choice;

        // Handle menu choice
        switch (choice)
        {
        case 0:
            cout << "\nExiting program... Goodbye!" << endl;
            return 0;  // Exit the program

        case 1:
            addTask();
            break;

        case 2:
            showTask();
            break;

        case 3:
            searchTask();
            break;

        case 4:
            deleteTask();
            break;

        case 5:
            updateTask();
            break;

        default:
            cout << "\nInvalid choice! Try again.\n";
            break;
        }
    }
}

// Display banner / heading
void banner()
{
    cout << "___________________________________" << endl;
    cout << "\t       MY TODO" << endl;
    cout << "___________________________________" << endl;
}

// Add a new task
void addTask()
{
    system("cls");
    banner();

    TODO todo;

    // Get task input
    cout << "Enter new Task: ";
    cin.get(); // Clear buffer
    getline(cin, todo.task);

    char save;
    cout << "Save? (y/n): ";
    cin >> save;

    if (save == 'y')
    {
        ID++;  // Increment global ID

        // Open file to append new task
        ofstream fout("todo.txt", ios::app);
        fout << ID << "\n" << todo.task << "\n";
        fout.close();

        cout << "\nTask Added Successfully!" << endl;
    }

    system("pause");  // Pause so user can see message
    system("cls");
}

// Display all tasks
void showTask()
{
    char exit;
    do
    {
        system("cls");
        banner();

        TODO todo;
        ifstream fin("todo.txt");

        if (!fin)
        {
            cout << "Error: Unable to open todo.txt file!" << endl;
            return;
        }

        cout << "Tasks: " << endl;
        bool taskFound = false;

        while (fin >> todo.id)
        {
            fin.ignore();
            getline(fin, todo.task);

            if (!todo.task.empty())
            {
                cout << "\t" << todo.id << ": " << todo.task << endl;
                taskFound = true;
            }
        }

        if (!taskFound)
        {
            cout << "\tNo Task Found!" << endl;
        }

        fin.close();

        cout << "\nExit? (y/n): ";
        cin >> exit;

    } while (exit != 'y');

    system("cls");
}

// Search for a task by ID
int searchTask()
{
    system("cls");
    banner();

    int id;
    cout << "Enter Id: ";
    cin >> id;

    TODO todo;
    ifstream fin("todo.txt");

    while (fin >> todo.id)
    {
        fin.ignore();
        getline(fin, todo.task);

        if (todo.id == id)
        {
            system("cls");
            cout << "\t" << todo.id << ": " << todo.task << endl;
            fin.close();
            return id;
        }
    }

    fin.close();
    system("cls");
    cout << "Task with id: " << id << " not found" << endl;
    return 0;
}

// Delete a task
void deleteTask()
{
    system("cls");
    int id = searchTask();  // Get ID to delete

    if (id != 0)
    {
        char del;
        cout << "\n\tDelete? (y/n): ";
        cin >> del;

        if (del == 'y')
        {
            TODO todo;
            ofstream tempFile("temp.txt");
            ifstream fin("todo.txt");

            if (!fin || !tempFile)
            {
                cout << "\nError opening files!" << endl;
                return;
            }

            // Copy all tasks except the one to delete
            while (fin >> todo.id)
            {
                fin.ignore();
                getline(fin, todo.task);

                if (todo.id != id)
                {
                    tempFile << todo.id << "\n" << todo.task << "\n";
                }
            }

            fin.close();
            tempFile.close();

            // Replace old file with new one
            remove("todo.txt");
            rename("temp.txt", "todo.txt");

            system("cls");
            cout << "\n\tDeleted Successfully!!" << endl;
        }
        else
        {
            system("cls");
            cout << "Task not Deleted!!" << endl;
        }
    }
}

// Update a task
void updateTask()
{
    system("cls");
    int idToUpdate = searchTask();

    if (idToUpdate != 0)
    {
        char update;
        cout << "\n\tUpdate? (y/n): ";
        cin >> update;

        if (update == 'y')
        {
            cin.ignore();

            string newTask;
            cout << "\n\tEnter New Task: ";
            getline(cin, newTask);

            TODO todo;
            ifstream fin("todo.txt");
            ofstream tempFile("temp.txt");

            if (!fin || !tempFile)
            {
                cout << "\nError opening files!" << endl;
                return;
            }

            while (fin >> todo.id)
            {
                fin.ignore();
                getline(fin, todo.task);

                if (todo.id == idToUpdate)
                {
                    tempFile << todo.id << "\n" << newTask << "\n";
                }
                else
                {
                    tempFile << todo.id << "\n" << todo.task << "\n";
                }
            }

            fin.close();
            tempFile.close();

            remove("todo.txt");
            rename("temp.txt", "todo.txt");

            system("cls");
            cout << "\n\tTask updated Successfully!!" << endl;
        }
        else
        {
            system("cls");
            cout << "\n\tTask not updated!!" << endl;
        }
    }
}

// Load the last ID from the file when program starts
void loadLastID()
{
    ifstream fin("todo.txt");
    TODO todo;
    int lastID = 0;

    while (fin >> todo.id)
    {
        fin.ignore();
        getline(fin, todo.task);

        if (!todo.task.empty())
        {
            lastID = todo.id;  // Keep updating with latest id
        }
    }

    ID = lastID;  // Set global ID
    fin.close();
}
