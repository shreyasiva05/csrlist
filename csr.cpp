
#include "csr.h"
///////////////CSR Class Implementation///////////////
/*
File: csr.cpp
Author: Shreya Sivakumar

*/
//Default constructor
// Name: Default Constructor
// Desc: Setting to default values
// Preconditions: the values weren't initialized
// Postconditions: the values were set
CSR::CSR(){
    m_values  = nullptr;      //array to store non-zero values
    m_col_index = nullptr;   //array to store column indices
    m_row_index = nullptr;//array to store row indices
    m_nonzeros = 0;     //number of non-zero values
    m_m = 0;            //number of rows
    m_n = 0;
    m_next = nullptr;
}
//Destructor
// Name: Destructor
// Desc: deallocating the values
// Preconditions: the values weren't deallocated
// Postconditions: all the values have been deallocated
CSR::~CSR(){
    clear();

}
//Copy Constructor
// Name: Copy Constructor
// Desc: Setting all default values to rhs
// Preconditions: the values weren't initialized to rhs
// Postconditions: the values were set
CSR::CSR(const CSR & rhs){

    m_nonzeros = rhs.m_nonzeros;     //number of non-zero values
    m_m = rhs.m_m;            //number of rows
    m_n = rhs.m_n;
    m_values = new int [m_nonzeros];
    m_col_index = new int[m_nonzeros];
    m_row_index = new int[m_m+1]();

    // Copy the values array
    for (int i = 0; i < m_nonzeros; i++) {
        m_values[i] = rhs.m_values[i];
        m_col_index[i] = rhs.m_col_index[i];
    }


    // Copy the row indices array
    for (int i = 0; i < m_m+1; i++) {
        m_row_index[i] = rhs.m_row_index[i];
    }

}
//clear
// Name: clear
// Desc: deallocating the values
// Preconditions: the values weren't deallocated
// Postconditions: all the values have been deallocated
void CSR::clear(){
    m_nonzeros = 0;     //number of non-zero values
    m_m = 0;            //number of rows
    m_n = 0;
    if (m_col_index!=nullptr){
        delete []m_col_index;
        m_col_index = nullptr;
    }
    if (m_row_index!= nullptr){
        delete []m_row_index;
        m_row_index= nullptr;
    }
    if(m_values!=nullptr){
        delete []m_values;
        m_values = nullptr;
    }
    m_next = nullptr;
}
//empty
// Name: empty
// Desc: checks if the values are deallocated
// Preconditions: the values to check
// Postconditions: returns true or false
bool CSR::empty() const{
    if ((m_values  == nullptr)&&(m_col_index == nullptr)&&( m_row_index==nullptr)){
        return true;

    }
    return false;
}
//compress
// Name: compress
// Desc: create a matrix allocating values
// Preconditions: inserts rows, columns , array and arraysize
// Postconditions: m_values is a array of a matrix
void CSR::compress(int m, int n, int array[], int arraySize){
    if (m <= 0 && n <= 0) {
        return;
    }
    if(!empty()){
        clear();
    }
    int total_values = m * n;
    int arraySize_2 = arraySize;
    if (arraySize > total_values) {
        arraySize_2 = m * n;
    }
    if (arraySize < total_values) {
        arraySize_2 = m * n;
    }

    m_nonzeros = 0;     //number of non-zero values
    for (int i = 0; i < arraySize_2; i++) {
        if (array[i] != 0) { //to check whether the value is not 0
            m_nonzeros++;
        }
    }
    m_m = m;            //number of rows
    m_n = n;//number of columns
    m_values = new int[m_nonzeros];
    m_col_index = new int[m_nonzeros];
    m_row_index = new int[m_m + 1]();

    int value_index = 0; //initializing the value index to 0

    for (int i = 0; i < arraySize_2; i++) {
        if (array[i] != 0) { //to check whether the value is not 0
            m_values[value_index] = array[i];
            m_col_index[value_index] = i % m_n; // remainder provides the column index of the current element
            value_index++;//incrementing the value index
            // Check if we are starting a new row
        }
        //if the index of the current element is equal to total columns -1
        if ((i + 1) % n == 0) {
            m_row_index[i / n + 1] = value_index; //setting the non_zeros numbers to the row index


        }
    }

}
//getAt
// Name: getAt
// Desc: returns the values of the index
// Preconditions: rows and columns to loop through
// Postconditions: returns the index of m_values or throw exception if not found
int CSR::getAt(int row, int  col) const{
    if ((row > 0 && row < m_m) && (col > 0 && col < m_n) ){
        int row_start = m_row_index[row];
        int row_end = m_row_index[row + 1];

        for (int i = row_start; i < row_end; i++) {
            if (m_col_index[i] == col) {
                // Found the element at the specified row and col
                return m_values[i];
            }
        }
    }
    else{
        throw std::runtime_error("Exception Error: Object is not in the list!");
    }

    return 0;
}
//operator Equality operator
// Name: operator==
// Desc: checks if the values are equal to rhs values
// Preconditions: checks if all the values are assigned correctly
// Postconditions: returns this based on the if condtions
bool CSR::operator==(const CSR & rhs) const{
    if(this !=&rhs) {
        if (m_nonzeros != rhs.m_nonzeros){
            return false;
        }
        if ((m_m != rhs.m_m)&&(m_n!= rhs.m_n)){
            return false;
        }

        if (rhs.m_values!= nullptr){
            for (int i = 0; i < m_nonzeros; i++) {
                if (m_values[i] != rhs.m_values[i]){
                    return false;
                }
            }
        }
        if((m_m>0)&&(m_n>0)){
            for (int i = 0; i < m_n; i++) {
                if(m_col_index[i] != rhs.m_col_index[i]){
                    return false;
                }
            }

            // Copy the row indices array
            for (int i = 0; i <= m_m; i++) {
                if (m_row_index[i] != rhs.m_row_index[i]){
                    return false;
                }
            }
        }
    }
    return true;
}
//sparseRatio
// Name: sparseRatio
// Desc: returns the ratio of zero numbers
// Preconditions: the ratio was not listed
// Postconditions: returns the ratio of zero numbers
int CSR::sparseRatio(){
    if ((m_col_index == nullptr)&&(m_row_index == nullptr)){
        return 0;
    }
    else if (m_m>0&& m_n>0) {
        int total_elements  = m_m*m_n;
        double ratio = double ((total_elements - m_nonzeros)/total_elements)*100;
        return ratio;

    }
    else if (m_m== 0 || m_n==0){
        return 100;
    }
    return 0;
}
//dump
// Name: dump
// Desc: prints the matrices
// Preconditions: the values weren't printed
// Postconditions: prints the matrices
void CSR::dump(){
    cout << endl;
    if (!empty()){
        for (int i=0;i<m_nonzeros;i++)
            cout << m_values[i] << " ";
        cout << endl;
        for (int i=0;i<m_nonzeros;i++)
            cout << m_col_index[i] << " ";
        cout << endl;
        for (int i=0;i<m_m+1;i++)
            cout << m_row_index[i] << " ";
    }
    else
        cout << "The object is empty!";
    cout << endl;
}

//////////////CSRList Class Implementation///////////////
//Default constructor
// Name: Default Constructor
// Desc: Setting to default values
// Preconditions: the values weren't initialized
// Postconditions: the values were set
CSRList::CSRList(){
    m_head = nullptr;    //the pointer to the head of the list
    m_size = 0; //intialize the size to 0
}
//Copy Constructor
// Name: Copy Constructor
// Desc: Setting all default values to rhs
// Preconditions: the values weren't initialized to rhs
// Postconditions: the values were set
CSRList::CSRList(const CSRList & rhs){
    //checks if the rhs head points to nullptr then
    if (rhs.m_head == nullptr){
        m_head= nullptr; //change mhead to nullptr
        return;
    }
    CSR *current = rhs.m_head; //make a node that points to rhs.mhead
    CSR *previous = nullptr;//pointing to nullptr
    while(current!=nullptr){ //loop through
        CSR* newNode = new CSR(*current); //creates a new node
        if (m_head == nullptr) {
            m_head = newNode; //change mhead to newNode
            previous = newNode;

        }
        else{
            previous->m_next=newNode;
            previous = newNode;
        }
    }
}
//Destructor
// Name: Destructor
// Desc: deallocating the values
// Preconditions: the values weren't deallocated
// Postconditions: all the values have been deallocated
CSRList::~CSRList(){
    clear();

}
//empty
// Name: empty
// Desc: checks if the values are deallocated
// Preconditions: the values to check
// Postconditions: returns true or false
bool CSRList::empty() const{
    if(m_head!= nullptr && m_size !=0)
        return false;
    else{
        return true;
    }

}
//insertAtHead
// Name: insertAtHead
// Desc: inserts values in the beginning
// Preconditions: th values weren't inserted
// Postconditions: all the values have been inserted
void CSRList::insertAtHead(const CSR & matrix){
    CSR * newNode = new CSR(matrix);
    newNode->m_next = m_head;
    m_head =newNode;
//    if (m_head== nullptr){
//        m_head= newNode;
//    }
//    else{
//        newNode->m_next = m_head;
//        m_head = newNode;
//    }
    m_size++;

}
//clear
// Name: clear
// Desc: deallocating the values
// Preconditions: the values weren't deallocated
// Postconditions: all the values have been deallocated
void CSRList::clear(){
//        CSR *temp = m_head;
//        CSR *comp;
//        while(temp!=nullptr){
//            comp = temp->m_next;
//            delete temp;
//            temp = comp;
//        }
//        m_head = nullptr;
//    m_size = 0;
    while(m_head!= nullptr){
        CSR* temp = m_head;
        m_head=m_head->m_next;
        delete temp;
    }

}
//getAt
// Name: getAt
// Desc: returns the values of the index
// Preconditions: rows and columns to loop through
// Postconditions: returns the index of m_values or throw exception if not found
int CSRList::getAt(int CSRIndex, int row, int col) const {

    if (CSRIndex < 0) {
        throw std::runtime_error("Exception Error: Object is not in the list!");
    }
    CSR *current = m_head;
    for(int i = 0; i < CSRIndex ; i++) {
        if(current == nullptr){
            throw std::runtime_error("Exception Error: Object is not in the list!");
        }
        current = current->m_next;
    }
    return current->getAt(row, col);

}
//operator==
// Name: operator==
// Desc: checks if the values are equal to rhs values
// Preconditions: checks if all the values are assigned correctly
// Postconditions: returns this based on the if condtions
bool CSRList::operator== (const CSRList & rhs) const{
    if (m_size != rhs.m_size){
        return false;
    }
    CSR *curr = this->m_head; //creating a node that points to m_head
    CSR *curr_2 = rhs.m_head; //creating a node pointing to rhs m_head
    while (curr!= nullptr){
        if(curr == curr_2){
            curr = curr->m_next; //looping through the list if each is node is eqaul
            curr_2 = curr_2->m_next;
        }
        else{
            return false; //
        }
    }
    if ((curr==nullptr) && (curr_2 == nullptr)){
        return true;
    }
    return false;

}
//Assignment Operator
// Name: operator=
// Desc: Setting all default values to rhs
// Preconditions: the values weren't initialized to rhs
// Postconditions: the values were set
const CSRList& CSRList::operator=(const CSRList & rhs){
    if(this !=&rhs){
        clear(); //calls the clear function
        CSR *current = rhs.m_head;
        CSR *previous = nullptr;
        while(current!=nullptr){ //loop through the end
            CSR* newNode = new CSR(*current);
            //if the node is the only node
            if (m_head == nullptr) {//if the list is empty
                m_head = newNode; //create a node and assign to m_head
                previous = newNode; //previous to newNode
            }
            else{
                previous->m_next=newNode; //create other nodes consequtively
                previous = newNode; //make previous point to newnode and previous to newnode
                current = current->m_next;
            }

        }
        return *this;//returns this after assigning all the values
    }
    return *this;// if they are equal return this
}
//averageSparseRatio
// Name: averageSparseRatio
// Desc: returns average of all the sparse ratios
// Preconditions: sparse ratio of one matrix
// Postconditions: returns average of all the sparse ratios
int CSRList::averageSparseRatio(){
    if (m_size <=0){
        return 0;
    }

    CSR *curr = m_head;
    int total_average = 0;
    while(curr!=m_head){

       total_average += curr->sparseRatio();
    }
    total_average = total_average/m_size;
    return total_average;
}
//dump
// Name: dump
// Desc: prints the matrices
// Preconditions: the values weren't printed
// Postconditions: prints the matrices
void CSRList::dump(){
    if (!empty()){
        CSR* temp = m_head;
        while (temp != nullptr){
            temp->dump();
            temp = temp->m_next;
        }
    }
    else
        cout << "Error: List is empty!" << endl;
}
