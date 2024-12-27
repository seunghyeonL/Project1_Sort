#ifndef ITERATOR_SORTS_H_
#define ITERATOR_SORTS_H_

#include <algorithm>
#include <iterator>

using namespace std;

// version for random iterator
template <typename RandomIt, typename Compare>
void bubbleSortIt(RandomIt begin, RandomIt end, Compare compare) {
    for (auto i = end - 1; i > begin; --i) {
        for (auto j = begin; j < i; j++) {
            if (!compare(*j, *(j + 1))) {
                iter_swap(j, j + 1);
            }
        }
    }
}

// version for random iterator
template <typename RandomIt, typename Compare>
void insertionSortIt(RandomIt begin, RandomIt end, Compare compare) {
    for (auto i = begin + 1; i != end; i++) {
        auto target = *i;
        auto j = i - 1;

        while (j >= begin && compare(target, *j)) {
            *(j + 1) = *j;
            j--;
        }

        *(j + 1) = target;
    }
}

// version to use tmp array
template <typename RandomIt, typename Compare>
void quickSortItProto(RandomIt begin, RandomIt end, Compare compare) {
    if (begin >= end) {
        return;
    }
    auto pivot = *begin;
    int size = distance(begin, end);

    auto* tmp = new int[size];
    RandomIt lTmpIt = tmp, rTmpIt = tmp + size;

    for (auto i = begin + 1; i != end; i++) {
        if (compare(pivot, *i)) {
            *(--rTmpIt) = *i;
        }
        else {
            *(lTmpIt++) = *i;
        }
    }

    RandomIt pivotIt = begin + distance(tmp, lTmpIt);
    *lTmpIt = pivot;

    for (int i = 0; i < size; i++) {
        *(begin + i) = *(tmp + i);
    }

    delete[] tmp;

    quickSortItProto(begin, pivotIt, compare);
    quickSortItProto(pivotIt + 1, end, compare);
}

// version for bidirectional iterator(linked list)  -> not efficient
template <typename BidirectionalIt, typename Compare>
void quickSortItBi(BidirectionalIt begin, BidirectionalIt end,
    Compare compare) {
    if (begin == end || next(begin) == end) {
        return;
    }

    auto pivot = *begin;
    BidirectionalIt lIt = next(begin), rIt = prev(end);

    while (prev(lIt) != rIt) {
        while (prev(lIt) != rIt && (*lIt == pivot || compare(*lIt, pivot))) {
            lIt++;
        }

        while (prev(lIt) != rIt && (*rIt == pivot || !compare(*rIt, pivot))) {
            rIt--;
        }

        if (lIt != rIt && prev(lIt) != rIt) {
            iter_swap(lIt, rIt);
        }
    }

    BidirectionalIt pivotIt = rIt;
    iter_swap(begin, pivotIt);

    quickSortItBi(begin, pivotIt, compare);
    quickSortItBi(next(pivotIt), end, compare);
}

// version for random iterator
template <typename RandomIt, typename Compare>
void quickSortIt(RandomIt begin, RandomIt end, Compare compare) {
    if (begin >= end) {
        return;
    }

    auto pivot = *begin;
    RandomIt lIt = begin + 1, rIt = end - 1;

    while (lIt <= rIt) {
        while (lIt <= rIt && (*lIt == pivot || compare(*lIt, pivot))) {
            lIt++;
        }
        while (lIt <= rIt && (*rIt == pivot || !compare(*rIt, pivot))) {
            rIt--;
        }

        if (lIt < rIt) {
            iter_swap(lIt, rIt);
        }
    }

    RandomIt pivotIt = rIt;
    iter_swap(begin, pivotIt);

    quickSortIt(begin, pivotIt, compare);
    quickSortIt(pivotIt + 1, end, compare);
}

// version for random iterator
template <typename RandomIt, typename Compare>
void merge(RandomIt begin, RandomIt middle, RandomIt end, RandomIt tmp,
    Compare compare) {
    RandomIt lIt = begin, rIt = middle, tIt = tmp;
    int size = distance(begin, end);

    while (lIt < middle && rIt < end) {
        if (compare(*lIt, *rIt)) {
            *(tIt++) = *(lIt++);
        }
        else {
            *(tIt++) = *(rIt++);
        }
    }

    if (lIt == middle) {
        while (rIt < end) {
            *(tIt++) = *(rIt++);
        }
    }
    else {
        while (lIt < middle) {
            *(tIt++) = *(lIt++);
        }
    }

    for (int i = 0; i < size; i++) {
        *(begin + i) = *(tmp + i);
    }
}

// version for random iterator
template <typename RandomIt, typename Compare>
void mergeSortIt(RandomIt begin, RandomIt end, RandomIt tmp, Compare compare) {
    int size = distance(begin, end);

    if (size > 1) {
        auto middle = begin + size / 2;
        mergeSortIt(begin, middle, tmp, compare);
        mergeSortIt(middle, end, tmp, compare);
        merge(begin, middle, end, tmp, compare);
    }
}

// version for bidrectional iterator
template <typename RandomIt, typename BidirectionalIt, typename Compare>
void mergeBi(BidirectionalIt begin, BidirectionalIt middle, BidirectionalIt end,
    RandomIt tmp, Compare compare) {
    BidirectionalIt lIt = begin, rIt = middle;
    RandomIt tIt = tmp;
    int size = distance(begin, end);

    while (lIt != middle && rIt != end) {
        if (compare(*lIt, *rIt)) {
            *(tIt++) = *(lIt++);
        }
        else {
            *(tIt++) = *(rIt++);
        }
    }

    if (lIt == middle) {
        while (rIt != end) {
            *(tIt++) = *(rIt++);
        }
    }
    else {
        while (lIt != middle) {
            *(tIt++) = *(lIt++);
        }
    }

    for (int i = 0; i < size; i++) {
        *(begin++) = *(tmp++);
    }
}

// version for bidirectionanl iterator
template <typename RandomIt, typename BidirectionalIt, typename Compare>
void mergeSortItBi(BidirectionalIt begin, BidirectionalIt end, RandomIt tmp,
    Compare compare) {
    int size = distance(begin, end);

    if (size > 1) {
        auto middle = begin;
        advance(middle, size / 2);
        mergeSortItBi(begin, middle, tmp, compare);
        mergeSortItBi(middle, end, tmp, compare);
        mergeBi(begin, middle, end, tmp, compare);
    }
}

#endif