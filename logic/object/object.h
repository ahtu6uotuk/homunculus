#pragma once
#include <functional>

#include "common/common.h"
#include "common/template_tricks/auto_register.h"
#include "common/template_tricks/static_for.h"
#include "logic/object/interaction.h"
#include "logic/object/object_base.h"
#include "logic/object/object_heap.h"
#include "logic/saveload/saveload.h"

template<typename Self, typename... Args>
class object : automatic_register<Self>, virtual public object_base, public Args...
{
public:
  std::string describe () const override
  {
    std::vector<std::string> parts;
    auto func = [&parts] (const auto attr) { parts.push_back (attr->policy_describe ()); };
    for_all_attrs (func);
    return string_join (parts, "\n");
  }
  std::vector<interaction> get_interactions () override
  {
    std::vector<interaction> res;
    auto func = [&res] (const auto attr) {
      std::vector<interaction> l_res = attr->policy_get_interactions ();
      res.insert (res.end (), make_move_iterator (l_res.begin ()), make_move_iterator (l_res.end ()));
    };
    for_all_attrs (func);
    return res;
  }
  bool operator == (const object<Self, Args...> &other) const
  {
    bool res = true;
    auto func = [&res, &other] (const auto attr)
    {
      const decltype (attr) casted_other = dynamic_cast<const decltype (attr)> (&other);
      assert_check (casted_other, "Internal error");
      if (!(attr->operator == (*casted_other)))
        res = false;
    };
    for_all_attrs (func);
    return res;
  }
  void build_saveload_tree (saveload_node &node)
  {
    auto func = [&node] (auto attr) { attr->policy_build_saveload_tree (node); };
    for_all_attrs (func);
  }

protected:
  virtual object_base &get_policy_private () override { return *this; }
  virtual const object_base &get_policy_private () const override { return *this; }

private:
  template<typename Func>
  void for_all_attrs (Func &func)
  {
    for_all_attrs_helper<Func, Args...> (func);
  }

  template<typename Func>
  void for_all_attrs (Func &func) const
  {
    for_all_attrs_helper<Func, Args...> (func);
  }

  template<typename Func, typename Attr>
  void for_all_attrs_helper (Func &func)
  {
    func.template operator() (dynamic_cast<Attr *> (this));
  }

  template<typename Func, typename Attr, typename AnotherAttr, typename... OtherAttrs>
  void for_all_attrs_helper (Func &func)
  {
    func.template operator() (dynamic_cast<Attr *> (this));
    for_all_attrs_helper<Func, AnotherAttr, OtherAttrs...> (func);
  }

  template<typename Func, typename Attr>
  void for_all_attrs_helper (Func &func) const
  {
    func.template operator() (dynamic_cast<const Attr *> (this));
  }

  template<typename Func, typename Attr, typename AnotherAttr, typename... OtherAttrs>
  void for_all_attrs_helper (Func &func) const
  {
    func.template operator() (dynamic_cast<const Attr *> (this));
    for_all_attrs_helper<Func, AnotherAttr, OtherAttrs...> (func);
  }

  static void register_type_for_heap ()
  {
    obj_heap_helper::singleton().push_back ([] (object_heap &heap) { heap.add_type<Self> (); });
  }
  template<typename D> friend struct automatic_register;
};
