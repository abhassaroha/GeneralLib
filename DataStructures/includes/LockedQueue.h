#ifndef GENERALLIB_LOCKEDQUEUE_H
#define GENERALLIB_LOCKEDQUEUE_H

#include <vector>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <atomic>

template <typename T>
class LockedQueue {
	public:
		LockedQueue(int capacity) : _capacity(capacity) {
			_data.reserve(_capacity);
			_count = 0;
		}
		~LockedQueue() { if(_data.size()) _data.erase(_data.begin(), _data.end()); }
		void put(T elem);
		T get();
		int size();
#ifdef DEBUG
		void try_lock();
#endif
	private:
		std::mutex _m;
		std::vector<T> _data;
		std::condition_variable _full;
		std::condition_variable _empty;
		std::atomic_int _count;
		int _capacity;
};


#endif
