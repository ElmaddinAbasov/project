#ifndef USER_H
#define USER_H
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <cstring>
class user
{
	enum {buf_cap = 255};
	char separator = ':';
	char buffer[BUFSIZ];
	char name[buf_cap];
	char password[buf_cap];
	char uid[buf_cap];
	char gid[buf_cap];
	char comment[buf_cap];
	char home[buf_cap];
	char interpretator[buf_cap];
	int length(const char* string);
public:	
	user();
	user(const char* nm, const char* pw, const char* usrid, const char* grpid, const char* cm, const char* hm, const char* intr);
	void set_name(const char* nm, int n=0);
	void set_password(const char* passwd, int n=0);
	void set_uid(const char* usrid, int n=0);
	void set_gid(const char* grpid, int n=0);
	void set_comment(const char* cm, int n=0);
	void set_home(const char* hm, int n=0);
	void set_interpretator(const char* hm, int n=0);
	const char* get_name() const;
	const char* get_password() const;
	const char* get_uid() const;
	const char* get_gid() const;
	const char* get_comment() const;
	const char* get_home() const;
	const char* get_interpretator() const;
	void reset();
	~user();
};
#endif
