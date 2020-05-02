#pragma once

#include <functional>

#include "external/rapidxml/rapidxml.hpp"
#include "resource/saveload/saveload_fwd.h"

namespace saveload
{
using xml_node_t = rapidxml::xml_node<>;
using xml_doc_t = rapidxml::xml_document<>;
template<typename DataT>
using create_node_func_t = std::function<std::unique_ptr<node_t> (xml_doc_t &, DataT &)>;
template<typename DataT>
using fill_node_func_t = std::function<void (node_t &, DataT &)>;
}
