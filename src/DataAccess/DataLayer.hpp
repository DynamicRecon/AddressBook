#ifndef DATALAYER_HPP
#define DATALAYER_HPP

#include <stdio.h>
#include <stdlib.h>
#include<string>
#include <sqlite3.h>

#include "Models/ContactInfo.hpp"
#include "Models/ContactLoc.hpp"

class DataLayer
{
public:
  DataLayer(std::string path, std::string db_name);
  ~DataLayer();
  bool is_opened();
  void create_db();
  void insert_contact(ContactInfo info, ContactLoc loc);
  void update_contact(ContactInfo info, ContactLoc loc);
  void delete_contact(int contact_id);
  void search_contact_by_name(std::string name, ContactInfo *info, ContactLoc *loc);
private:
  std::string m_path;
  std::string m_db_name;
  bool m_opened;
  int m_fail;
  sqlite3 *m_db;
  char *m_ErrMsg;
};


#endif
