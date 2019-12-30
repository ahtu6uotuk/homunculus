#pragma once

#include <string>
#include <memory>
using namespace std;


inline void do_nothing (...) {}
void do_nothing_no_inline ();

template<typename T> int toi (T value) { return static_cast<int> (value); }

template<typename T> int isize (const T &container) { return toi (container.size ()); }

void assert_check (bool check, string message);

int fuzzycmp (double a, double b = 0.0, double eps = 1e-16);

template<typename T>
bool uptrs_are_equal (const unique_ptr<T> &a, const unique_ptr<T> &b)
{
  return (!a and !b) or (*a == *b);
}

string get_assets_path_prefix ();
