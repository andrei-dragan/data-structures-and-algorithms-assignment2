#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->current = this->bag.head;
	this->freq = 1;
} // Theta(1)

void BagIterator::first() {
	this->current = this->bag.head;
	this->freq = 1;
} // Theta(1)


void BagIterator::next() {
	if (!this->valid())
		throw exception();

	if (this->freq == this->bag.elems[this->current].freq) {
		this->current = this->bag.next[this->current];
		this->freq = 1;
	}
	else
		this->freq++;
} // Theta(1)


bool BagIterator::valid() const {
	return (current != -1);
} // Theta(1)



TElem BagIterator::getCurrent() const
{
	if (!this->valid())
		throw exception();
	return this->bag.elems[this->current].info;
} // Theta(1)
