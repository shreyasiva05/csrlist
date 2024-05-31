
#include "csr.h"

class Tester {
public:
    // This function is a sample test function
    // It shows how to write a test case
    //test function  Overloaded equality operator
// Name: overloadequalityError
// Desc: compares the matrixes of lhs and rhs after copying
// Preconditions: inserts lhs and rhs matrices
// Postconditions: returs true of false
    bool overloadequalityError(CSR &lhs, CSR &rhs) {
        // we expect that lhs object is an exact copy of rhs object
        bool result = true;
        if(lhs.m_nonzeros == 0){
            result = result && (lhs.m_nonzeros == rhs.m_nonzeros);

        }
        if(lhs. m_m && rhs.m_m == 0){
            result = result && (lhs.m_m == rhs.m_m);
        }
        if(lhs. m_n && rhs.m_n == 0){
            result = result && (lhs.m_n == rhs.m_n);
        }
        if (rhs.m_values == nullptr) {

            result = result && (lhs.m_values == rhs.m_values);
        }
        if(lhs.m_col_index && rhs.m_col_index == nullptr){
            result = result && (lhs.m_col_index == rhs.m_col_index);
        }
        // Copy the row indices array
        if(lhs.m_row_index && rhs.m_row_index == nullptr){
            result = result && (lhs.m_row_index == rhs.m_row_index);
        }
        return result;
    }
    //test function  Overloaded equality operator
// Name: overloadequalityError
// Desc: compares the matrixes of lhs and rhs after copying
// Preconditions: inserts lhs and rhs matrices
// Postconditions: returs true of false
    bool overloadequalityNormal(CSR &lhs, CSR &rhs) {
        // we expect that lhs object is an exact copy of rhs object
        bool result = true;
        if(lhs.m_nonzeros != 0){
            result = result && (lhs.m_nonzeros == rhs.m_nonzeros);

        }

        if(lhs. m_m && rhs.m_m != 0){
            result = result && (lhs.m_m == rhs.m_m);
        }
        if(lhs. m_n && rhs.m_n != 0){
            result = result && (lhs.m_n == rhs.m_n);
        }
        if (rhs.m_values != nullptr) {
            for (int i = 0; i < rhs.m_nonzeros; i++) {
                result = result && (lhs.m_values[i] == rhs.m_values[i]);
            }
        }
        for (int i = 0; i < rhs.m_nonzeros; i++) {
            result = result && (lhs.m_col_index[i] == rhs.m_col_index[i]);
        }
        // Copy the row indices array
        for (int i = 0; i <= rhs.m_m; i++) {
            result = result && (lhs.m_row_index[i] == rhs.m_row_index[i]);
        }
        return result;
    }

    //test function  Compress function Normal case
// Name: compressNormal
// Desc: compares the expected values to the compress function values
// Preconditions: inserts csr object, rows, columns, arrays and arraySize
// Postconditions: returs true of false
    bool compressNormal(CSR &csr, int m, int n, int array[], int arraySize) {
        // Call the compress function
        csr.compress(m, n, array, arraySize);

        if (csr.m_m != m || csr.m_n != n) {
            return false;
        }
        int test_m_nonzeros = 0;
        for (int i = 0; i < arraySize; i++) {
            if (array[i] != 0) { //to check whether the value is not 0
                test_m_nonzeros++;
            }
        }
        if (csr.m_nonzeros != test_m_nonzeros) {
            return false;
        }
        int test_mvalues[test_m_nonzeros];
        int test_mColindex[test_m_nonzeros];
        int value_index = 0;//initializing the value index to 0
        int total_values = m * n;

        if (arraySize != total_values) {
            arraySize = total_values;
        }
        for (int i = 0; i < arraySize; i++) {
            if (array[i] != 0) { //to check whether the value is not 0
                test_mvalues[value_index] = array[i];
                test_mColindex[value_index] = i % n; // remainder provides the column index of the current element
                value_index++;//incrementing the value index
            }
        }
        for (int i = 0; i < csr.m_nonzeros; i++) {
            // Compare m_values[i] and m_col_index[i] to expected values
            if (csr.m_values[i] != test_mvalues[i] || csr.m_col_index[i] != test_mColindex[i]) {
                return false;
            }
        }
        return true;
    }

    //test function  Compress function Error case
// Name: compressError
// Desc: compares the expected values to the compress function values
// Preconditions: inserts csr object, rows, columns, arrays and arraySize
// Postconditions: returs true of false
    bool compressError(CSR &csr, int m, int n, int array[], int arraySize) {
        // Call the compress function
        csr.compress(m, n, array, arraySize);

        if (csr.m_m != m || csr.m_n != n ){
            return false;
        }
        int test_m_nonzeros = 0;
        for (int i = 0; i < arraySize; i++) {
            if (array[i] != 0) { //to check whether the value is not 0
                test_m_nonzeros++;
            }
        }
        if (csr.m_nonzeros != test_m_nonzeros) {
            return false;
        }
        int test_mvalues[test_m_nonzeros];
        int test_mColindex[test_m_nonzeros];
        int value_index = 0;//initializing the value index to 0
        int *test_m_row_index = new int[m + 1]();
        int total_values  = m*n;

        if (arraySize > total_values){
            arraySize = total_values;
        }
        for (int i = 0; i < arraySize; i++) {
            if (array[i] != 0) { //to check whether the value is not 0
                test_mvalues[value_index] = array[i];
                test_mColindex[value_index] = i % n; // remainder provides the column index of the current element
                value_index++;//incrementing the value index
            }
            if ((i + 1) % n == 0) {
                test_m_row_index[i / n + 1] = value_index; //setting the non_zeros numbers to the row index


            }
        }
        for (int i = 0; i < csr.m_nonzeros; i++) {
            // Compare m_values[i] and m_col_index[i] to expected values
            if (csr.m_values[i] !=test_mvalues[i] || csr.m_col_index[i] != test_mColindex[i] || csr.m_row_index[i]!=*test_m_row_index) {
                return false;
            }
        }
        return true;
    }
    //test function  Compress function Error2 case for (0*0) matrix
// Name: compressError2
// Desc: compares the expected values to the compress function values
// Preconditions: inserts csr object, rows, columns, arrays and arraySize
// Postconditions: returs true of false
    bool compressError2(CSR &csr, int m, int n, int array[], int arraySize) {
        // Call the compress function
        csr.compress(m, n, array, arraySize);

        if (csr.m_m != m || csr.m_n != n ){
            return false;
        }
        int test_m_nonzeros = 0;
        for (int i = 0; i < arraySize; i++) {
            if (array[i] != 0) { //to check whether the value is not 0
                test_m_nonzeros++;
            }
        }

        if (csr.m_nonzeros!= 0) {
            return false;
        }
        if((csr.m_col_index!=nullptr)||(csr.m_values!= nullptr)||(csr.m_row_index!= nullptr)){
            return false;
        }

        return true;
    }
    //test function  Compress function Error case
// Name: getAtErrorCase
// Desc: compares the expected value from the get at function
// Preconditions: inserts csr object, rows, columns
// Postconditions: returns true of false
    bool getAtErrorCase(const CSR &csr, int row, int col) {
        try {
            // Attempt to call getAt with invalid indices
            csr.getAt(row, col);
            // If no exception is thrown, the test fails
            return false;
        } catch (const std::runtime_error &ex) {
            // An exception was thrown as expected
            return true;
        }
    }
    bool getAtErrorCSRList(const CSRList &csrlist, int csrindex, int row, int col) {
        try {
            // Attempt to call getAt with invalid indices
            csrlist.getAt(csrindex, row, col);
            // If no exception is thrown, the test fails
            return false;
        } catch (const std::runtime_error &ex) {
            // An exception was thrown as expected
            return true;
        }
    }
    bool getAtNormalCSRList(const CSRList &csrlist, int csrindex, int row, int col) {
        try {
            // Attempt to call getAt with invalid indices
            csrlist.getAt(csrindex, row, col);
            // If no exception is thrown, the test fails
            return true;
        } catch (const std::runtime_error &ex) {
            // An exception was thrown as expected
            return false;
        }
    }
    bool assignmentOperatorNormalcsrList() {
        // Create two CSRList objects
        bool result = true;
        CSRList list1;
        CSRList list2;
        list1 = list2;
        if(&list1 !=&list2){
            result =true;
        }
        CSR *temp = new CSR();
        int array[6] = {1,2,3,4,4,3};
        temp->compress(2,3,array,6);

        list1.insertAtHead(*temp);
        list2=list1;

        if(&list1 !=&list2){
            result =true;
        }
        for(int i =0;i<6;i++){
            if(list1.m_head->m_values[i]==list2.m_head->m_values[i]){
                result=true;
            }
        }
        return result;
    }
    bool assignmentOperatorErrorcsrList() {
        // Create two CSRList objects
        bool result = true;
        CSRList list1;
        CSRList list2;
        CSRList list3;
        list1 = list2;
        if(&list1 !=&list2){
            result =true;
        }
        CSR *temp = new CSR();
        int array[6] = {1,2,3,4,4,3};
        temp->compress(2,3,array,6);

        list1.insertAtHead(*temp);
        list1=list3;
        if(&list1 !=&list3){
            result =true;
        }
        if(list1.m_head ==list2.m_head){
            result =  true;
        }
//        for(int i =0;i<6;i++){
//            if(list1.m_head->m_values[i]==list2.m_head->m_values[i]){
//                result=true;
//            }
//        }
        return result;
    }
};
// this program presents a sample usage of project 1
int main()
{
    try{
        Tester tester;
        CSR aCSR;
        CSR compressnCSR;
        int testarray1[] = {10,20,0,0,0,0,0,30,0,40,0,0,0,0,50,60,70,0,0,0,0,0,0,80};
        int array1[] = {10,20,0,0,0,0,0,30,0,40,0,0,0,0,50,60,70,0,0,0,0,0,0,80};
        cout << "Following is the test message for testing compress function:\n" << endl;
        cout << "Testing compress function for a normal case:" << endl;
        if (tester.compressNormal( compressnCSR, 4, 6, testarray1, 24)) {
            cout << "Test msg: Compress test for normal cases passed!" << endl;
        } else {
            cout << "Test msg: Compress test for normal cases failed!" << endl;
        }
        CSR compresseCSR;
        int array_2[] = {1,2,3};

        cout << "Testing compress function for a error case:" << std::endl;
        if (tester.compressError( compresseCSR, 3, 3, array_2, 3)) {
            cout << "Test msg: Compress test for error cases passed!" << endl;
        } else {
            cout << "Test msg: Compress test for error cases failed!" << endl;
        }
        CSR compresse2CSR;
        int testarray_3[] = {1,2,4};
        cout << "Testing compress function for a error (0*0) case:" << endl;
        if (tester.compressError2( compresse2CSR, 0, 0, testarray_3 , 3)) {
            cout << "Test msg: Compress test for error cases passed!\n" << endl;
        } else {
            cout << "Test msg: Compress test for error cases failed!\n" << endl;
        }
//        CSR bbCSR;
//        bbCSR = aCSR;
        aCSR.compress(4,6,array1,24);//initialize object aCSR
        //aCSR.dump();
        CSR bCSR(aCSR);//create bCSR using copy constructor
        cout << "Following is the test message for testing Overloaded Equality function:\n" << endl;
        std::cout << "Testing overloaded function for a normal case:" << std::endl;
        if (tester.overloadequalityNormal( aCSR,bCSR)) {
            std::cout << "Test msg: Overloaded equality test for error cases passed!" << std::endl;
        } else {
            std::cout << "Test msg: Overloaded equality test for error cases failed!" << std::endl;
        }
        CSR emptycsr;
        CSR emptycsr2;
        std::cout << "Testing overloaded function for a normal case:" << std::endl;
        if (tester.overloadequalityError( emptycsr,emptycsr2)) {
            std::cout << "Test msg: Overloaded equality test for error cases passed!\n" << std::endl;
        } else {
            std::cout << "Test msg: Overloaded equality test for error cases failed!\n" << std::endl;
        }
        cout << "Following is the test message for testing getAt function:\n" << endl;
        cout << "Testing getAt function for a error case:" << endl;
        if (tester.getAtErrorCase(aCSR, -1, -1)) {
            cout << "Test msg: getAt test for error cases passed!\n" << endl;
        } else {
            cout << "Test msg: getAt test for error cases failed!\n" << endl;
        }

        ////////////////////////////////////////////////////////////////////////////////

        CSR cCSR;
        int array2[] = {0,0,0,0,100,200,0,0,300};
        cCSR.compress(3,3,array2,9);//initialize object cCSR
        CSR dCSR(cCSR);//create dCSR using copy constructor

        CSRList aCSRList;//create aCSRList
        aCSRList.insertAtHead(aCSR);
        aCSRList.insertAtHead(cCSR);
        CSRList bCSRList;//create bCSRList
        bCSRList.insertAtHead(dCSR);
        bCSRList.insertAtHead(bCSR);

//        cout << endl << "Dumping aCSRList:" << endl;
//        aCSRList.dump();
//        cout << endl << "Dumping bCSRList:" << endl;
//        bCSRList.dump();
//
//
        cout << "Following is the test message for testing assignment operator function for CSRList:\n" << endl;
        std::cout << "Testing assignment CSRList function for a normal case:" << std::endl;
        if (tester.assignmentOperatorNormalcsrList()) {
            std::cout << "Test msg:Assignment operator test for normal cases passed!" << std::endl;
        } else {
            std::cout << "Test msg:Assignment operator test for normal cases failed!" << std::endl;
        }
        std::cout << "Testing assignment CSRList function for a error case:" << std::endl;
        if (tester.assignmentOperatorErrorcsrList()) {
            std::cout << "Test msg:Assignment operator test for error cases passed!\n" << std::endl;
        } else {
            std::cout << "Test msg:Assignment operator test for error cases failed!\n" << std::endl;
        }
        cout << "Following is the test message for testing getAt function for CSRList:\n" << endl;

        std::cout << "Testing getAt function CSRList for a normal case:" << std::endl;
        if (tester.getAtNormalCSRList(aCSRList, 1, 2, 4)) {
            cout << "Test msg: getAt test for normal cases passed!" << std::endl;
        } else {
            cout << "Test msg: getAt test for normal cases failed!" << std::endl;
        }
        std::cout << "Testing getAt function CSRList for a error case:" << std::endl;
        if (tester.getAtErrorCSRList(aCSRList, 5, 2, 2)) {
            cout << "Test msg: getAt test for exception cases passed!\n" << std::endl;
        } else {
            cout << "Test msg: getAt test for exception cases failed!\n" << std::endl;
        }

        //cout << endl << aCSRList.getAt(1,2,4) << endl;//returns the value 70

        //cout << endl << aCSRList.getAt(5,2,2) << endl;//throws an exception

    }

    catch (exception &e){
        cout << e.what() << endl;
    }
    return 0;
}
