//
// Created by dirii on 19/12/2022.
//

#ifndef SFML_TEST_CUSTOMRANDOM_H
#define SFML_TEST_CUSTOMRANDOM_H

#include <random>
#include <chrono>
#include <algorithm>

namespace rd{
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    template <typename X>
    void randomArray(std::vector<X> &a){
        std::shuffle(a.begin(), a.end(), rng);
    }
}

#endif //SFML_TEST_CUSTOMRANDOM_H
