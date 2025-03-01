# Expense Management CLI

## Overview
This is a simple command-line application for managing personal expenses. It allows users to add, update, delete, list, and summarize expenses stored in a text file.
It is inspired from the [Expense Tracker](https://roadmap.sh/projects/expense-tracker) project featured in the [Backend Roadmap](https://roadmap.sh/backend) from [roadmap.sh](https://roadmap.sh/).

## Features
- Add new expenses with a description and amount.
- Update existing expenses.
- Delete an expense by ID.
- List all recorded expenses.
- Show total expenses with an optional monthly filter.

## Requirements
- C++ compiler (GCC, Clang, MSVC, etc.)
- Standard C++ libraries

## Installation
1. Clone or download the repository.
2. Compile the source code using a C++ compiler:
   ```sh
   g++ -o expense-cli expense.cpp
   ```
3. Run the executable:
   ```sh
   ./expense-cli <command> [arguments]
   ```

## Usage
### Add an expense
```sh
./expense-cli add "Description" Amount
```
Example:
```sh
./expense-cli add "Lunch" 12.50
```

### Update an expense
```sh
./expense-cli update ID "New Description" NewAmount
```
Example:
```sh
./expense-cli update 1 "Dinner" 15.00
```

### Delete an expense
```sh
./expense-cli delete ID
```
Example:
```sh
./expense-cli delete 1
```

### List all expenses
```sh
./expense-cli list
```

### Show total expenses
```sh
./expense-cli summary
```

### Show total expenses for a specific month
```sh
./expense-cli summary --month MM
```
Example:
```sh
./expense-cli summary --month 02
```
(This will show expenses for February.)

## Data Storage
Expenses are stored in a text file named `expenses.txt` with the format:
```
ID Description|Amount CreatedAt|UpdatedAt
```

## License
This project is licensed under the MIT License.

## Author
Developed by Srinithesh A.

