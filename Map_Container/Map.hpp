/*
 * Implement your functionality here without changing given test cases
 */

// valgrind --leak-check=yes -v ./test
// g++ -std=c++11 -Wall -Wextra -pedantic minimal.cpp -o minimal 


#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <utility>

#define MAX_LVL 20 

namespace cs540 {
	/*  Random Level Generator  */
	float frand() {
	    return (float) rand() / RAND_MAX;
	}
	 
	int random_level() {
	    static bool first = true;
	    if (first) 
	    {
	        srand((unsigned)time(NULL));
	        first = false;
	    }
	    int lvl = (int)(log(frand()) / log(1.-0.5));
	    return lvl < MAX_LVL ? lvl : MAX_LVL;
	}
	/* ------------------------ */


	template<typename Key_T, typename Mapped_T>
	class Map;

	template<typename Key_T, typename Mapped_T>
	class Node {
		public:
			typedef std::pair<const Key_T, Mapped_T> ValueType;
			ValueType Node_data;
			Node<Key_T, Mapped_T> **forw;
			Node<Key_T, Mapped_T> **back;
			int curr_lvl;

		Node(int lvl, const ValueType &temp_value): Node_data(temp_value), curr_lvl(lvl) {
			forw = new Node*[MAX_LVL+1];
			back = new Node*[MAX_LVL+1];
		};

		Node() {
			forw = new Node*[MAX_LVL+1];
			back = new Node*[MAX_LVL+1];
		}

		~Node() {
			delete [] forw;
			delete [] back;
		} 
	};

	template<typename Key_T, typename Mapped_T>
	class Map {
	public:
		typedef std::pair<const Key_T, Mapped_T> ValueType;
		//ValueType data_member;

		class Iterator {
			public:
				Node<Key_T, Mapped_T> *data;
				Iterator() {

				}

				Iterator(const Iterator &iter) {
					data = iter.get_iter_data();
				}

				Iterator& operator=(const Iterator &iter) {
					data = iter.get_iter_data();
					return *this; 
				}

				Iterator& operator++() {
					if(data == nullptr) {
						return *this;
					}
					data=data->forw[0];
					return *this;
				}

				Iterator operator++(int) {
					Iterator temp = *this;
					if(data == nullptr) {
						return *this;
					}
					data = data ->forw[0];
					return temp;
				}

				Iterator& operator--() {
					if(data == nullptr) {
						return *this;
					}
					data=data->back[0];
					return *this;
				}

				Iterator operator--(int) {
					Iterator temp = *this;
					if(data == nullptr) {
						return *this;
					}
					data = data ->back[0];
					return temp;
				}

				ValueType &operator*() const {
					return data->Node_data;
				}

				ValueType &operator->() const {
					return data->Node_data;
				}
				
				Iterator(Node<Key_T, Mapped_T>* tempNode) {
					data = tempNode;
				}

				Node<Key_T, Mapped_T>* get_iter_data() const {
					return data;
				}

				~Iterator() {
					data = nullptr;
				}
		};

		class ConstIterator{
			public:
				Node<Key_T, Mapped_T> *data;
				ConstIterator() {

				}

				ConstIterator(const Iterator &iter) {
					data = iter.get_iter_data();
				}

				ConstIterator(const ConstIterator &c_iter) {
					data = c_iter.get_iter_data();
				}

				ConstIterator& operator=(const ConstIterator &c_iter) {
					data = c_iter.get_iter_data();
					return *this; 
				}

				ConstIterator& operator++() {
					if(data == nullptr) {
						return *this;
					}
					data=data->forw[0];
					return *this;
				}

				ConstIterator operator++(int) {
					ConstIterator temp = *this;
					if(data == nullptr) {
						return *this;
					}
					data = data ->forw[0];
					return temp;
				}

				ConstIterator& operator--() {
					if(data == nullptr) {
						return *this;
					}
					data=data->back[0];
					return *this;
				}

				ConstIterator operator--(int) {
					ConstIterator temp = *this;
					if(data == nullptr) {
						return *this;
					}
					data = data ->back[0];
					return temp;
				}

				const ValueType &operator*() const {
					return data->Node_data;
				}

				const ValueType &operator->() const {
					return data->Node_data;
				}
				
				ConstIterator(Node<Key_T, Mapped_T>* tempNode) {
					data = tempNode;
				}

				Node<Key_T, Mapped_T>* get_iter_data() const {
					return data;
				}

				~ConstIterator() {
					data = nullptr;
				}
		};

		class ReverseIterator{
			public:
				Node<Key_T, Mapped_T> *data;
				ReverseIterator() {

				}

				ReverseIterator(const ReverseIterator &iter) {
					data = iter.get_iter_data();
				}

				ReverseIterator &operator=(const ReverseIterator &iter) {
					data = iter.get_iter_data();
					return *this; 
				}

				ReverseIterator& operator++() {
					if(data == nullptr) {
						return *this;
					}
					data=data->back[0];
					return *this;
				}

				ReverseIterator operator++(int) {
					ReverseIterator temp = *this;
					if(data == nullptr) {
						return *this;
					}
					data = data ->back[0];
					return temp;
				}

				ReverseIterator& operator--() {
					if(data == nullptr) {
						return *this;
					}
					data=data->forw[0];
					return *this;
				}

				ReverseIterator operator--(int) {
					ReverseIterator temp = *this;
					if(data == nullptr) {
						return *this;
					}
					data = data->forw[0];
					return temp;
				}

				ValueType &operator*() const {
					return data->Node_data;
				}

				ValueType &operator->() const {
					return data->Node_data;
				}
				
				ReverseIterator(Node<Key_T, Mapped_T>* tempNode) {
					data = tempNode;
				}

				Node<Key_T, Mapped_T>* get_iter_data() const {
					return data;
				}

				~ReverseIterator() {
					data = nullptr;
				}
		};

		Node<Key_T, Mapped_T> *head;
		Node<Key_T, Mapped_T> *tail;
		int lvl;
		int count;


		/* Constructor and Assignment Operator */

		void initialise(const ValueType &temp_value) {
			head = new Node<Key_T, Mapped_T>(MAX_LVL, temp_value);
			tail = new Node<Key_T, Mapped_T>(MAX_LVL, temp_value);
			for(int i=MAX_LVL; i>=0; i--) {
				head->forw[i] = tail;
				tail->back[i] = head;

				head->back[i] = nullptr;
				tail->forw[i] = nullptr;
			}
			lvl=0;
			count=0;
		}


		Map() {
			//Create an empy map
			head = nullptr;
			tail = nullptr;
		}

		Map(const Map &temp_map) {
			//Copy Constructor
			bool map_created = false;
			Node<Key_T, Mapped_T> *temp = temp_map.head->forw[0];
			for(;temp!=temp_map.tail; temp=temp->forw[0]) {
				if(!map_created) {
					initialise(temp->Node_data);
					map_created = true;
				}
				insert(temp->Node_data);
			}
		}

		Map(std::initializer_list<ValueType> init_list) {
			//std::cout << "Initializer list" << std::endl;
			bool map_created = false;
			auto it = init_list.begin();
			for(it=init_list.begin(); it!=init_list.end(); it++) {
				if(!map_created) {
					initialise(*it);
					map_created=true;
				}
				insert(*it);
			}
		}

		Map& operator=(const Map& temp_map) {
			//std::cout << "Copy Assignment ?" << std::endl;
			Node<Key_T, Mapped_T> *tempNode = temp_map.head->forw[0];
			if(tempNode == temp_map.tail) {
				return *this;
			}
			while(tempNode != temp_map.tail) {
				insert(tempNode->Node_data);
				tempNode = tempNode->forw[0];
			}
			return *this;
		}

		/* -------------------------------------- */

		//std::pair<Iterator, bool> insert(const ValueType &temp_value);
		//Mapped_T &at(const Key_T&);
		//const Mapped_T &at(const Key_T&) const;

		Node<Key_T, Mapped_T>* get_Node(const Key_T &temp_key) const {
			if(head != nullptr) {
				Node<Key_T, Mapped_T> *tempNode = head;
				for(int i=lvl; i>=0; i--) {
					while(tempNode->forw[i] != tail &&
						tempNode->forw[i]->Node_data.first < temp_key) {
						tempNode = tempNode->forw[i];
					}
				}
				tempNode = tempNode->forw[0];
				if(tempNode->Node_data.first == temp_key &&
					tempNode!=tail ) {
					return tempNode;
				}
				else {
					return nullptr;
				}
			}
			return nullptr;
		}



		/* Size */ 

		size_t size() const {
			return count;
		}

		bool empty() const {
			if(count == 0) {
				return true;
			}
			return false;
		}

		/* ------------------------------------- */

		/* Iterators */
		Iterator begin() {
			if(head!=nullptr) {
				return head->forw[0];
			}
			return nullptr;
		}

		Iterator end() {
			return tail;
		}

		ConstIterator begin() const {
			if(head!=nullptr) {
				return head->forw[0];
			}
			return nullptr;
		}

		ConstIterator end() const {
			return tail;
		}

		ReverseIterator rbegin() {
			if(tail!=nullptr) {
				return tail->back[0];
			}
			else {
				return nullptr;
			}

		}

		ReverseIterator rend() {
			if(head!=nullptr) {
				return head;
			}
			return nullptr;
		}



		/* ------------------------------------- */

		/* Element Access */ 

		Iterator find(const Key_T& find_key) {
			Node<Key_T, Mapped_T> *tempNode = get_Node(find_key);
			if(tempNode == nullptr) {
				return Iterator(tail);
			}
			return Iterator(tempNode);			
		}

		ConstIterator find(const Key_T& find_key) const {
			Node<Key_T, Mapped_T> *tempNode = get_Node(find_key);
			if(tempNode == nullptr) {
				return ConstIterator(tail);
			}
			return ConstIterator(tempNode);			
		}




		Mapped_T& at(const Key_T &find_key) {
			//std::cout << "AT hit !" << std::endl;
			Node<Key_T, Mapped_T> *tempNode = get_Node(find_key);
			if(tempNode == nullptr) {
				//std::cout << "Index out of range " << std::endl;
				throw std::out_of_range("Index out of range!");
			}
			else {
				//std::cout << "At found " << tempNode->Node_data.second << std::endl;
				return tempNode->Node_data.second;
			}
			//unreachable section
			return tempNode->Node_data.second;
		}

		const Mapped_T& at(const Key_T &find_key) const {
			//std::cout << "AT hit !" << std::endl;
			Node<Key_T, Mapped_T> *tempNode = get_Node(find_key);
			if(tempNode == nullptr) {
				//std::cout << "Index out of range " << std::endl;
				throw std::out_of_range("Index out of range!");
			}
			else {
				//std::cout << "At found " << tempNode->Node_data.second << std::endl;
				return tempNode->Node_data.second;
			}
			//unreachable section
			return tempNode->Node_data.second;
		}

		Mapped_T& operator[](const Key_T &find_key) {
			//std::cout << "[] operator hit !" << std::endl;
			Node<Key_T, Mapped_T> *tempNode = get_Node(find_key);
			if(tempNode == nullptr) {
				// if not found, value initialize
				ValueType temp_value = std::make_pair(find_key, Mapped_T{});
				Iterator temp_iter = insert(temp_value).first;
				return temp_iter.data->Node_data.second;
			}
			return tempNode->Node_data.second;
		}

		/* ------------------------------------- */

		/* Modifiers */

		

		std::pair<Iterator, bool> insert(const ValueType &temp_value) {
			if(head==nullptr) {
				initialise(temp_value);
			}

			Node<Key_T, Mapped_T> *temp_h = head;
			Node<Key_T, Mapped_T> *update[MAX_LVL+1];

			for(int i=lvl; i>=0; i--) {
				while(temp_h->forw[i]!=tail &&
					temp_h->forw[i]->Node_data.first < temp_value.first) {
					temp_h = temp_h->forw[i];
				}
				update[i] = temp_h;
			}

			if(temp_h->forw[0]->Node_data.first == temp_value.first &&
				temp_h->forw[0]!=tail) {
				// std::cout << " ??? " << std::endl;
				Iterator it(temp_h->forw[0]);
				//Iterator it;
				return std::make_pair(it, true);
			}

			if(temp_h->forw[0] == tail ||
				!(temp_h->forw[0]->Node_data.first == temp_value.first) ) {
				count += 1;
				int new_lvl = random_level();

				if(new_lvl == 0) {
					new_lvl = 1;
				}

				Node<Key_T, Mapped_T> *tempNode = new Node<Key_T, Mapped_T>(new_lvl, temp_value);

				if(new_lvl > lvl) {
					for(int i=new_lvl+1 ; i>=lvl; i--) {
						head->forw[i]=tempNode;
						tempNode->forw[i] = tail;
						tail->back[i] = tempNode;
						tempNode->back[i] = head;
						update[i]=nullptr;
					}
					lvl = new_lvl;
				}

				for(int i=0;i<=new_lvl; i++) {
					if(update[i]!=nullptr) {
						tempNode->forw[i]=update[i]->forw[i];
						update[i]->forw[i]->back[i] = tempNode;
						update[i]->forw[i] = tempNode;
						tempNode->back[i]=update[i];
					}
				}

				Iterator it(tempNode);
				return std::make_pair(it,true);
			}
			for(int i=0; i<MAX_LVL; i++) {
				update[i] = nullptr;
				delete update[i];
			}
			return std::make_pair(tail, false);
		}

		template<typename IT_T>
		void insert(IT_T range_beg, IT_T range_end) {
			auto it = range_beg;
			for(it=range_beg; it!=range_end; it++) {
				insert(*it);
			}
		}



		void erase(Iterator pos) {
			Node<Key_T, Mapped_T> *tempNode = head;
			Node<Key_T, Mapped_T> *update[MAX_LVL+1];
			const Key_T &temp_value = pos.get_iter_data()->Node_data.first;

			for(int i=lvl; i>=0; i--) {
				while(tempNode->forw[i]!=tail &&
					tempNode->forw[i]->Node_data.first < temp_value) {
					tempNode = tempNode->forw[i];
				}
				update[i] = tempNode;
			}
			tempNode = tempNode->forw[0];
			if(tempNode!=tail &&
				tempNode->Node_data.first == temp_value) {
				for(int i=0; i<=lvl;i++) {
					if(update[i]->forw[i] == tempNode) {
						update[i]->forw[i] = tempNode->forw[i];
						tempNode->forw[i]->back[i] = update[i];
					}
					else {
						break;
					}
				}
				count += -1;
				delete tempNode;

				while(lvl>0 &&
					head->forw[lvl] == tail) {
					lvl += -1;
				}
			}
		}

		void erase(const Key_T &temp_key) {
			Node<Key_T, Mapped_T> *tempNode = head;
			Node<Key_T, Mapped_T> *update[MAX_LVL+1];

			for(int i=lvl; i>=0; i--) {
				while(tempNode->forw[i]!=tail &&
					tempNode->forw[i]->Node_data.first < temp_key) {
					tempNode = tempNode->forw[i];
				}
				update[i] = tempNode;
			}
			tempNode = tempNode->forw[0];
			if(tempNode->Node_data.first == temp_key && tempNode!=tail) {
				for(int i=0;i<=lvl; i++) {
					if(update[i]->forw[i] != tempNode) {
						break;
					}
					update[i]->forw[i] = tempNode->forw[i];
					tempNode->forw[i]->back[i]=update[i];
				}
				count += -1;
				delete tempNode;
				while(lvl>0 && head->forw[lvl]==tail) {
					lvl--;
				}
			}
		}

		void clear() {
			if(head!=nullptr && tail!=nullptr) {
				Node<Key_T, Mapped_T> *tempNode = head->forw[0];
				while(tempNode!=tail) {
					erase(find(tempNode->Node_data.first));
					tempNode=head->forw[0];
				}
				delete head;
				delete tail;
			}
		} 

		/* ------------------------------------- */



		/* Comparison operators for Map */

		friend bool operator==(const Map<Key_T, Mapped_T>& m1, const Map<Key_T, Mapped_T>& m2) {
			Node<Key_T, Mapped_T> *temp1 = m1.head->forw[0];
			Node<Key_T, Mapped_T> *temp2 = m2.head->forw[0];

			while(temp1 != m1.tail &&
				temp2 != m2.tail) {
				if(temp1->Node_data != temp2->Node_data) {
					return false;
				}
				temp1 = temp1->forw[0];
				temp2 = temp2->forw[0];
			}
			if(temp1 == m1.tail && temp2 == m2.tail) {
				return true;
			}
			else {
				return false;
			}
		}

		friend bool operator!=(const Map<Key_T, Mapped_T>& m1, const Map<Key_T, Mapped_T>& m2) {
			if(m1==m2) {
				return false;
			}
			return true;
		}

		friend bool operator<(const Map<Key_T, Mapped_T>& m1, const Map<Key_T, Mapped_T>& m2) {
			if(m1.size()< m2.size()) {
				return true;
			}
			else if(m1.size() > m2.size()) {
				return false;
			}
			else {
				auto it1 = m1.begin();
				auto it2 = m2.begin();
				for(it1 = m1.begin(); it1!=m1.end(); it1++) {
					if(it1.data->Node_data.first < it2.data->Node_data.first) {
						continue;
					}
					else {
						return false;
					}
				}
				return true;
			}
		}


		/* ------------------------------------- */

		/* Comparision for Iterators */

		friend bool operator==(const Iterator &it1, const Iterator &it2) {
			return (it1.data == it2.data);
		}

		friend bool operator==(const ConstIterator &it1, const ConstIterator &it2) {
			return (it1.data == it2.data);
		}

		friend bool operator==(const Iterator &it1, const ConstIterator &it2) {
			return (it1.data == it2.data);
		}

		friend bool operator==(const ConstIterator &it1, const Iterator &it2) {
			return (it1.data == it2.data);
		}

		friend bool operator!=(const Iterator &it1, const Iterator &it2) {
			return !(it1.data == it2.data);
		}

		friend bool operator!=(const ConstIterator &it1, const ConstIterator &it2) {
			return !(it1.data == it2.data);
		}

		friend bool operator!=(const Iterator &it1, const ConstIterator &it2) {
			return !(it1.data == it2.data);
		}

		friend bool operator!=(const ConstIterator &it1, const Iterator &it2) {
			return !(it1.data == it2.data);
		}


		friend bool operator==(const ReverseIterator &it1, const ReverseIterator &it2) {
			return (it1.data == it2.data);
		}

		friend bool operator!=(const ReverseIterator &it1, const ReverseIterator &it2) {
			return !(it1.data == it2.data);
		}



		/* ------------------------------------- */

		~Map() {
			clear();
		}

	};
}