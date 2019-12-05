#pragma once
#include "common/common.h"
#include "external/rapidxml/rapidxml.hpp"
#include "external/rapidxml/rapidxml_print.hpp"

std::string xml_node_to_string (const rapidxml::xml_node<> &node);
