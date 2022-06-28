#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	this->cap = 1;
	this->elems = new Pelem[this->cap];
	this->next = new int[this->cap];
	this->head = -1;
	for (int i = 0; i <= this->cap - 2; i++)
		this->next[i] = i + 1;
	this->next[this->cap - 1] = -1;
	this->firstEmpty = 0;
} // Theta(N) 


void Bag::add(TElem elem) {

	// search for it
	int current = this->head;
	while (current != -1 && this->elems[current].info != elem) {
		current = this->next[current];
	}

	if (current != -1) {
		// we found it => we increase the frequency
		this->elems[current].freq++;
		return;
	}

	// the element is not already in the bag => we need to add it
	if (this->firstEmpty == -1) {
		// resize the array
		Pelem* newElems = new Pelem[this->cap * 2];
		int* newNext = new int[this->cap * 2];

		for (int i = 0; i < this->cap; i++) {
			newElems[i] = this->elems[i];
			newNext[i] = this->next[i];
		}

		for (int i = this->cap; i < this->cap * 2 - 1; i++) {
			newNext[i] = i + 1;
		}
		newNext[this->cap * 2 - 1] = -1;

		delete[] this->elems;
		delete[] this->next;

		this->elems = newElems;
		this->next = newNext;
		this->firstEmpty = this->cap;
		this->cap *= 2;
	}

	Pelem newElem;
	newElem.info = elem;
	newElem.freq = 1;

	int newPosition = firstEmpty;
	this->elems[newPosition] = newElem;
	this->firstEmpty = this->next[newPosition];
	this->next[newPosition] = this->head;
	this->head = newPosition;
} // Best Case: Theta(1), Worst Case: Theta(n) => Total: O(n)


bool Bag::remove(TElem elem) {
	// search for it
	int current = this->head;
	int prev = -1;
	while (current != -1 && this->elems[current].info != elem) {
		prev = current;
		current = this->next[current];
	}

	if (current != -1) {
		// we found it
		this->elems[current].freq--;

		if (this->elems[current].freq == 0) {
			// we remove it as well
			if (current == this->head) {
				this->head = this->next[this->head];
			}
			else {
				this->next[prev] = this->next[current];
			}
		
			// update the firstEmpty
			this->next[current] = this->firstEmpty;
			this->firstEmpty = current;
		}
		return true;
	}

	return false; 
} // Best Case: Theta(1), Worst Case: Theta(n) => Total: O(n)


bool Bag::search(TElem elem) const {
	int current = this->head;
	while (current != -1 && this->elems[current].info != elem) {
		current = this->next[current];
	}

	if (current != -1)
		return true;

	return false; 
} // Best Case: Theta(1), Worst Case: Theta(n) => Total: O(n)

int Bag::nrOccurrences(TElem elem) const {
	int current = this->head;
	while (current != -1 && this->elems[current].info != elem) {
		current = this->next[current];
	}
	if (current != -1)
		return this->elems[current].freq;
	return 0; 
} // Best Case: Theta(1), Worst Case: Theta(n) => Total: O(n)


int Bag::size() const {
	int total = 0;
	int current = this->head;
	while (current != -1) {
		total += this->elems[current].freq;
		current = this->next[current];
	}
	return total;
} // Theta(n)


bool Bag::isEmpty() const {
	if (this->head == -1)
		return 1;
	return 0;
} // Theta(1)

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}

int Bag::getRange() const {
	if (this->isEmpty())
		return -1;

	int maximum = INT_MIN;
	int minimum = INT_MAX;
	int e;
	int current = this->head;

	while (current != -1) {
		e = this->elems[current].info;
		current = this->next[current];

		if (e > maximum)
			maximum = e;

		if (e < minimum)
			minimum = e;
	}

	return (maximum - minimum);
} // Theta(n) 

Bag::~Bag() {
	delete[] this->elems;
	delete[] this->next;
} // Theta(1)

