#include "main.h"

extern int MAXSIZE;

class Node {
	public:
		string name;
		int energy;
		Node* next;

		Node() {
			next = nullptr;
		}

		Node(string na, int ene) {
			this->energy = ene;
			this->name = na;
			this->next = nullptr;
		}
};

class LinkedList{
	public:
		int size = 0;
		Node* head;
	public:
		LinkedList() {
			head = nullptr;
		}
		// string getName() {
		// 	return this->name;
		// }

		// int getEnergy() {
		// 	return this->energy;
		// }

		int getSize() {
			return this->size;
		}

		bool isEmpty() {
			if (head == nullptr) {
				return false;
			}
			else {
				return true;
			}
		}

		void addTail(string na, int ene) {
			Node* temp = new Node(na, ene);

			if (head == nullptr) {
				head = temp;
			}
			else {
				Node* tempo = head;
				while (tempo->next != nullptr) {
					tempo = tempo->next;
				}

				tempo->next = temp;
			}

			size++;
			
		}

		Node* getHead() {
			return head;
		}

		void removeHead() {
			if (head != nullptr) {
				Node* temp = head;
				head = head->next;
				delete temp;
				size--;
			}

		}
		void delALL() {
			Node* temp = head;
			while (temp != nullptr) {
				temp = head;
				head = head->next;
				delete temp;
			}

			this->size = 0;

		}
		// void ShellSort() {		//Do it later
		// 	int count = size;

		// }
		
};

class imp_res : public Restaurant
{
	public:
		LinkedList queCustomer;
		LinkedList FiFOCustomer;
		int numCustomer = 0;
		customer* head = nullptr;
		customer* X = nullptr;

	public:	
		imp_res() {};

		void AddCusBefore(customer* new_cus, customer* X_cus) {
			customer* temp = X_cus->next;
			X_cus->next = new_cus;
			new_cus->next = temp;
			new_cus->prev = X_cus;
			temp->prev = new_cus;
			numCustomer++;
		}

		void AddCusAfter(customer* new_cus, customer* X_cus) {
			customer* temp = X_cus->prev;
			X_cus->prev = new_cus;
			new_cus->prev = temp;
			new_cus->next = X_cus;
			temp->next = new_cus;

			numCustomer++;
		}

		bool isAtRestaurant_or_Queue(LinkedList queue, LinkedList fifo, string na) {
			Node* temp1 = queue.head;
			Node* temp2 = fifo.head;

			while (temp1 != nullptr) {
				if (na == temp1->name) {
					return true;
				}

				temp1 = temp1->next;
			}

			while (temp2 != nullptr) {
				if (na == temp2->name) {
					return true;
				}

				temp2 = temp2->next;
			}
			return false;
		}



		void RED(string name, int energy)
		{
			cout << name << " " << energy << endl;
			customer *cus = new customer (name, energy, nullptr, nullptr);

			if (numCustomer == MAXSIZE) {		//if restaurant is full we push them to queue
				if (queCustomer.getSize() == MAXSIZE) {		//if queue is full, invite them to go house
					return;
				}
				else {		//if queue is not full push them to queue
					if ( isAtRestaurant_or_Queue(queCustomer, FiFOCustomer, cus->name) ) {
						return ;
					}
					else {
						queCustomer.addTail(name, energy);
					}
				}
			}
			else if (numCustomer >= 0 && numCustomer < MAXSIZE/2) {		//First way to go to Restaurant
				if (cus->energy == 0) {		//engergy = 0 get out of here
					return;
				}
				else if ( isAtRestaurant_or_Queue(queCustomer, FiFOCustomer, cus->name) ) {
					return;
				}
				else {		//energy is not equal 0, we push them to Restaurant
					if (numCustomer == 0) {
						head = cus;
						head->next = head;
						head->prev = head;
						X = head;
					}
					else {
						if (cus->energy >= X->energy) {
							AddCusAfter(cus, X);
							X = cus;
						}
						else {
							AddCusBefore(cus, X);
							X = cus;
						}
					}
				}
			}
			else {		//numCustomer >= maxsize/2, change the way we push them into restaurant
				
			}

			
			
		}
		void BLUE(int num)
		{
			cout << "blue "<< num << endl;
		}
		void PURPLE()
		{
			cout << "purple"<< endl;
		}
		void REVERSAL()
		{
			cout << "reversal" << endl;
		}
		void UNLIMITED_VOID()
		{
			cout << "unlimited_void" << endl;
		}
		void DOMAIN_EXPANSION()
		{
			cout << "domain_expansion" << endl;
		}
		void LIGHT(int num)
		{
			cout << "light " << num << endl;
		}
};