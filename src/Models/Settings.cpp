#include "Settings.hpp"

Settings::Settings() {}

std::string Settings::get_name()
{
  return m_name;
}

void Settings::set_name(std::string val)
{
  m_name = val;
}

std::string Settings::get_value()
{
  return m_value;
}

void Settings::set_value(std::string val)
{
  m_value = val;
}