#include "vec4.h"
#include <algorithm>
#include <iostream>
#include <set>

/**
 * Generates all the various 90 degree rotations of the given Vec4
 * Adds all of these variations to the vector
 * Ex: (1, 2) -> (1, 2), (-1, 2), (1, -2), (-1, -2)
 * Except for Vec4
 */
void negativePermutations(Vec4 vec4, std::vector<Vec4> *vector)
{
    // std::cout << "negative permutations: " << std::endl;
    // A set it used to prevent duplicates
    std::set<Vec4> *perms = new std::set<Vec4>();

    // 0 through 15 is 0000 to 1111 in binary,
    // which can be used to get all the possible combinations of plus and negative signs
    for (size_t i = 0; i < 15; i++)
    {
        int x = vec4.x;
        int y = vec4.y;
        int t = vec4.t;
        int u = vec4.u;

        Vec4 newVec{x, y, u, t};

        // check each of the bits of i 
        // each bit corresponds to a axis of the vector and if that bit is one,
        // change the sign of that component (multiply by negative one)
        if (i & (0x1 << 0))
        {
            newVec.x *= -1;
        }

        if (i & (0x1 << 1))
        {
            newVec.y *= -1;
        }

        if (i & (0x1 << 2))
        {
            newVec.u *= -1;
        }

        if (i & (0x1 << 3))
        {
            newVec.t *= -1;
        }

        perms->insert(newVec);
        // std::cout << "(" << newVec.x << ", " << newVec.y << ", " << newVec.u << ", " << newVec.t << ")" << std::endl;
        // vector->push_back(newVec);
    }
    // move from the set to the given vector
    for(auto v : *perms)
    {
        vector->push_back(v);
    }
    // std::cout << std::endl;
}

/**
 * Uses lexographical ordering in order to get all the unique orderings of the coordinates of the vector
 * this lets you get all the different ways that a piece can travel given a single way it can travel
 * (all piece movement has the same kind of symetry)
 * On top of lexogrpahical ordering for permutations, this also uses negativePermutations()
 * in order to get all the various ways (1, 2, 3, 4) can becomes (-1, 2, 3, 4), (1, -2, -3, 4) etc
 * https://medium.com/@rwillt/two-very-different-algorithms-for-generating-permutations-412e8cc0039c
 */
std::vector<Vec4> *Vector4::getAllPermutations(Vec4 vec4)
{
    std::vector<Vec4> *permutations = new std::vector<Vec4>();

    int vecArray[4] = {vec4.t, vec4.u, vec4.x, vec4.y};
    std::sort(vecArray, vecArray + 4);
    Vec4 v{vecArray[0], vecArray[1], vecArray[2], vecArray[3]};

    // negative permutations adds v to the vector on it's own, so we don't have to do it 
    negativePermutations(v, permutations);

    while (true)
    {
        int i = 3;
        int j = 3;
        int k = 3;

        while (i > 0 && vecArray[i - 1] >= vecArray[i])
        {
            i--;
        }

        if (i <= 0)
        {
            break;
        }

        while (vecArray[j] <= vecArray[i - 1])
        {
            j--;
        }

        int temp = vecArray[i - 1];
        vecArray[i - 1] = vecArray[j];
        vecArray[j] = temp;

        while (i < k)
        {
            int temp = vecArray[i];
            vecArray[i] = vecArray[k];
            vecArray[k] = temp;
            i++;
            k--;
        }

        Vec4 v{vecArray[0], vecArray[1], vecArray[2], vecArray[3]};
        // negative permutations adds v to the vector for us
        negativePermutations(v, permutations);
    }

    return permutations;
}