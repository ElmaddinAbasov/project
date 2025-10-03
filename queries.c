#include "queries.h"

const char* queries[] = {"CREATE TABLE IF NOT EXISTS my_table ("
                                   "id SERIAL PRIMARY KEY,"
                                   "name VARCHAR(255) NOT NULL,"
                                   "password VARCHAR(255) NOT NULL,"
                                   "uid VARCHAR(255) NOT NULL,"
                                   "gid VARCHAR(255) NOT NULL,"
                                   "comment VARCHAR(255) NOT NULL,"
                                   "home VARCHAR(255) NOT NULL,"
                                   "interpretator VARCHAR(255) NOT NULL"
                                   ");", "SELECT name FROM my_table;" };     
