#pragma once
#include <string>

inline void do_nothing (...) {}
void do_nothing_no_inline ();

template<typename T> int toi (T value) { return static_cast<int> (value); }

template<typename T> int isize (const T &container) { return toi (container.size ()); }

void assert_check (bool check, std::string message);

int fuzzycmp (double a, double b = 0.0, double eps = 1e-16);

std::string get_assets_path_prefix ();
std::string get_saved_game_path_prefix ();
