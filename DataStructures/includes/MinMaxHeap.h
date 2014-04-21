#ifndef GENERALLIB_MIN_MAX_HEAP_H
#define GENERALLIB_MIN_MAX_HEAP_H
template <typename T>
class MinMaxHeap {
    public:
        MinMaxHeap() {};
        MinMaxHeap(int num) { _data.reserve(num); };
        MinMaxHeap(T* data, int num);
        T delete_min();
        T delete_max();
        T get_min();
        T get_max();
        T add(T elem);
        T remove(T elem);
    private:
        void heapify(T* data);
        int get_next_min();
        int left(int index) { return 2*index + 1; };
        int right(int index) { return 2*index + 2; };
        int parent(index) { return (index - 1)/2; };
        void fix_down_min();
        std::vector<T> _data;
};
#endif
