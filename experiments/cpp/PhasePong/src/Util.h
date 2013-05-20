#ifndef _PONG_UTIL_H_
#define _PONG_UTIL_H_

// from: http://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

template <typename T> T clamp(T val, const T min, const T max) {
    assert(min <= max);

    if (val < min) val = min;
    else if (val > max) val = max;

    return val;
}

#endif
