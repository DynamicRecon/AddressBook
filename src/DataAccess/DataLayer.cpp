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

DataLayer::DataLayer(std::string path, std::string db_name)
{
  m_path = path;
  m_db_name = db_name;   
}

DataLayer::~DataLayer()
{}

bool DataLayer::is_opened()
{
  return m_opened;
}

void DataLayer::create_db()
{
  const char *contactinfo_tbl;
  const char *contactloc_tbl;
  const char *contact_view;

  std::string file_path = m_path + "/" + m_db_name;
  m_fail = sqlite3_open(file_path.c_str(), &m_db);
  if (m_fail)
  {
    m_opened = false;
    return;
  } else
  {
    m_opened = true;
    return;
  }
  
  contactinfo_tbl = "CREATE TABLE IF NOT EXISTS ContactInfo (" \
    "ID INT PRIMARY KEY NOT NULL," \
    "NAME TEXT NOT NULL,"\
    "PHONENUMBER TEXT," \
    "EMAIL TEXT);";

  m_fail = sqlite3_exec(m_db, contactinfo_tbl, callback_create, 0, &m_ErrMsg);
  if(m_fail != SQLITE_OK)
  {
    return;
  }
    
  contactloc_tbl = "CREATE TABLE IF NOT EXISTS ContactLoc(" \
    "ID INT PRIMARY KEY NOT NULL," \
    "CONTACT_ID INT NOT NULL," \
    "ADDRESS TEXT,"\
    "CITY TEXT,"\
    "STATE TEXT,"\
    "ZIP TEXT,"\
    "FORIEGN KEY(CONTACT_ID) REFERENCES ContactInfo(ID));";

  m_fail = sqlite3_exec(m_db, contactloc_tbl, callback_create, 0, &m_ErrMsg);
  if(m_fail != SQLITE_OK)
  {
    return;
  }

 contact_view = "CREATE VIEW IF NOT EXISTS vContacts AS" \
    "SELECT t.CONTACT_ID, t.NAME, t.PHONENUMBER, t.EMAIL," \
    "l.ADDRESS, l.CITY, l.STATE, l.ZIP" \
    "FROM ContactInfo t" \
   "LEFT OUTER JOIN ContactLoc l ON l.CONTACT_ID = t.ID;";

 m_fail = sqlite3_exec(m_db, contact_view, callback_create, 0, &m_ErrMsg);
  if(m_fail != SQLITE_OK)
  {
    return;
  }
  sqlite3_close(m_db);
}

void DataLayer::insert_contact(ContactInfo info, ContactLoc loc)
{}

void DataLayer::update_contact(ContactInfo info, ContactLoc loc)
{}

void DataLayer::delete_contact(int contact_id)
{}

void DataLayer::search_contact_by_name(std::string name, ContactInfo *info, ContactLoc *loc)
{}
