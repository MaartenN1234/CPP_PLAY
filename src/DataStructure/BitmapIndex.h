/*
 * BitmapIndex.h
 *
 *  Created on: 15 Jul 2019
 *      Author: Maarten
 */

#ifndef DATASTRUCTURE_BITMAPINDEX_H_
#define DATASTRUCTURE_BITMAPINDEX_H_

#include "include.h"

namespace std {

class BitmapIndex {
public:

	BitmapIndex(int size);
	BitmapIndex(int size, bool allTrue);
	virtual ~BitmapIndex();

	void setIndexIsMember(int i);
	bool getIndexIsMember(int i);
	void orOp  (const BitmapIndex& other);
	void andOp (const BitmapIndex& other);

	int          mBitLength;
	void debugDisplay();

private:
	unsigned int *mData;
};

} /* namespace std */

#endif /* DATASTRUCTURE_BITMAPINDEX_H_ */
