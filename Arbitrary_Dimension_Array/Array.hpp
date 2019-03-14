#include <iostream>
#include <typeinfo>
#include <vector>

namespace cs540 {

	std::vector<size_t> size_acc;

	void do_size(size_t t) {
		size_acc.push_back(t);
	}

	template<typename T, typename... Rest> 
	void do_size(T t, Rest... rest) {
		size_acc.push_back(t);
		do_size(rest...);
	}
	
	class OutOfRange {

	};

	template <typename T, size_t D1, size_t... Dims>
	class Array {
	public:

		static T ValueType;
		int len_arr;
		Array<T, Dims...> data_arr[D1];
		// T data_arr[D1];

		Array() {
			// std::cout << "Defaul const " << typeid(T).name() << " " << D1 << " " << sizeof...(Dims) << std::endl; 
			len_arr = D1;		
		}

		Array(const Array& arr) {

			// std::cout << "Copy const hit " << std::endl; 
			std::copy(std::begin(arr.data_arr), std::end(arr.data_arr),std::begin(data_arr));
			len_arr = arr.len_arr;
			//std::cout << arr.len_arr << std::endl; 
		}

		template <typename U>
		Array(const Array<U, D1, Dims...> &arr) {
			// std::cout << "V templated Copy const" << std::endl; 
			std::copy(std::begin(arr.data_arr), std::end(arr.data_arr),std::begin(data_arr));
			len_arr = arr.len_arr; 
		}

		Array &operator=(const Array &arr ) {
			// std::cout << "assignment op" << std::endl;
			std::copy(std::begin(arr.data_arr), std::end(arr.data_arr),std::begin(data_arr));
			len_arr = arr.len_arr; 
		}

		template <typename U>
		Array &operator=(const Array<U, D1, Dims...> &arr) {
			// std::cout << "v template assignment op" << std::endl;
			std::copy(std::begin(arr.data_arr), std::end(arr.data_arr),std::begin(data_arr));
			len_arr = arr.len_arr; 
		}


		Array<T, Dims...>& operator[](size_t index) {
			if(index < 0 || index >= len_arr) {
				OutOfRange obj;
				throw obj;
			}
			//std::cout << sizeof...(Dims) << "< S \n";
			return data_arr[index];
		}

		const Array<T, Dims...>&operator[](size_t index) const {
			if(index < 0 || index >= len_arr) {
				OutOfRange obj;
				throw obj;
			}
			return data_arr[index];
		}

		class FirstDimensionMajorIterator {
		public:
			T* data_val;
			int maj_count;
			int min_count;
			int main_count;

			FirstDimensionMajorIterator() {

			}

			FirstDimensionMajorIterator(const FirstDimensionMajorIterator &fdm_it) {

			}

			FirstDimensionMajorIterator &operator=(const FirstDimensionMajorIterator &fdm_it) {
				// std::cout << "assignment op?" << "\n";
				data_val = fdm_it.data_val;
			}

			FirstDimensionMajorIterator &operator++() {
				data_val += 1;
				return *this;
			}

			FirstDimensionMajorIterator operator++(int) {
				FirstDimensionMajorIterator temp_obj = *this;
				data_val += 1;
				return temp_obj;
			}

			T &operator*() const {
				return *(data_val);
			}

		};

		FirstDimensionMajorIterator fmbegin() {
			FirstDimensionMajorIterator obj;
			obj.data_val = (data_arr[0].Array<T,Dims...>::fmbegin()).data_val;
			//std::cout << *(obj.data_val) << "\n";
			// std::copy(std::begin(data_arr[0]), std::end(data_arr[0]),std::begin(obj.data_arr));
			obj.maj_count = 0;
			obj.min_count = 0;
			obj.main_count = 0;
			return obj;
		}

		FirstDimensionMajorIterator fmend() {
			FirstDimensionMajorIterator obj;
			obj.data_val = (data_arr[len_arr-1].Array<T,Dims...>::fmend()).data_val;
			// std::copy(std::begin(data_arr[len_arr-1]), std::end(data_arr[len_arr-1]),std::begin(obj.data_arr));
			obj.maj_count = 0;
			obj.min_count = 0;
			obj.main_count = 0;
			return obj;
		}

		friend bool operator==(const FirstDimensionMajorIterator &fdm_it1, 
				const FirstDimensionMajorIterator &fdm_it2) {
			return (fdm_it1.data_val == fdm_it2.data_val);
		}

		friend bool operator!=(const FirstDimensionMajorIterator &fdm_it1, 
				const FirstDimensionMajorIterator &fdm_it2) {
			return (fdm_it1.data_val != fdm_it2.data_val);
		}
	};

	template<typename T, size_t D>
	class Array<T,D> {
	public:
		T data_arr[D];
		static T ValueType;
		int total_size;
		
		Array() {
			// std::cout << "Hit ???" << std::endl;
			total_size = D;
		}

		Array(const Array& arr) {
			// std::cout << "Copy const" << std::endl; 
			std::copy(std::begin(arr.data_arr), std::end(arr.data_arr),std::begin(data_arr));
			total_size = arr.total_size;
		}

		template <typename U>
		Array(const Array<U, D> &arr) {
			// std::cout << "templated Copy const" << std::endl; 
			std::copy(std::begin(arr.data_arr), std::end(arr.data_arr),std::begin(data_arr));
			total_size = arr.total_size;
		}

		Array &operator=(const Array &arr ) {
			// std::cout << "assignment op" << std::endl;
			std::copy(std::begin(arr.data_arr), std::end(arr.data_arr),std::begin(data_arr));
			total_size = arr.total_size;
		}

		template <typename U>
		Array &operator=(const Array<U, D> &arr) {
			// std::cout << "templated assignment op" << std::endl;
			std::copy(std::begin(arr.data_arr), std::end(arr.data_arr),std::begin(data_arr));
			total_size = arr.total_size;
		}

		
		T& operator[](int index) {

			if(index < 0 ) {
				// std::cout << "Low Out of range" << "\n";
				OutOfRange obj;
				throw obj;
			}
			if(index >= D) {
				// std::cout << "High Out of range" << "\n";
				OutOfRange obj;
				throw obj;
			}
			return data_arr[index];
		}

		const T& operator[](int index) const {
			if(index < 0 ) {
				// std::cout << "Low Out of range" << "\n";
				OutOfRange obj;
				throw obj;
			}
			if(index >= D) {
				// std::cout << "High Out of range" << "\n";
				OutOfRange obj;
				throw obj;
			}
			return data_arr[index];
		}

		class FirstDimensionMajorIterator {
		public:
			T* data_val;

			FirstDimensionMajorIterator() {

			}

			FirstDimensionMajorIterator(const FirstDimensionMajorIterator &fdm_it) {

			}

			FirstDimensionMajorIterator &operator=(const FirstDimensionMajorIterator &fdm_it) {
				data_val = fdm_it.data_val;
			}

			FirstDimensionMajorIterator &operator++() {
				data_val++;
				return *this;
			}

			FirstDimensionMajorIterator operator++(int) {
				FirstDimensionMajorIterator temp_obj = *this;
				data_val++;
				return temp_obj;
			}

			T &operator*() const {
				return (*data_val);
			}
		};

		class LastDimensionMajorIterator {
		public:
			T* data_val;

			LastDimensionMajorIterator() {

			}

			LastDimensionMajorIterator(const LastDimensionMajorIterator &ldm_it) {

			}

			LastDimensionMajorIterator &operator=(const LastDimensionMajorIterator &ldm_it) {
				data_val = ldm_it.data_val;
			}

			LastDimensionMajorIterator &operator++() {
				data_val++;
				return *this;
			}

			LastDimensionMajorIterator operator++(int) {
				LastDimensionMajorIterator temp_obj = *this;
				data_val++;
				return temp_obj;
			}

			T &operator*() const {
				return (*data_val);
			}

		};
		
		FirstDimensionMajorIterator fmbegin() {
			FirstDimensionMajorIterator obj;
			obj.data_val = data_arr;
			return obj;
		}

		FirstDimensionMajorIterator fmend() {
			FirstDimensionMajorIterator obj;
			obj.data_val = data_arr+total_size ;
			return obj;
		}

		friend bool operator==(const FirstDimensionMajorIterator &fdm_it1, 
				const FirstDimensionMajorIterator &fdm_it2) {
			return (fdm_it1.data_val == fdm_it2.data_val);
		}

		friend bool operator!=(const FirstDimensionMajorIterator &fdm_it1, 
				const FirstDimensionMajorIterator &fdm_it2) {
			return (fdm_it1.data_val != fdm_it2.data_val);
		}

		LastDimensionMajorIterator lmbegin() {
			LastDimensionMajorIterator obj;
			obj.data_val = data_arr;
			return	obj;
		}

		LastDimensionMajorIterator lmend() {
			LastDimensionMajorIterator obj;
			obj.data_val = data_arr + total_size;
			return obj;
		}

		friend bool operator==(const LastDimensionMajorIterator &ldm_it1,
                const LastDimensionMajorIterator &ldm_it2) {
			return (ldm_it1.data_val == ldm_it2.data_val);
		}

		friend bool operator!=(const LastDimensionMajorIterator &ldm_it1,
                const LastDimensionMajorIterator &ldm_it2) {
			return (ldm_it1.data_val != ldm_it2.data_val);
		}

	};


}