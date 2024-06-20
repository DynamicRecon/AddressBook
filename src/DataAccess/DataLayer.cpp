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

bool DataLayer::is_opened()
{
  return m_opened;
}

int DataLayer::get_last_row_id(char *name)
{
  return m_last_row_id;
}


std::string DataLayer::get_errors()
{
  std::string error_msg(m_ErrMsg);
  return error_msg;
}

void DataLayer::create_db_contacts()
{
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
    "FOREIGN KEY(CONTACT_ID) REFERENCES ContactInfo(ID));";

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



void DataLayer::insert_contact_info(char *name, char* email, char *phonenum)
{
  sqlite3_stmt *stmt;
  int id;
  const char *sql = "INSERT INTO ContactInfo(NAME, EMAIL, PHONENUMBER) VALUES(?, ?, ?);";
  m_fail = sqlite3_open(m_path.c_str(), &m_db);
  m_opened = true;
  if (m_fail)
  {
    m_opened = false;
    return;
  } 
  
  m_fail = sqlite3_prepare_v2(m_db, sql, -1, &stmt, NULL);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error preparing insert: %s\n", sqlite3_errmsg(m_db));
    return;
  }

  m_fail = sqlite3_bind_text(stmt, 1, name, strlen(name), NULL);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error binding name: %s\n", sqlite3_errmsg(m_db));
    return;
  }
  
  m_fail = sqlite3_bind_text(stmt, 2, email, strlen(email), NULL);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error binding email: %s\n", sqlite3_errmsg(m_db));
    return;
  }

  m_fail = sqlite3_bind_text(stmt, 3, phonenum, strlen(phonenum), NULL);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error binding phone number: %s\n", sqlite3_errmsg(m_db));
    return;
  }

  m_fail = sqlite3_step(stmt);
  if(m_fail != SQLITE_DONE)
  {
    fprintf(stderr, "Insert of contact information did not finish: %s\n", sqlite3_errmsg(m_db));
    return;
  }

  m_last_row_id = sqlite3_last_insert_rowid(m_db);

  sqlite3_finalize(stmt);  
  sqlite3_close(m_db);
}

void DataLayer::insert_contact_loc(int contact_id, char *address, char *city, char *state, char *zip)
{
  sqlite3_stmt *stmt;
  int id;
  const char *sql = "INSERT INTO ContactLoc(CONTACT_ID, ADDRESS, CITY, STATE, ZIP) VALUES(?, ?, ?, ?, ?);";
  m_fail = sqlite3_open(m_path.c_str(), &m_db);
  m_opened = true;
  if (m_fail)
  {
    m_opened = false;
    return;
  }

  m_fail = sqlite3_prepare_v2(m_db, sql, -1, &stmt, NULL);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error preparing insert: %s\n", sqlite3_errmsg(m_db));
    return;
  } 

  m_fail = sqlite3_bind_int(stmt, 1, contact_id);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error binding contact_id: %s\n", sqlite3_errmsg(m_db));
    return;
  }
  
  m_fail = sqlite3_bind_text(stmt, 2, address, strlen(address), NULL);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error binding address: %s\n", sqlite3_errmsg(m_db));
    return;
  }
  
  m_fail = sqlite3_bind_text(stmt, 3, city, strlen(city), NULL);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error binding city: %s\n", sqlite3_errmsg(m_db));
    return;
  }

  m_fail = sqlite3_bind_text(stmt, 4, state, strlen(state), NULL);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error binding state: %s\n", sqlite3_errmsg(m_db));
    return;
  }

  m_fail = sqlite3_bind_text(stmt, 5, zip, strlen(zip), NULL);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error binding zip: %s\n", sqlite3_errmsg(m_db));
    return;
  }

  m_fail = sqlite3_step(stmt);
  if(m_fail != SQLITE_DONE)
  {
    fprintf(stderr, "Insert of contact location did not finish: %s\n", sqlite3_errmsg(m_db));
    return;
  }
  
  m_last_row_id  = sqlite3_last_insert_rowid(m_db);
  sqlite3_finalize(stmt);  
  sqlite3_close(m_db);
}


void DataLayer::update_contact_info(char *name, char* email, char *phonenum)
{
  sqlite3_stmt *stmt;
  sqlite3_stmt *updated_row_stmt;
  int id;
  const char *sql = "UPDATE ContactInfo SET EMAIL = ?, PHONENUMBER = ? WHERE NAME = ?";
  m_fail = sqlite3_open(m_path.c_str(), &m_db);
  m_opened = true;
  if (m_fail)
  {
    m_opened = false;
    return;
  } 
  
  m_fail = sqlite3_prepare_v2(m_db, sql, -1, &stmt, NULL);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error preparing update contact info: %s\n", sqlite3_errmsg(m_db));
    return;
  }

  m_fail = sqlite3_bind_text(stmt, 1, email, strlen(email), NULL);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error binding email: %s\n", sqlite3_errmsg(m_db));
    return;
  }

  m_fail = sqlite3_bind_text(stmt, 2, phonenum, strlen(phonenum), NULL);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error binding phone number: %s\n", sqlite3_errmsg(m_db));
    return;
  }

  m_fail = sqlite3_bind_text(stmt, 3, name, strlen(name), NULL);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error binding name: %s\n", sqlite3_errmsg(m_db));
    return;
  }

  m_fail = sqlite3_step(stmt);
  if(m_fail != SQLITE_DONE)
  {
    fprintf(stderr, "Update of contact information did not finish: %s\n", sqlite3_errmsg(m_db));
    return;
  }

  
   
  sqlite3_finalize(stmt);
  sqlite3_close(m_db);
}

void DataLayer::update_contact_loc(int contact_id, char *address, char *city, char *state, char *zip)
{
   sqlite3_stmt *stmt;
  int id;
  const char *sql = "UPDATE ContactLoc SET ADDRESS = ?, CITY = ?, STATE = ?, ZIP = ? WHERE CONTACT_ID = ?;";
  m_fail = sqlite3_open(m_path.c_str(), &m_db);
  m_opened = true;
  if (m_fail)
  {
    m_opened = false;
    return;
  }

  m_fail = sqlite3_prepare_v2(m_db, sql, -1, &stmt, NULL);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error preparing to update contact location: %s\n", sqlite3_errmsg(m_db));
    return;
  } 

  
  m_fail = sqlite3_bind_text(stmt, 1, address, strlen(address), NULL);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error binding address: %s\n", sqlite3_errmsg(m_db));
    return;
  }
  
  m_fail = sqlite3_bind_text(stmt, 2, city, strlen(city), NULL);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error binding city: %s\n", sqlite3_errmsg(m_db));
    return;
  }

  m_fail = sqlite3_bind_text(stmt, 3, state, strlen(state), NULL);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error binding state: %s\n", sqlite3_errmsg(m_db));
    return;
  }

  m_fail = sqlite3_bind_text(stmt, 4, zip, strlen(zip), NULL);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error binding zip: %s\n", sqlite3_errmsg(m_db));
    return;
  }

  m_fail = sqlite3_bind_int(stmt, 5, contact_id);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error binding contact_id: %s\n", sqlite3_errmsg(m_db));
    return;
  }

  m_fail = sqlite3_step(stmt);
  if(m_fail != SQLITE_DONE)
  {
    fprintf(stderr, "Update of contact location did not finish: %s\n", sqlite3_errmsg(m_db));
    return;
  }

  sqlite3_finalize(stmt);  
  sqlite3_close(m_db);
}


void DataLayer::delete_contact_info(char *name)
{
  sqlite3_stmt *stmt;
  sqlite3_stmt *updated_row_stmt;
  int id;
  const char *sql = "DELETE FROM ContactInfo WHERE NAME = ?";
  m_fail = sqlite3_open(m_path.c_str(), &m_db);
  m_opened = true;
  if (m_fail)
  {
    m_opened = false;
    return;
  }

  m_fail = sqlite3_prepare_v2(m_db, sql, -1, &stmt, NULL);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error preparing delete ContactInfo: %s\n", sqlite3_errmsg(m_db));
    return;
  }

  m_fail = sqlite3_bind_text(stmt, 1, name, strlen(name), NULL);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error binding name for delete of ContactInfo: %s\n", sqlite3_errmsg(m_db));
    return;
  }

  m_fail = sqlite3_step(stmt);
  if(m_fail != SQLITE_DONE)
  {
    fprintf(stderr, "Delete of ContactInfo did not finish: %s\n", sqlite3_errmsg(m_db));
    return;
  }

  sqlite3_finalize(stmt);  
  sqlite3_close(m_db);
}

void DataLayer::delete_contact_loc(int contact_id)
{
  sqlite3_stmt *stmt;
  sqlite3_stmt *updated_row_stmt;
  int id;
  const char *sql = "DELETE FROM ContactLoc WHERE CONTACT_ID = ?";
  m_fail = sqlite3_open(m_path.c_str(), &m_db);
  m_opened = true;
  if (m_fail)
  {
    m_opened = false;
    return;
  }

  m_fail = sqlite3_prepare_v2(m_db, sql, -1, &stmt, NULL);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error preparing delete ContactLoc: %s\n", sqlite3_errmsg(m_db));
    return;
  }
  
  m_fail = sqlite3_bind_int(stmt, 1, contact_id);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error binding contact_id: %s\n", sqlite3_errmsg(m_db));
    return;
  }

  m_fail = sqlite3_step(stmt);
  if(m_fail != SQLITE_DONE)
  {
    fprintf(stderr, "Delete of ContactInfo did not finish: %s\n", sqlite3_errmsg(m_db));
    return;
  }

  sqlite3_finalize(stmt);  
  sqlite3_close(m_db);
}

void DataLayer::search_contact_info(char *name, int &contact_id, char *email, char *phone)
{
  sqlite3_stmt *stmt;
  const char *sql = "SELECT ID, NAME, EMAIL, PHONENUMBER FROM ContactInfo WHERE UPPER(NAME) = UPPER(?);";
  m_fail = sqlite3_open(m_path.c_str(), &m_db);
  m_opened = true;
  if (m_fail)
  {
    m_opened = false;
    return;
  } 

  m_fail = sqlite3_prepare_v2(m_db, sql, -1, &stmt, NULL);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error preparing search for contact info: %s\n", sqlite3_errmsg(m_db));
    return;
  } 

  m_fail = sqlite3_bind_text(stmt, 1, name, strlen(name), NULL);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error binding name: %s\n", sqlite3_errmsg(m_db));
    return;
  } 

  m_fail = sqlite3_step(stmt);
  if(m_fail == SQLITE_ROW)
  {
    contact_id = sqlite3_column_int(stmt, 0);
    strcpy(email, (char*)sqlite3_column_text(stmt, 2));
    strcpy(phone, (char*)sqlite3_column_text(stmt, 3));
  }
  sqlite3_finalize(stmt);
  sqlite3_close(m_db);
}

void DataLayer::search_contact_loc(int contact_id, char *address, char *city, char *state, char *zip)
{
  sqlite3_stmt *stmt;
  const char *sql = "SELECT ADDRESS, CITY, STATE, ZIP FROM ContactLoc WHERE CONTACT_ID = ?;";
  m_fail = sqlite3_open(m_path.c_str(), &m_db);
  m_opened = true;
  if (m_fail)
  {
    m_opened = false;
    return;
  } 

  m_fail = sqlite3_prepare_v2(m_db, sql, -1, &stmt, NULL);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error preparing search for contact location: %s\n", sqlite3_errmsg(m_db));
    return;
  } 

  m_fail = sqlite3_bind_int(stmt, 1, contact_id);
  if(m_fail != SQLITE_OK)
  {
    fprintf(stderr, "Error binding contact_id: %s\n", sqlite3_errmsg(m_db));
    return;
  } 
  m_fail = sqlite3_step(stmt);
  if(m_fail == SQLITE_ROW)
  {
    strcpy(address, (char*)sqlite3_column_text(stmt, 0));
    strcpy(city, (char*)sqlite3_column_text(stmt, 1));
    strcpy(state, (char*)sqlite3_column_text(stmt, 2));
    strcpy(zip, (char*)sqlite3_column_text(stmt, 3));
  }
  sqlite3_finalize(stmt);
  sqlite3_close(m_db);
}
