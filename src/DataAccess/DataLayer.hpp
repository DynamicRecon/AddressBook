#ifndef DATALAYER_HPP
#define DATALAYER_HPP

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<string>
#include <sqlite3.h>

class DataLayer
{
public:
  DataLayer(std::string path) { m_path = path; };
  ~DataLayer();
  bool is_opened();
  std::string get_errors();
  int get_last_row_id();
  void create_db_contacts();
  void insert_contact_info(char *name, char* email, char *phonenum);
  void insert_contact_loc(int contact_id, char *address, char *city, char *state, char *zip);
  void update_contact_info(char *name, char* email, char *phonenum);
  void update_contact_loc(int contact_id, char *address, char *city, char *state, char *zip);
  void delete_contact_info(char *name);
  void delete_contact_loc(int contact_id);
  void search_contact_info(char *name);
  void search_contact_loc(int contact_id);
private:
  std::string m_path;
  int m_last_row_id;
  bool m_opened;
  int m_fail;
  sqlite3 *m_db;
  char *m_ErrMsg;
};


#endif
