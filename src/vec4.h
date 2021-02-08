#ifndef VEC4_H
#define VEC4_H

#include <vector>


struct Vec4 {
    int x;
    int y;
    int u;
    int t;

    // implements std::less which is important for the set in negativePermutations
    bool operator <(const Vec4& vec) const
    {
        // order of significance of the fields is x is more significant than y, mst u mst t
        if (x < vec.x) 
            return true;
        if (x == vec.x && y < vec.y) 
            return true;
        if (x == vec.x && y == vec.y && u < vec.u)  
            return true;
        if (x == vec.x && y == vec.y && u == vec.u && t < vec.t)  
            return true;

        return false;
    }
};

namespace Vector4{
    std::vector<Vec4>* getAllPermutations(Vec4);    
}



#endif // VEC4_H