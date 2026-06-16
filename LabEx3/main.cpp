#include <cmath>
#include <math.h>
#include "../Executor.h"


void printComplexity(const string& name, int steps, int n) {
    double logN    = log2((double)n);
    double logLogN = log2(logN);
    double sqrtN   = sqrt((double)n);
    double logSqrtN = log2(sqrtN);

    cout << " " << name << endl;
    cout << " n            : " << n << endl;
    cout << " Actual steps  : " << steps << endl;

    if (name.find("BIS*") != string::npos) {
        cout << "│ Average Case  : O(log log n) = " << (int)logLogN  << " steps" << endl;
        cout << "│ Worst Case    : O(log √n)    = " << (int)logSqrtN << " steps" << endl;
    } else if (name.find("BIS") != string::npos) {
        cout << "│ Average Case  : O(log log n) = " << (int)logLogN << " steps" << endl;
        cout << "│ Worst Case    : O(√n)        = " << (int)sqrtN   << " steps" << endl;
    } else if (name.find("Interpolation") != string::npos) {
        cout << "│ Average Case  : O(log log n) = " << (int)logLogN << " steps" << endl;
        cout << "│ Worst Case    : O(n)         = " << n            << " steps" << endl;
    } else if (name.find("Binary") != string::npos) {
        cout << "│ Average Case  : O(log n)     = " << (int)logN   << " steps" << endl;
        cout << "│ Worst Case    : O(n)         = " << n           << " steps" << endl;
    }

}

Record binarySearch(const vector<Record>& recs, long long target, Sorter::key_extractor ext) {
    int low = 0;
    int high = recs.size() - 1;
    while (low <= high) {
        int midVal = low + (high - low) / 2;
        long long midKey = ext(recs[midVal]);
        if (midKey == target) {
            return recs[midVal];
        } else if (midKey < target) {
            low = midVal + 1; 
        } else {
            high = midVal - 1; 
        }
    }
    return Record(); 
}

Record interoplationSearch(const vector<Record>& recs, long long target, Sorter::key_extractor ext) {
    int low = 0;
    int high = recs.size() - 1;

    while (low <= high && target >= ext(recs[low]) && target <= ext(recs[high])) {
        
        // Αν low == high, έχουμε 1 στοιχείο
        if (low == high) {
            if (ext(recs[low]) == target)
                return recs[low];
            return Record();
        }

        // Ο τύπος παρεμβολής
        int pos = low + ((double)(target - ext(recs[low])) / 
                         (ext(recs[high]) - ext(recs[low]))) * (high - low);

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
    int left = 0;
    int right = recs.size() - 1;
    int steps = 0;

    while (left <= right && target >= ext(recs[left]) && target <= ext(recs[right])) {
        steps++;
        int size = right - left + 1;

        // Βήμα 2: υπολογισμός αρχικής θέσης next με παρεμβολή
        int next = left + (int)((double)size * (target - ext(recs[left])) / 
                         (ext(recs[right]) - ext(recs[left])));

        // Clamp για ασφάλεια
        if (next < left) next = left;
        if (next > right) next = right;

        if (ext(recs[next]) == target){
             printComplexity("BIS", steps, recs.size());
            return recs[next];
        }
            

        int i = 0;
        size = right - left + 1;
        int step = (int)std::sqrt((double)size);

        if (ext(recs[next]) <= target) {
            // Βήματα 7-10: ψάχνουμε δεξιά
            while (next + i * step < right && 
                   target > ext(recs[next + i * step])) {
                i++;
            }
            right = min(next + i * step, (int)recs.size() - 1);
            left  = next + (i - 1) * step + 1;
            if (left < 0) left = 0;

        } else {
            // Βήματα 12-15: ψάχνουμε αριστερά
            while (next - i * step > left && 
                   target < ext(recs[next - i * step])) {
                i++;
            }
            right = next - (i - 1) * step - 1;
            left  = next - i * step;
            if (left < 0) left = 0;
        }
    }

    // Αν το υπολοιπόμενο εύρος είναι πολύ μικρό (size <= 3), απευθείας αναζήτηση
    for (int k = left; k <= right && k < (int)recs.size(); k++) {
        steps++;
        if (ext(recs[k]) == target) {
            printComplexity("BIS", steps, recs.size());
            return recs[k];
        }
    }

    return Record(); // Δεν βρέθηκε
}

Record bisStarSearch(const vector<Record>& recs, long long target, Sorter::key_extractor ext) {
    int n = recs.size();
    int steps = 0;

    // Παρεμβολή για αρχικό next
    int left = 0;
    int right = n - 1;

    if (target < ext(recs[left]) || target > ext(recs[right])) {
        printComplexity("BIS*", steps, n);
        return Record();
    }

    int next = left + (int)((double)(right - left + 1) * (double)(target - ext(recs[left])) /
                             (double)(ext(recs[right]) - ext(recs[left])));

    if (next < 0) next = 0;
    if (next >= n) next = n - 1;

    steps++;

    if (ext(recs[next]) == target) {
        printComplexity("BIS*", steps, n);
        return recs[next];
    }

    // STEP 1: Εκθετικά άλματα για να βρούμε το διάστημα
    int sqrtN = 1;
    while (sqrtN * sqrtN < n) sqrtN++; // sqrtN ≈ √n

    int bisLeft, bisRight;

    if (ext(recs[next]) < target) {
        // Ψάχνουμε δεξιά: next+√n, next+2√n, next+4√n, ...
        int j = 0;
        int prevPos = next;
        int currPos = next;

        while (true) {
            steps++;
            int jump = (1 << j) * sqrtN; // 2^j * √n
            currPos = next + jump;

            if (currPos >= n) {
                currPos = n - 1;
                bisLeft  = prevPos;
                bisRight = currPos;
                break;
            }

            if (ext(recs[currPos]) >= target) {
                bisLeft  = prevPos;
                bisRight = currPos;
                break;
            }

            prevPos = currPos;
            j++;
        }
    } else {
        // Ψάχνουμε αριστερά: next-√n, next-2√n, next-4√n, ...
        int j = 0;
        int prevPos = next;
        int currPos = next;

        while (true) {
            steps++;
            int jump = (1 << j) * sqrtN; // 2^j * √n
            currPos = next - jump;

            if (currPos < 0) {
                currPos = 0;
                bisLeft  = currPos;
                bisRight = prevPos;
                break;
            }

            if (ext(recs[currPos]) <= target) {
                bisLeft  = currPos;
                bisRight = prevPos;
                break;
            }

            prevPos = currPos;
            j++;
        }
    }

    // STEP 2: Binary Search στο διάστημα [bisLeft, bisRight]
    while (bisLeft <= bisRight) {
        steps++;
        int mid = bisLeft + (bisRight - bisLeft) / 2;

        if (ext(recs[mid]) == target) {
            printComplexity("BIS*", steps, n);
            return recs[mid];
        } else if (ext(recs[mid]) < target) {
            bisLeft = mid + 1;
        } else {
            bisRight = mid - 1;
        }
    }

    printComplexity("BIS* (not found)", steps, n);
    return Record();
}


int main() {
    try {    
        const string csvFilePath = "../effects-of-covid-19-on-trade-at-15-december-2021-provisional.csv";
        auto ms = make_unique<MergeSort>();
        auto cs = make_unique<CountingSort>();
        auto hs = make_unique<HeapSort>();
        auto qs = make_unique<QuickSort>();

        Executor executor(*ms, csvFilePath, [](const Record& r) {return r.getCumulative(); });
        executor.executeSearch(binarySearch);
        executor.executeSearch(interoplationSearch);
        executor.executeSearch(binaryInterpolationSearch);

        executor.setSorter(*cs);
        executor.executeSearch(binarySearch);
        executor.executeSearch(interoplationSearch);
        executor.executeSearch(binaryInterpolationSearch);
        executor.executeSearch(bisStarSearch);

        executor.setSorter(*hs);
        executor.executeSearch(binarySearch);
        executor.executeSearch(interoplationSearch);
        executor.executeSearch(binaryInterpolationSearch);

        executor.setSorter(*qs);
        executor.executeSearch(binarySearch);
        executor.executeSearch(interoplationSearch);
        executor.executeSearch(binaryInterpolationSearch);

        executor.executeSearch(binarySearch);
        executor.executeSearch(interoplationSearch);
        executor.executeSearch(binaryInterpolationSearch);

    } catch (const exception& e) {
        cerr << "\n[FATAL ERROR] Application aborted: " << e.what() << endl;
        return 1;
    }
    return 0;
}
