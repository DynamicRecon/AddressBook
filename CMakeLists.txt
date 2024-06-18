cmake_minimum_required(VERSION 3.24)
project(AddressBook VERSION 0.0.1)

set(wxBUILD_SHARED OFF)
option(with-qt ON)

set(SOURCES
        src/Models/Settings.hpp
        src/Models/Settings.cpp
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

add_subdirectory(lib/wxWidgets)
add_subdirectory(lib/sqlite3)

add_executable(AddressBook ${SOURCES})


target_include_directories(AddressBook 
	PUBLIC
	   ${PROJECT_SOURCE_DIR}/include
	   ${PROJECT_SOURCE_DIR}/lib/wxWidgets/include
	PRIVATE
	   ${PROJECT_SOURCE_DIR}/src
   )

target_link_libraries(AddressBook 
                      PUBLIC
                       wx::net wx::core wx::base
                      PRIVATE 
                        libsqlite3)
