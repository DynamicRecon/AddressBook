#include "DataLayer.hpp"

static int callback_create(void *NotUsed, int argc, char **argv, char **azColName)
{
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

DataLayer::~DataLayer()
{}

DataLayer::DataLayer(std::string settings_path)
{
  m_settings_path = settings_path;
}

bool DataLayer::is_opened()
{
  return m_opened;
}

std::string DataLayer::get_errors()
{
  std::string error_msg(m_ErrMsg);
  return error_msg;
}

void DataLayer::create_db_contacts(std::string contacts_path)
{
  m_path = contacts_path;
  const char *sql;

  
  m_fail = sqlite3_open(m_path.c_str(), &m_db);
  m_opened = true;
  if (m_fail)
  {
    m_opened = false;
    return;
  } 
  
   sql = "CREATE TABLE IF NOT EXISTS ContactInfo (" \
    "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
    "NAME TEXT NOT NULL,"\
    "PHONENUMBER TEXT," \
    "EMAIL TEXT);";

  m_fail = sqlite3_exec(m_db, sql, callback_create, 0, &m_ErrMsg);
  if(m_fail != SQLITE_OK)
  {
    printf("Create ContactsInfo Table Failed %s\n", m_ErrMsg);
    sqlite3_free(m_ErrMsg);
  }
    
  sql = "CREATE TABLE IF NOT EXISTS ContactLoc (" \
    "ID INTEGER PRIMARY KEY AUTOINCREMENT, " \
    "CONTACT_ID INT NOT NULL, " \
    "ADDRESS TEXT, "\
    "CITY TEXT, "\
    "STATE TEXT, "\
    "ZIP TEXT, "\
    "FORIEGN KEY(CONTACT_ID) REFERENCES ContactInfo(ID));";

  m_fail = sqlite3_exec(m_db, sql, callback_create, 0, &m_ErrMsg);
  if(m_fail != SQLITE_OK)
  {
    printf("Create ContactLoc Table Failed %s\n", m_ErrMsg);
    sqlite3_free(m_ErrMsg);
  }

 sql = "CREATE VIEW IF NOT EXISTS vContacts AS " \
    "SELECT t.ID, t.NAME, t.PHONENUMBER, t.EMAIL, " \
    "l.ADDRESS, l.CITY, l.STATE, l.ZIP " \
    "FROM ContactInfo t " \
   "LEFT OUTER JOIN ContactLoc l ON l.CONTACT_ID = t.ID;";

 m_fail = sqlite3_exec(m_db, sql, callback_create, 0, &m_ErrMsg);
  if(m_fail != SQLITE_OK)
  {
    printf("Create vContacts View Failed %s\n", m_ErrMsg);
    sqlite3_free(m_ErrMsg);
  }
  sqlite3_close(m_db);
}

void DataLayer::create_db_settings(std::string settings_path)
{
  m_settings_path = settings_path;
  m_fail = sqlite3_open(m_settings_path.c_str(), &m_db);
  m_opened = true;
  if (m_fail)
  {
    m_opened = false;
    return;
  }

  const char *create_settings_tbl = "CREATE TABLE IF NOT EXISTS Settings (" \
  "ID INTEGER PRIMARY KEY AUTOINCREMENT, " \
  "NAME TEXT NOT NULL, VALUE TEXT);";
  m_fail = sqlite3_exec(m_db, create_settings_tbl, callback_create, 0, &m_ErrMsg);
  if(m_fail != SQLITE_OK)
  {
    printf("...I failed: %s\n", m_ErrMsg);
    sqlite3_free(m_ErrMsg);
  }
  sqlite3_close(m_db);
}

void DataLayer::insert_contact(ContactInfo info, ContactLoc loc)
{
  

}

void DataLayer::insert_setting(Settings set)
{
  const char *insert_sql;
  sqlite3_stmt *stmt;
  int rc;
  m_fail = sqlite3_open(m_settings_path.c_str(), &m_db);
  m_opened = true;
  if (m_fail)
  {
    m_opened = false;
    return;
  } 
  
  insert_sql = "INSERT INTO Settings (NAME,VALUE) VALUES (?, ?);";
  rc = sqlite3_prepare_v2(m_db, insert_sql, -1, &stmt, NULL);
  
  if(rc == SQLITE_OK)
  {
    rc = sqlite3_bind_text(stmt, 1, set.get_name().c_str(), sizeof(set.get_name().c_str()), 0);
    if(rc != SQLITE_OK)
    {
      printf("Error with inserting setting name: %s\n", sqlite3_errmsg(m_db));
      sqlite3_close(m_db);
      exit(-1);
    }
    
    sqlite3_bind_text(stmt, 2, set.get_value().c_str(), sizeof(set.get_value().c_str()), 0);
    if(rc != SQLITE_OK)
    {
       printf("Error with inserting setting value: %s\n", sqlite3_errmsg(m_db));
      sqlite3_close(m_db);
      exit(-1);
    }

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
  } else 
  {
    printf("Error with preparing insert into Settings: %s\n", sqlite3_errmsg(m_db));
  }

  sqlite3_close(m_db);  

}

void DataLayer::update_contact(ContactInfo info, ContactLoc loc)
{

}

void DataLayer::update_setting(Settings set) 
{
   const char *sql = "UPDATE Settings SET VALUE = ?" \
   "WHERE NAME = ?";
   sqlite3_stmt *stmt;
   m_fail = sqlite3_open(m_settings_path.c_str(), &m_db);
   m_opened = true;
   if (m_fail)
   {
    m_opened = false;
    return;
   } 

   int rc = sqlite3_prepare_v2(m_db, sql, sizeof(sql), &stmt, NULL);
   if(rc == SQLITE_OK)
   {
    sqlite3_bind_text(stmt, 1, set.get_value().c_str(), sizeof(char *), 0);
    sqlite3_bind_text(stmt, 2, set.get_name().c_str(), sizeof(char *), 0);
    
     sqlite3_step(stmt);
     sqlite3_finalize(stmt);
   }

   sqlite3_close(m_db);  

}

void DataLayer::delete_contact(ContactInfo info, ContactLoc loc)
{

}

void DataLayer::delete_setting(Settings set)
{
  const char *sql = "DELETE FROM Settings WHERE NAME = ?";
  sqlite3_stmt *stmt;
   m_fail = sqlite3_open(m_settings_path.c_str(), &m_db);
   m_opened = true;
   if (m_fail)
   {
    m_opened = false;
    return;
   } 

   int rc = sqlite3_prepare_v2(m_db, sql, sizeof(sql), &stmt, NULL);
   if(rc == SQLITE_OK)
   {
    sqlite3_bind_text(stmt, 1, set.get_name().c_str(), sizeof(char *), 0);
    
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
   }

   sqlite3_close(m_db);
}

void DataLayer::search_contact(ContactInfo *info, ContactLoc *loc)
{
  
}

void DataLayer::get_setting(Settings *set)
{
   const char *sql = "SELECT VALUE FROM Settings WHERE NAME = ?";
   sqlite3_stmt *stmt;
   
   m_fail = sqlite3_open(m_settings_path.c_str(), &m_db);
   m_opened = true;
   if (m_fail)
   {
    m_opened = false;
   } 
   int rc = sqlite3_prepare_v2(m_db, sql, sizeof(sql), &stmt, NULL);
   sqlite3_bind_text(stmt, sizeof(char*), set->get_name().c_str(), sizeof(char*), 0);
   int step = sqlite3_step(stmt);
    if(step == SQLITE_ROW)
    {
     std::string val((char *)sqlite3_column_text(stmt, 0));
     set->set_value(val);
    }
   sqlite3_finalize(stmt);
   sqlite3_close(m_db);
 }