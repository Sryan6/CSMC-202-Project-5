/************************************************
 ** File: Book.cpp
 ** Project: CMSC 202 Project 5, E-Reader
 ** Author: Steven Ryan
 ** Date: 4/28/19
 ** Section: 12
 ** E-Mail: sryan6@umbc.edu
 **
 ** This file is used to write the source code
 ** for the Book methods
 ***********************************************/

//Preprocessor Directives
#include "Book.h"

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
Book::Book(){
  setTitle("The Book of Books");
  setAuthor("Steven Ryan");
  setRank(1);
  setPrice(10.00);
}

//Overloaded Constructor
Book::Book(string title, string author, int rank, double price){
  setTitle(title);
  setAuthor(author);
  setRank(rank);
  setPrice(price);
}

//Getter for title
string Book::getTitle()const{
  return m_title;
}

//Getter for author
string Book::getAuthor()const{
  return m_author;
}

//Getter for rank
int Book::getRank()const{
  return m_rank;
}

//Getter for price
double Book::getPrice()const{
  return m_price;
}

//Setter for title
void Book::setTitle(string title){
  m_title = title;
}

//Setter for author
void Book::setAuthor(string author){
  m_author = author;
}

//Setter for rank
void Book::setRank(int rank){
  m_rank = rank;
}

//Setter for price
void Book::setPrice(double price){
  m_price = price;
}

//Overloaded operater organizes book data output legibly
ostream& operator<<(ostream& output, Book& book){
  cout << setw(4) << right << book.m_rank << setw(42) << book.m_title
       << setw(23) << book.m_author << setw(12) << "($" << book.m_price << ")";
  return output;
}

//Compares the price of two books
bool operator< (Book const & lhs, Book const & rhs){
  if(lhs.getPrice() < rhs.getPrice()){
    return true;
  }
  else{
    return false;
  }
}
