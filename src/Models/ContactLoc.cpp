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
}

void ContactLoc::Update()
{

}

void ContactLoc::Delete()
{

}

void ContactLoc::Search()
{

}