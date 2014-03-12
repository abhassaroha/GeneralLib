#ifndef GENERALLIB_HEAP_H
#define GENERALLIB_HEAP_H

#include <functional>
#include <vector>

template <typename T, typename default_op = std::greater<T>>
class Heap {
	public:
		Heap(long size) : _size(size) {};
		Heap(T *arr, long size) : _size(size) {
			build_heap(arr);
		};
		T front();
		T get();
		void add(T elem);
		void remove(T elem);
		inline long size() { return _size; };
#ifdef DEBUG
		void print_data();
#endif
		~Heap() = default;
	private:
		void build_heap(T *arr);
		void bubble_down(long i);
		void bubble_up(long i);
		inline long left_elem(long i) { return 2 * i + 1; };
		inline long right_elem(long i) { return 2 * i + 2; };
		inline long parent_elem(long i) { return (i - 1)/2; }
		long _size;
		std::vector<T> _data;
};
#endif
