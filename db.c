#include "db.h"

void data_base::run_transaction(pqxx::nontransaction& w, const char* sql_query)
{
	try
	{
		pqxx::result res = w.exec(sql_query);
		w.commit();
	}
	catch (const pqxx::sql_error& e)
	{
		fprintf(stderr, "ERROR: Failed to execute %s query\n", sql_query);
		exit(1);
	}
}

#if 0
void data_base::run_transaction(pqxx::connection* c, const char* sql_query)
#else
pqxx::result data_base::run_transaction(pqxx::connection* c, const char* sql_query)
#endif
{
	pqxx::result res;
	try
	{
		pqxx::work w(*c);
		res = w.exec(sql_query);
		w.commit();
	}
	catch (const pqxx::broken_connection& e)
        {
                        fprintf(stderr, "ERROR: void data_base::run_transaction(pqxx::connection& c, const char* sql_query), query - %s. Failed to connect to a database\n", sql_query);
                        exit(2);
        }	
	catch (const pqxx::sql_error& e)
	{
	fprintf(stderr, "ERRPR: void data_base::run_transaction(pqxx::connection& c, const char* sql_query), query - %s\n",
				sql_query);
		exit(3);
	}
	return res;
}

void data_base::check_data_base_existence(pqxx::connection& c, const char* sql_query, const char* db_name, int& ok)
{
	try
	{
		pqxx::work w(c);
		pqxx::result r = w.exec(sql_query);
		w.commit();
		for (const pqxx::row row : r)
		{
			if (0 == strcmp(row[0].as<const char*>(), db_name))
			{
				ok = 1;
				return;
			}
		}
	}
	catch (const pqxx::sql_error& e)
	{
		fprintf(stderr, "ERROR: failed to execute %s query\n", sql_query);
		exit(4);
	}
}

void data_base::generate_string(char* buffer, const char* arg1, ...)
{
        va_list vl;
        const char* p;
        size_t len;
        va_start(vl, arg1);
        for (p = arg1; p; p = va_arg(vl, const char*))
                strcat(buffer, p);
        len = strlen(buffer);
        *(buffer + len) = 0;
        printf("DEBUG PRINT - %s\n", buffer);
        va_end(vl);
}

void data_base::start_new_connection(const char* db_name)
{
	errno = 0;
	try
	{
		generate_string(sql, "dbname=", NULL);
		generate_string(sql, db_name, " user=gacy password=gacy1996 host=localhost port=5432", NULL);
		nc = new pqxx::connection("dbname=users user=gacy password=gacy1996 host=localhost port=5432");
	}
	catch (const pqxx::broken_connection& e)
	{
                        fprintf(stderr, "ERROR: void data_base::start_new_connection(const char* db_name). Failed to connect to a database\n");
                        exit(5);
	}
}

void data_base::open_src(int& fd)
{
	errno = 0;
	fd = open(src_path, O_RDONLY);
	if (fd == -1)
	{
		perror("ERROR: void data_base::open_src(int& fd)-> fd = open(src_path, O_RDONLY), failed to open a file\n");
		exit(6);
	}
}

void data_base::close_src(int fd)
{
	int res;
	errno = 0;
	res = close(fd);
	if (res == -1)
	{
		perror("ERROR: void data_base::close_src(int& fd)-> res = close(fd), failed to close a file\n");
		exit(7);
	}
}

void data_base::read_from_src(int fd, char* buf, size_t size)
{
	ssize_t cnt;
	errno = 0;
	cnt = read(fd, buf, size);
	if (cnt == -1)
	{
		perror("ERROR: void data_base::read_from_src(int fd, char* buf, size_t size)-> cnt = read(fd), failed to close a file\n");
		exit(8);
	}
	*(buf + cnt) = 0;
}

void data_base::choose_option(int option_value, user& u, const char* buf, pos& p)
{
	switch (option_value)
        {
		case set_name :
			u.set_name(buf + p.start, p.curr_pos - p.start);
                        break;
                case set_password :
                        u.set_password(buf + p.start, p.curr_pos - p.start);
                        break;
                case set_uid :
                        u.set_uid(buf + p.start, p.curr_pos - p.start);
                        break;
                case set_gid :
                        u.set_gid(buf + p.start, p.curr_pos - p.start);
                        break;
                case set_comment :
                        u.set_comment(buf + p.start, p.curr_pos - p.start);
                        break;
                case set_home :
                        u.set_home(buf + p.start, p.curr_pos - p.start);
                        break;
                case set_interpretator :
                        u.set_interpretator(buf + p.start, p.curr_pos - p.start);
                        break;
         }
}

void data_base::parse(const char* buf)
{
	user u;	
	int len, i, num_of_separators;
	pos p;
	len = strlen(buf);
	num_of_separators = 0;
	for (i = 0; i < len; i++)
	{
		p.curr_pos = i;
		if (*(buf + i) == ':' || *(buf + i) == '\n')
		{
			num_of_separators++;
			choose_option(num_of_separators, u, buf, p);
			p.start = p.curr_pos + 1;
		}
		if (num_of_separators == max_num_of_separators)
		{
			try
			{
				pqxx::work w(*nc);
				pqxx::params params;
				params.append(u.get_name());
				params.append(u.get_password());
				params.append(u.get_uid());
				params.append(u.get_gid());
				params.append(u.get_comment());
				params.append(u.get_home());
				params.append(u.get_interpretator());
				pqxx::result r = w.exec_params("INSERT INTO my_table (name, password, uid, gid, comment, home, interpretator) VALUES ($1, $2, $3, $4, $5, $6, $7)", params);
				w.commit();
				u.reset();
				num_of_separators = 0;
			}
			catch (const pqxx::sql_error& e)
			{
				fprintf(stderr, "ERROR: data_base::parse(const char* buf) - %s\n", e.what());
				exit(9);
			}
		}
	}
}

data_base::data_base(const char* db_name)
{
	size_t len;
	int ok;
	try
	{
		pqxx::connection c(default_data_base);
		strcpy(sql, create_db_sql);
		strcat(sql, db_name);
		len = strlen(sql);
		*(sql + len) = 0;
		ok = 0;
		check_data_base_existence(c, select_dbs_sql, db_name, ok);
		if (!ok)
		{
			pqxx::nontransaction w(c);
			run_transaction(w, sql);
		}
		c.close();
		*sql = 0;
		start_new_connection(db_name);
	}
	catch (const pqxx::broken_connection& e)
	{
		fprintf(stderr, "ERROR: Failed to connect to a test_erp database\n data_base::data_base()");
		exit(11);
	}
}

data_base::~data_base()
{
	nc->close();
	delete nc;
}

void data_base::populate_table()
{
        int fd;
        char* buf;
        open_src(fd);
        errno = 0;
        buf = (char*)malloc(BUFSIZ);
        if (!buf)
        {
                perror("ERROR: void data_base::populate_database() -> buf = (char*)malloc(BUFSIZ), failed to allocate buffer\n");
                exit(10);
        }
        read_from_src(fd, buf, BUFSIZ);
        close_src(fd);
        parse(buf);
        free(buf);
}

pqxx::result data_base::query(const char* sql_query)
{
	pqxx::result r = run_transaction(nc, sql_query);	
	return r;
}
