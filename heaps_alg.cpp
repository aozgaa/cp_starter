#include<algorithm>
#include<iostream>
#include<numeric>
#include<vector>

using namespace std;

/** k'th element is fixed on recursive call -- initial call should be A.size() */
void heaps(vector<int> &A, int k) {
    if (k <= 1) { // last recusrive call wouldn't permute anything
        std::for_each(A.begin(), A.end(), [](auto i){ cout << i << " "; });
        cout << endl;
        return;
    }
    heaps(A, k - 1);
    for(int i = 0; i < k-1; ++i) {
        if (k%2 == 0) {
            std::swap(A[i], A[k-1]);
        } else {
            std::swap(A[0], A[k-1]);
        }
        heaps(A, k - 1);
    }
}

/** k'th element is not fixed on recursive call -- initial call should be A.size() - 1 */
void heaps2(vector<int> &A, int k) {
    // cerr << "heap2({ ";
    // std::for_each(A.begin(), A.end(), [](auto i){ cerr << i << " "; });
    // cerr << " }, " << k << ")" << endl;

    if (k <= 0) { // last recusrive call wouldn't permute anything
        std::for_each(A.begin(), A.end(), [](auto i){ cout << i << " "; });
        cout << endl;
        return;
    }
    heaps2(A, k - 1);
    for(int i = 0; i < k; ++i) {
        if (k%2 == 0) {
            std::swap(A[0], A[k]);
        } else {
            std::swap(A[i], A[k]);
        }
        heaps2(A, k - 1);
    }
}

void heaps_nr(vector<int> &A) {
    vector<int> ks(A.size() - 1);

    std::for_each(A.begin(), A.end(), [](auto i){ cout << i << " "; });
    cout << endl;

    int sp = 1; // "stack pointer" to ks
    while (sp < A.size()) {
        if (ks[sp] < sp) {
            if(sp%2) {
                std::swap(A[sp], A[ks[sp]]);
            } else {
                std::swap(A[sp], A[0]);
            }
            std::for_each(A.begin(), A.end(), [](auto i){ cout << i << " "; });
            cout << endl;
            ks[sp]++;
            sp=1;
        } else {
            ks[sp] = 0;
            sp++;
        }
    }


}

void nr_loop(int n) {
    vector<int> ks(n - 1);
    cout << " ## result ##" << endl;
    int sp = 1;
    while(sp < n) {
        cout << "sp = " << sp << " :: ";
        cout << "ks = { ";
        std::for_each(ks.begin(), ks.end(), [](auto i){ cout << i << " "; });
        cout << "}" << endl;
        if(ks[sp] < sp) {
            cout << " ## result ##" << endl;
            ks[sp]++;
            sp=1;
        } else {
            ks[sp] = 0;
            sp++;
        }


    }
}

/** k'th element not yet fixed on recursive call -- inital call should be 0 */
void heaps_rev(vector<int> &A, int k) {
    if (k >= (int)A.size() - 1) {
        std::for_each(A.begin(), A.end(), [](auto i){ cout << i << " "; });
        cout << endl;
        return;
    }
    heaps_rev(A, k+1);
    for(int i = k + 1; i < A.size(); ++i) {
        if ((A.size() - k) % 2) {
            std::swap(A[k], A[A.size()-1]);
        } else {
            std::swap(A[k], A[i]);
        }
        heaps_rev(A, k+1);
    }
}

int main(int argc, char **argv) {
    int n = atoi(argv[1]);

    vector<int> v(n);
    // std::iota(v.begin(), v.end(), 1);
    // heaps(v, v.size());
    // std::iota(v.begin(), v.end(), 1);
    // heaps2(v, v.size() - 1);
    // std::iota(v.begin(), v.end(), 1);
    // heaps_nr(v);
    //std::iota(v.begin(), v.end(), 1);
    //heaps_rev(v, 0);
    
    nr_loop(n);
}
