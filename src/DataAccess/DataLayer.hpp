#ifndef DATALAYER_HPP
#define DATALAYER_HPP

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<string>
#include <sqlite3.h>

#include "Models/ContactInfo.hpp"
#include "Models/ContactLoc.hpp"
#include "Models/Settings.hpp"

class DataLayer
{
public:
  DataLayer() {};
  DataLayer(std::string settings_path);
  ~DataLayer();
  bool is_opened();
  std::string get_errors();
  void create_db_contacts(std::string contacts_path);
  void create_db_settings(std::string settings_path);
  void insert_setting(Settings set);
  void insert_contact(ContactInfo info, ContactLoc loc);
  void update_setting(Settings set);
  void update_contact(ContactInfo info, ContactLoc loc);
  void delete_setting(Settings set);
  void delete_contact(ContactInfo info, ContactLoc loc);
  void get_setting(Settings *set);
  void search_contact(ContactInfo *info, ContactLoc *loc);
private:
  std::string m_path;
  std::string m_settings_path;
  bool m_opened;
  int m_fail;
  sqlite3 *m_db;
  char *m_ErrMsg;
};


#endif
