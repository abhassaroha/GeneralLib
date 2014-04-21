#include "MinMaxHeap.h"

T MinMaxHeap::delete_min()
{
    // TODO: Assert size >= 1
    T result;
    result = _data[0];
    if (_data.size() == 1) {
        _data.clear();
    }
    else {
        std::swap(_data[0], _data[_data.size() - 1]);
        _data.pop_back();
    }
    fix_down_min(0);
    return result;
}

T MinMaxHeap::delete_max()
{
    // TODO: Assert size >= 2
    T result;
    int idx;
    if (_data.size() == 2) {
        result = _data[1];
        _data.pop_back();
    }
    else {
        idx = std::max(_data[1], _data[2]) == _data[1] ? 1 : 2;
        result = _data[idx];
        std::swap(_data[idx], _data[_data.size() - 1]);
        _data.pop_back();
        fix_down_max(idx);
    }
}

void MinMaxHeap::fix_down_min(int index)
{
    if ((index + 1) >= _data.size()) return;

    int next_min = get_next_min(index);
    if (next_min != -1) {
        if (std::min(_data[index], _data[next_min]) != _data[index]) {
            std::swap(_data[index], _data[next_min]);
            if (next_min > right(index) &&
                    std::max(_data[next_min], _data[parent(next_min)])
                    == _data[next_min]) {
                std::swap(_data[next_min], _data[parent(next_min)]);
                fix_down_min(next_min);
            }
        }
    }
}

void MinMaxHeap::fix_down_max(int index)
{
    if ((index + 1) >= _data.size()) return;

    int next_max = get_next_max(index);
    if (next_max != -1) {
        if (std::max(_data[index], _data[next_max]) != _data[index]) {
            std::swap(_data[index], _data[next_max]);
            if (next_max > right(index) && 
                    (std::min(_data[next_max], _data[parent(next_max)])
                     == _data[next_max])) {
                std::swap(_data[next_max], _data[parent(next_max)]);
                fix_down_max(next_max);
            }
        }
    }
}

int MinMaxHeap::get_next_min(int index)
{

    int left_ = left(index);
    int right_ = right(index);
    if (_data.size() <= left_) return -1;
    if (_data.size() == right_) return left_;

    int start, idx, result = -1;
    idx = start = left(left_);
    if (_data.size() > idx) {
        result = idx;
        idx++;
        // search only in next min layer
        while (idx < _data.size() && _idx < start + 4) {
            result = std::min(_data[idx], _data[result]) == _data[idx] ? idx : result;
            idx++;
        }
    }

    if (result == -1) {
        result = std::min(_data[left_], _data[right_]) == _data[left_] ? left_ : right_;
    }
    else {
        result = std::min(_data[left_], _data[result]) == _data[left_] ? left_ : result;
        result = std::min(_data[right_], _data[result]) == _data[right_] ? right_ : result;
    }

    return result;
}

int MinMaxHeap::get_next_max(int index)
{
    int left_ = left(index);
    int right_ = right(index);
    if (left_ >= _data.size()) return -1;
    if (right_ == _data.size()) return left_;
 
    int idx, start, result = -1;
    idx = start = left(left_);
    if (idx < _data.size()) {
        result = idx;
        idx++;
        while(idx < _data.size() && idx < start + 4) {
            result = std::max(_data[idx], _data[result]) == _data[idx] ? idx : result;
            idx++;
        }
    }

    if (result == -1) {
        result = std::max(_data[left_] : _data[right_]) == _data[left_] ? left_ : right_; 
    }
    else {
        result = std::max(_data[left_], _data[result]) == _data[left_] ? left_ : result;
        result = std::max(_data[right_], _data[result]) == _data[right_] ? right_ : result;
    }
    return result;
}
