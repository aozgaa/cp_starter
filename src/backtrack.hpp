#pragma once

struct Ctx {
    int upper_bound;
    int lower_bound;
};

inline bool finished = false;

template <typename T>
void backtrack(int *part, int sz, T &ctx);

template <typename T>
void make_cands(const int *part, int psz, T &ctx, int **cands, int *csz);

template <typename T>
bool is_soln(const int *part, int sz, T &ctx);

template <typename T>
void proc_soln(const int *soln, int sz, T &ctx);

template <typename T>
int proc_part(const int *part, int sz, T &ctx) {
    if (is_soln(part, sz, ctx)) {
        proc_soln(part, sz, ctx);
        return 1;
    }
    return 0;
}

template <typename T>
void backtrack(int *part, int sz, T &ctx) {
    if (proc_part(part, sz, ctx) != 0) {
        return;
    }

    sz += 1;

    int *cands;
    int csz;
    make_cands(part, sz, ctx, &cands, &csz);
    for (int i = 0; i < csz; ++i) {
        part[sz] = cands[i];
        backtrack(part, sz, ctx);
    }
}
