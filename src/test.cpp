#include <bits/stdc++.h>
#include "fast_openmp.h"
#include "fast_thread.h"
#include "gen.h"
#include "slow.h"

using namespace std;
using namespace chrono;

class timer: high_resolution_clock {
    const time_point start_time;
public:
    timer(): start_time(now()) {}
    rep elapsed_time() const { return duration_cast<milliseconds>(now()-start_time).count(); } };

int test(int k, int q, int* d, int* qs, int* res,
        function<void(int, int, int*, int*, int*)> solution){
    timer t;
    solution(k, q, d, qs, res);
    return t.elapsed_time();
}

int main(int argc, char** argv){
    mt19937 rnd(time(NULL));
    int k = 1e7, q = 1e7;
    if(argc > 1)
        k = atoi(argv[1]);
    if(argc > 2)
        q = atoi(argv[2]);
    int *d, *qs;
    gen(k, q, d, qs);
    int* resslow = new int[q], * resfast = new int[q];
    cout << "Elapsed time without multithreading: " << test(k, q, d, qs, resslow, slow) << "ms" << endl;
    cout << "Elapsed time with std::thread: " << test(k, q, d, qs, resfast, fast_thread) << "ms" << endl;
    for(int i = 0; i < q; i++){
        assert(resslow[i] == resfast[i]);
    }
    cout << "Elapsed time with openMP: " << test(k, q, d, qs, resfast, fast_openmp) << "ms" << endl;
    for(int i = 0; i < q; i++)
        assert(resslow[i] == resfast[i]);

}

