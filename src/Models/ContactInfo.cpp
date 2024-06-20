#include "ContactInfo.hpp"

ContactInfo::ContactInfo() 
{}

ContactInfo::ContactInfo(std::string db_path) 
{ 
  m_db_path = db_path; 
}

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

void ContactInfo::set_phone_number(std::string val)
{
  m_phone_number = val;
}

std::string ContactInfo::get_phone_number()
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

void ContactInfo::Add()
{
  DataLayer add_dl(m_db_path);
  char name[100];
  strcpy(name, m_name.c_str());
  char email[500]; 
  strcpy(email, m_email.c_str());
  char phone[500];
  strcpy(phone, m_phone_number.c_str());
  add_dl.insert_contact_info(name, email, phone);
  set_contact_id(add_dl.get_last_row_id(name));
}

void ContactInfo::Update()
{
  DataLayer update_dl(m_db_path);
  char name[100];
  strcpy(name, m_name.c_str());
  char email[500]; 
  strcpy(email, m_email.c_str());
  char phone[500];
  strcpy(phone, m_phone_number.c_str());
  update_dl.update_contact_info(name, email, phone);
}

void ContactInfo::Delete()
{

}

void ContactInfo::Search()
{
  DataLayer search_dl(m_db_path);
  char name[100];
  strcpy(name, m_name.c_str());
  char email[500];
  char phone[500];
  int contact_id;
  search_dl.search_contact_info(name, contact_id, email, phone);
  std::string str_email(email);
  std::string str_phone(phone);
  m_email = str_email;
  m_phone_number = str_phone;
  m_contact_id = contact_id;
}