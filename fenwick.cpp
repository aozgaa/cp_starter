#include <vector>
#include <cstdio>

using namespace std;

#define LSOne(S) ((S) & (-S))

#define FT_MAX 1000000

typedef vector<int> vi;

class FT {
    private:
        vi ft;

        void build(const vi &f) {
            int m = (int)f.size() - 1;
            ft.assign(m+1, 0);
            for(int i = 1; i <= m; ++i) {
                ft[i] += f[i];
                if (i + LSOne(i) <= m) {
                    ft[i + LSOne(i)] += ft[i];
                }
            }
        }
    public:
        FT(int m) : ft(m+1,0) {}
        FT(const vi &f) { build(f); }
        FT(int m, const vi &s) {
            vi f(m+1, 0);
            for (int i = 0; i < (int)s.size(); ++i) {
                ++f[s[i]];
            }
            build(f);
        }
        int rsq(int j) { // range sum query
            int sum = 0;
            while(j) {
                sum += ft[j];
                j -= LSOne(j);
            }
            return sum;
        }
        int rsq(int i, int j) { return rsq(j) - rsq(i); }
        void update(int i, int v) {
            while(i < (int)ft.size()) {
                ft[i] += v;
                i += LSOne(i);
            }
        }
        auto select(int k) {
            int lo = 1, hi = ft.size() - 1;
            for(int i = 0; i < 8 * sizeof(int); ++i) {
                int mid = (lo / 2) + (hi / 2) + (1 & (lo & hi));
                if (rsq(mid) < k) { lo = mid; } else { hi = mid; }
            }
            return hi;
        }
};

int main() {
    FT ft(1 << 4);
    ft.update(7,3);
    for (int i = 0; i <= 1 << 4; ++i) {
        printf("ft.rsq(%d) == %d\n", i, ft.rsq(i));
        printf("ft.select(%d) == %d\n", i, ft.select(i));
    }

}
