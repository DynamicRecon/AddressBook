#include "ContactLoc.hpp"

ContactLoc::ContactLoc() 
{}

ContactLoc::ContactLoc(std::string db_path) 
{ 
  m_db_path = db_path; 
}

void ContactLoc::set_location_id(int val)
{
  m_location_id = val;
}

int ContactLoc::get_location_id()
{
  return m_location_id;
}

void ContactLoc::set_contact_id(int val)
{
  m_contact_id = val;
}

int ContactLoc::get_contact_id()
{
  return m_contact_id;
}

void ContactLoc::set_address(std::string val)
{
  m_address = val;
}

std::string ContactLoc::get_address()
{
  return m_address;
}

void ContactLoc::set_city(std::string val)
{
  m_city = val;
}

std::string ContactLoc::get_city()
{
  return m_city;
}

void ContactLoc::set_state(std::string val)
{
  m_state = val;
}

std::string ContactLoc::get_state()
{
  return m_state;
}

void ContactLoc::set_zip(std::string val)
{
  m_zip = val;
}

std::string ContactLoc::get_zip()
{
  return m_zip;
}

void ContactLoc::Add()
{
  DataLayer add_dl(m_db_path);
  char address[500];
  strcpy(address, m_address.c_str());
  char city[100];
  strcpy(city, m_city.c_str());
  char state[100];
  strcpy(state, m_state.c_str());
  char zip[100];
  strcpy(zip, m_zip.c_str());
  add_dl.insert_contact_loc(m_contact_id, address, city, state, zip);
  m_location_id = add_dl.get_last_row_id();
}

void ContactLoc::Update()
{

}

void ContactLoc::Delete()
{

}

void ContactLoc::Search()
{
  DataLayer search_dl(m_db_path);
  char address[500];
  char city[100];
  char state[100];
  char zip[100];
  search_dl.search_contact_loc(m_contact_id, address, city, state, zip);
  std::string str_address(address);
  std::string str_city(city);
  std::string str_state(state);
  std::string str_zip(zip);
  m_address = str_address;
  m_city = str_city;
  m_state = str_state;
  m_zip = str_zip;
}