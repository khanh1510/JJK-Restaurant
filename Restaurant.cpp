#include "main.h"

extern int MAXSIZE;

class Node {
	public:
		string name;
		int energy;
		Node* next;


		Node(string name, int energy) {
			this->energy = energy;
			this->name = name;
			this->next = nullptr;
		}
};

class LinkedList{
	public:
		int size;
		Node* head;
	public:
		LinkedList() : head(nullptr), size(0) {}

		int getSize() {
			return this->size;
		}

		bool isEmpty() {
			return head == nullptr;
		}

		//This function is add a new Node at the end of the linked list
		//MAKE QUEUE, hang doi
		void addTail(string na, int ene) {
			Node* newNode = new Node(na, ene);

			if (isEmpty()) {
				head = newNode;
			}
			else {
				Node* tempo = head;
				while (tempo->next != nullptr) {
					tempo = tempo->next;
				}

				tempo->next = newNode;

			}

			size++;
			
		}

		//This function is add a new Node at the first of the linked list
		//MAKE STACK, tao ngan xep
		void addHead(string na, int ene) {
			Node* newNode = new Node(na, ene);

			newNode->next = head;
			head = newNode;

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
			else {		//Nothing to delete
				return;
			}

		}

		//This function is delete a any Node in Linked list
		//Delete Node with the Name of Node
		void delNode(string na) {
			Node* current = head;
			Node* prev = nullptr;

			while (current) {
				if (current->name == na) {
					if (prev) {
						prev->next = current->next;
					}
					else {
						head = current->next;
					}

					delete current;
				}

				prev = current;
				current = current->next;
			}

			size--;
		}

		//get a node have exactly name like timeCustomer
		Node* getNodeName(string name) {
			Node* temp = head;
			
			while (temp != nullptr) {
				if (temp->name == name) {
					return temp;
				}
				else {
					temp = temp->next;
				}
			}
			
			return head;		//I think function always return temp not return head
		}

		//I think this funcion shouldn't use anymore
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
		//Hàm này chưa tính tới trường hợp là queue rỗng
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
		//Shell sort còn sai cần phải viết lại
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

					while ( current2 != last && abs(current2->energy) > abs(current2->next->energy) ) {
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
		LinkedList TimerCustomer;
		int numCustomer = 0;
		customer* head = nullptr;
		customer* X = nullptr;

	public:	
		imp_res() {};

		//Thêm phần tử vào phía trước mặt của X
		void AddCusBefore(customer* new_cus, customer* X_cus) {
			customer* temp = X_cus->next;
			X_cus->next = new_cus;
			new_cus->next = temp;
			new_cus->prev = X_cus;
			temp->prev = new_cus;

			numCustomer++;
		}

		//Thêm phần tử vào phía sau lưng của X
		void AddCusAfter(customer* new_cus, customer* X_cus) {
			customer* temp = X_cus->prev;
			X_cus->prev = new_cus;
			new_cus->prev = temp;
			new_cus->next = X_cus;
			temp->next = new_cus;

			numCustomer++;
		}


		//Kiểm tra xem thử cái tên đó có ở trong bàn ăn hay là ở trong hàng chờ hay không
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


		//Xoá tất cả con người trong linked list vòng
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

		//Xoá người có tên trong bàn ăn
		void del_Name_customer(string na) {
			if (!head || na == "") {
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

		//This function calculate sum of all energy
		//Với i == 1 thì tính tổng năng lượng trong bàn ăn của chú thuật sư (Mahotsukai)
		//Với i == 0 thì tính tổng năng lượng trong bàn ăn của oán linh (Onryo)
		int sumEnergy(int i) {
			customer* temp = head;
			int sum = 0;

			if (i == 1) { 			//Calculate sum of energy of Mahotsukai
				do {
					if (temp->energy > 0) {
						sum += temp->energy;
					}

					temp = temp->next;
				}
				while (temp != head);
			}
			else {					//Calculate sum of energy of Onryo
				do {
					if (temp->energy < 0) {
						sum += abs(temp->energy);
					}
					temp = temp->next;
				}
				while (temp != head);
			}

			return sum;
		}



		void RED(string name, int energy)
		{
			cout << name << " " << energy << endl;
			customer *cus = new customer (name, energy, nullptr, nullptr);

			if (numCustomer == MAXSIZE) {		//if restaurant is full we push them to queue
				if (queCustomer.size == MAXSIZE) {		//if queue is full, invite them to go house
					return;
				}
				else {		//if queue is not full push them to queue
					if ( isAtRestaurant_or_Queue(queCustomer, FiFOCustomer, cus->name) ) {
						return ;
					}
					else {
						queCustomer.addTail(name, energy);
						TimerCustomer.addHead(name, energy);
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
							AddCusBefore(cus, X);
							X = cus;
						}
						else {
							AddCusAfter(cus, X);
							X = cus;
						}
					}
					FiFOCustomer.addTail(name, energy);
					TimerCustomer.addHead(name, energy);
				}
			}
			else {		//numCustomer >= maxsize/2, change the way we push them into restaurant
				int max_abs_energy = 0;
				customer* cus_to_add = this->X;
				customer* temp = this->X;

				for (int i = 0; i < numCustomer; i++) {
					int RES = abs(cus->energy - temp->energy);
					if ( RES > max_abs_energy ) {
						cus_to_add = temp;
						max_abs_energy = RES;

						temp = temp->next;
					}
					else {
						temp = temp->next;
					}
				}

				if ((cus->energy - cus_to_add->energy) > 0) {
					AddCusBefore(cus, cus_to_add);
					X = cus;
					FiFOCustomer.addTail(name, energy);					
				}
				else {
					AddCusAfter(cus, cus_to_add);			
					X = cus;
					FiFOCustomer.addTail(name, energy);
				}
				TimerCustomer.addHead(name, energy);
			}
		}
		//End RED function

		
		//Để ý thêm là cần phải xoá cả trong Timer Queue
		void BLUE(int num)		//Invite customer get out of here
		{
		// 	void delCustomer() {
		// 	if (!head) {
		// 		return;
		// 	}
			
		// 	customer* current = head;
		// 	do {
		// 		customer* temp = current;
		// 		current = current->next;
		// 		delete temp;
		// 	}
		// 	while (current != head);

		// 	delete current;

		// 	head = nullptr;

		// 	numCustomer = 0;
		// }
			if (num == 0) {
				return;		//Do nothing
			}
			if (num >= numCustomer) {		//we throw all of them
				//Xoá trong bàn ăn, FiFo customer, và TimerCustomer
				if (numCustomer == 0) {
					//Do nothing
					return;
				}
				else {
					customer* current = head;
					customer* nextNode;

					do {
						nextNode = current->next;
						string delNem = current->name;
						delete current;
						current = nextNode;

						FiFOCustomer.delNode(delNem);
						TimerCustomer.delNode(delNem);
					}
					while (current != head);

					head = nullptr;

					X = nullptr;

					numCustomer = 0;
				}
				//delCustomer();
				//FiFOCustomer.delALL();
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
					TimerCustomer.delNode(find_name);
				}

				//Dang viet den doan sau khi duoi N khach di khoi ban an
				//Gio can viet them tu hang cho vao trong ban an

				while (numCustomer < MAXSIZE && queCustomer.size > 0) {
					//Tao mot customer lay tu Head cua hang cho, roi xoa phan tu dau hang cho
					customer* que_to_restaurant  = new customer(queCustomer.head->name, queCustomer.head->energy, nullptr, nullptr);
					queCustomer.removeHead();

					if (numCustomer > 0 && numCustomer < MAXSIZE/2) {		//Cach thu nhat de chon cho ngoi
						if (que_to_restaurant->energy >= X->energy) {
							AddCusBefore(que_to_restaurant, X);
							X = que_to_restaurant;
							FiFOCustomer.addTail(que_to_restaurant->name, que_to_restaurant->energy);
						}
						else {
							AddCusAfter(que_to_restaurant, X);
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

			cout << "blue "<< num << endl;
		}
		void PURPLE()
		{
			
			if (queCustomer.size == 0 || queCustomer.size == 1) {
				return;
			}
			else {
				
			}

			cout << "purple"<< endl;			
		}
		void REVERSAL()
		{

			cout << "reversal" << endl;

			if (numCustomer == 0 || numCustomer == 1) {		//If num Customer is 0 or 1 just do nothing
				return;
			}
			LinkedList positive;
			LinkedList negative;
			customer* temp = X;

			for (int i = 0; i < numCustomer; i++) {
				if (temp->energy > 0) {
					positive.addHead(temp->name, temp->energy);
				}
				else {
					negative.addHead(temp->name, temp->energy);
				}

				temp = temp->prev;
			}

			string name_Of_X = X->name;
			//int energy_Of_X = X->energy;

			temp = temp->prev;

			for (int i = 0; i < numCustomer; i++) {
				if (temp->energy > 0) {
					temp->energy = positive.head->energy;
					temp->name = positive.head->name;

					positive.removeHead();
				}
				else {
					temp->energy = negative.head->energy;
					temp->name = negative.head->name;

					negative.removeHead();
				}

				temp = temp->prev;
			}

			temp = temp->prev;

			for (int j = 0; j < numCustomer; j++) {
				if (temp->name == name_Of_X) {
					X = temp;
				}
			}

			

		}
		void UNLIMITED_VOID()
		{

			cout << "unlimited_void" << endl;

			if (numCustomer < 4) {
				return;
			}
			int min_energy = X->energy;
			int last_min_energy = X->energy;
			int current_energy = 0;
			int current_length = 0;
			customer* min_energy_start = nullptr;

			customer* current = X;
			customer* start = X;

			do {
				current_energy += current->energy;
				current_length++;

				//Check if we found the min energy
				if (current_energy < min_energy && current_length >= 4) {
					min_energy = current_energy;
					min_energy_start = start;
					last_min_energy = min_energy;
				}
				else if (current_energy == last_min_energy) {
					last_min_energy = current_energy;
				}

				current = current->next;

				if (current == X) {
					start = start->next;
					current = start;
					current_energy = 0;
					current_length = 0;
				}
			}
			while (current != X);

			//We print all customer in the min ENERGY
			if (min_energy_start != nullptr) {
				cout << "Day con co tong ENERGY nho nhat: " << min_energy << endl;
				current = min_energy_start;
				do {
					cout << current->name << "-" << current->energy << endl;
					current = current->next;
				}
				while (current != min_energy_start);
			}
		}
		void DOMAIN_EXPANSION()			//Kick the customers
		{
			cout << "domain_expansion" << endl;
			cout << sumEnergy(1) << " " << sumEnergy(0) << endl;
			if (numCustomer == 0 || numCustomer == 1) {
				return;
			}

			if (sumEnergy(1) >= sumEnergy(0)) {		//Neu nang luong cua chu thuat su lon hon oan linh thì đuổi hết oán linh
				Node* temp_kick = FiFOCustomer.head;
				Node* wait_kick = queCustomer.head;

				while (temp_kick != nullptr) {
					if (temp_kick->energy < 0) {
						string name_to_kick = temp_kick->name;
						temp_kick = temp_kick->next;

						del_Name_customer(name_to_kick);
						FiFOCustomer.delNode(name_to_kick);
						continue;
					}
					temp_kick = temp_kick->next;
				}
				//Toàn bộ khúc trên là xoá oán linh trong bàn ăn và trong cái FIFOcustomer
				//Giờ cần phải xoá ở hàng chờ

				while (wait_kick != nullptr) {
					if (wait_kick->energy < 0) {
						string name_wait_kick = wait_kick->name;
						wait_kick = wait_kick->next;

						queCustomer.delNode(name_wait_kick);
						continue;
					}
					wait_kick = wait_kick->next;
				}

				//In ra oan lin bị đuổi theo thứ tự từ muộn nhất đến sớm nhất
				Node* temporary = TimerCustomer.head;
				while (temporary != nullptr) {
					if (temporary->energy < 0) {
						cout << temporary->name << "-" << temporary->energy << endl;
					}
					temporary = temporary->next;
				}
				
				//Xoa cac oan linh trong TimerCustomer
				Node* tempo2 = TimerCustomer.head;
				while (tempo2 != nullptr) {
					if (tempo2->energy < 0) {
						string removeName = tempo2->name;
						tempo2 = tempo2->next;

						TimerCustomer.delNode(removeName);
					}

					tempo2 = tempo2->next;
				}
			}
			else {			//Đuổi hết chú thuật sư
				Node* temp_kick = FiFOCustomer.head;
				Node* wait_kick = queCustomer.head;

				while (temp_kick != nullptr) {
					if (temp_kick->energy > 0) {
						string name_to_kick = temp_kick->name;
						temp_kick = temp_kick->next;

						del_Name_customer(name_to_kick);
						FiFOCustomer.delNode(name_to_kick);
						continue;
					}
					temp_kick = temp_kick->next;
				}

				//Toàn bộ khúc trên là xoá chú thuật sư trong bàn ăn và trong FIFOcustomer
				//GIờ cần phải xoá ở hàng chờ nữa

				while (wait_kick != nullptr) {
					if (wait_kick->energy > 0) {
						string name_wait_kick = wait_kick->name;
						wait_kick = wait_kick->next;

						queCustomer.delNode(name_wait_kick);
						continue;
					}
					wait_kick = wait_kick->next;
				}

				//in ra chu thuat su bi duoi
				Node* temporary = TimerCustomer.head;
				while (temporary != nullptr) {
					if (temporary->energy > 0) {
						cout << temporary->name << "-" << temporary->energy << endl;
					}
					temporary = temporary->next;
				}
				//Xoa cac oan linh trong TimerCustomer
				Node* tempo2 = TimerCustomer.head;
				while (tempo2 != nullptr) {
					if (tempo2->energy > 0) {
						string removeName = tempo2->name;
						tempo2 = tempo2->next;

						TimerCustomer.delNode(removeName);
						continue;
					}

					tempo2 = tempo2->next;
				}
			}


			//Toàn bộ trên đây là xoá khách khỏi nhà hàng
			//Giờ cần phải làm thêm đó chính là nếu hàng đợi còn người thì thêm vô bàn ăn
			
			while (numCustomer < MAXSIZE && queCustomer.size > 0) {
					//Tao mot customer lay tu Head cua hang cho, roi xoa phan tu dau hang cho
					customer* que_to_restaurant  = new customer(queCustomer.head->name, queCustomer.head->energy, nullptr, nullptr);
					queCustomer.removeHead();

					if (numCustomer > 0 && numCustomer < MAXSIZE/2) {		//Cach thu nhat de chon cho ngoi
						if (que_to_restaurant->energy >= X->energy) {
							AddCusBefore(que_to_restaurant, X);
							X = que_to_restaurant;
							FiFOCustomer.addTail(que_to_restaurant->name, que_to_restaurant->energy);
						}
						else {
							AddCusAfter(que_to_restaurant, X);
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

			//In ra khách bị đuổi theo thứ tự ai đến sớm nhất thì 
			
			
			
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
				if (numCustomer == 0 && queCustomer.size == 0) {
					cout << "Nothing to print" << endl;
					return;
				}
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
						cout << temp->name << "||" << temp->energy << endl;
						temp = temp->prev;
					}
					while (temp != X);
				}
			}
		}
};