project(AddressBook)
cmake_minimum_required(VERSION 2.8)

set(wxWidgets _CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})



set(SOURCES
        src/Models/ContactLoc.hpp
	src/Models/ContactLoc.cpp
	src/Models/ContactInfo.hpp
	src/Models/ContactInfo.cpp
	src/DataLayer.hpp
	src/DataLayer.cpp
	src/AddressBookFrame.hpp
        src/AddressBookFrame.cpp
	src/AddressBookApp.cpp
)

add_executable(AddressBook ${SOURCES})

target_include_directories(AddressBook 
	PRIVATE
	   ${PROJECT_SOURCE_DIR}/include
	   ${PROJECT_SOURCE_DIR}/src
   )

target_link_libraries(StarTextEditor ${wxWidgets_LIBRARIES})
