#ifndef Deque_DEFINE_H
#define Deque_DEFINE(t)\
struct Deque_##t##_Iterator;							\
struct Deque_##t {										\
		int front_ind;									\
		int back_ind;									\
		t* arr;											\
		size_t curr_size;								\
		size_t total_size;								\
		char type_name[sizeof("Deque_"#t)];				\
		bool (*is_less) (const t&, const t&);			\
		void (*push_back) (Deque_##t*, t);				\
		void (*push_front) (Deque_##t*, t);				\
		void (*pop_back) (Deque_##t*);					\
		void (*pop_front) (Deque_##t*);					\
		t& (*at) (Deque_##t*, size_t);					\
		void (*clear) (Deque_##t*);						\
		void (*dtor) (Deque_##t*);						\
		void (*sort) (Deque_##t*, Deque_##t##_Iterator, Deque_##t##_Iterator );	\
		Deque_##t##_Iterator (*begin) (Deque_##t*);		\
		Deque_##t##_Iterator (*end) (Deque_##t*);		\
		size_t (*size) (Deque_##t* );					\
		bool (*empty) (Deque_##t* );					\
		t& (*front) (Deque_##t* );						\
		t& (*back) (Deque_##t* );						\
};														\
struct Deque_##t##_Iterator {							\
	int ind;											\
	size_t curr_size;									\
	t* val;												\
	t& (*deref) (Deque_##t##_Iterator*);				\
	void (*inc) (Deque_##t##_Iterator*);				\
	void (*dec) (Deque_##t##_Iterator*);				\
	bool (*is_less_it) (const t&, const t&);			\
	int (*sort_comp) (const void*, const void*);		\
};														\
bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator it1, \
	Deque_##t##_Iterator it2) {							\
	if( it1.ind == it2.ind) {							\
		return true;									\
	}													\
	return false;										\
}														\
t& deref_fn(Deque_##t##_Iterator* it) {					\
		return *(it->val);								\
}														\
void inc_fn(Deque_##t##_Iterator* it) {					\
		it->ind++;										\
		it->val++;										\
}														\
void dec_fn(Deque_##t##_Iterator* it) {					\
		it->ind--;										\
		it->val--;										\
}														\
size_t size_fn(Deque_##t* deq) {						\
	return deq->total_size;								\
}														\
bool empty_fn(Deque_##t* deq) {							\
	if(deq->total_size == 0) {							\
		return true;									\
	}													\
	return false;										\
}														\
void push_back_fn( Deque_##t* deq, t val) { 			\
	if(deq->front_ind==-1) {							\
		deq->front_ind = 0;						\
		deq->back_ind = 0;						\
		deq->arr[deq->back_ind] = val;			\
		deq->total_size++;						\
	}											\
	else {										\
		if( deq->curr_size > deq->total_size ) {	\
			deq->back_ind = (deq->back_ind+1)%(deq->curr_size);	\
			deq->arr[deq->back_ind] = val;					\
			deq->total_size++;								\
		}													\
		else {												\
			deq->curr_size = 2 * deq->total_size;			\
			t* temp_arr = (t*) malloc(deq->curr_size * sizeof(t));			\
			memcpy(temp_arr, deq->arr, deq->total_size * sizeof(t) );	\
			free(deq->arr);									\
			deq->arr = (t*)malloc(deq->curr_size * sizeof(t));			\
			memcpy(deq->arr, temp_arr, deq->curr_size * sizeof(t));		\
			deq->back_ind = (deq->back_ind+1)%(deq->curr_size);	\
			deq->arr[deq->back_ind] = val;					\
			deq->total_size++;								\
			free(temp_arr);									\
		}													\
	}													\
}														\
void push_front_fn( Deque_##t* deq, t val) {			\
	if(deq->front_ind==-1) {							\
		deq->front_ind = 0;						\
		deq->back_ind = 0;						\
		deq->arr[deq->back_ind] = val;			\
		deq->total_size++;						\
	}											\
	else {										\
		if(deq->curr_size > deq->total_size) {		\
			deq->front_ind = (deq->front_ind-1)%(deq->curr_size);	\
			deq->arr[deq->front_ind] = val;						\
			deq->total_size++;								\
		}													\
		else {												\
			t* temp_arr = (t*)malloc(2*deq->curr_size*sizeof(t));		\
			int i = deq->front_ind;							\
			int i_temp = i;									\
			while(i!=deq->back_ind) {						\
				temp_arr[i_temp] = deq->arr[i];				\
				i = (i+1) % deq->curr_size;					\
				i_temp++;									\
			}												\
			temp_arr[i_temp] = deq->arr[i];					\
			deq->back_ind = i_temp;							\
			deq->curr_size = 2*deq->curr_size;				\
			deq->front_ind = (deq->front_ind-1)%(deq->curr_size);	\
			temp_arr[deq->front_ind] = val;					\
			free(deq->arr);									\
			deq->arr = (t*)malloc(deq->curr_size * sizeof(t));		\
			memcpy(deq->arr, temp_arr, deq->curr_size* sizeof(t));	\
			deq->total_size++;								\
			free(temp_arr);									\
		}													\
	}													\
}														\
t& front_fn(Deque_##t* deq) {							\
	return deq->arr[deq->front_ind];					\
}														\
t& back_fn(Deque_##t* deq) {							\
	return deq->arr[deq->back_ind];						\
}														\
t& at_fn(Deque_##t* deq, size_t index) {				\
	int temp;											\
	temp = (deq->front_ind+index)%deq->curr_size;		\
	return deq->arr[temp];								\
}														\
void clear_fn(Deque_##t* deq) {							\
	t* temp_arr = (t*)malloc(deq->curr_size * sizeof(t));			\
	free(deq->arr);										\
	deq->arr = (t*)malloc(deq->curr_size * sizeof(t));				\
	memcpy(deq->arr, temp_arr, deq->curr_size);			\
	free(temp_arr);										\
}														\
void dtor_fn(Deque_##t* deq) {							\
	clear_fn(deq);										\
	free(deq->arr);										\
}														\
void pop_back_fn(Deque_##t* deq ) {						\
	if(deq->back_ind!= -1) {							\
		if(deq->back_ind == deq->front_ind) {			\
			deq->back_ind = -1;							\
			deq->front_ind = -1;						\
		}												\
		else {											\
			deq->back_ind = (deq->back_ind-1)%(deq->curr_size);	\
		}												\
	deq->total_size--;									\
	}													\
	else {												\
		printf("DEQ Empty --> Invalid Pop back !!\n");	\
	}													\
}														\
void pop_front_fn(Deque_##t* deq ) {					\
	if(deq->front_ind != -1) {							\
		if(deq->front_ind == deq->back_ind) {			\
			deq->back_ind = -1;							\
			deq->front_ind = -1;						\
		}												\
		else {											\
			deq->front_ind = (deq->front_ind+1)%(deq->curr_size);	\
		}												\
	deq->total_size--;									\
	}													\
	else {												\
		printf("DEQ Empty --> Invalid Pop front !!\n");	\
	}													\
}														\
bool Deque_##t##_equal(Deque_##t deq1, Deque_##t deq2) {	\
	auto deq_it1 = deq1.begin(&deq1);						\
	auto deq_it2 = deq2.begin(&deq2);						\
	if(deq1.size(&deq1) == deq2.size(&deq2)) {									\
		while(!Deque_##t##_Iterator_equal(deq_it1, deq1.end(&deq1))) {			\
			if( deq1.is_less( *(deq_it1.val), *(deq_it2.val)) ) {				\
				return false;													\
			}																	\
			else if ( deq1.is_less( *(deq_it2.val), *(deq_it1.val)) ) {			\
				return false;													\
			}																	\
			deq_it1.inc(&deq_it1);						\
			deq_it2.inc(&deq_it2);						\
		}												\
		return true;									\
	}													\
	return false;										\
}														\
void sort_fn(Deque_##t* deq, Deque_##t##_Iterator dq_beg, Deque_##t##_Iterator dq_end ) {	\
	int nitems = 0; 								\
	nitems = dq_end.ind - dq_beg.ind;				\
	auto it = dq_beg;			\
	int i=0;					\
	Deque_##t##_Iterator* it_arr = (Deque_##t##_Iterator*)malloc(nitems * sizeof(it));	\
	for(it = dq_beg;			\
	!Deque_##t##_Iterator_equal(it, dq_end);	\
	it.inc(&it)) {				\
		it_arr[i] = it;			\
		i++;					\
	}							\
	qsort(it_arr, nitems, sizeof(Deque_##t##_Iterator), dq_beg.sort_comp);	\
	t* ip_arr = (t*) malloc( nitems*sizeof(t));						\
	for(int i=0; i < nitems; i++) {									\
		ip_arr[i] = *(it_arr[i].val);								\
	}																\
	memcpy(deq->arr+dq_beg.ind, ip_arr, nitems*sizeof(t));			\
	free(it_arr);	\
	free(ip_arr);	\
}													\
int sort_##t##_comp_fn(const void* p1, const void* p2) {					\
	Deque_##t##_Iterator* it1 = ((Deque_##t##_Iterator *) p1);		\
	Deque_##t##_Iterator* it2 = ((Deque_##t##_Iterator *) p2);		\
	if(it1->is_less_it(it1->deref(it1), it2->deref(it2))) {			\
		return -1;													\
	}																\
	else if(it2->is_less_it(it2->deref(it2), it1->deref(it1))) {	\
		return 1;													\
	}																\
	return 0;														\
}																	\
Deque_##t##_Iterator begin_fn(Deque_##t* deq) {			\
		Deque_##t##_Iterator temp_it;					\
		temp_it.ind = deq->front_ind;					\
		temp_it.curr_size = deq->curr_size;				\
		temp_it.val = &(deq->arr[deq->front_ind]);		\
		temp_it.deref = deref_fn;						\
		temp_it.inc = inc_fn;							\
		temp_it.dec = dec_fn;							\
		temp_it.is_less_it = deq->is_less;				\
		temp_it.sort_comp = sort_##t##_comp_fn;			\
		return temp_it;									\
}														\
Deque_##t##_Iterator end_fn(Deque_##t* deq) {			\
		Deque_##t##_Iterator temp_it;					\
		temp_it.ind = deq->back_ind +1;					\
		temp_it.curr_size = deq->curr_size;				\
		temp_it.val = &deq->arr[deq->back_ind]+1;		\
		temp_it.deref = deref_fn;						\
		temp_it.inc = inc_fn;							\
		temp_it.dec = dec_fn;							\
		temp_it.is_less_it = deq->is_less;				\
		temp_it.sort_comp = sort_##t##_comp_fn;				\
		return temp_it;									\
}														\
void Deque_##t##_ctor( Deque_##t* deq, bool (*b)(const t& o1, const t& o2)) {		\
	strcpy(deq->type_name, "Deque_"#t);					\
	deq->arr = (t*)malloc(2*sizeof(t));					\
	deq->front_ind = -1;								\
	deq->back_ind = -1;								\
	deq->total_size = 0;								\
	deq->size = size_fn;								\
	deq->empty = empty_fn;								\
	deq->push_back = push_back_fn;						\
	deq->push_front = push_front_fn;					\
	deq->front = front_fn;								\
	deq->back = back_fn;								\
	deq->pop_back = pop_back_fn;						\
	deq->pop_front = pop_front_fn;						\
	deq->begin = begin_fn;								\
	deq->end = end_fn;									\
	deq->at = at_fn;									\
	deq->clear = clear_fn;								\
	deq->dtor = dtor_fn;								\
	deq->is_less = b;									\
	deq->curr_size = 2;									\
	deq->sort = sort_fn;								\
}
#endif