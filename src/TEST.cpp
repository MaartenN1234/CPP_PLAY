
#include <iostream>
#include <string>
#include "DataStructure\BitmapIndex.h"
#include "DataStructure\DataContainer.h"

using namespace std;

void displayData(vector<unordered_map<string,string>> data){
	cout << "Data point count " << data.size()  << endl;
	for (auto& map: data){
		for (auto& pair : map){
			cout << pair.first << "=" << pair.second <<" ";
		}
		cout << endl;
	}
}




int main() {
	DataContainer set;
	unordered_map<string,string> record1;
	unordered_map<string,string> record2;
	unordered_map<string,string> record3;
	unordered_map<string,string> record4;
	unordered_map<string,string> predicates;

	record1.insert(pair<string,string>("A","1"));
	record1.insert(pair<string,string>("B","3"));
	record1.insert(pair<string,string>("C","4"));

	record2.insert(pair<string,string>("A","1"));
	record2.insert(pair<string,string>("B","5"));
	record2.insert(pair<string,string>("C","2"));

	record3.insert(pair<string,string>("A","3"));
	record3.insert(pair<string,string>("B","3"));
	record3.insert(pair<string,string>("C","3"));

	record4.insert(pair<string,string>("A","1"));
	record4.insert(pair<string,string>("B","3"));
	record4.insert(pair<string,string>("C","7"));

	set.addDataRecord(record1);
	set.addDataRecord(record2);
	set.addDataRecord(record3);

	predicates.insert(pair<string,string>("B","3"));
	predicates.insert(pair<string,string>("A","1"));

	displayData(set.getAllMatchingData(predicates));

	set.addDataRecord(record4);

	displayData(set.getAllMatchingData(predicates));

	/* code below is to test for memory leakage
	for (int i=0; i<1000; i++)
		set.addDataRecord(record4);

	for (int i=0; i<1000000; i++)
		set.RebuildIndices();
	// */

	return 0;
}
