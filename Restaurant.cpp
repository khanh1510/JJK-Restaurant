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

		//Find the largest abs value in the queCustomer
		Node* maxAbsCustomer() {		
			Node* temp = head;
			
			int max = abs(temp->energy);
			Node* returnNode = head;
			
			while (temp != nullptr) {
				if ( abs(temp->energy) >= max ) {
					returnNode = temp;
					max = abs(temp->energy);
				}

				temp = temp->next;
			}

			return returnNode;
		}

		//Shell Sort for a Linked List
		int ShellSort(Node* head, Node* last) {
			int n = 0;
			Node* current = head;
			while (current != last) {
				n++;
				current = current->next;
			}

			int swapCount = 0;

			for (int cha = size/2; cha > 0; cha /= 2) {
				for (int i = cha; i < size; i++) {
					int temp = 0;
					current = head;
					for (int j = 0; j < i - cha; j++) {
						current = current->next;
					}
					Node* current2 = current->next;

					while (current2 != last && current2->energy < current2->next->energy) {
						temp = current2->energy;
						current2->energy = current2->next->energy;
						current2->next->energy = temp;
						current2 = current2->next;
						swapCount++;
					}
				}
			}

			return swapCount;
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

		void delCustomer() {
			if (!head) {
				return;
			}
			
			customer* current = head;
			do {
				customer* temp = current;
				current = current->next;
				delete temp;
			}
			while (current != head);

			delete current;

			head = nullptr;

			numCustomer = 0;
		}

		void del_Name_customer(string na) {
			if (!head) {
				return;
			}

			customer* temp = head;
			do {
				if (temp->name == na) {
					if (temp == head && head->next == head) {		//if there left one customer
						delete temp;
						head = nullptr;

						numCustomer--;
						return;
					}
					else if (temp == head) {		//if we need delete first customer
						customer* tail = head->prev;
						head = head->next;
						tail->next = head;
						head->prev = tail;
						delete temp;

						numCustomer--;
						return;
					}
					else {		//if delete any node in linked list
						customer* prevNode = temp->prev;
						customer* nextNode = temp->next;
						prevNode->next = nextNode;
						nextNode->prev = prevNode;
						delete temp;

						numCustomer--;
						return;
					}
				}
				temp = temp->next;
			} while (temp != head);
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

						numCustomer++;
					}
					else {
						if (cus->energy >= X->energy) {
							AddCusAfter(cus, X);
							X = cus;
							FiFOCustomer.addTail(name, energy);
						}
						else {
							AddCusBefore(cus, X);
							X = cus;
							FiFOCustomer.addTail(name, energy);
						}
					}
				}
			}
			else {		//numCustomer >= maxsize/2, change the way we push them into restaurant
				int max_abs_energy = 0;
				customer* cus_to_add = this->head;
				customer* temp = this->head;

				for (int i = 0; i < numCustomer; i++) {
					int RES = abs(cus->energy - temp->energy);
					if ( RES > max_abs_energy ) {
						cus_to_add = temp;
						max_abs_energy = RES;
					}
					else {
						temp = temp->next;
					}
				}

				if ((cus->energy - cus_to_add->energy) > 0) {
					AddCusAfter(cus, cus_to_add);
					X = cus;
					FiFOCustomer.addTail(name, energy);
					
				}
				else {
					AddCusBefore(cus, cus_to_add);			
					X = cus;
					FiFOCustomer.addTail(name, energy);
				}
			}	
		}
		void BLUE(int num)		//Invite customer get out of here
		{
			cout << "blue "<< num << endl;
			if (num >= numCustomer) {		//we throw all of them
				delCustomer();
				FiFOCustomer.delALL();
			}
			else {		//Not throw all customer
				for (int i = 0; i < num; i++) {
					string find_name = FiFOCustomer.getHead()->name;

					customer* temp = head;
					while (temp->name != find_name) {
						temp = temp->next;
					}

					if (temp->energy > 0) {
						X = temp->next;
					}
					else {
						X = temp->prev;
					}

					del_Name_customer(find_name);
					FiFOCustomer.removeHead();
				}

				//Dang viet den doan sau khi duoi N khach di khoi ban an
				//Gio can viet them tu hang cho vao trong ban an

				while (numCustomer < MAXSIZE && queCustomer.size > 0) {
					//Tao mot customer lay tu Head cua hang cho, roi xoa phan tu dau hang cho
					customer* que_to_restaurant  = new customer(queCustomer.head->name, queCustomer.head->energy, nullptr, nullptr);
					queCustomer.removeHead();

					if (numCustomer > 0 && numCustomer < MAXSIZE/2) {		//Cach thu nhat de chon cho ngoi
						if (que_to_restaurant->energy >= X->energy) {
							AddCusAfter(que_to_restaurant, X);
							X = que_to_restaurant;
							FiFOCustomer.addTail(que_to_restaurant->name, que_to_restaurant->energy);
						}
						else {
							AddCusBefore(que_to_restaurant, X);
							X = que_to_restaurant;
							FiFOCustomer.addTail(que_to_restaurant->name, que_to_restaurant->energy);
						}
					}
					else {			//Khi ban an vuot qua 1/2 MAXSIZE
						int max_abs_energy = 0;
						customer* cus_to_add = this->head;
						customer* temp = this->head;

						for (int i = 0; i < numCustomer; i++) {
							int RES = abs(que_to_restaurant->energy - temp->energy);
							if ( RES > max_abs_energy ) {
								cus_to_add = temp;
								max_abs_energy = RES;
							}
							else {
								temp = temp->next;
							}
						}

						if ((que_to_restaurant->energy - cus_to_add->energy) > 0) {
							AddCusAfter(que_to_restaurant, cus_to_add);
							X = que_to_restaurant;
							FiFOCustomer.addTail(que_to_restaurant->name, que_to_restaurant->energy);
							
						}
						else {
							AddCusBefore(que_to_restaurant, cus_to_add);			
							X = que_to_restaurant;
							FiFOCustomer.addTail(que_to_restaurant->name, que_to_restaurant->energy);
						}

					}
				}
			}
		}
		void PURPLE()
		{
			cout << "purple"<< endl;

			if (queCustomer.size == 0 || queCustomer.size == 1) {
				return;
			}
			else {
				int N = queCustomer.ShellSort(queCustomer.head, queCustomer.maxAbsCustomer());
				BLUE(N);
			}
			
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
			
			if (num == 0) {
				Node* temp = queCustomer.head;

				while (temp != nullptr) {
					cout << temp->name << "-" << temp->energy << endl;
					temp = temp->next;
				}
			}
			else {
				if (num > 0) {
					customer* temp = X;

					do {
						cout << temp->name << "-" << temp->energy << endl;
						temp = temp->next;
					}
					while (temp != X);
				}
				else {
					customer* temp = X;

					do {
						cout << temp->name << "-" << temp->energy << endl;
						temp = temp->prev;
					}
					while (temp != X);
				}
			}
		}
};