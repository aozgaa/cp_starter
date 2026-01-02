#include<bits/stdc++.h>

using namespace std;

int main() {
    for(;;) {
        int n[4];
        for(int i = 0; i < 4; ++i) {
            scanf("%d", &n[i]);
            printf("%c\n", n[i] + '0');
        }
        if(n[0] == 0) { break; }
    }
}
