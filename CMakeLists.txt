cmake_minimum_required(VERSION 3.0)
project(AddressBook VERSION 0.0.1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(wxWidgets _CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})




set(SOURCES
        src/Models/ContactLoc.hpp
	src/Models/ContactLoc.cpp
	src/Models/ContactInfo.hpp
	src/Models/ContactInfo.cpp
	src/DataAccess/DataLayer.hpp
	src/DataAccess/DataLayer.cpp
	src/AddressBookFrame.hpp
        src/AddressBookFrame.cpp
	src/AddressBookApp.cpp
)

add_executable(AddressBook ${SOURCES})


target_include_directories(AddressBook 
	PRIVATE
	   ${PROJECT_SOURCE_DIR}/src
   )

target_link_libraries(AddressBook ${wxWidgets_LIBRARIES})

find_package (SQLITE3)
if (SQLITE3_FOUND)
  include_directories(${SQLITE3_INCLUDE_DIRS})
  target_link_libraries (AddressBook ${SQLITE3_LIBRARIES})
endif (SQLITE3_FOUND)
