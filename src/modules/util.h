#ifndef MY_UTIL
#define MY_UTIL

using namespace std;

class RangeRandGenerator {
    uniform_real_distribution<double> dist;
    random_device rd;
    default_random_engine gen;
public:
    RangeRandGenerator(double from, double to) :
        dist(from, to), gen(rd()) {}

    double get() {
        return dist(gen);
    }
};

#endif