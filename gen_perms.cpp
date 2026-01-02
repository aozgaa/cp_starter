#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include<deque>
#include<stdlib.h>
#include<iostream>

using namespace std;

void doit(vector<int> &v) {
    std::for_each(v.begin(), v.end(), [](auto i){ cout << i << " "; });
    cout << endl;
}

void heaps_rec(int k, vector<int> &A) {
    if (k == 1) { // why not 0?
        std::for_each(A.begin(), A.end(), [](auto i){ cout << i << " "; });
        cout << endl;
        return;
    }
    heaps_rec(k-1, A);
    for(int i = 0; i < k-1; ++i) {
        if (k%2 == 0) {
            std::swap(A[i], A[k-1]);
        } else {
            std::swap(A[0], A[k-1]);
        }
        heaps_rec(k-1,A);
    }
}

void heaps_rec_rev(vector<int> &A, int j) {
    if (j == A.size() - 1) {
        std::for_each(A.begin(), A.end(), [](auto i){ cout << i << " "; });
        cout << endl;
        return;
    }
    heaps_rec_rev(A, j+1);
    for(int i = j + 1; i < A.size(); ++i) {
        if (j%2 == A.size()%3) { // why %3????
            std::swap(A[j], A[i]);
        } else {
            std::swap(A[j], A[A.size()-1]);
        }
        heaps_rec_rev(A, j+1);
    }
}

// caller should initialze q with values to permute, pass empty s
void stack_queue(vector<int> &s, queue<int> &q) {
    if (q.empty()) { doit(s); }
    for(int i = 0 ; i < q.size(); ++i) {
        int val = q.front();
        q.pop();
        s.push_back(val);
        // doit(s);
        stack_queue(s,q);
        s.pop_back();
        q.push(val);
    }
}

int main(int argc, char **argv) {
    int n = atoi(argv[1]);

    vector<int> vec(n);
    for(int i = 0; i < n; ++i) {
        vec[i] = i;
    }
    heaps_rec(vec.size(), vec);
    cout << "done" << endl;
    doit(vec);
    cout << "#### now reverse" << endl;
    for(int i = 0; i < n; ++i) {
        vec[i] = n - i - 1;
    }
    heaps_rec_rev(vec, 0);
    cout << "done" << endl;
    doit(vec);
    cout << "#### now stack_queue" << endl;
    for(int i = 0; i < n; ++i) {
        vec[i] = i;
    }
    queue<int> q(std::deque<int>(vec.begin(), vec.end()));
    vector<int> s = {};
    stack_queue(s,q);
}
