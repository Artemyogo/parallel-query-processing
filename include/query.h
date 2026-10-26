#pragma once

struct query{
    int a, id;
    inline bool operator <(const query& q) const{
        return a < q.a;
    }
};
