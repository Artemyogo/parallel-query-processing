#include <bits/stdc++.h>
#include <thread>
#include "fast_thread.h"
#include "query.h"

void fast_thread(int k, int q, int* d, int* qs, int* res) {
    int* p = new int[k];
    memcpy(p, d, k*sizeof(int));
    for(int i = 1; i < k; i++)
        p[i] += p[i - 1];

    int num_threads = std::thread::hardware_concurrency();
    int sz = q / num_threads;
    int rem = q % num_threads;
    auto calc = [&](int t_id){
        int start, end;
        if (t_id < rem) {
            start = t_id * (sz + 1);
            end = start + sz + 1;
        } else {
            start = t_id * sz + rem;
            end = start + sz;
        }

        query* local_qs = new query[end - start];

        for (int i = start; i < end; ++i) {
            local_qs[i - start] = {qs[i], i};
        }

        std::sort(local_qs, local_qs+end - start);

        int j = 0;
        for(int i = 0; i < end - start; i++){
            while (j < k && p[j] <= local_qs[i].a) {
                ++j;
            }
            res[local_qs[i].id] = j;
        }
    };
    std::vector<std::thread> ts(num_threads);
    for(int i = 0; i < num_threads; i++)
        ts[i] = std::thread(calc, i);
    for(auto& i : ts)
        i.join();
    delete[] p;
}
