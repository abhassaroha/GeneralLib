#ifndef GENERALLIB_LOCKEDQUEUE_H
#define GENERALLIB_LOCKEDQUEUE_H

#include <vector>
#include <mutex>
#include <vector>
#include <condition_variable>

template <typename T>
class LockedQueue {
	public:
		LockedQueue(int capacity) : _capacity(capacity) {
			_data.reserve(_capacity);
		}
		~LockedQueue() { _data.erase(_data.begin(), _data.end()); }
		void put(T elem);
		T get();
		int size();
	private:
		std::mutex _m;
		std::vector<T> _data;
		std::condition_variable _cv;
		int _capacity;
};


#endif