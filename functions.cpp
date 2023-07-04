#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// FUNCTIONS - DEFINITIONS

int getTotalLines(string filename);
int getLineByID(string id);
string replaceUnderscore(string text);
string askingInfo(string context);
string askingID(string word);
void readLine(string filename, int lineNum);
void showRecords(string filename);
void showLabel(string label);
void searchByLine(int line);
void updateByLine(int line, string new_value);
void deleteByLine(int line);
void showInsertedRecords();

// FUNCTIONS - BODYS

// get number of lines from a text file
int getTotalLines(string filename) {
  // creating a file pointer
  fstream reading_file;
  // create helping variables
  string line;
  int count = 0;
  // reading file
  reading_file.open(filename, ios::in);
  if (reading_file.is_open())
  {
    while (getline(reading_file, line))
    {
      // read one line, count increased 1
      count++;
    }
    // close file
    reading_file.close();
  }
  // return number of count
  return count;
}

// read value from each line in text file
void readLine(string filename, int lineNum) {
  // creating a file pointer
  fstream myfile;
  // create helping variables
  string line;
  int count_line = 0;
  // reading file
  myfile.open(filename, ios::in);
  if (myfile.is_open())
  {
    while (getline(myfile, line))
    {
      // read one line, count increased 1
      count_line++;
      // if the count_line equal line we want, print out
      if (count_line == lineNum)
      {
        cout <<"\t\t\t" << line << endl;
        break;
      }
    }
    // close file
    myfile.close();
  }
}

// replace the underscore with Space
string replaceUnderscore(string text) {
  string newText = text;
  // looping through each character to find underscore
  for (int i = 0; i < text.length(); i++)
  {
    if (newText[i] == '_')
    {
      // when found it, replace with space
      newText.replace(i, 1, " ");
    }
  }
  // return replaced text
  return newText;
}

// show records
void showRecords(string filename) {
  // get total lines of a file
  int number_of_line = getTotalLines(filename);
  // if there is no line, print out no record
  if (number_of_line == 0)
  {
    cout << "\t\t\tNo record has been inserted!" <<endl;
  } else {
    // else print out each line.
    for (int i = 1; i <= number_of_line; i++)
    {
      readLine(filename, i);
    }
  }
}

// Showing label of each section based on input
void showLabel(string label) {
  // print out the header
  cout << "\t\t\t\033[1;32m-------------------------------------------\033[0m\n";
  cout << "\t\t\t\033[1;32m-------  "<< label <<  "  -------\033[0m\n";
  cout << "\t\t\t\033[1;32m-------------------------------------------\033[0m\n";
}

// search value in text file by line number
void searchByLine(int line) {
  // if line equal -1, it means there's no matching record.
  if (line == -1)
  {
    cout << "\n\n\t\t\t\033[31mResult : Not Found...!\033[0m" << "\n\n";
    sleep(1.5);
  } else {
    // else start reading a file
    fstream reading_file;
    string value_by_line;
    int counter = 0;
    reading_file.open("studentRecords.txt", ios::in);
    if (reading_file.is_open())
    {
      while (getline(reading_file, value_by_line))
      {
        counter++;
        // if the line counter equal to line number we want, print it out.
        if (counter == line)
        {
          cout << "\n\n\t\t\t\033[1;32mResult :\033[0m " << value_by_line << "\n\n";
        } 
      }
    }
  }
}

// update value in text file by line number
void updateByLine(int line, string new_value) {
  // reading file
  fstream read_file;
  string value_by_line;
  int counter = 0;
  string file_content;
  read_file.open("studentRecords.txt", ios::in);
  if (read_file.is_open())
  {
    while (getline(read_file, value_by_line))
    {
      counter++;
      // if the line counter equal to line we want, add value you wanna update.
      if (counter == line)
      {
        file_content += new_value + "\n";
      } else {
        // otherwise, appending data into file_content variable to update entire file later.
        file_content += value_by_line + "\n";
      }
    } 
    read_file.close();
  }

  // writing file
  fstream write_file;
  write_file.open("studentRecords.txt", ios::out);
  if (write_file.is_open())
  {
    // update the entire file by appending data from file_content var.
    write_file << file_content;
  }
  write_file.close();
  // print out Updated successfully
  cout << "\n\t\t\t\033[1;32mUpdated Successfully!\033[0m" << endl;
  sleep(1.5);
}

// getting line number from text file by ID
int getLineByID(string id) {
  // create a file pointer
  fstream reading_file;
  // create helping variables
  string line_value;
  int result_line;
  int counter = 0;
  // start reading a file.
  reading_file.open("studentRecords.txt", ios::in);
  if (reading_file.is_open())
  {
    while (getline(reading_file, line_value))
    {
      // counting line number to get when it's matching with ID
      counter++;
      // getting index of comma (,) 
      int comma_index = line_value.find(",");
      // extract the ID from file
      string id_in_file = line_value.substr(0, comma_index);
      // if extracted ID equal to id you want, return that.
      if (id_in_file == id)
      {
        result_line = counter;
        return result_line;
      }
    }
  }
  return -1;
}

// delete value in text file by line number 
void deleteByLine(int line) {
  // if line equal -1, there's no matching data.
  if (line == -1)
  {
    cout << "\n\n\t\t\t\033[31mResult : Not Found...!\033[0m" << "\n\n";
    sleep(1.5);
  } else {
    // otherwise, start reading file
    fstream reading_file;
    string value_of_line;
    string file_content;
    int counter = 0;
    // reading a file
    reading_file.open("studentRecords.txt", ios::in);
    if (reading_file.is_open())
    {
      while (getline(reading_file, value_of_line))
      {
        // line counter
        counter++;
        // if line counter equal line you wanna delete, skip that line.
        if (counter != line)
        {
          // passing the skipped lines into file_content variable.
          file_content += value_of_line + "\n";
        }
      }
      reading_file.close();
    }

    fstream writing_file;
    writing_file.open("studentRecords.txt", ios::out);
    if (writing_file.is_open())
    {
      // writing back the new data from file_content variable
      writing_file << file_content;
    }
    writing_file.close();
    cout << "\n\t\t\t\033[1;32mDeleted Successfully!\033[0m" << endl;
    sleep(1.5);
  }
}

// Asking info and return result
string askingInfo(string context) {
  string result;
  string temp_id, temp_fullname, temp_dob, temp_grade;
  // asking information about ID, name, DOB, grade when inserting and updating
  cout << "\n\n\t\t\t\033[31mNOTE! : \033[0m using space with \033[1;32munderscore(_)\033[0m" << endl;
  cout << "\n\n\t\t\tEnter" <<context << "ID [1-999] : ";
  cin >> temp_id;
  // asking new fullname
  cout << "\t\t\tEnter" << context << "name [John_Doe] : ";
  cin >> temp_fullname;
  // asking new dob
  cout << "\t\t\tEnter" << context << "DOB [14-02-2000] : ";
  cin >> temp_dob;
  // asking new grade
  cout << "\t\t\tEnter" << context << "Grade [Year_3] : ";
  cin >> temp_grade;
  // combine all replaced-underscore inputs into result variable. 
  result = replaceUnderscore(temp_id) + ", " + replaceUnderscore(temp_fullname) + ", " + replaceUnderscore(temp_dob) + ", " + replaceUnderscore(temp_grade);
  // return that result variable
  return result;
}

// display the inserted records 
void showInsertedRecords() {
  // show all records with header files
  cout << "\n\n\t\t\t\033[1;32m------------- Inserted Record -------------\033[0m\n";
  cout << "\t\t\t\033[1;32mID         Name          DOB          Grade" << endl;
  cout << "\t\t\t\033[1;32m-------------------------------------------\033[0m\n";
  // show records
  showRecords("studentRecords.txt");
  cout << "\t\t\t\033[1;32m-------------------------------------------\033[0m\n";
}

// showing alert with input and getting ID
string askingID(string word) {
  string result;
  cout <<"\n\n\t\t\t\033[31mNOTE! : \033[0m" << word <<" based on ID" <<endl;
  // asking for ID to update, search or delete
  cout <<"\n\n\t\t\tEnter ID to " << word << " : ";
  cin >> result;
  return result;
}
