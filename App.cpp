#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include "functions.cpp"
using namespace std;

class App {
  public:
    void menu();
    void insertRecord();
    void showAllRecords();
    void searchRecord();
    void updateRecord();
    void deleteRecord();
    void backHome();
};

void App::menu() {
  int choice;
  char repeat;
  // clear the terminal
  system("cls");
  // display STUDENT MANAGEMENT SYSTEM Label
  showLabel("STUDENT MANAGEMENT SYSTEM");
  // showing menu options
  cout << "\n\n\t\t\t\033[1;32m[1]\033[0m Insert New Student Record" << endl;
  cout << "\t\t\t\033[1;32m[2]\033[0m Show All Student Records" << endl;
  cout << "\t\t\t\033[1;32m[3]\033[0m Search Student Record" << endl;
  cout << "\t\t\t\033[1;32m[4]\033[0m Update Student Record" << endl;
  cout << "\t\t\t\033[1;32m[5]\033[0m Delete Student Record" << endl;
  cout << "\t\t\t\033[1;32m[6]\033[0m Exit" << endl;
  cout << "\n\t\t\t You can choose :  \033[1;32m1/2/3/4/5/6\033[0m" << endl;
  cout << "\n\n\t\t\t Enter your choice : ";
  cin >> choice;
  // choosing conditions with user's input
  switch (choice)
  {
  case 1:
    do
    {
      insertRecord();
      cout << "\n\t\t\tAdd another student record ? (Y/N) : ";
      cin >> repeat;
    } while (repeat == 'y' || repeat == 'Y');
    menu();
    break;
  case 2:
    showAllRecords();
    break;
  case 3:
    searchRecord();
    break;
  case 4:
    updateRecord();
    break;
  case 5:
    deleteRecord();
    break;
  case 6:
    exit(0);
    break;
  default:
    cout << "\n\t\t\t Invalid choice... Please try again!" << endl;
    sleep(1.5);
    menu();
    break;
  }
}
void App::insertRecord() {
  // clear the terminal
  system("cls");
  // display INSERT NEW STUDENT RECORD Label
  showLabel("Insert New Student Record");
  // display Inserted Records
  showInsertedRecords();
  // asking for value to insert
  string content;
  content = askingInfo(" ");
  fstream file;
  file.open("studentRecords.txt", ios::app | ios::out);
  if (file.is_open())
  {
    file << content <<endl;
  }
  file.close();
}
void App::showAllRecords() {
  // clear the terminal
  system("cls");
  // display STUDENT RECORD Label
  showLabel(" Show All Student Records");
  // display Inserted Records
  showInsertedRecords();
  // Heading back to MENU
  backHome();
}
void App::searchRecord() {
  // clear the terminal
  system("cls");
  string search_id;
  // display SEARCH STUDENT RECORD Label
  showLabel("  Search Student Record  ");
  // display Inserted Records
  showInsertedRecords();
  // asking for ID to search
  search_id = askingID("Search");
  // Search the record
  searchByLine(getLineByID(search_id));
  // Heading to MENU
  backHome();
}
void App::updateRecord() {
  // clear the terminal
  system("cls");
  string update_id;
  // display UPDATE STUDENT RECORD Label
  showLabel("  Update Student Record  ");
  // display Inserted Records
  showInsertedRecords();
  // asking for ID to update
  update_id = askingID("Update");
  // check if the ID existed
  int updatable_line = getLineByID(update_id);
  // if it's not found, asking to back to menu. Otherwize asking for new values to update.
  if (updatable_line == -1)
  {
    cout << "\n\n\t\t\t\033[31mResult : Not Found...!\033[0m" << "\n\n";
    sleep(1.5);
    backHome();
  } else {
    updateByLine(updatable_line, askingInfo(" new "));
    backHome();
  }
}
void App::deleteRecord() {
  // clear the terminal
  system("cls");
  string delete_id;
  // display DELETE STUDENT RECORD Label
  showLabel("  Delete Student Record  ");
  // display Inserted Records
  showInsertedRecords();
  // asking for ID to delete
  delete_id = askingID("Delete");
  // Delete the record
  deleteByLine(getLineByID(delete_id));
  // Heading back to MENU
  backHome();
}
void App::backHome() {
  // initialize variable
  char answer;
  // asking for backing home
  cout << "\n\n";
  cout << "\t\t\t Get back Home (Y/N) ? : ";
  cin >> answer;
  // conditions
  if (answer == 'y' || answer == 'Y')
  {
    menu();
  } else {
    cout << "\n\t\t\tBye!\n\n" << endl;
    exit(0);
  }
}