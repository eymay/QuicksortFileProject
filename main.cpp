#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

vector<vector<string>> bookArray; /*!< Vector of vector of strings to be sorted */
float unsorted_values[11127];
int sorted_keys[11127];


/*!
 *
 * Parser() reads the csv file in local directory named "books.csv" and feeds it into a vector of vector of strings. The vector of strings represent the rows and make the swaps easier. The outer vector is used as the file's internal representation in code.
 *
 * Parser() opens the file and uses vector.push_back extensively.  
 */
void parser(){
    ifstream reader;
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

}
void extractor(vector<>){

}

void writer(vector<string> header){
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
	while(line_index < bookArray.size()){
	line = bookArray[line_index][0];
	
		for(int i = 1; i < bookArray[0].size(); i++){
			line += ',';

			line += bookArray[line_index][i]; 
	}
	line += '\n';
		
	line_index++;
	//cout << line_index << endl;
	writer << line ;

    
	}
	writer.close();


	return;
}

void printer(vector<vector<string>>  &toBePrinted){
	for (int i= 0 ; i  < toBePrinted.size(); i++) {
		cout << toBePrinted[i][3] << endl;
	}
}


int tb_partition (vector<vector<string>> &toBeSorted, int low, int high){
    
    int i = low -1;

    float Pivot = stof(toBeSorted[high][3]);
    for (int j = low; j < high; j++){
        if ( stof(toBeSorted[j][3]) <= Pivot ){
            i++;

            swap(toBeSorted[i], toBeSorted[j]);
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

int partition (vector<vector<string>> &toBeSorted, int low, int high){
    int i = low;
    int j = low;

    float Pivot = stof(toBeSorted[high][3]);
//cout << (toBeSorted[i][3]);

//cout << (toBeSorted[j][3]);
    //if(j >= i){
    while (stof(toBeSorted[i][3]) <= Pivot && stof(toBeSorted[j][3]) <= Pivot && j < high -1){
        j++;
        i++;
        //cout << i << j ;
        //cout << "Inc both loop" << endl;
    }

    while ( j < high){
        j++;
        if(stof(toBeSorted[j][3]) < Pivot)
            swap(toBeSorted[i], toBeSorted[j]);
        while(stof(toBeSorted[i][3]) <= Pivot && i < j)
            i++;
    }

    //i = i -1;
    //i = j; //After swap update i

    //if(stof(toBeSorted[j][3]) == Pivot) 
    if(j == high)
        swap(toBeSorted[i], toBeSorted[high]);

    return i;
}
void quicksort(vector<vector<string>> &toBeSorted, int low, int high){

    int i;
    if(low < high ){
        //cout << i ;
        //cout << "Partition1 loop" << endl;
	//printer(toBeSorted);
        i = partition(toBeSorted, low, high);
            quicksort(toBeSorted, low, i - 1);
            quicksort(toBeSorted, i + 1, high);
    }
}
int partition2 (vector<vector<string>> &toBeSorted, int low, int high){
    int i = low;
    int j = high;
    int pivIndex = rand() % (high - low) + low;
    float Pivot = stof(toBeSorted[pivIndex ][3]);

    swap(toBeSorted[pivIndex], toBeSorted[low]);

    while (i < j){ 
        while ( stof(toBeSorted[i][3]) <= Pivot && i < high ){
            i++;
        }
        while ( stof(toBeSorted[j][3]) >= Pivot && j >= i && j > low){
            j--;
        }
        
        if(i >= j){
            swap(toBeSorted[low], toBeSorted[j]);
            return j;
        }
        if((stof(toBeSorted[j][3]) < Pivot  ||  stof(toBeSorted[i][3]) > Pivot) && i < j){
            swap(toBeSorted[i], toBeSorted[j]);
        }


    }
    /*
    if(pivIndex < j)
        swap(toBeSorted[pivIndex], toBeSorted[j]);
    if(pivIndex > i)
        swap(toBeSorted[pivIndex], toBeSorted[i]);
        */
    return j;   
}


void quicksort2(vector<vector<string>> &toBeSorted, int low, int high){
    int i;
    if(low < high ){
        //cout << i ;
        //cout << "Partition loop" << endl;
        i = partition2(toBeSorted, low, high);
	    //printer(toBeSorted);

        if(i>0){

            quicksort2(toBeSorted, low, i - 1);
            quicksort2(toBeSorted, i + 1, high);
        }
    }

}

void checker(vector<vector<string>> &toBeChecked){
    bool isSorted = true;
    for (int i = 0; i < toBeChecked.size() -1; i++){
        if(stof(toBeChecked[i][3]) > stof(toBeChecked[i+1][3])){
            cout << "Error at " << i << endl;
            cout << toBeChecked[i][3] << " " << toBeChecked[i+1][3] << endl;
            isSorted = false;
        }
    }
    if(isSorted)
        cout << "Sorted" << endl;
    else
        cout << "Not Sorted" << endl;
}

int main(){

    parser();
   vector<string> header;
    header = bookArray[0] ;
    bookArray.erase(bookArray.begin());
    
    int low = 0;
    int high = bookArray.size() - 1;


	//printer(bookArray);
    quicksort(bookArray, low, high);
    checker(bookArray);
	writer(header);
    cout << "sorting..." << endl;

	//printer(bookArray);
    return 0;

}
