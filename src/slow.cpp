#include <bits/stdc++.h>
#include "slow.h" 
#include "query.h"

 
void slow(int k, int q, int* d, int *qs, int* res){
    int* p = new int[k];
    memcpy(p, d, k*sizeof(int));
    for(int i = 1; i < k; i++)
        p[i] += p[i - 1];
    
    query* sorted_qs = new query[q];
    for(int i = 0; i < q; i++)
        sorted_qs[i] = {qs[i], i};
    std::sort(sorted_qs, sorted_qs + q);
    int j = 0;
    for(int i = 0; i < q; i++){
        while(j < k && p[j] <= sorted_qs[i].a)
            ++j;
        res[sorted_qs[i].id] = j;
    }
    delete[] p;
}
