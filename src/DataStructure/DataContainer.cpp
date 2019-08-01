/*
 * DataContainer.cpp
 *
 *  Created on: 15 Jul 2019
 *      Author: Maarten
 */

#include "DataContainer.h"


namespace std {

vector<unordered_map<string,string>> mData;
unordered_map<string,unordered_map<string, shared_ptr<BitmapIndex>>>  mIndexes;
bool validIndexes;

DataContainer::DataContainer() {
	validIndexes = false;
}

DataContainer::~DataContainer() {
	ClearCurrentIndices();
}

void DataContainer::addDataRecord(unordered_map<string,string> dataRecord){
	mData.insert(mData.end(), dataRecord);
	validIndexes = false;
}


void DataContainer::CheckRebuildIndices(){
	if (!validIndexes)
		RebuildIndices();
}

void DataContainer::ClearCurrentIndices(){
	mIndexes.clear();
}


void DataContainer::RebuildIndices(){
	ClearCurrentIndices();

	int dataSize  = mData.size();

	for (int dataIndex = 0; dataIndex < dataSize; dataIndex++){
		unordered_map<string,string> dataRecord = mData.at(dataIndex);

		for (auto& dataPoint : dataRecord){
			string key   = dataPoint.first;
			string value = dataPoint.second;

			if (mIndexes.count(key)==0){
				unordered_map<string, shared_ptr<BitmapIndex>> subMap;
				mIndexes.insert (pair<string, unordered_map<string, shared_ptr<BitmapIndex>>>(key, subMap) );
			}
			if (mIndexes.at(key).count(value)==0){
				shared_ptr<BitmapIndex> bmIndex (new BitmapIndex(dataSize, false));
				mIndexes.at(key).insert(pair<string, shared_ptr<BitmapIndex>>(value, bmIndex));
			}

			mIndexes.at(key).at(value)->setIndexIsMember(dataIndex);
		}
	}

	validIndexes = true;
}


vector<unordered_map<string,string>> DataContainer::geDataFromIndex (BitmapIndex index){
	vector<unordered_map<string,string>> result;
	for (int i =0; i< index.mBitLength; i++)
		if (index.getIndexIsMember(i))
			result.insert(result.end(), mData.at(i));

	return result;

}


vector<unordered_map<string,string>> DataContainer::getAllMatchingData (unordered_map<string,string> predicates){
	CheckRebuildIndices();
	unique_ptr<BitmapIndex> index(new BitmapIndex(mData.size(), true));

	for (auto& predicate : predicates){
		string key   = predicate.first;
		string value = predicate.second;

		if (mIndexes.count(key)==0)
			return vector<unordered_map<string,string>> ();
		if (mIndexes.at(key).count(value)==0)
			return vector<unordered_map<string,string>> ();

		index->andOp(*mIndexes.at(key).at(value));
	}

	vector<unordered_map<string,string>> result = geDataFromIndex(*index);
	return result;
}



} /* namespace std */

