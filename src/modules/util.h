#ifndef MY_UTIL
#define MY_UTIL

class RangeRandGenerator {
    std::uniform_real_distribution<double> dist;
    std::random_device rd;
    std::default_random_engine gen;
public:
    RangeRandGenerator(double from, double to) :
        dist(from, to), gen(rd()) {}

    double get() {
        return dist(gen);
    }
};

#endif