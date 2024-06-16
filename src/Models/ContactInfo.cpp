#include "ContactInfo.hpp"

ContactInfo::ContactInfo() {}

void ContactInfo::set_contact_id(int val)
{
  m_contact_id = val;
}

int ContactInfo::get_contact_id()
{
  return m_contact_id;
}

void ContactInfo::set_name(std::string val)
{
  m_name = val;
}

std::string ContactInfo::get_name()
{
  return m_name;
}

void ContactInfo::set_phone_number(long int val)
{
  m_phone_number = val;
}

long int ContactInfo::get_phone_number()
{
  return m_phone_number;
}

void ContactInfo::set_email(std::string val)
{
  m_email = val;
}

std::string ContactInfo::get_email()
{
  return m_email;
}
