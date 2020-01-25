#pragma once
#include <vector>
#include <unordered_map>

#include "logic/saveload/saveload.h"
#include "common/template_tricks/static_for.h"
#include "common/common.h"

template<const char *name, typename EnumT>
struct named_enum
{
  string get_name () { return name; }
  EnumT get_en () { return {}; }
};

template <typename ... NamedEnums>
class plot_tag_set
{
public:
  void set (const string &name, const string &str_enum_value)
  {
    assert_check (m_plot_properties.count (name), "No such property in this set");
    m_plot_properties[name]->set (str_enum_value);
  }

  bool has (const string &name, const string &str_enum_value) const
  {
    assert_check (m_plot_properties.count (name), "No such property in this set");
    auto it = m_plot_properties.find (name);
    return it->second->has (str_enum_value);
  }

  template<typename EnumT>
  EnumT get (const string &name)
  {
    assert_check (m_plot_properties.count (name), "No such property in this set");
    return (EnumT) m_plot_properties[name]->get ();
  }

  int get (const string &name)
  {
    assert_check (m_plot_properties.count (name), "No such property in this set");
    return m_plot_properties[name]->get ();
  }

  plot_tag_set ()
  {
    tuple<NamedEnums...> helper;
    static_for<0, sizeof...(NamedEnums)>::apply ([this, &helper] (auto N) {
      string name = std::get<N> (helper).get_name ();
      using EnumT = decltype (std::get<N> (helper).get_en ());

      assert_check (!m_plot_properties.count (name), "No name duplicates should be here");
      m_plot_properties[name] = make_unique<plot_tag<EnumT>> ();
    });
  }

  void build_saveload_tree (saveload_node &node)
  {
    for (pair<const string, unique_ptr<plot_tag_base>> &it: m_plot_properties)
      it.second->add_to_tree_named (node, it.first);
  }

  string print () const
  {
    vector<string> parts;
    for (const pair<const string, unique_ptr<plot_tag_base>> &it: m_plot_properties)
      parts.push_back (string_printf ("Tag name: %s, tag value: %s", it.first.c_str (), it.second->print ().c_str ()));
    return string_join (parts, "\n");
  }

  bool operator == (const plot_tag_set<NamedEnums...> &other) const
  {
    for (const pair<const string, unique_ptr<plot_tag_base>> &it : m_plot_properties)
      {
        auto other_it = other.m_plot_properties.find (it.first);
        if (other_it == other.m_plot_properties.end ())
          return false;
        if (!uptrs_are_equal (it.second, other_it->second))
          return false;
      }
    return true;
  }

private:
  struct plot_tag_base
  {
    virtual ~plot_tag_base () {}
    virtual void set (const string &str_enum_value) = 0;
    virtual bool has (const string &str_enum_value) const = 0;
    virtual int get () const = 0;
    virtual void add_to_tree_named (saveload_node &node, const string &name) = 0;
    virtual bool operator == (const plot_tag_base &other) const = 0;
    virtual string print () const = 0;
  };

  template<typename EnumT>
  struct plot_tag : plot_tag_base
  {
    ~plot_tag () { m_property_value = EnumT::COUNT; }
    void set (const string &str_enum_value) override
    {
      for (int i = 0; i < (int) EnumT::COUNT; i++)
        if (enum_to_string ((EnumT) i) == str_enum_value)
          {
            m_property_value = (EnumT) i;
            return;
          }
      assert_check (false, "No such enum value in this property");
    }
    int get () const override { return (int) m_property_value; }
    bool has (const string &str_enum_value) const override
    {
      return enum_to_string (m_property_value) == str_enum_value;
    }
    void add_to_tree_named (saveload_node &node, const string &name) override
    {
      node.add (m_property_value, name);
    }
    bool operator == (const plot_tag_base &other) const override
    {
      const plot_tag<EnumT> *typed_other = dynamic_cast<const plot_tag<EnumT> *> (&other);
      if (!typed_other)
        return false;

      return m_property_value == typed_other->m_property_value;
    }
    virtual string print () const override { return enum_to_string (m_property_value); }

    EnumT m_property_value;
  };

private:
  unordered_map<string, unique_ptr<plot_tag_base>> m_plot_properties;
};
