set(SOURCES sqlite3.c)
   
add_library(libsqlite3 STATIC ${SOURCES})

target_include_directories(libsqlite3
   PUBLIC
     ${PROJECT_SOURCE_DIR}/include
)
