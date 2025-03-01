#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Expense {
    int id;
    string description;
    double amount;
    string createdAt;
    string updatedAt;
};

// Get current timestamp
string getCurrentTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << (1900 + ltm->tm_year) << "-"
       << setw(2) << setfill('0') << (1 + ltm->tm_mon) << "-"
       << setw(2) << setfill('0') << ltm->tm_mday << " "
       << setw(2) << setfill('0') << ltm->tm_hour << ":"
       << setw(2) << setfill('0') << ltm->tm_min << ":"
       << setw(2) << setfill('0') << ltm->tm_sec;
    return ss.str();
}

// Load expenses from text file
vector<Expense> loadExpenses() {
    vector<Expense> expenses;
    ifstream file("expenses.txt");
    if (!file) return expenses;

    Expense e;
    while (file >> e.id >> ws && getline(file, e.description, '|') &&
           file >> e.amount >> ws && getline(file, e.createdAt, '|') &&
           getline(file, e.updatedAt)) {
        expenses.push_back(e);
    }
    file.close();
    return expenses;
}

// Save expenses to text file
void saveExpenses(const vector<Expense>& expenses) {
    ofstream file("expenses.txt");
    for (const auto& e : expenses) {
        file << e.id << " " << e.description << "|"
             << e.amount << " " << e.createdAt << "|"
             << e.updatedAt << endl;
    }
    file.close();
}

// Generate a new unique ID
int generateID(const vector<Expense>& expenses) {
    int maxID = 0;
    for (const auto& e : expenses) maxID = max(maxID, e.id);
    return maxID + 1;
}

// Add a new expense
void addExpense(const string& description, double amount) {
    vector<Expense> expenses = loadExpenses();
    Expense newExpense{generateID(expenses), description, amount, getCurrentTime(), getCurrentTime()};
    expenses.push_back(newExpense);
    saveExpenses(expenses);
    cout << "Expense added successfully (ID: " << newExpense.id << ")\n";
}

// Update an existing expense
void updateExpense(int id, const string& newDescription, double newAmount) {
    vector<Expense> expenses = loadExpenses();
    for (auto& e : expenses) {
        if (e.id == id) {
            e.description = newDescription;
            e.amount = newAmount;
            e.updatedAt = getCurrentTime();
            saveExpenses(expenses);
            cout << "Expense updated successfully.\n";
            return;
        }
    }
    cout << "Expense not found.\n";
}

// Delete an expense
void deleteExpense(int id) {
    vector<Expense> expenses = loadExpenses();
    auto it = remove_if(expenses.begin(), expenses.end(), [&](const Expense& e) { return e.id == id; });

    if (it != expenses.end()) {
        expenses.erase(it, expenses.end());
        saveExpenses(expenses);
        cout << "Expense deleted successfully.\n";
    } else {
        cout << "Expense not found.\n";
    }
}

// List all expenses
void listExpenses() {
    vector<Expense> expenses = loadExpenses();
    if (expenses.empty()) {
        cout << "No expenses recorded.\n";
        return;
    }

    cout << left << setw(5) << "ID" << setw(20) << "Description" << setw(10) << "Amount" << "Created At\n";
    cout << string(50, '-') << endl;

    for (const auto& e : expenses) {
        cout << left << setw(5) << e.id << setw(20) << e.description << "$" << setw(9) << e.amount << e.createdAt << "\n";
    }
}

// Show total expense summary
void showSummary(int month = 0) {
    vector<Expense> expenses = loadExpenses();
    double total = 0;

    for (const auto& e : expenses) {
        if (month > 0) {
            int expenseMonth = stoi(e.createdAt.substr(5, 2));
            if (expenseMonth != month) continue;
        }
        total += e.amount;
    }

    if (month > 0)
        cout << "Total expenses for month " << month << ": $" << total << "\n";
    else
        cout << "Total expenses: $" << total << "\n";
}

// Main CLI handler
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: expense-cli <command> [arguments]\n";
        return 1;
    }

    string command = argv[1];

    if (command == "add" && argc >= 4) {
        addExpense(argv[2], stod(argv[3]));
    } else if (command == "update" && argc >= 5) {
        updateExpense(stoi(argv[2]), argv[3], stod(argv[4]));
    } else if (command == "delete" && argc >= 3) {
        deleteExpense(stoi(argv[2]));
    } else if (command == "list") {
        listExpenses();
    } else if (command == "summary") {
        if (argc == 4 && string(argv[2]) == "--month")
            showSummary(stoi(argv[3]));
        else
            showSummary();
    } else {
        cout << "Invalid command.\n";
    }

    return 0;
}
