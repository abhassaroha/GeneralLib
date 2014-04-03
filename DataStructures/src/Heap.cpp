#include "Heap.h"

template <typename T, typename default_op>
T Heap<T, default_op>::front()
{
	return _data.front();
}

template <typename T, typename default_op>
T Heap<T, default_op>::get()
{
	if (_size > 1)
		std::swap(_data[0], _data[_size - 1]);
	T result = _data.back();
	_data.pop_back();
	_size--;
	bubble_down(0);
	return result;
}

template <typename T, typename default_op>
void Heap<T, default_op>::add(T elem)
{
	_data.push_back(elem);
	bubble_up(_size++);
}

template <typename T, typename default_op>
void Heap<T, default_op>::remove(T elem)
{
	long index = -1;
	for (long i = 0; i < _size; i++) {
		if (_data[i] == elem) { 
			index = i;
			break;
		}
	}
	if (index != -1) {
		std::swap(_data[index], _data[_size - 1]);
		bool up = _comp_op(_data[index], _data[_size - 1]);
		_data.pop_back();
		_size--;
		if (up)
			bubble_up(index);
		else
			bubble_down(index);
	}
}

template <typename T, typename default_op>
void Heap<T, default_op>::build_heap(T *arr)
{
	_data.reserve(_size);
	for (long i = 0; i < _size; i++)
		_data.push_back(arr[i]);

	for (long i = _size - 1; i >= 0; i--)
		bubble_down(i);
}

template <typename T, typename default_op>
void Heap<T, default_op>::bubble_down(long i)
{
	while (i < _size) {
		long largest = i;
		long left = left_elem(i);
		long right = right_elem(i);
		if (left < _size && _comp_op(_data[left], _data[largest]))
			largest = left; 
		if (right < _size &&
				_comp_op(_data[right], _data[largest]))
			largest = right;
		if (largest != i) { 
			std::swap(_data[i], _data[largest]);
			i = largest;
		}
		else break;
	}
}

template <typename T, typename default_op>
void Heap<T, default_op>::bubble_up(long i)
{
	while (i > 0) {
		int parent = parent_elem(i);
		if (_comp_op(_data[i], _data[parent])) { 
			std::swap(_data[i], _data[parent]);
			i = parent; 
		}
		else break;
	}
}

#ifdef DEBUG

#include <iostream>
#include <cstdlib>

template <typename T, typename default_op>
void Heap<T, default_op>::print_data()
{
	using std::cout;
	for (int i = 0; i < _size; i++) {
		cout<<_data[i]<<" ";
		int left = left_elem(i);
		int right = right_elem(i);
		if ((left < _size && _comp_op(_data[left], _data[i])) ||
			(right <_size && _comp_op(_data[right], _data[i]))) {
			cout<<"Invariant violated"<<std::endl;
			exit(EXIT_FAILURE);
		}
 
	}
	cout<<std::endl;
}

#endif

/** Test Client */
#define NUM_ELEMS 7
int main()
{
	int data[NUM_ELEMS] = {7, 4, 6, 1, 2, 3, 5};
	Heap<int> inst(data, NUM_ELEMS);
	std::cout<<"Size "<<inst.size()<<std::endl;
	inst.remove(1);
	std::cout<<"Size after remove "<<inst.size()<<std::endl;
	inst.add(8);
	std::cout<<"Size after add "<<inst.size()<<std::endl;
	std::cout<<"Front "<<inst.front()<<std::endl;
	std::cout<<"Size after front "<<inst.size()<<std::endl;
	std::cout<<"Get "<<inst.get()<<std::endl;
	std::cout<<"Size after get "<<inst.size()<<std::endl;
#ifdef DEBUG
	inst.print_data();
#endif
	return 0;
}
