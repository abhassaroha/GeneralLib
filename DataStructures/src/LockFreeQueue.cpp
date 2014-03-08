/**
 * A lock free queue.
 */
#include "LockFreeQueue.h"

#include <atomic>
#include <iostream>
#include <thread>

template <typename T, T default_ret>
bool LockFreeQueue<T, default_ret>::put(T elem)
{
	bool result = false;
	if (_divider != _capacity) {
		_data.push_back(elem);
		_divider++;
		result = true;
	}
	return result;
}

template <typename T, T default_ret>
T LockFreeQueue<T, default_ret>::get()
{
	T result = default_ret;
	if (_head != _divider) {
		result = _data.front();
		_data.erase(_data.begin());
		_divider--;
	}
	return result;
}

static LockFreeQueue<int> queue(10);
static std::atomic_int produced;
static std::atomic_int consumed;
static int consumed_count[100] = {0}; 
static int produced_count[100] = {0};

void produce()
{
	int num;
	while (produced <= 100) {
		num = produced++;
		while(!queue.put(num));
		produced_count[num - 1]++;
	}
}

void consume()
{
	while (consumed != 100) {
		int dummy = -1;
		int elem = queue.get();
		if (elem) {
			if (consumed != 100) {
				consumed++;
				consumed_count[elem - 1]++;
			}
			// release all waiting consumer threads...
			if (consumed == 100) {
				while(!queue.put(dummy));
			}
		}
		else {
			std::cout<<"Stall... Waiting for Elems "<<std::endl;
		}
	}
}

int main(int argc, char** argv)
{
	std::thread producer(produce);
	std::thread consumer(consume);
	producer.join();
	consumer.join();

	std::cout<<"Last produced "<<(produced - 1)<<std::endl;
	for (int i = 0; i < 100; i++) {
		if(produced_count[i] != 1)
			std::cout<<"Produced item "<<(i + 1)<<" "
				<<produced_count[i]<<" times"<<std::endl;
		if (consumed_count[i] != 1)
			std::cout<<"Consumed item "<<(i + 1)<<" "
				<<consumed_count[i]<<" times"<<std::endl;
	}
	return 0;
}
