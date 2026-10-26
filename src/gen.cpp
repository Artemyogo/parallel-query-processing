#include "gen.h"
#include <random>
#include <chrono>
using namespace std;

constexpr int MAXA = 1e9;

void gen(int k, int q, int*& d, int*& qs){
    mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
    const int MAXD = MAXA/k*2;
    d = new int[k];
    for(int i = 0; i < k; i++){
        d[i] = rnd()%MAXD;
    }
    qs = new int[q];
    for(int i = 0; i < q; i++)
        qs[i] = rand()%MAXA;
}

