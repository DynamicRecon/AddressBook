#ifndef CONTACTINFO_HPP
#define CONTACTINFO_HPP

#include<string>

class ContactInfo
{
public:
  ContactInfo();
  void set_contact_id(int val);
  int get_contact_id();
  void set_name(std::string val);
  std::string get_name();
  void set_phone_number(long int val);
  long int get_phone_number();
  void set_email(std::string val);
  std::string get_email();
private:
  int m_contact_id;
  std::string m_name;
  long int m_phone_number;
  std::string m_email;
};

#endif
