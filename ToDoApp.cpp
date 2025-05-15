#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int ShowMenu();
void AddToDo();
void SeeToDoList();
void PressEnterToContinue();
void DeleteTask();

int main()
{
    bool quit = false;
    int choice = 0;

    std::cout << "Welcome\n";
    while (!quit) {
        system("cls");
        choice = ShowMenu();
        system("cls"); 

        switch (choice)
        {
        case 1:
            AddToDo();
            PressEnterToContinue();
            break;
        case 2:
            SeeToDoList();
            PressEnterToContinue();
            break;
        case 3:
            DeleteTask();
            PressEnterToContinue();
            break;
        case 4:
            quit = true;
            std::cout << "Goodbye!\n";
            break;
        default:
            std::cout << "Invalid input\n";
            PressEnterToContinue();
            break;
        }
    }

    return 0;
}

int ShowMenu() {
    int choice;
    std::cout << "\n===== ToDo Menu =====\n";
    std::cout << "1. Add a ToDo\n";
    std::cout << "2. See ToDo List\n";
    std::cout << "3. Delete a ToDo\n";
    std::cout << "4. Quit\n";
    std::cout << "Choose an option: ";
    std::cin >> choice;

    // Handle invalid input (non-numeric)
    if (std::cin.fail()) {
        std::cin.clear(); // Clear error flag
        std::cin.ignore(1000, '\n'); // Skip to the next line
        return 0;
    }

    return choice;
}

void AddToDo() {
    std::cin.ignore(); // Flush leftover newline
    std::string task;
    std::cout << "Enter your task: ";
    std::getline(std::cin, task);

    // Ensure the file exists (it will be created if it doesn't)
    std::ofstream file("todo.txt", std::ios::app); // append mode
    if (file.is_open()) {
        file << task << '\n';
        file.close();
        std::cout << "Task added.\n";
    }
    else {
        std::cerr << "Error: Unable to create or open file.\n";
    }
}

void SeeToDoList() {
    // Check if the file exists using ifstream
    std::ifstream testFile("todo.txt");
    if (!testFile.good()) {
        std::cout << "\n===== ToDo List =====\n";
        std::cout << "No tasks found (file does not exist yet).\n";
        return;
    }
    testFile.close();

    std::ifstream file("todo.txt");
    std::string line;
    int count = 1;

    std::cout << "\n===== ToDo List =====\n";
    while (std::getline(file, line)) {
        std::cout << count++ << ". " << line << '\n';
    }
    file.close();

    if (count == 1) {
        std::cout << "No tasks found.\n";
    }
}

void PressEnterToContinue() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

void DeleteTask() {
    std::ifstream file("todo.txt");
    if (!file.is_open()) {
        std::cout << "No tasks found (file does not exist).\n";
        return;
    }

    // Read all tasks into a vector
    std::string line;
    std::string tasks[100]; // Allow up to 100 tasks
    int count = 0;

    while (std::getline(file, line) && count < 100) {
        tasks[count++] = line;
    }
    file.close();

    if (count == 0) {
        std::cout << "No tasks found.\n";
        return;
    }

    // Show tasks
    std::cout << "\n===== ToDo List =====\n";
    for (int i = 0; i < count; ++i) {
        std::cout << (i + 1) << ". " << tasks[i] << '\n';
    }

    // Get user choice
    int indexToDelete;
    std::cout << "Enter the number of the task to delete: ";
    std::cin >> indexToDelete;

    if (std::cin.fail() || indexToDelete < 1 || indexToDelete > count) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid task number.\n";
        return;
    }

    // Rewrite the file without the selected task
    std::ofstream outFile("todo.txt");
    if (!outFile.is_open()) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    for (int i = 0; i < count; ++i) {
        if (i != indexToDelete - 1) {
            outFile << tasks[i] << '\n';
        }
    }

    outFile.close();
    std::cout << "Task deleted.\n";
}
