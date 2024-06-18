#ifndef CONTACTINFO_HPP
#define CONTACTINFO_HPP

#include<string>

#include "DataAccess/DataLayer.hpp"

class ContactInfo
{
public:
  ContactInfo();
  ContactInfo(std::string db_path);
  void set_contact_id(int val);
  int get_contact_id();
  void set_name(std::string val);
  std::string get_name();
  void set_phone_number(std::string val);
  std::string get_phone_number();
  void set_email(std::string val);
  std::string get_email();
  void Add();
  void Update();
  void Delete();
  void Search();
private:
  std::string m_db_path;
  int m_contact_id;
  std::string m_name;
  std::string m_phone_number;
  std::string m_email;
};

#endif
