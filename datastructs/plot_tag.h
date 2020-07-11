#pragma once
#include <vector>
#include <unordered_map>

#include "resource/saveload/saveload.h"
#include "common/template_tricks/static_for.h"
#include "common/common.h"

template<const char *name, typename EnumT>
struct named_enum
{
  std::string get_name () { return name; }
  EnumT get_en () { return {}; }
};

template <typename ... NamedEnums>
class plot_tag_set
{
public:
  void set (const std::string &name, const std::string &str_enum_value)
  {
    assert_check (m_plot_properties.count (name), "No such property in this set");
    m_plot_properties[name]->set (str_enum_value);
  }

  bool has (const std::string &name, const std::string &str_enum_value) const
  {
    assert_check (m_plot_properties.count (name), "No such property in this set");
    auto it = m_plot_properties.find (name);
    return it->second->has (str_enum_value);
  }

  template<typename EnumT>
  EnumT get (const std::string &name)
  {
    assert_check (m_plot_properties.count (name), "No such property in this set");
    return (EnumT) m_plot_properties[name]->get ();
  }

  int get (const std::string &name)
  {
    assert_check (m_plot_properties.count (name), "No such property in this set");
    return m_plot_properties[name]->get ();
  }

  plot_tag_set ()
  {
    std::tuple<NamedEnums...> helper;
    static_for<0, sizeof...(NamedEnums)>::apply ([this, &helper] (auto N) {
      std::string name = std::get<N> (helper).get_name ();
      using EnumT = decltype (std::get<N> (helper).get_en ());

      assert_check (!m_plot_properties.count (name), "No name duplicates should be here");
      m_plot_properties[name] = std::make_unique<plot_tag<EnumT>> ();
    });
  }
  plot_tag_set (const plot_tag_set<NamedEnums...> &other) { *this = other; }

  void build_saveload_tree (saveload::node_t &node)
  {
    std::tuple<NamedEnums...> helper;
    static_for<0, sizeof...(NamedEnums)>::apply ([this, &helper, &node] (auto N) {
      std::string name = std::get<N> (helper).get_name ();
      using EnumT = decltype (std::get<N> (helper).get_en ());

      auto it = m_plot_properties.find (name);
      if (it != m_plot_properties.end ())
        it->second = std::make_unique<plot_tag<EnumT>> ();
      it->second->add_to_tree_named (node, name);
    });
  }

  std::string print () const
  {
    std::vector<std::string> parts;
    for (const std::pair<const std::string, std::unique_ptr<plot_tag_base>> &it: m_plot_properties)
      parts.push_back (string_printf ("Tag name: %s, tag value: %s", it.first.c_str (), it.second->print ().c_str ()));
    return string_join (parts, "\n");
  }

  bool operator == (const plot_tag_set<NamedEnums...> &other) const
  {
    for (const std::pair<const std::string, std::unique_ptr<plot_tag_base>> &it : m_plot_properties)
      {
        auto other_it = other.m_plot_properties.find (it.first);
        if (other_it == other.m_plot_properties.end ())
          return false;
        if (!uptrs_are_equal (it.second, other_it->second))
          return false;
      }
    return true;
  }

  plot_tag_set<NamedEnums...> &operator = (const plot_tag_set<NamedEnums...> &other)
  {
    m_plot_properties.clear ();
    for (const std::pair<const std::string, std::unique_ptr<plot_tag_base>> &it : other.m_plot_properties)
      m_plot_properties[it.first] = it.second->clone ();
    return *this;
  }

private:
  struct plot_tag_base
  {
    virtual ~plot_tag_base () {}
    virtual void set (const std::string &str_enum_value) = 0;
    virtual bool has (const std::string &str_enum_value) const = 0;
    virtual int get () const = 0;
    virtual void add_to_tree_named (saveload::node_t &node, const std::string &name) = 0;
    virtual bool operator == (const plot_tag_base &other) const = 0;
    virtual std::unique_ptr<plot_tag_base> clone () const = 0;
    virtual std::string print () const = 0;
  };

  template<typename EnumT>
  struct plot_tag : plot_tag_base
  {
    ~plot_tag () { m_property_value = EnumT::COUNT; }
    void set (const std::string &str_enum_value) override
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
    bool has (const std::string &str_enum_value) const override
    {
      return enum_to_string (m_property_value) == str_enum_value;
    }
    void add_to_tree_named (saveload::node_t &node, const std::string &name) override
    {
      saveload::add (node, m_property_value, name);
    }
    bool operator == (const plot_tag_base &other) const override
    {
      const plot_tag<EnumT> *typed_other = dynamic_cast<const plot_tag<EnumT> *> (&other);
      if (!typed_other)
        return false;

      return m_property_value == typed_other->m_property_value;
    }
    std::unique_ptr<plot_tag_base> clone () const override
    {
      std::unique_ptr<plot_tag<EnumT>> res = std::make_unique<plot_tag<EnumT>> ();
      res->set (enum_to_string (m_property_value));
      return res;
    }
    std::string print () const override { return enum_to_string (m_property_value); }

    EnumT m_property_value;
  };

private:
  std::unordered_map<std::string, std::unique_ptr<plot_tag_base>> m_plot_properties;
};
