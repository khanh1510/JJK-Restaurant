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

			while (current != nullptr) {
				if (current->name == na) {
					if (prev) {
						prev->next = current->next;
					}
					else {
						head = current->next;
					}

					delete current;
					break;
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

		//This function get name of node have energy
		string getName(int ene) {
			Node* temp = head;
			while (temp != nullptr) {
				if (temp->energy == ene) {
					return temp->name;
				}

				temp = temp->next;
			}

			return "";
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
		int maxAbsCustomer() {		
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

			return returnNode->energy;
		}

		Node* getNodeAt(int index) {
			int count = 0;
			Node* current = head;
			while (current && count < index) {
				current = current->next;
				count++;
			}

			return current;
		}

		Node* index(int n, Node* start) {
			Node* temp = start;
			while (n--) {
				temp = temp->next;
			}

			return temp;
		}

		int getSize(Node* endNode) {
			int size = 1;
			Node* current = head;
			while (current && current != endNode) {
				size++;
				current = current->next;
			}

			return size;
		}

		// void swappp(int a, int b) {
		// 	Node* nodeA = getNodeAt(a);
		// 	Node* nodeB = getNodeAt(b);

		// 	if (nodeA != nullptr && nodeB != nullptr) {
		// 		swap(nodeA->energy, nodeB->energy);
		// 		swap(nodeA->name, nodeB->name);
		// 	}
		// }

		int inssort2(Node* start, int n, int incr) {
			int swapCount = 0;
			for (int i = incr; i < n; i += incr) {
				for (int j = i; (j >= incr) && (abs(index(j, start)->energy) > abs(index(j-incr, start)->energy)); j-=incr) {
					Node* a = index(j, start);
					Node* b = index(j-incr, start);

					swap(a->name, b->name);
					swap(a->energy, b->energy);
					swapCount++;
				}
			}

			return swapCount;
		}

		int shellSort(int n) {
			int totalSwap = 0;
			for (int i = n/2; i > 2; i/=2) {
				for (int j = 0; j < i; j++) {
					Node* star = head;
					for (int h = 0; h < j; h++) {
						star = star->next;
					}
					totalSwap += inssort2(star, n-j, i);
				}
			}
			totalSwap += inssort2(head, n, 1);

			return totalSwap;
		}

		//Shell Sort for a Linked List
		//Shell sort còn sai cần phải viết lại
		// int ShellSort(Node* head, Node* last) {
		// 	int n = 0;
		// 	Node* current = head;
		// 	while (current != last) {
		// 		n++;
		// 		current = current->next;
		// 	}

		// 	int swapCount = 0;

		// 	for (int cha = size/2; cha > 0; cha /= 2) {
		// 		for (int i = cha; i < size; i++) {
		// 			int temp = 0;
		// 			current = head;
		// 			for (int j = 0; j < i - cha; j++) {
		// 				current = current->next;
		// 			}
		// 			Node* current2 = current->next;

		// 			while ( current2 != last && abs(current2->energy) > abs(current2->next->energy) ) {
		// 				temp = current2->energy;
		// 				current2->energy = current2->next->energy;
		// 				current2->next->energy = temp;
		// 				current2 = current2->next;
		// 				swapCount++;
		// 			}
		// 		}
		// 	}

		// 	return swapCount;
		// }

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
						X = nullptr;

						numCustomer--;
						return;
					}
					else if (temp == head) {		//if we need delete first customer
						customer* tail = head->prev;
						head = head->next;
						tail->next = head;
						head->prev = tail;

						if (temp->energy > 0) {
							X = temp->next;
						}
						else {
							X = temp->prev;
						}

						delete temp;

						numCustomer--;
						return;
					}
					else {		//if delete any node in linked list
						customer* prevNode = temp->prev;
						customer* nextNode = temp->next;
						prevNode->next = nextNode;
						nextNode->prev = prevNode;

						if (temp->energy > 0) {
							X = temp->next;
						}
						else {
							X = temp->prev;
						}
						
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
			//cout << "red" << endl;
			//cout << name << " " << energy << endl;
			customer *cus = new customer (name, energy, nullptr, nullptr);
			if (MAXSIZE == 1) {
				head = cus;
				head->next = head;
				head->prev = head;
				X = head;

				numCustomer++;

				return;
			}
			if (numCustomer == MAXSIZE) {		//if restaurant is full we push them to queue
				if (queCustomer.size == MAXSIZE) {		//if queue is full, invite them to go house
					//cout << name << endl;
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
				//cout << "go to restaurant " << endl;
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
			//cout << "blue "<< num << endl;
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

			
		}
		void PURPLE()
		{
			//cout << "purple"<< endl;
			int totalCount = 0;
			if (queCustomer.size == 0 || queCustomer.size == 1) {
				return;
			}
			else {
				int num = queCustomer.maxAbsCustomer();
				//cout << "Testttt: " << num << endl;
				string nem = TimerCustomer.getName(num);
				//cout << "Testttt: " <<  << endl;

				int saiz = queCustomer.getSize(queCustomer.getNodeName(nem));

				totalCount = queCustomer.shellSort(saiz);


			}
			BLUE(totalCount % MAXSIZE);

		}
		void REVERSAL()
		{

			//cout << "reversal" << endl;

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
			//cout << "Coi ne: " << name_Of_X << endl;
			//int energy_Of_X = X->energy;

			temp = X;

			for (int i = 0; i < numCustomer; i++) {
				if (temp->energy > 0) {
					temp->name = positive.head->name;
					temp->energy = positive.head->energy;

					positive.removeHead();
				}
				else {
					temp->name = negative.head->name;
					temp->energy = negative.head->energy;

					negative.removeHead();
				}

				temp = temp->prev;
			}
			
			customer* hmm = X;
			for (int i = 0; i < numCustomer; i++) {
				if (hmm->name == name_Of_X) {
					X = hmm;
					break;
				}
				hmm = hmm->next;
			}

		}
		
		void UNLIMITED_VOID()
		{

			// cout << "unlimited_void" << endl;
			// cout << "ten cua X next la: " << X->next->name << endl;
			if (numCustomer < 4) {		//Neu nhu ban an it hon 4 nguoi do nothing
				return;
			}
			else {		//Ban an nhieu hon 4 nguoi 
				int RES = 0;
				customer* first_four = X;
				for (int i = 0; i < 4; i++) {		//Co tong nang luong cua 4 thang dau tien
					RES += first_four->energy;
					first_four = first_four->next;
				}
				//cout << "tong nang luong cua 4 tk dau tien " << RES << endl;

				customer* result_dau = X;
				customer* result_cuoi = first_four->prev;

				for (int k = 4; k <= numCustomer; k++) {
					int sum = 0;
					customer* dau = X;
					customer* cuoi = nullptr;
					customer* temp = X;
					for (int i = 0; i < k; i++) {
						sum += temp->energy;
						temp = temp->next;
					}
					cuoi = temp->prev;

					for (int j = 0; j < numCustomer; j++) {
						dau = dau->next;
						cuoi = cuoi->next;
						sum = sum - dau->prev->energy + cuoi->energy;
						if (sum <= RES) {
							RES = sum;
							result_dau = dau;
							result_cuoi = cuoi;
						}
					}
				}
				
				customer* iphone_promax = result_dau;
				while (iphone_promax != result_cuoi->next) {
					iphone_promax->print();
					iphone_promax = iphone_promax->next;
				}
				// cout << "result dau " << result_dau->name << endl;
				// cout << "result cuoi" << result_cuoi->name << endl;
				// cout << "Tong nang luong nho nhat cua day con la: " << RES << endl;

			}
			
		}
		void DOMAIN_EXPANSION()			//Kick the customers
		{
			//cout << "domain_expansion" << endl;
			//cout << sumEnergy(1) << " " << sumEnergy(0) << endl;
			if (numCustomer == 0 || numCustomer == 1) {
				//cout << "test" << endl;
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
				
				Node* temp_haiz = FiFOCustomer.head;
				Node* wait_kick = queCustomer.head;

				LinkedList haizz;
				while (temp_haiz != nullptr) {
					haizz.addHead(temp_haiz->name, temp_haiz->energy);
					temp_haiz = temp_haiz->next;
				}

				Node* temp_kick = haizz.head;

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
			//cout << "light " << num << endl;
			
			if (num == 0) {
				Node* temp = queCustomer.head;

				while (temp != nullptr) {
					cout << temp->name << "-" << temp->energy << endl;
					temp = temp->next;
				}
			}
			else {
				if (numCustomer == 0) {
					//cout << "Nothing to print" << endl;
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
						cout << temp->name << "-" << temp->energy << endl;
						temp = temp->prev;
					}
					while (temp != X);
				}
			}
		}
};