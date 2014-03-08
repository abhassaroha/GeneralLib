#ifndef GENERALLIB_LOCKFREEQUEUE_H
#define GENERALLIB_LOCKFREEQUEUE_H

#include <atomic>
#include <vector>

template <typename T, T default_ret = T()>
class LockFreeQueue {
	public:
		LockFreeQueue(int capacity) : _capacity(capacity) {
			_head = _divider = 0;
			_tail = capacity;
			_data.reserve(capacity);
		};
		~LockFreeQueue() = default;
		bool put(T elem);
		T get();
	private:
		std::atomic_int _head;
		std::atomic_int _divider;
		std::atomic_int _tail;
		std::vector<T> _data;
		int _capacity;
};

#endif
