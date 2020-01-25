#include "friend.h"

const char *enum_to_string (mood m)
{
  switch (m)
    {
    case mood::happy:
      return "happy";
    case mood::sad:
      return "sad";
    case mood::melancholic:
      return "melancholic";
    case mood::COUNT:
      return "";
    }
  return "";
}

const char *enum_to_string (bloodtype m)
{
  switch (m)
    {
    case bloodtype::o:
      return "o";
    case bloodtype::a:
      return "a";
    case bloodtype::b:
      return "b";
    case bloodtype::ab:
      return "ab";
    case bloodtype::COUNT:
      return "";
    }
  return "";
}
