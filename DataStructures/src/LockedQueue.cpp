/**
 * A bounded thread safe queue.
 * Uses locks and conditionals for synchronization.
 */
#include "LockedQueue.h"

#include <thread>
#include <iostream>
#include <atomic>
#include <cstdint>
#include <sys/time.h>

template <typename T>
void LockedQueue<T>::put(T elem)
{
	std::unique_lock<std::mutex> lock(_m);
	_cv.wait(lock, [=] { return _data.size() < _capacity; });
	_data.push_back(elem);
#ifdef DEBUG
	std::cout<<"Put into queue "<<elem<<std::endl;
#endif
	lock.unlock();
	// TODO: investigate using notify_one and still avoiding deadlock
	_cv.notify_all();
}

template <typename T>
T LockedQueue<T>::get()
{
	// TODO: try using different locks for put and get
	std::unique_lock<std::mutex> lock(_m);
	_cv.wait(lock, [=] { return _data.size() > 0; });
	T result = *_data.begin();
#ifdef DEBUG
	std::cout<<"Get from queue "<<result<<std::endl;
#endif
	_data.erase(_data.begin());
	lock.unlock();
	_cv.notify_all();
	// TODO: investigate using notify_one and still avoiding deadlock
	return result;
}

template <typename T>
int LockedQueue<T>::size()
{
	return _data.size();
}

#ifdef DEBUG
template <typename T>
void LockedQueue<T>::try_lock()
{
	if(_m.try_lock()) {
		std::cout<<"Got lock!"<<std::endl;
	}
	else {
		std::cout<<"Failed to get lock!"<<std::endl;
	}
}
#endif


/** Test Client */

#define NUM_THREADS 10
#define NUM_OBJECTS 1000

static LockedQueue<int> queue(10);
static std::atomic_int produced;
static std::atomic_int consumed;
static int produced_count[NUM_OBJECTS] = {0};
static int consumed_count[NUM_OBJECTS] = {0}; 

void produce()
{
	// produced cannot be used directly as index as its shared across
	// threads and access needs to be synchronized.
	// Atomicity at line 67 guarantees num will be unique for 
	// each thread.
	while (produced <= NUM_OBJECTS) {
		int num = produced++;
		// safeguard, don't know why its not called.
		if (num <= NUM_OBJECTS) {
			queue.put(num);
			produced_count[num - 1]++;
		}
		else {
			std::cout<<"Ignoring excess payload..."<<std::endl;
		}
	}
#ifdef DEBUG
	size_t hash = std::hash<std::thread::id>() (std::this_thread::get_id());
	std::cout<<"Producer "<<hash<<std::endl;
	std::cout<<"Produced "<<produced<<std::endl;
	std::cout<<"Consumed "<<consumed<<std::endl;
#endif
}

void consume()
{
	int dummy = -1;
	while (consumed < NUM_OBJECTS) {
		int num = queue.get();
		if (consumed < NUM_OBJECTS) {
			consumed++;
			consumed_count[num - 1]++;
		}
		// release all waiting consumer threads...
		if (consumed == NUM_OBJECTS)	
			queue.put(dummy);
	}
#ifdef DEBUG
	size_t hash = std::hash<std::thread::id>() (std::this_thread::get_id());
	std::cout<<"Consumer "<<hash<<std::endl;
	std::cout<<"Produced "<<produced<<std::endl;
	std::cout<<"Consumed "<<consumed<<std::endl;
#endif
}

uint64_t get_small_time()
{
	// start time
	struct timeval tv;
	gettimeofday(&tv, NULL);
	uint64_t result = tv.tv_usec;
	result /= 1000;
	result += tv.tv_sec * 1000;
	return result;
}

void run_once()
{
	std::thread producers[NUM_THREADS];
	std::thread consumers[NUM_THREADS];

	produced = 1;
	for (int i = 0; i < NUM_THREADS; i++) {
		consumers[i] = std::thread(consume);
	}
	for (int i = 0; i < NUM_THREADS; i++) {
		producers[i] = std::thread(produce);
	}


	for (int i = 0; i < NUM_THREADS; i++) {
		producers[i].join();
		consumers[i].join();
	}

#ifdef DEBUG
	std::cout<<"Last Produced "<<(produced - 1)<<std::endl;
#endif
	for (int i = 0; i < NUM_OBJECTS; i++) {
		// validation check that each item 
		// produced and consumed is unique
		if(produced_count[i] != 1)
			std::cout<<"Produced item "<<(i + 1)<<" "
				<<produced_count[i]<<" times"<<std::endl;
		if (consumed_count[i] != 1)
			std::cout<<"Consumed item "<<(i + 1)<<" "
				<<consumed_count[i]<<" times"<<std::endl;
	}
}

int main(int argc, char** argv)
{
#define ITERATIONS 1
	uint64_t start_time = get_small_time();
	for (int i = 0; i < ITERATIONS; i++) {
		run_once();
#ifdef DEBUG
		queue.try_lock();
#endif
	}
	uint64_t end_time = get_small_time();
	std::cout<<"Elapsed Time: "<<(end_time - start_time)<<std::endl;


	return 0;
}
