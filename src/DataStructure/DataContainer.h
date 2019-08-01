/*
 * DataContainer.h
 *
 *  Created on: 15 Jul 2019
 *      Author: Maarten
 */

#ifndef DATASTRUCTURE_DATACONTAINER_H_
#define DATASTRUCTURE_DATACONTAINER_H_

#include "include.h"
#include "BitmapIndex.h"

namespace std {

class DataContainer {
public:
	DataContainer();
	virtual ~DataContainer();

	void addDataRecord(unordered_map<string,string> dataRecord);
	vector<unordered_map<string,string>> getAllMatchingData (unordered_map<string,string> predicates);
	void RebuildIndices();

private:
	 void CheckRebuildIndices();
	 void ClearCurrentIndices();
	 vector<unordered_map<string,string>> geDataFromIndex (BitmapIndex index);
};

} /* namespace std */

#endif /* DATASTRUCTURE_DATACONTAINER_H_ */
