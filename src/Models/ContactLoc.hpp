#ifndef CONTACTLOC_HPP
#define CONTACTLOC_HPP

#include<string>

#include "DataAccess/DataLayer.hpp"

class ContactLoc {
public:
  ContactLoc();
  ContactLoc(std::string db_path);
  void set_location_id(int val);
  int get_location_id();
  void set_contact_id(int val);
  int get_contact_id();
  void set_address(std::string val);
  std::string get_address();
  void set_city(std::string val);
  std::string get_city();
  void set_state(std::string val);
  std::string get_state();
  void set_zip(std::string val);
  std::string get_zip();
  void Add();
  void Update();
  void Delete();
  void Search();
private:
  std::string m_db_path;
  int m_location_id;
  int m_contact_id;
  std::string m_address;
  std::string m_city;
  std::string m_state;
  std::string m_zip;
};

#endif
