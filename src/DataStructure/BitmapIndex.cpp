/*
 * BitmapIndex.cpp
 *
 *  Created on: 15 Jul 2019
 *      Author: Maarten
 */

#include "BitmapIndex.h"


namespace std {
	const int BITS_PER_INT = 8*(sizeof(int));
	int       mDataSize;

	BitmapIndex::BitmapIndex(int size, bool allTrue) {
		mBitLength = size;
		mDataSize  = ((BITS_PER_INT-1+mBitLength)/BITS_PER_INT);
		mData      = new unsigned int[mDataSize];

		int initialBits =  allTrue ? ~0 : 0;

		for (int i=0; i<mDataSize; i++)
			mData[i] = initialBits;
	}


	BitmapIndex::~BitmapIndex() {
		delete [] mData;
	}

	void BitmapIndex::setIndexIsMember(int i){
		if (i >= mBitLength || i<0)
			throw invalid_argument( "BitmapIndex::setIndexIsMember index out of bounds." );

		int index    = i / BITS_PER_INT;
		int subindex = i % BITS_PER_INT;
		mData[index] |= (1 << subindex);
	}

	bool BitmapIndex::getIndexIsMember(int i){
		if (i >= mBitLength || i<0)
			throw invalid_argument( "BitmapIndex::getIndexIsMember index out of bounds." );

		int index    = i / BITS_PER_INT;
		int subindex = i % BITS_PER_INT;
		return 1==(1 & (mData[index] >> subindex));
	}

	void BitmapIndex::orOp  (const BitmapIndex& other){
		if (other.mBitLength != mBitLength)
			throw invalid_argument( "BitmapIndex::orOp bitLength doesn't match." );

		for (int i=0; i<mDataSize; i++)
			mData[i] |= other.mData[i];
	}

	void BitmapIndex::andOp (const BitmapIndex& other){
		if (other.mBitLength != mBitLength)
			throw invalid_argument( "BitmapIndex::andOp bitLength doesn't match." );

		for (int i=0; i<mDataSize; i++)
			mData[i] &= other.mData[i];
	}


	void BitmapIndex::debugDisplay(){
		for (int i =0; i< mBitLength; i++)
			if (getIndexIsMember(i))
				cout << i<<",";
		cout << endl;
	}

} /* namespace std */
