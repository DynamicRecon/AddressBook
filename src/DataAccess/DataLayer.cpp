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



int DataLayer::insert_contact_info(char *name, char* email, char *phonenum)
{
  
  
}

void DataLayer::insert_contact_loc(int contact_id, char *address, char *city, char *state, char *zip)
{

}


void DataLayer::update_contact_info(char *name, char* email, char *phonenum)
{

}

void DataLayer::update_contact_loc(int contact_id, char *address, char *city, char *state, char *zip)
{

}


void DataLayer::delete_contact_info(char *name)
{

}

void DataLayer::delete_contact_loc(int contact_id)
{

}



void DataLayer::search_contact_info(char *name)
{
  
}

void DataLayer::search_contact_loc(int contact_id)
{

}
