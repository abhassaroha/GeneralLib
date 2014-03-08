/**
 * A bounded thread safe queue.
 * Uses locks and conditionals for synchronization.
 */
#include "LockedQueue.h"

#include <thread>
#include <iostream>
#include <atomic>

template <typename T>
void LockedQueue<T>::put(T elem)
{
	std::unique_lock<std::mutex> lock(_m);
	_cv.wait(lock, [=] { return _data.size() < _capacity; });
	_data.push_back(elem);
	// std::cout<<"Put into queue "<<elem<<std::endl;
	lock.unlock();
	// TODO: investigate using notify_one and still avoiding deadlock
	_cv.notify_all();
}

template <typename T>
T LockedQueue<T>::get()
{
	std::unique_lock<std::mutex> lock(_m);
	_cv.wait(lock, [=] { return _data.size() > 0; });
	T result = *_data.begin();
	// std::cout<<"Get from queue "<<result<<std::endl;
	_data.erase(_data.begin());
	lock.unlock();
	// TODO: investigate using notify_one and still avoiding deadlock
	_cv.notify_all();
	return result;
}

template <typename T>
int LockedQueue<T>::size()
{
	return _data.size();
}


/** Test Client */

static LockedQueue<int> queue(10);
static std::atomic_int produced;
static std::atomic_int consumed;
static int produced_count[100] = {0};
static int consumed_count[100] = {0}; 

void produce()
{
	// produced cannot be used directly as index as its shared across
	// threads and access needs to be synchronized.
	// Atomicity at line 67 guarantees num will be unique for 
	// each thread.
	while (produced <= 100) {
		int num = produced++;
		if (num <= 100) {
			queue.put(num);
			produced_count[num - 1]++;
		}
		else {
			std::cout<<"Ignoring excess payload..."<<std::endl;
		}
	}
//	size_t hash = std::hash<std::thread::id>() (std::this_thread::get_id());
//	std::cout<<"Producer "<<hash<<std::endl;
//	std::cout<<"Produced "<<produced<<std::endl;
//	std::cout<<"Consumed "<<consumed<<std::endl;
}

void consume()
{
	int dummy = -1;
	while (consumed < 100) {
		int num = queue.get();
		if (consumed < 100) {
			consumed++;
			consumed_count[num - 1]++;
		}
		// release all waiting consumer threads...
		if (consumed == 100)	
			queue.put(dummy);
	}
//	size_t hash = std::hash<std::thread::id>() (std::this_thread::get_id());
//	std::cout<<"Consumer "<<hash<<std::endl;
//	std::cout<<"Produced "<<produced<<std::endl;
//	std::cout<<"Consumed "<<consumed<<std::endl;
}

int main(int argc, char** argv)
{
	std::thread producers[10];
	std::thread consumers[10];
	produced = 1;
	for (int i = 0; i < 10; i++) {
		consumers[i] = std::thread(consume);
	}
	for (int i = 0; i < 10; i++) {
		producers[i] = std::thread(produce);
	}


	for (int i = 0; i < 10; i++) {
		producers[i].join();
		consumers[i].join();
	}

	std::cout<<"Last Produced "<<(produced - 1)<<std::endl;

	for (int i = 0; i < 100; i++) {
		// validation check that each item 
		// produced and consumed is unique
		if(produced_count[i] != 1)
			std::cout<<"Produced item "<<(i + 1)<<" "
				<<produced_count[i]<<" times"<<std::endl;
		if (consumed_count[i] != 1)
			std::cout<<"Consumed item "<<(i + 1)<<" "
				<<consumed_count[i]<<" times"<<std::endl;
	}

	return 0;
}
