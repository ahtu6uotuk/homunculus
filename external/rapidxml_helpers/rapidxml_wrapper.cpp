#include "external/rapidxml_helpers/rapidxml_wrapper.h"

std::string xml_node_to_string (const rapidxml::xml_node<> &node)
{
  std::string s;
  print (std::back_inserter(s), node, 0);
  return s;
}
