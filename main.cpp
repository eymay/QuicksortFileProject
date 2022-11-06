#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class sorting{

float unsorted_values[11127];
int sorted_keys[11127];
    public:
    float getValue(int index){
        if (index >= 11127 ){
            throw std::invalid_argument("Index out of bounds");
            return -1;
        }else
            return unsorted_values[sorted_keys[index]];
    }
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

void sorting::extractor(vector<vector<string>>  &toBeExtracted){
	for (int i= 0 ; i  < toBeExtracted.size(); i++) {
		sort.unsorted_values[i] =  stof(toBeExtracted[i][3]);
	}
    for(int i = 0; i < 11127; i++){
        sort.sorted_keys[i] = i;
    }

}
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

void sorting::printer(){
	for (int i= 0 ; i  < sizeof(unsorted_values)/sizeof(float); i++) {
		cout << unsorted_values[i] << endl;
	}
}


int tb_partition (vector<vector<string>> &toBeSorted, int low, int high){
    
    int i = low -1;

    float Pivot = stof(toBeSorted[high][3]);
    for (int j = low; j < high; j++){
        if ( sort.getValue(j) <= Pivot ){
            i++;
            sort.swap(i,j);
        }
    }
        swap(toBeSorted[i+1], toBeSorted[high]);
        return i+1;
}
void tb_quicksort(vector<vector<string>> &toBeSorted, int low, int high){

    int i;
    if(low < high ){
        //cout << i ;
        //cout << "Partition1 loop" << endl;
	//printer(toBeSorted);
        i = tb_partition(toBeSorted, low, high);
            tb_quicksort(toBeSorted, low, i - 1);
            tb_quicksort(toBeSorted, i + 1, high);
    }
}
/*!
  Under the condition j >= i // j moves first

  do
  j++, i++
  No Swap
  While Arr[i], Arr[j] <= Pivot

  do
  j++
  Swap Arr[i] and Arr[j]
  While Arr[j] > Pivot

  After Swap update i.

  if Arr[j] == Pivot then:
  Swap Arr[i] and Arr[High]
  return i    //for partitioning 
              //1) From Low to i-1 , 2) From i+1 to High
              REPEAT SORTING for these sub-arrays

*/

int partition ( int low, int high){
    int i = low;
    int j = low;

    float Pivot = sort.getValue(high); 
//cout << (toBeSorted[i][3]);

//cout << (toBeSorted[j][3]);
    //if(j >= i){
    while (sort.getValue(i) <= Pivot && sort.getValue(j) <= Pivot && j < high -1){
        j++;
        i++;
        //cout << i << j ;
        //cout << "Inc both loop" << endl;
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
void quicksort( int low, int high){

    int i;
    if(low < high ){
        i = partition( low, high);
            quicksort( low, i - 1);
            quicksort( i + 1, high);
    }
}
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
        if((sort.getValue(j) < Pivot  ||  sort.getValue(j) > Pivot) && i < j){
            sort.swap(i,j);
        }


    }
    return j;   
}


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
