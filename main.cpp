#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
/*!
 *to perform safer index based sorting a class with private arrays of the extracted numbers to be sorted and their referencing index array is created. 
 Any function that needs to access these arrays except functions for the sorting are methods. 
 */
class sorting{

float unsorted_values[11127];/*!< Every element at i corresponds to the unsorted rating number at i'th row*/
int sorted_keys[11127];/*!< Every element at i corresponds to the sorted row numbers*/
    public:
    /*!
     * getValue() function returns the rating number at index refered by the sorted_keys array at index i. The index of value to be sorted is stored in another array which gets sorted.
     */
    float getValue(int index){
        if (index >= 11127 ){
            throw std::invalid_argument("Index out of bounds");
            return -1;
        }else
            return unsorted_values[sorted_keys[index]];
    }
    /*!
     *Swap is performed by swapping positions of value indices at sorted_keys array.

     */
    void swap(int index1, int index2){
        std::swap(sorted_keys[index1], sorted_keys[index2]);
     }

    void extractor(vector<vector<string>>  &toBeExtracted);
    bool checker();
    void printer();
    void writer(vector<string> header, vector<vector<string>> bookArray);

};
sorting sort;


/*!
 *
 * Parser() reads the csv file in local directory named "books.csv" and feeds it into a vector of vector of strings. The vector of strings represent the rows and make the swaps easier. The outer vector is used as the file's internal representation in code.
 *
 * Parser() opens the file and uses vector.push_back extensively.  
 */
vector<vector<string>> parser(){
    ifstream reader;
    vector<vector<string>> bookArray; /*!< Vector of vector of strings to be sorted */
    string line;
    bookArray.reserve(11128);

    reader.open("books.csv");
    while (reader) {
        while (getline(reader, line))
        {
            stringstream ss(line);
            vector<string> linevec;
	while (getline(ss, line, ','))
            {
                linevec.push_back(line);
            }
            bookArray.push_back(linevec);


        }
    }
    reader.close();
return bookArray;
}
/*!
 *Extractor is used to minimise the usage of stof() function throughout the programme. It introduces a linear complexity which can be neglected.
 Unsorted_values array has the values extractec from the read vector of vector of strings.Also the sorted_keys are initialised as before the sorting every i index points to the i'th row. 
 */
void sorting::extractor(vector<vector<string>>  &toBeExtracted){
	for (int i= 0 ; i  < toBeExtracted.size(); i++) {
		sort.unsorted_values[i] =  stof(toBeExtracted[i][3]);
	}
    for(int i = 0; i < 11127; i++){
        sort.sorted_keys[i] = i;
    }

}
/*!
 *Writer() places the header of the csv first and then proceeds to read the vector of vector of strings. The read operation to the vector is performed non-sequentially. The row to be written is found by reading the sorted_keys array sequentially. The overhead introduced by finding the vector index from the sorted_keys array has a linear complexity as it is done once in the outer loop and the value is used throughout the inner loop.  
 */
void sorting::writer(vector<string> header, vector<vector<string>> bookArray){
	ofstream writer;
	string line;

	writer.open("sorted_books.csv", ios_base::out );
	int line_index;
	line_index = 0;
    
	line = header[0];
	
		for(int i = 1; i < header.size(); i++){
			line += ',';

			line += header[i];
        }
    line += '\n';    

	writer << line ;
    int vector_index;
    for(int i = 0; i < bookArray.size(); i++){
        vector_index = sort.sorted_keys[i];
        line = bookArray[vector_index][0];
        for(int j = 1; j < bookArray[vector_index].size(); j++){
            line += ',';
            line += bookArray[vector_index][j];
        }
        line += '\n';
        writer << line;
    }
	
	writer.close();


	return;
}

/*!
 *Printer() is used for debugging purposes, especially for smaller sized inputs.
 */

void sorting::printer(){
	for (int i= 0 ; i  < sizeof(unsorted_values)/sizeof(float); i++) {
		cout << unsorted_values[i] << endl;
	}
}

/*!
 *The partition code is from the textbook (Introduction to Algorithms, Cormen) and used for debugging purposes.
 */
int tb_partition (int low, int high){
    
    int i = low -1;

    float Pivot = sort.getValue(high);
    for (int j = low; j < high; j++){
        if ( sort.getValue(j) <= Pivot ){
            i++;
            sort.swap(i,j);
        }
    }
    sort.swap(i+1, high);
    return i+1;
}
/*!
 *The quicksort code is from the textbook (Introduction to Algorithms, Cormen) and used for debugging purposes.
 */

void tb_quicksort(int low, int high){

    int i;
    if(low < high ){
        i = tb_partition(low, high);
            tb_quicksort( low, i - 1);
            tb_quicksort(i + 1, high);
    }
}
/*!
The code for the Part I, partition function starts by 
walking i and j until a value bigger than the pivot is seen. The conditional j < high - 1
is added for bound safety.
After a value bigger than the pivot is seen j walks alone.Here is a conditional added: 
The swap to perform is made if only the new value is bigger than pivot.
As j gets updated it can see values smaller than the pivot and it is wasteful to swap them.

The pseudocode allowed to update i in various ways. The method developed eventually was to 
make i walk until j or a value bigger than pivot was seen.

If j gets to the last element which is pivot, it gets swapped with i. As i is indicating the 
first element bigger than the pivot, it is a safe index to swap the pivot.
*/

int partition ( int low, int high){
    int i = low;
    int j = low;

    float Pivot = sort.getValue(high); 
    while (sort.getValue(i) <= Pivot && sort.getValue(j) <= Pivot && j < high -1){
        j++;
        i++;
    }

    while ( j < high){
        j++;
        if(sort.getValue(j) < Pivot)
            sort.swap(i,j);
        while(sort.getValue(i) <= Pivot && i < j)
            i++;
    }


    if(j == high)
        sort.swap(i, high);
    return i;
}
/*!
 *quicksort function of Part I. Since only the partition scheme changes the quicksort() 
 functions of Part I and II are almost identical. 
The reason there is not an argument of array is that the value reading and swap operations
are performed with a global object's methods. The objects can be made an argument as an improvement.
 */
void quicksort( int low, int high){

    int i;
    if(low < high ){
        i = partition( low, high);
            quicksort( low, i - 1);
            quicksort( i + 1, high);
    }
}
/*!
 *The code for Part II, the partition function starts by walking i from the low index and j from the
 high index. The pivot is selected randomly. In addition to the pseudocode, I decided to store the 
 pivot in the low index at the beginning and restore it in the end to have the pivot in the right place 
 ath the end of partitioning.
 i walks until seeing a value bigger than pivot and j walks backwards from the end until seeing a value 
 smaller than pivot. If either i point to a value larger than pivot or j points to a value smaller than 
 pivot and i is smaller than j swap i and j. 
 In the end j points to the first value smaller than pivot so it is safe to swap the pivot at low  and j. 
 */
int partition2 ( int low, int high){
    int i = low;
    int j = high;
    int pivIndex = rand() % (high - low) + low;
    float Pivot = sort.getValue(pivIndex);
    sort.swap(pivIndex, low);

    while (i < j){ 
        while ( sort.getValue(j) <= Pivot && i < high ){
            i++;
        }
        while ( sort.getValue(j) >= Pivot && j >= i && j > low){
            j--;
        }
        
        if(i >= j){
            sort.swap(low, j);
            return j;
        }
        if((sort.getValue(j) < Pivot  ||  sort.getValue(i) > Pivot) && i < j){
            sort.swap(i,j);
        }


    }
    return j;   
}


/*!
 *quicksort function of Part I. Since only the partition scheme changes the quicksort() 
 functions of Part I and II are almost identical. 
 */
void quicksort2(int low, int high){
    int i;
    if(low < high ){
        i = partition2(low, high);

        if(i>0){

            quicksort2(low, i - 1);
            quicksort2(i + 1, high);
        }
    }

}
/*!
 *Checker is used for testing the if the sorting was correct. It returns a boolean which is used for 
 deciding to write to a file. It also useful for debugging.
 */
bool sorting::checker(){
    bool isSorted = true;

    for (int i = 0; i < sizeof(sorted_keys)/sizeof(float) - 1; i++){
        if(sort.getValue(i) > sort.getValue(i+1)){
            cout << "Error at " << i << endl;
            cout << sort.getValue(i) << " " << sort.getValue(i + 1) << endl;
            isSorted = false;
        }
    }
    if(isSorted)
        cout << "Sorted" << endl;
    else
        cout << "Not Sorted" << endl;

    return isSorted;
}
/*!
 *Parser returns the vector of vector of strings which is the parsed intermediate
 format of input csv file. The first row of header contains title information and 
 has no data so it is stored in the header variable and the first row is erased in 
 the vector. The low and high indices are calculated from the resulting data vector.
 Extractor initialises the sorting arrays. After sorting, the result is checked with
checker. If it is correct the result is written to a csv file with writer().
For small input sizes the printer functions can be uncommented.
 */
int main(){

 vector<vector<string>> bookArray =  parser();

   vector<string> header;
    header = bookArray[0] ;
    bookArray.erase(bookArray.begin());
    
    int low = 0;
    int high = bookArray.size() - 1;


	//printer(bookArray);
    sort.extractor(bookArray);
    quicksort( low, high);
    if(sort.checker()){
	    sort.writer(header, bookArray);
        cout << "writing to file" << endl;
    }   

	//printer(bookArray);
    return 0;

}
