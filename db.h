#ifndef DB_H
#define DB_H
#include <stdlib.h>
#include <cstring>
#include <sys/types.h>
#include <errno.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <pqxx/pqxx>
#include "user.h"
class data_base
{
	enum {buf_len = 512};
	enum {max_num_of_separators = 7};
	enum {set_name = 1, set_password = 2, set_uid = 3, set_gid = 4, set_comment = 5, set_home = 6, set_interpretator = 7};
	char sql[buf_len];
	const char* create_db_sql = "CREATE DATABASE ";
	const char* select_dbs_sql = "SELECT datname FROM pg_database";
	const char* default_data_base = "dbname=test_erp user=gacy password=gacy1996 host=localhost port=5432";
	const char* src_path = "/etc/passwd";
	struct pos
	{
		int start;
		int curr_pos;
		pos()
		{
			start = 0;
			curr_pos = 0;
		}
	};
	pqxx::connection* nc;
	void run_transaction(pqxx::nontransaction& w, const char* sql_query);
	pqxx::result run_transaction(pqxx::connection* c, const char* sql_query);
	void check_data_base_existence(pqxx::connection& c, const char* sql_query, const char* db_name, int& ok);
	void generate_string(char* buffer, const char* arg1, ...);
	void start_new_connection(const char* db_name);
	void open_src(int& fd);
	void close_src(int fd);
	void read_from_src(int fd, char* buf, size_t size);
	void choose_option(int option_value, user& u, const char* buf, pos& p);
	void parse(const char* buf);
public:	
	data_base(const char* db_name);
	void populate_table();
	pqxx::result query(const char* sql_query);
	~data_base();
};
#endif
