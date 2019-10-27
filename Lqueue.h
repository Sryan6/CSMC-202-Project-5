#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

template <class T>
class Node {
public:
  Node( const T& data ); //Node Constructor
  T& GetData(); //Node Data Getter
  void SetData( const T& data ); //Node Data Setter
  Node<T>* GetNext(); //Node m_next getter
  void SetNext( Node<T>* next ); //Node m_next setter
private:
  T m_data; //Holds templated data
  Node<T>* m_next; //Pointer to next node
};

template <class T>
Node<T>::Node( const T& data ) {
   m_data = data;
   m_next = nullptr;
}

template <class T>
T& Node<T>::GetData() {
   return m_data;
}

template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}

template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

template <class T>
class Lqueue {
 public:
  // Name: Lqueue() (Linked List Queue) - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
  Lqueue();
  // Name: ~Lqueue() - Destructor
  // Desc: Used to destruct a Lqueue
  // Preconditions: There is an existing lqueue with at least one node
  // Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
 ~Lqueue();
  // Name: Lqueue (Copy Constructor)
  // Preconditions: Creates a copy of existing LQueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  Lqueue(const Lqueue&);
  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: Copies an Lqueue into an existing Lqueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  Lqueue<T>& operator= (const Lqueue&);
  // Name: Push
  // Preconditions: Takes in data. Creates new node. 
  //                Requires a Lqueue
  // Postconditions: If the bool = false, adds to front else adds a new node to the
  //                 end of the lqueue.
  void Push(const T&, bool);
  // Name: Pop
  // Preconditions: Lqueue with at least one node. 
  // Postconditions: Removes first node in the lqueue, returns data from first node.
  T Pop();
  // Name: Display
  // Preconditions: Outputs the lqueue.
  // Postconditions: Displays the data in each node of lqueue
  void Display();
  // Name: Front
  // Preconditions: Requires a populated lqueue
  // Postconditions: Returns whatever data is in front 
  T Front();
  // Name: IsEmpty
  // Preconditions: Requires a lqueue
  // Postconditions: Returns if the lqueue is empty.
  bool IsEmpty();
  // Name: GetSize
  // Preconditions: Requires a lqueue
  // Postconditions: Returns m_size
  int GetSize();
  // Name: Swap(int)
  // Preconditions: Requires a lqueue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  void Swap(int);
  // Name: Clear
  // Preconditions: Requires a lqueue
  // Postconditions: Removes all nodes in a lqueue
  void Clear();
  // Name: TestHeadTail() (Optional test function)
  // Preconditions: Requires a lqueue
  // Postconditions: Returns the value of the head and the tail (used for main below)
  void TestHeadTail();
  // Name: operator<< (Overloaded << operator)
  // Preconditions: Requires a lqueue
  // Postconditions: Returns an ostream with the data from each node on different line
  template <class U>
  friend ostream& operator<<(ostream& output, const Lqueue<U>&);
  //Name: Overloaded [] operator
  //Precondition: Existing Lqueue
  //Postcondition: Returns object from Lqueue using []
  T& operator[] (int x);//Overloaded [] operator to pull data from Lqueue
private:
  Node <T> *m_head; //Node pointer for the head
  Node <T> *m_tail; //Node pointer for the tail
  int m_size; //Number of nodes in queue
};
//*****************************************************************
//Implement Lqueue here

//Default Constructor
template <class T>
Lqueue<T>::Lqueue(){
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}

//Destructor calls clear
template <class T>
Lqueue<T>::~Lqueue(){
  Clear();
}

//Copy Constructor
template <class T>
Lqueue<T>::Lqueue(const Lqueue& lqueue){
  m_size = 0;
  //If the lqueue is not empty
  if(lqueue.m_size != 0){
    Node<T>* curr = lqueue.m_head;
    curr->SetData(lqueue.m_head->GetData());
    //Iterates through the linked list and copies it
    for(curr = lqueue.m_head; curr != nullptr; curr = curr->GetNext()){
      curr->SetData(curr->GetData());
      Push(curr->GetData(), 1);
    }
  }
}

//Overloaded Assignment operator
template <class T>
Lqueue<T>& Lqueue<T>::operator= (const Lqueue& lqueue){
  //If the size of the list is not zero
  if(lqueue.m_size != 0){
    Node<T>* curr = lqueue.m_head;
    //Iterates through the linked list and copy the data into the variable being assigned
    for(curr = lqueue.m_head; curr != nullptr; curr = curr->GetNext()){
      curr->SetData(curr->GetData());
      Push(curr->GetData(), 1);
    }
  }
  //returns the data
  return *this;
}

//Adds templated data to the linked list at either the end or the beginning
template <class T>
void Lqueue<T>::Push(const T& data, bool placement){
  Node<T>* node = new Node<T>(data);
  
  if(m_size != 0){
    //If placement is at the end
    if(placement){
      m_tail->SetNext(node);
      m_tail = node;
    }
    //If placement is at the beginning
    else{
      node->SetNext(m_head);
      m_head = node;
    }
  }
  //If the list is one element long
0  else{
    m_head = node;
    m_tail = node;
  }
  //Increments size
  m_size++;
}

//Deletes templated data in the linked list at the beginning
template <class T>
T Lqueue<T>::Pop(){
  Node<T>* temp = m_head;

  //Case when the list is empty
  if(IsEmpty()){
    cout << "Cannot pop from an empty list" << endl;
    return 0;
  }
  else{
    T data = m_head->GetData();

    //deletes the first element of the list and
    //deallocates it using a temp variable
    temp = m_head->GetNext();
    delete m_head;
    m_head = temp;
    temp = nullptr;
    delete temp;
    
    //Decrements size
    m_size--;
    
    return data;
  }
}

//Displays the function
template <class T>
void Lqueue<T>::Display(){
  //In case the Lqueue is empty
  if(IsEmpty()){
    cout << "This Lqueue is empty" << endl;
  }
  else{
    //Sets a node to iterate through the list
    Node<T>* curr = m_head;
    curr->SetData(m_head->GetData());

    //Iterates through the linked list and prints it out
    //using the overloaded operator
    for(curr = m_head; curr != nullptr; curr = curr->GetNext()){
      cout << curr->GetData() << endl;
    }
  }
}

//returns the data at the beginning of the linked list
template <class T>
T Lqueue<T>::Front(){
  return m_head->GetData();
}

//Returns true if the Lqueue is empty and false if not
template <class T>
bool Lqueue<T>::IsEmpty(){
  if(m_size == 0){
    return true;
  }
  return false;
}

//Returns the size of the list
template <class T>
int Lqueue<T>::GetSize(){
  return m_size;
}

//Exchanges the indexed Node with the one before it
template <class T>
void Lqueue<T>::Swap(int index){
  Node<T>* temp;
  Node<T>* former;

  //Case when the user selects the first and 0th
  if(index == 0){
    cout << "You cannot swap this as there is no previous element";
    return;
  }

  //Case when there are not enough elements in the list
  if(m_size < 2){
    cout << "Must be at least 2 elements to swap" << endl;
    return;
  }

  //Swapping first and second element
  if(index == 1){
    temp = m_head->GetNext();
    m_head->SetNext(temp->GetNext());
    temp->SetNext(m_head);
    m_head = temp;
  }
  
  //Swapping the last element with previous
  else if(index == m_size - 1){
    temp = m_head;
    //sets the temporary node
    for(int i = 0; i < m_size - 1; i++){
      temp = temp->GetNext();
    }
    temp->SetNext(nullptr);
    m_tail->SetNext(temp);
    m_tail = temp;
  }

  //Swapping in the middle of the list
  else{
    former = m_head;
    //sets the previous Node as former
    for(int i = 0; i < index - 2; i++){
      former = former->GetNext();
    }
    temp = former->GetNext();
    former->SetNext(temp->GetNext());
    temp->SetNext(temp->GetNext()->GetNext());
    former->GetNext()->SetNext(temp);
  }
}

//Clears and deallocates the Lqueue
template <class T>
void Lqueue<T>::Clear(){
  if(IsEmpty()){
    cout << "";
  }
  else{
    //Iterates through the list and deletes each node
    Node<T>* temp = m_head;
    while(m_head != nullptr){
      temp = m_head->GetNext();
      delete m_head;
      m_head = temp;
    }

    //Resets variables
    m_size = 0;
    m_head = nullptr;
    m_tail = nullptr;
  }
}

//Test function uses to display the head and tail of the Lqueue
template <class T>
void Lqueue<T>::TestHeadTail(){
  cout << "Head: " << m_head->GetData() << endl;
  cout << "Tail: " << m_tail->GetData() << endl;
}

//Displays the Lqueue in its entirety
template <class U>
ostream& operator<<(ostream& output, const Lqueue<U>& lqueue){
  //If the Lqueue is empty
  if(lqueue.m_size == 0){
    cout << "This lqueue is empty" << endl;
    return output;
  }
  //else the Lqueue is not empty
  else{
    Node<U>* curr = lqueue.m_head;

    //Iterates through the Lqueue displaying the data from each node
    for(int i = 0; i < lqueue.m_size; i++){
      cout << curr->GetData() << endl;
      curr = curr->GetNext();
    }

    //returns all the couts
    return output;
  }
}

//Provides indexing for the linked list
template <class T>
T& Lqueue<T>::operator[] (int x){
  Node<T>* temp = m_head;
  //if the chosen index is 0
  if(x == 0){
    return temp->GetData();
  }
  //If the chose index is any other positive number
  for(int i = 0; i < x; i++){
    temp = temp->GetNext();
  }
  return temp->GetData();
}



//****************************************************************
// To test just Lqueue follow these instructions:
//   1.  mv Lqueue.h Lqueue.cpp
//   2.  Uncomment out int main below
//   3.  make Lqueue
//   4.  ./Lqueue (try valgrind too!)

/*
int main () {
  //Test 1 - Default Constructor and Push
  cout << "Test 1 - Default Constructor and Push Running" << endl;
  //Test Default Constructor
  Lqueue <int> newLQ1;
  //Push 4 nodes into Lqueue
  newLQ1.Push(10, 1);
  newLQ1.Push(11, 1);
  newLQ1.Push(12, 1);
  newLQ1.Push(13, 1);
  cout << endl;

  //Test 2 - Copy Constructor and Assignment Operator
  cout << "Test 2 - Copy Constructor and Assignment Operator Running" << endl;
  //Test Copy constructor
  Lqueue <int> newLQ2(newLQ1);
  //Test Overloaded Assignment Operator
  Lqueue <int> newLQ3;
  newLQ3 = newLQ1;
  cout << endl;

  //Test 3 - Test Display and Overloaded <<
  cout << "Test 3 - Display and Overloaded << Running" << endl;
  cout << "newLQ1" << endl;
  newLQ1.Display();
  cout << "newLQ2" << endl;
  newLQ2.Display();
  cout << "newLQ3" << endl;
  newLQ3.Display();
  cout << "newLQ1" << endl;
  cout << newLQ1;
  cout << "newLQ2" << endl;
  cout << newLQ2;
  cout << "newLQ3" << endl;
  cout << newLQ3;
  cout << endl;

  //Test 4 - Test Front and Pop
  cout << "Test 4 - Front and Pop Running" << endl;
  //Test Front()
  cout << "Testing Front - Output 10" << endl;
  cout << newLQ1.Front() << endl;
  //Test Pop with Display of Pop
  cout << "Popping one node and displaying it" << endl;
  cout << newLQ1.Pop() << endl;
  //Test Pop with Display of Pop
  cout << "Popping one node and displaying it" << endl;
  cout << newLQ1.Pop() << endl;
  cout << endl;

  //Test 5 - Test GetSize and Clear
  cout << "Test 5 - GetSize and Clear Running" << endl;
  //Test GetSize()
  cout << "Outputting the size" << endl;
  cout << newLQ1.GetSize() << endl;
  //Test Clear()
  cout << "Clearing all nodes" << endl;
  newLQ1.Clear();
  cout << endl;

  //Test 6 - Test Swap
  cout << "Test 6 - Swap Running" << endl;
  newLQ2.Swap(2);
  cout << "Swap 2 - Should display 10->12->11->13->END" << endl;
  newLQ2.Display();
  //Testing to make sure head and tail point at the correct node
  newLQ2.TestHeadTail();
  cout << "Should display head 10 and tail 13" << endl;
  cout << endl;  

  return 0;
}
*/
