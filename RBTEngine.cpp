//*******************************************************
// Author:                       Matt Matuk
// Created:                      11/15/2017
// Source File:                  RBTEngine.cpp
// Description:
//
// Editor:                          Emacs
//*******************************************************

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <time.h>
#include <sstream> //for std::istringstream
#include <string>
#include <vector> //for std::vector
#include "RBT.h"

//*****************Test**********************************
struct Cars
{
public:
  string make;
  string model;
  int year;
  int rating;

  bool operator>(const Cars &c1) { return rating > c1.rating; }
  bool operator>=(const Cars &c1) { return rating >= c1.rating; }
  bool operator<(const Cars &c1) { return rating < c1.rating; }
  bool operator<=(const Cars &c1) { return rating <= c1.rating; }
  bool operator==(const Cars &c1) { return (rating != c1.rating); }
  bool operator!=(const Cars &c1) { return (rating != c1.rating); }
  friend ostream &operator<<(ostream &os, const Cars &car)
  {
    os << "make: " << car.make << " model: " << car.model
       << " year: " << car.year << " rating: " << car.rating << "\n";
    return os;
  }
};
//*******************************************************

// Function Prototype
void displayIntro();
int *getListOfInts(int &); // Get a list of ints from cin

// Global Variable
int testCase = 1;

int main()
{
  RBT<int> intRBT = RBT<int>();   // Integer test case
  RBT<Cars> carRBT = RBT<Cars>(); // Struct test case for template
  int input = -1;

  system("clear");
  displayIntro();
  cout << "Choice: ";
  cin >> input;
  while (cin.fail() || input > 5 || input < -1) // User did not enter proper choice
  {
    cout << "Error: Please only enter only -1-5\n";
    cin.clear();
    cin.ignore(256, '\n');
    cout << "Choice: ";
    cin >> input;
  }
  while (input != 0)
  {
    switch (input)
    {
    case -1: // swap current selected Tree test case
    {
      if (testCase == 1)
      {
        testCase = 2;
      }
      else
      {
        testCase = 1;
      }
      system("clear");
      displayIntro();
      break;
    }
    case 1: // Insert Value into RBT
    {
      // system("clear");
      // displayIntro();
      if (testCase == 1) // Int tree
      {
        int *input;
        int size = 0;
        cin.clear(); // clear cin buffer
        cin.ignore(256, '\n');

        cout << "Enter list of integer values: ";
        input = getListOfInts(size);

        for (int i = 0; i < size; i++)
        {
          if (intRBT.RBTInsert(input[i]) == -1) // Value exists
          {
            cout << input[i] << " already in Binary Tree.\n";
          }
          else // Vlaue does not exist and was added
          {
            cout << input[i] << " added to Binary Tree.\n";
          }
        }
      }
      else // Car insert
      {
        Cars insert = Cars();
        cout << "Enter make: ";
        cin >> insert.make;
        cout << "\nEnter model: ";
        cin >> insert.model;
        cout << "\nEnter year: ";
        cin >> insert.year;
        while (cin.fail()) // User did not enter a Integer
        {
          cout << "Error: Please only enter only Integers\n";
          cin.clear();
          cin.ignore(256, '\n');
          cout << "Enter year: ";
          cin >> insert.year;
        }

        cout << "\nEnter rating: ";
        cin >> insert.rating;
        while (cin.fail()) // User did not enter a Integer
        {
          cout << "Error: Please only enter only Integers\n";
          cin.clear();
          cin.ignore(256, '\n');
          cout << "Enter rating: ";
          cin >> insert.rating;
        }
        if (carRBT.RBTInsert(insert) == -1) // value exists
        {
          cout << insert << " already in Binary Tree.\n";
        }
        else // value does not exist and was added
        {
          cout << insert << "added to Binary Tree.\n";
        }
      }
      break;
    }
    case 2: // Delete Element
    {
      system("clear");
      displayIntro();

      if (testCase == 1)
      {
        int remove = 0; // value to remove
        cout << "Enter Integer to Delete: ";
        cin >> remove;
        while (cin.fail()) // User did not enter a Integer
        {
          cout << "Error: Please only enter only Integers\n";
          cin.clear();
          cin.ignore(256, '\n');
          cout << "Enter Integer to Delete: ";
          cin >> remove;
        }

        if (intRBT.RBTDelete(remove) == -1) // value not in tree
        {
          cout << "Value: " << remove << " was not found in Binary Tree.\n";
        }
        else // value deleted
        {
          cout << "Value: " << remove << " was deleted from Binary Tree.\n";
        }
      }
      else
      {
        Cars remove = Cars();
        cout << "Enter car tinfo to delete: \n";
        cout << "Enter make: ";
        cin >> remove.make;
        cout << "\nEnter model: ";
        cin >> remove.model;
        cout << "\nEnter year: ";
        cin >> remove.year;
        while (cin.fail()) // User did not enter a Integer
        {
          cout << "Error: Please only enter only Integers\n";
          cin.clear();
          cin.ignore(256, '\n');
          cout << "Enter year: ";
          cin >> remove.year;
        }

        cout << "\nEnter rating: ";
        cin >> remove.rating;
        while (cin.fail()) // User did not enter a Integer
        {
          cout << "Error: Please only enter only Integers\n";
          cin.clear();
          cin.ignore(256, '\n');
          cout << "Enter rating: ";
          cin >> remove.rating;
        }

        if (carRBT.RBTDelete(remove) == -1) // value not in tree
        {
          cout << "Value: " << remove << " was not found in Binary Tree.\n";
        }
        else // value deleted
        {
          cout << "Value: " << remove << " was deleted from Binary Tree.\n";
        }
      }
      break;
    }
    case 3: // Inorder print
    {
      system("clear");
      displayIntro();

      if (testCase == 1)
      {
        intRBT.inOrder(intRBT.getRoot());
      }
      else
      {
        carRBT.inOrder(carRBT.getRoot());
      }
      cout << "\n";
      break;
    }
    case 4: // postorder print
    {
      system("clear");
      displayIntro();

      if (testCase == 1)
      {
        intRBT.postOrder(intRBT.getRoot());
      }
      else
      {
        carRBT.postOrder(carRBT.getRoot());
      }
      cout << "\n";
      break;
    }
    case 5: // preorder print.
    {
      system("clear");
      displayIntro();

      if (testCase == 1)
      {
        intRBT.preOrder(intRBT.getRoot());
      }
      else
      {
        carRBT.preOrder(carRBT.getRoot());
      }
      cout << "\n";
      break;
    }
    default:
      break;
    }
    cout << "Choice: ";
    cin >> input;
    while (cin.fail() || input > 5 || input < -1) // User did not enter proper choice
    {
      cout << "Error: Please only enter only 0-5\n";
      cin.clear();
      cin.ignore(256, '\n');
      cout << "Choice: ";
      cin >> input;
    }
  }
  while (input != 0)
    ;

  exit(0);
}

/**
 * @brief Displays the choices the user can make to test the Binary Tree.
 *
 */
void displayIntro()
{
  string strTest;
  if (testCase == 1)
  {
    strTest = "Integer";
  }
  else
  {
    strTest = "Car Struct";
  }
  cout << "//----------------------------------------------------------\\\\\n";
  cout << "||              Welcome to Binary Search Tree               ||\n";
  cout << "||----------------------------------------------------------||\n";
  cout << "||  Test Case: " << setw(10) << left << strTest
       << "                                   ||\n";
  cout << "||                                                          ||\n";
  cout << "||  1. Insert Element                                       ||\n";
  cout << "||  2. Delete Element                                       ||\n";
  cout << "||  3. Inorder Print                                        ||\n";
  cout << "||  4. PostOrder Print                                      ||\n";
  cout << "||  5. PreOrder Print                                       ||\n";
  cout << "||                                                          ||\n";
  cout << "|| -1. Swap Test Case                                       ||\n";
  cout << "||  0. Exit                                                 ||\n";
  cout << "||                                                          ||\n";
  cout << "\\\\----------------------------------------------------------//\n";
}

/**
 * @brief Get a list of integers from the cin inputs from keyboard.
 *
 * @param size Sets the size of the returned intArr.
 *
 * @return Return array of ints, NUll if not all ints.
 */
int *getListOfInts(int &size)
{
  string str;
  getline(cin, str);

  vector<string> result;

  istringstream iss(str);
  for (std::string s; iss >> s;) // parse each int by space
  {
    result.push_back(s);
  }
  int *intArr = new int[result.size()];

  for (int i = 0; i < result.size(); i++) // convert each string into int
  {
    for (int j = 0; j < result[i].size(); j++) // Check if string is int
    {
      if (result[i][j] < '0' || result[i][j] > '9') // conatins a non int
      {
        cout << "Only Enter ineteger!\n";
        return NULL;
      }
    }
    intArr[i] = stoi(result[i]);
  }
  size = result.size();
  return intArr;
}
