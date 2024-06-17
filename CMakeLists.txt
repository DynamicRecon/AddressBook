cmake_minimum_required(VERSION 3.24)
project(AddressBook VERSION 0.0.1)

set(wxBUILD_SHARED OFF)
option(with-qt ON)
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
#set(wxWidgets _CONFIGURATION mswu)
#find_package(wxWidgets REQUIRED COMPONENTS core base)
#if(wxWidgets_USE_FILE) # not defined in CONFIG mode
#    include(${wxWidgets_USE_FILE})
#endif()



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
#if(X11_FOUND)
#  add_definitions(-DCMAKE_HAS_X)
# include_directories(${X11_INCLUDE_DIR})
#  target_link_libraries(AddressBook ${X11_LIBRARIES})
#endif()

#find_package (SQLITE3)
#if (SQLITE3_FOUND)
#  include_directories(${SQLITE3_INCLUDE_DIRS})
#  target_link_libraries (AddressBook ${SQLITE3_LIBRARIES})
#endif (SQLITE3_FOUND)
