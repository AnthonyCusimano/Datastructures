#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

#include <iostream>

template <typename Tmplt>

class A_SingleLinkedList {

private:

	//nodes within the list
	//nested class to discourage making (a) node(s) outside of a LinkedList
	struct A_SingleLinkedList_Node {

		//constructor
		A_SingleLinkedList_Node(Tmplt* const _data) {

			//assign this the _data passed
			myData = *_data;

			//for now, assume this is the back of the LinkedList
			this->nextNode = 0;

		}

		//data contained within the node
		Tmplt myData;

		//the next node in the list
		A_SingleLinkedList_Node* nextNode;


	};//END OF Node

	  // pointers to first and last nodes in the list
	A_SingleLinkedList_Node *front, *back;

	//the number of elements in this list
	int listSize;

public:

	//public iterator class for our single linked list
	class A_SingleLinkedList_Iterator {

	private:

		//A_SingleLinkedList declared as friend to avoid wasting time accessing iterator objects
		//seen as benificial since iterator is essentially a helper class for A_SingleLinkedList
		friend class A_SingleLinkedList;

		A_SingleLinkedList_Node *node;

	public:


		/**
		default constructor sets this iterator's node to 0
		*/
		A_SingleLinkedList_Iterator() {

			this->node = 0;

		}

		/**
		destructor
		*/
		~A_SingleLinkedList_Iterator() {
			//=D
		}

		/**
		returns this iterator's node
		*/
		A_SingleLinkedList_Node* getMyNode() {
			return this->node;
		}

		/**
		equality operator for checking if two iterators are pointing
		to the same position
		*/
		const bool operator ==(A_SingleLinkedList_Iterator* const _oi) {

			return this->node == _oi->node;

		}

		/**
		inequality operator for checking if two iterators are pointing
		to different positions
		*/
		const bool operator !=(A_SingleLinkedList_Iterator* const _oi) {

			return this->node != _oi->node;

		}

		/**
		sets this iterator to the back node of _list
		*/
		const A_SingleLinkedList_Iterator* toBack(A_SingleLinkedList* const _list) {

			this->node = _list->back;
			return this;

		}

		/**
		sets this iterator to the front node of _list
		*/
		const A_SingleLinkedList_Iterator* toFront(A_SingleLinkedList* const _list) {

			this->node = _list->front;
			return this;

		}

		const A_SingleLinkedList_Iterator* getNext() {

			this->node = this->node->nextNode;

			return this;

		}

		/**
		searches _list for _target and removes it without breaking _list up in any way
		WARNING: if _target is not found, this will likely crash
		*/
		const A_SingleLinkedList_Iterator* Erase(A_SingleLinkedList* _list, A_SingleLinkedList_Node* _target) {

			A_SingleLinkedList_Node *T_Placehold;

			//checks for if the target is at the back or the front of the list
			if (_target == _list->front) _list->PopFront();
			else if (_target == _list->back) _list->PopBack();

			else {

				//go to the front of _list
				this->node = _list->front;

				//begin iterating
				//go until we find the target or the end of the list
				//currently omitting back check because it should be handled above
				while (this->node->nextNode != _target/* && this->node != _list->back*/) {

					this->node = this->node->nextNode;

				}
				
				//if we found the target
				//this->node->nextNode IS the target
				if (this->node->nextNode == _target) {

					//set placehold to the node after the target
					T_Placehold = this->node->nextNode->nextNode;

					//delete the target
					delete this->node->nextNode;

					//rejoin the halves of the list
					this->node->nextNode = T_Placehold;

					//the list has lost a node
					--_list->listSize;

				}

				//in any case, we will always return this iterator
				//no case exists for if we found the back element of the list (and it isn't the target, as would be implied if we reached this code block)
				//due to no action being necissary in that case
				return this;

			}

			return this;

		}

		/**
		searches for a particular value within the list
		this will send the iterator to the start of _list as a part of the method
		will not work for 0 values
		*/
		const A_SingleLinkedList_Iterator* Find(Tmplt& const _value, A_SingleLinkedList* _list) {

			//start at the front of this list
			this->node = _list->front;

			while (this->node->myData != _value && this->node != _list->back) {

				this->node = this->node->nextNode;

			}

			//at the end of the while loop, we either went to the end of the list
			return this;

		}

	};//end of A_SingleLinkedListIterator

	/**
	Default constructor
	initializes front, back, and listSize to 0
	*/
	A_SingleLinkedList() {

		this->front = this->back = 0;

		this->listSize = 0;

	}

	/**
	returns true if the list is not empty
	*/
	const bool IsEmpty() {

		if (this->listSize == 0) return true;

		//if we've gotten to this line, it's acceptable to return false
		return false;

	}

	/**
	returns the size of this list
	*/
	const int getSize() {

		return this->listSize;

	}

	/**
	returns a constant pointer to the first pointer in this list
	*/
	const Tmplt& getFront() {

		//if the list is not empty, it's fine to return the front
		if (this->listSize > 0)
			return this->front->myData;

		//if the list is currently empty, return 0
		return 0;

	}

	/**
	returns a constant pointer to the last pointer in this list
	*/
	const Tmplt& getBack() {

		if (this->listSize > 0)
			return this->back->myData;

		//if the list is currently empty, return 0
		return 0;

	}
	
	/**
	pushes this data into a new node, located at the front of the list
	*/
	void PushFront(Tmplt* const _newNode) {

		//the new front of the list
		A_SingleLinkedList_Node *T_NewFront = new A_SingleLinkedList_Node(_newNode);

		//if this is empty, this should be a new node which is both the front and the back of this list
		if (this->listSize == 0) {

			this->front = this->back = T_NewFront;

		}

		//if not, place the new node at the new front of the list, and have it pointing to the former front
		else {

			T_NewFront->nextNode = this->front;
			this->front = T_NewFront;

		}

		//list got bigger
		++this->listSize;

		T_NewFront = 0;
		delete T_NewFront;

	}

	/**
	pushes this data into a new node, located at the back of the list
	*/
	void PushBack(Tmplt* const _newNode) {

		//std::cout << "I'm in PushBack, and _newNode is: " << _newNode << '\n';

		//the new front of the list
		A_SingleLinkedList_Node *T_NewBack = new A_SingleLinkedList_Node(_newNode);

		//if this is empty, this should be a new node which is both the front and the back of this list
		if (this->listSize == 0) {

			this->back = this->front = T_NewBack;

		}
		
		//if not, place the new node at the new back of the list, and have the former back pointing to it
		else {

			this->back->nextNode = T_NewBack;
			this->back = T_NewBack;

		}

		//list got bigger
		++this->listSize;

		//test this
		//meant to avoid memory leak
		T_NewBack = 0;
		delete T_NewBack;

	}

	/**
	used to remove the front most element from this list
	DO NOT check for an empty list before calling this method, it accounts for size 0
	*/
	void PopFront() {

		//if the list is not empty
		if (this->listSize > 0) {

			//if this list only has one element to begin with remove it
			//by making both front and back null
			//DEBUG does this leak without delete?
			if (this->front == this->back)
				this->front = this->back = 0;

			//this will fire if the list size is greater than 1
			else {

				//temporary pointer to hold the position of the old head of the list
				A_SingleLinkedList::A_SingleLinkedList_Node *T_OldHead = this->front;

				//moving the list's head pointer to it's new head
				this->front = this->front->nextNode;

				//deleting the pointer to the value to the old head of the list
				delete T_OldHead;

			}

			//either way, decrement the size of the list
			--this->listSize;

		}

	}

	/**
	used to remove the back most element from this list
	DO NOT check for an empty list before calling this method, it accounts for size 0
	*/
	void PopBack() {
		//if the list is not empty
		if (this->listSize > 0) {

			//if the list only has one element to begin with remove it
			//by making both the front and back null
			if (this->front == this->back) {

				this->front = this->back = 0;

			}

			//this will fire if the list size is greater than 1
			else {

				//holding the address of the old back of the list
				A_SingleLinkedList::A_SingleLinkedList_Node *T_OldBack = this->back;
				//going to use our back pointer to traverse the list, to the node before it's old value
				this->back = this->front;
				while (this->back->nextNode != T_OldBack) 
					this->back = this->back->nextNode;

				//the new back is found, temp must be deleted
				delete T_OldBack;

			}

			//either way, decrement the size of the list
			--this->listSize;

		}

	}

	/**
	recersive function to delete this list's contents
	pass the front node of this list
	*/
	void Clear(A_SingleLinkedList_Node* _front) {

		//call this function on the next node in the array
		//until you've found the back
		if (_front != this->back)
			this->Clear(_front->nextNode);

		//delete each pointer
		//recursion will cause each of these to resolve off the stack from back to front 
		//and exit this method after removing _front itself
		delete _front;
		_front = 0;

	}

	/**
	destructor mirrors the Clear method
	*/
	~A_SingleLinkedList() {

		this->Clear(this->front);

	}

};
#endif