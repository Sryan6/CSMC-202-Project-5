/************************************************
 ** File: EReader.cpp
 ** Project: CMSC 202 Project 6, E-Reader
 ** Author: Steven Ryan
 ** Date: 4/28/19
 ** Section: 12
 ** E-Mail: sryan6@umbc.edu
 **
 ** This file is used to write the source code
 ** for the EReader methods
 ***********************************************/

//Preprocessor Directives
#include "EReader.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

//Default Constructor
EReader::EReader(){
  
}

//Overloaded Constructor
EReader::EReader(string filename){
  LoadCatalog(filename);
}

//Destructor for EReader
EReader::~EReader(){
  //Cycles through the list and deletes all the dynamically allocated memory
  for(int i = 0; i < (int)m_bookCatalog.size(); i++){
    delete m_bookCatalog.at(i);
  }
  
}

//Populates the booklist from the file
void EReader::LoadCatalog(string filename){
  cout << "Catalog populated with 150 books." << endl;
  ifstream inputStream;

  //Dynamically creates book
  Book* book = new Book();
  
  //Opens file
  inputStream.open(filename);

  
  if(inputStream.is_open()){
    //Creates all the variables
    string title;
    string author;
    string rankString;
    double cost;
    int rank;

    //While the file still has data to read
    while(inputStream){
      //Reads in the book variables
      getline(inputStream, title, ',');
      getline(inputStream, author, ',');
      getline(inputStream, rankString, ',');

      //Reads in an double, as a delimiter is not needed
      inputStream >> cost;

      //Ignores newline
      inputStream.ignore(1);

      //Converts the rank string into an integer
      rank = stoi(rankString);

      //Uses mutators to set all the book variables
      book->setTitle(title);
      book->setAuthor(author);
      book->setRank(rank);
      book->setPrice(cost);

      //Adds book to the catalog
      m_bookCatalog.push_back(book);
      
      //Dynamically allocates a new book
      if(inputStream){
	book = new Book();
      }
    }
  }
}

//Creates User interface and organizes program
void EReader::MainMenu(){
  int choice = 0;
  //While the user does not quit
  while(choice != 5){
    //Displays Menu
    cout << "What would you like to do?" << endl;
    cout << "1. Display All Books" << endl;
    cout << "2. Add Book to Readlist" << endl;
    cout << "3. Display Readlist" << endl;
    cout << "4. Sort Readlist by Price" << endl;
    cout << "5. Quit" << endl;
    cin >> choice;
    //Validates Input
    while((choice > 5) || (choice < 1)){
      cout << "Please choose a valid option" << endl << endl;
      cout << "1. Display All Books" << endl;
      cout << "2. Add Book to Readlist" << endl;
      cout << "3. Display Readlist" << endl;
      cout << "4. Sort Readlist by Price" << endl;
      cout << "5. Quit" << endl;
      cin >> choice;
    }
    //If user chooses 1
    if(choice == 1){
      DisplayBooks();
    }
    //If user chooses 2
    else if(choice == 2){
      AddBook();
    }
    //If user chooses 3
    else if(choice == 3){
      DisplayReadlist();
    }
    //If user chooses 4
    else if(choice == 4){
      SortReadlist();
    }
  }
}

//Displays the Book catalog using the overloaded operator
void EReader::DisplayBooks(){
  for(int i = 0; i < (int)m_bookCatalog.size() - 1; i++){
    cout << *m_bookCatalog.at(i) << endl;
  }
}

void EReader::AddBook(){
  int choice;
  //Prompts user for another choice
  cout << "Choose the book you would like to add to your reading list." << endl;
  DisplayBooks();
  cout << "Enter the number of the book you would like to add:" << endl;
  cin >> choice;
  //Validats input
  while((choice < 1) || (choice > (int)m_bookCatalog.size())){
    cout << "Please enter a valid choice." << endl;
    cin >> choice;
  }
  //Iterates through the catalog and puts book in readList.
  for(int i = 0; i < (int) m_bookCatalog.size() - 1; i++){
    if(m_bookCatalog.at(i)->getRank() == choice){
      m_readList.Push(*m_bookCatalog.at(i), true);
    }
  }
}

//Displays readList by calling display function
void EReader::DisplayReadlist(){
  m_readList.Display();
}

//Sorts the Readlist using the bubble sort method
void EReader::SortReadlist(){
  bool endFlag = false;
  while(endFlag == false){
    endFlag = false;
    for(int i = 1; i < m_readList.GetSize(); i++){
      if(m_readList[i - 1] < m_readList[i]){
	m_readList.Swap(i);
	endFlag = true;
      }
    }
  }
}
