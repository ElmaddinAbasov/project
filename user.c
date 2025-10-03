#include "user.h"

int user::length(const char* string)
{
	int len;
	len = 0;
	while (*(string + len) != '\n')
		len++;
	return len;
}

user::user()
{

}

user::user(const char* nm, const char* pw, const char* usrid, const char* grpid, const char* cm, const char* hm, const char* intr)
{
	strcpy(name, nm);
	strcpy(password, pw);
	strcpy(uid, usrid);
	strcpy(gid, grpid);
	strcpy(comment, cm);
	strcpy(home, hm);
	strcpy(interpretator, intr);
}

void user::set_name(const char* nm, int n)
{
	size_t len;
	len = length(nm);
	if (len >= buf_cap)
	{
		fprintf(stderr, "ERROR: void user::set_name(const char* nm, int n) -> nm len is bigger than buf_cap size\n");
		exit(1);
	}
	strncpy(name, nm, n);
	*(name + n) = 0;
}

void user::set_password(const char* passwd, int n)
{
        size_t len;
        len = length(passwd);
        if (len >= buf_cap)
        {
                fprintf(stderr, "ERROR: void user::set_password(const char* passwd, int n) -> passwd len is bigger than buf_cap size\n");
                exit(2);
        }
        strncpy(password, passwd, n);
	*(password + n) = 0;
}

void user::set_uid(const char* usrid, int n)
{
        size_t len;
        len = length(usrid);
        if (len >= buf_cap)
        {
                fprintf(stderr, "ERROR: void user::set_uid(const char* usrid, int n) -> usrid len is bigger than buf_cap size\n");
                exit(3);
        }
        strncpy(uid, usrid, n);
	*(uid + n) = 0;
}

void user::set_gid(const char* grpid, int n)
{
        size_t len;
        len = length(grpid);
        if (len >= buf_cap)
        {
                fprintf(stderr, "ERROR: void user::set_gid(const char* grpid, int n) -> grpid len is bigger than buf_cap size\n");
                exit(3);
        }
        strncpy(gid, grpid, n);
	*(gid + n) = 0;
}

void user::set_comment(const char* cm, int n)
{
        size_t len;
        len = length(cm);
        if (len >= buf_cap)
        {
                fprintf(stderr, "ERROR: void user::set_comment(const char* cm, int n) -> cm len is bigger than buf_cap size\n");
                exit(4);
        }
        strncpy(comment, cm, n);
	*(comment + n) = 0;
}

void user::set_home(const char* hm, int n)
{
        size_t len;
        len = length(hm);
        if (len >= buf_cap)
        {
                fprintf(stderr, "ERROR: void user::set_home(const char* hm, int n) -> hm len is bigger than buf_cap size\n");
                exit(5);
        }
        strncpy(home, hm, n);
	*(home + n) = 0;
}
        
void user::set_interpretator(const char* inter, int n)
{
        size_t len;
        len = length(inter);
        if (len >= buf_cap)
        {
                fprintf(stderr, "ERROR: void user::set_interpretator(const char* inter, int n) -> inter len is bigger than buf_cap size\n");
                exit(5);
        }
        strncpy(interpretator, inter, n);
	*(interpretator + n) = 0;
}

const char* user::get_name() const
{
	return name;
}

const char* user::get_password() const
{
        return password;
}

const char* user::get_uid() const
{
        return uid;
}

const char* user::get_gid() const
{
        return gid;
}

const char* user::get_comment() const
{
	return comment;
}
        
const char* user::get_home() const
{
	return home;
}
        
const char* user::get_interpretator() const
{
	return interpretator;
}

void user::reset()
{
	*name = 0;
	*password = 0;
	*uid = 0;
	*gid = 0;
	*comment = 0;
	*home = 0;
	*interpretator = 0;
}

user::~user()
{

}
