#pragma once

#include <vector>
#include <optional>
#include <iostream>
#include <functional>

#include "common/string/string_converters.h"
#include "common/common.h"

template<typename T>
int print_choices_and_get_answer (
    const vector<T> &choices, function<string (const T &)> print_func, bool enable_quit = false)
{
  while (true)
    {
      printf ("Choose:\n");
      print_choices (choices, print_func, enable_quit);
      if (optional<int> res = get_answer_number_or_print_error (choices, enable_quit))
        return *res;
    }
}

template<typename T>
void print_choices (
    const vector<T> &choices, function<string (const T &)> print_func, bool enable_quit = false)
{
  for (int i = 0; i < isize (choices); i++)
    {
      const T &answer = choices[i];
      printf ("%d: %s\n", i + 1, print_func (answer).c_str ());
    }
  if (enable_quit)
    printf ("0: Quit\n");
}

template<typename T>
optional<int> get_answer_number_or_print_error (const vector<T> &choices, bool enable_quit = false)
{
  string player_input;
  getline (cin, player_input);

  int answer_number = 0;
  err_t err = string_to_data (player_input, answer_number);
  answer_number--;

  if (!err.ok ())
    {
      printf ("%s\n", err.descr_c_str ());
      return nullopt;
    }

  if (enable_quit && answer_number == -1)
    return -1;

  if (answer_number >= isize (choices) || answer_number < 0)
    {
      printf ("There is no answer with such number\n");
      return nullopt;
    }

  return answer_number;
}
