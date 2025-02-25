#include <iostream>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>
#include <tbb/parallel_reduce.h>
#include <vector>
#include <chrono>
#include <cmath>

const long VECTOR_SIZE = 10000000;
std::vector<long> v(VECTOR_SIZE);

void fillVector() {
    tbb::parallel_for(
        tbb::blocked_range<int>(0, VECTOR_SIZE),
         [&](tbb::blocked_range<int> r){
        for (int i = r.begin(); i < r.end(); i++) {
            v[i] = 10LL;
        }
    });
}

void normaP(int q, long& result) {
    result = tbb::parallel_reduce(
        tbb::blocked_range<int>(0, VECTOR_SIZE),
        0,
        [&](tbb::blocked_range<int> r, long init) -> long {
            for (int i = r.begin(); i < r.end(); i++) {
                init += pow(v[i], q);
            }
            return init;
        },
        std::plus<long long>()
    );

    result = pow(result, 1 / q);
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    fillVector();

    long result = 0;
    normaP(2, result);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time TBB: " << duration.count() << " ms" << std::endl;
    std::cout << result << std::endl;

    return 0;
}