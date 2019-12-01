#pragma once

#include <string>
using namespace std;



inline void do_nothing (...) {}

template <typename T>
int isize (const T& container) { return toi (container.size ()); }

void assert (bool check, string message);

int fuzzycmp (double a, double b = 0.0, double eps = 1e-16);
