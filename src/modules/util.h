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

float rnd(float min, float max) {
    // construct a trivial random generator engine from a time-based seed:
    RangeRandGenerator generator(min, max);
    return (float) generator.get();
}

#endif