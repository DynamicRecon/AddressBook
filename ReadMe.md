# Simple Address Book

## Description
   A simple address book CRUD Application. It stores name, address, city, state, zip as well as phonenumber and email into a sqlite3 database.

## Requirements
 * GTK3 (On linux if not installed. for wxWidgets included as submodule)
 * cmake >= 3.0
 * gcc 13.2.0

## Build and Install

* This project has wxWidgets as a submodule. So First:
      ** git submodule init
      ** git submodule update

* Then build (may take a while):
     ** mkdir build
     ** cd build
     ** cmake ..
     ** make



