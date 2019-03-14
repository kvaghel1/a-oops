#include <iostream>

namespace cs540 {
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	class Counter_class {
    public:
    	int ref_count;
    	Counter_class() {
    		ref_count = 0;
    	}

    	void inc_count() {
    		ref_count += 1;
    	}
    	void dec_count() {
    		ref_count += -1;
    	}

    	virtual ~Counter_class() {

    	}
    };
    template<typename T>
    class Counter_derived : public Counter_class {
    public:
    	T* obj;
    	Counter_derived() {
    		obj = nullptr;
    	}
    	Counter_derived(T* temp) {
    		obj = temp;
    	}
    	~Counter_derived() {
    		delete obj;
    		obj = nullptr;
    	}
    };

	template<typename T>
    class SharedPtr {
    public:
    	Counter_class* count_ref;
    	T* data_ref;

    	SharedPtr() {
    		std::cout << "Default Const";
    		data_ref = nullptr;
    		count_ref = nullptr;
    	}

    	template <typename U> 
    	explicit SharedPtr(U *obj) {
    		data_ref = obj;
    		count_ref = new Counter_derived<U>(obj);
    		pthread_mutex_lock(&mutex);
    		count_ref->inc_count();
    		pthread_mutex_unlock(&mutex);
    	}

    	SharedPtr(const SharedPtr &p) {
    		count_ref = p.count_ref;
    		data_ref = p.data_ref;
    		if(count_ref != nullptr) {
    			pthread_mutex_lock(&mutex);
    			count_ref->inc_count();
    			pthread_mutex_unlock(&mutex);
    		}
    	}

    	template <typename U> 
    	SharedPtr(const SharedPtr<U> &p) {
    		data_ref = p.data_ref;
    		count_ref = p.count_ref;
    		if(count_ref != nullptr) {
    			pthread_mutex_lock(&mutex);
    			count_ref->inc_count();
    			pthread_mutex_unlock(&mutex);
    		}
    	}

    	SharedPtr(SharedPtr &&p) {

    	}

		template <typename U> 
		SharedPtr(SharedPtr<U> &&p) {
			data_ref = p.data_ref;
			count_ref = p.count_ref;
		}

		SharedPtr &operator=(const SharedPtr &p) {
			if(p != nullptr) {
				if(count_ref != p.count_ref) {
					int temp_count = 0;
					if(count_ref != nullptr) {
						pthread_mutex_lock(&mutex);
						count_ref->dec_count();
						temp_count = count_ref->ref_count;
						pthread_mutex_unlock(&mutex);

						if(temp_count==0) {
							if(count_ref != nullptr) {
								delete count_ref;
							}
						}
					}
					count_ref = p.count_ref;
					pthread_mutex_lock(&mutex);
					count_ref->inc_count();
					pthread_mutex_unlock(&mutex);
				}
			}
			return *this;
		}
		
		template <typename U>
		SharedPtr<T> &operator=(const SharedPtr<U> &) {

		}

		SharedPtr &operator=(SharedPtr &&p) {
			if(p != nullptr) {
				if(count_ref != p.count_ref) {
					int temp_count = 0;
					if(count_ref != nullptr) {
						pthread_mutex_lock(&mutex);
						count_ref->dec_count();
						temp_count = count_ref->ref_count;
						pthread_mutex_unlock(&mutex);

						if(temp_count == 0) {
							if(count_ref != nullptr) {
								delete count_ref;
							}
						}	
					}
					count_ref = p.count_ref;
					pthread_mutex_lock(&mutex);
					count_ref->inc_count();
					pthread_mutex_unlock(&mutex);
				}

			}
			return *this;
		}
		
		template <typename U> 
		SharedPtr &operator=(SharedPtr<U> &&p) {
			if(p!=nullptr) {
				if(count_ref != p.count_ref) {
					int temp_count = 0;
					if(count_ref != nullptr) {
						pthread_mutex_lock(&mutex);
						count_ref->dec_count();
						temp_count = count_ref->ref_count;	
						pthread_mutex_unlock(&mutex);

						if(temp_count == 0) {
							if(count_ref != nullptr) {
								delete count_ref;
							}
						}
					}
					count_ref = p.count_ref;
					pthread_mutex_lock(&mutex);
					count_ref->inc_count();
					pthread_mutex_unlock(&mutex);
				}
			}
			p=nullptr;
        	return *this;
		}

		~SharedPtr() {

		}

		void reset() {
			if(count_ref != nullptr) {
				int temp_count = 0;
				pthread_mutex_lock(&mutex);
				count_ref->dec_count();
				temp_count = count_ref->ref_count;
				pthread_mutex_unlock(&mutex);
				if(temp_count <= 0 ) {
					delete count_ref;
				}
				count_ref = nullptr;
				data_ref = nullptr;
			}
		}

		template <typename U> 
		void reset(U *p) {
			if(count_ref != nullptr) {
				int temp_count = 0;
				pthread_mutex_lock(&mutex);
				count_ref->dec_count();
				temp_count = count_ref->ref_count;
				pthread_mutex_unlock(&mutex);

				if(temp_count <=0 ) {
					delete count_ref;
				}
				count_ref = nullptr;
			}
			count_ref = new Counter_derived<U>(p);
			data_ref = p;
			pthread_mutex_lock(&mutex);
			count_ref->inc_count();
			pthread_mutex_unlock(&mutex);
		}

		T* get() const {
			return data_ref;
		}

		T& operator*() const {
			return *data_ref;
		}

		T* operator->() const {
			return data_ref;
		}

		explicit operator bool() const {
			if(data_ref == nullptr) {
				return false;
			}
			return true;
		}

    };

    template <typename T1, typename T2>
	bool operator==(const SharedPtr<T1> &sp1, const SharedPtr<T2> &sp2) {
		if(sp1 == nullptr && sp2 == nullptr){
	        return true;
	    }
	    if(sp1==nullptr && sp2!=nullptr){
	        return false;
	    }
	    if(sp2==nullptr && sp1!=nullptr){
	        return false;
	    }
	    if(sp1.data_ref!=nullptr & sp2.data_ref==nullptr ){
	        return false;
	    }
	    if(sp1.data_ref==sp2.data_ref){
	        return true;
	    }
	    return false;
	}

	template <typename T>
	bool operator==(const SharedPtr<T> &sp, std::nullptr_t np) {
		return (sp.data_ref == np);
	}
	
	template <typename T>
	bool operator==(std::nullptr_t np , const SharedPtr<T> &sp) {
		return (np == sp);
	}

	template <typename T1, typename T2>
	bool operator!=(const SharedPtr<T1>&sp1, const SharedPtr<T2> &sp2) {
		return !(sp1 == sp2);
	}

	template <typename T>
	bool operator!=(const SharedPtr<T> &sp, std::nullptr_t np) {
		return !(sp == np);
	}
	
	template <typename T>
	bool operator!=(std::nullptr_t np , const SharedPtr<T> &sp) {
		return !(np == sp);
	}

	template <typename TT, typename U>
	SharedPtr<TT> static_pointer_cast(const SharedPtr<U> &sp) {
		SharedPtr<TT> temp_sp;
		temp_sp.data_ref = static_cast<TT*>(sp.data_ref);
		temp_sp.count_ref = sp.count_ref;
		pthread_mutex_lock(&mutex);
		temp_sp.count_ref-> inc_count();
		pthread_mutex_unlock(&mutex);
		return temp_sp;
	}

	template <typename TT, typename U>
	SharedPtr<TT> dynamic_pointer_cast(const SharedPtr<U> &sp) {
		SharedPtr<TT> temp_sp;
		temp_sp.data_ref = dynamic_cast<TT*>(sp.data_ref);
		temp_sp.count_ref = sp.count_ref;
		pthread_mutex_lock(&mutex);
		temp_sp.count_ref-> inc_count();
		pthread_mutex_unlock(&mutex);
		return temp_sp;	
	}

}