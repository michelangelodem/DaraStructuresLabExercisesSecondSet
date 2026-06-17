#ifndef SEARCH_H
#define SEARCH_H

#include <cmath>
#include "../Executor.h"

inline int interpolatePosition(int left, int right, long long target, long long leftVal, long long rightVal) {
    int size = right - left + 1;
    int pos = left + (int)((double)size * (target - leftVal) / (rightVal - leftVal));
    if (pos < left) pos = left;
    if (pos > right) pos = right;
    return pos;
}

inline int clampIndex(int idx, int minIdx, int maxIdx) {
    if (idx < minIdx) return minIdx;
    if (idx > maxIdx) return maxIdx;
    return idx;
}

inline int calculateSqrtN(int n) {
    try {
        return static_cast<int>(std::sqrt(static_cast<double>(n)));
    } catch (const std::exception& e) {
        std::cerr << "Error calculating sqrt(n): " << e.what() << std::endl;
        return 1; 
    }
}

Record binarySearch(const vector<Record>& recs, long long target, Sorter::key_extractor ext) {
    cout << "Executing binary search" << endl;
    int low = 0;
    int high = recs.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        long long midKey = ext(recs[mid]);
        if (midKey == target) {
            return recs[mid];
        } else if (midKey < target) {
            low = mid + 1; 
        } else {
            high = mid - 1; 
        }
    }
    return Record(); 
}

Record interoplationSearch(const vector<Record>& recs, long long target, Sorter::key_extractor ext) {
    cout << "Executing interpolation search" << endl;
    int low = 0;
    int high = recs.size() - 1;

    while (low <= high && target >= ext(recs[low]) && target <= ext(recs[high])) {
        if (low == high) {
            return (ext(recs[low]) == target) ? recs[low] : Record();
        }

        int pos = interpolatePosition(low, high, target, ext(recs[low]), ext(recs[high]));
        
        if (ext(recs[pos]) == target)
            return recs[pos];
        else if (ext(recs[pos]) < target)
            low = pos + 1;
        else
            high = pos - 1;
    }

    return Record();
}

Record binaryInterpolationSearch(const vector<Record>& recs, long long target, Sorter::key_extractor ext) {
    cout << "Executing binary interpolation search" << endl;
    int left = 0;
    int right = recs.size() - 1;

    while (left <= right && target >= ext(recs[left]) && target <= ext(recs[right])) {
        int next = interpolatePosition(left, right, target, ext(recs[left]), ext(recs[right]));

        if (ext(recs[next]) == target) {
            return recs[next];
        }

        int size = right - left + 1;
        int step = (int)std::sqrt((double)size);

        if (ext(recs[next]) <= target) {
            while (next + step < right && target > ext(recs[next + step])) {
                next += step;
            }
            right = clampIndex(next + step, 0, (int)recs.size() - 1);
            left = next + 1;
        } else {
            while (next - step > left && target < ext(recs[next - step])) {
                next -= step;
            }
            right = next - 1;
            left = clampIndex(next - step, 0, next);
        }
    }

    return Record();
}

inline pair<int, int> findExponentialBounds(const vector<Record>& recs, int next, long long target, 
                                            Sorter::key_extractor ext, int sqrtN, int n, bool searchRight) {
    int prevPos = next;
    int currPos = next;

    int j = 0;
    while (true) {
        int jump = (1 << j) * sqrtN;
        currPos = searchRight ? next + jump : next - jump;

        if (searchRight && currPos >= n) {
            return {prevPos, n - 1};
        } else if (!searchRight && currPos < 0) {
            return {0, prevPos};
        }

        if ((searchRight && ext(recs[currPos]) >= target) || 
            (!searchRight && ext(recs[currPos]) <= target)) {
            return searchRight ? make_pair(prevPos, currPos) : make_pair(currPos, prevPos);
        }

        prevPos = currPos;
        j++;
    }
}

inline Record binarySearchRange(const vector<Record>& recs, long long target, 
                                Sorter::key_extractor ext, int left, int right) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        long long midKey = ext(recs[mid]);

        if (midKey == target) {
            return recs[mid];
        } else if (midKey < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return Record();
}

Record bisStarSearch(const vector<Record>& recs, long long target, Sorter::key_extractor ext) {
    cout << "Executing binary interpolation star search" << endl;
    int n = recs.size();
    int left = 0;
    int right = n - 1;

    if (target < ext(recs[left]) || target > ext(recs[right])) {
        return Record();
    }

    int next = interpolatePosition(left, right, target, ext(recs[left]), ext(recs[right]));

    if (ext(recs[next]) == target) {
        return recs[next];
    }

    int sqrtN = calculateSqrtN(n);
    auto [bisLeft, bisRight] = (ext(recs[next]) < target) ? 
        findExponentialBounds(recs, next, target, ext, sqrtN, n, true) :
        findExponentialBounds(recs, next, target, ext, sqrtN, n, false);

    return binarySearchRange(recs, target, ext, bisLeft, bisRight);
}

#endif
