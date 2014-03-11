//=============================================================================
//
 // file :        LibHdb++.h
//
// description : Include for the LibHdb library.
//
// Author: Graziano Scalamera
//
// $Revision: 1.4 $
//
// $Log: LibHdb++.h,v $
// Revision 1.4  2014-03-07 13:15:00  graziano
// added remove_Attr, start_Attr, stop_Attr
// removed _HDBEVENTDATA
//
// Revision 1.3  2014-02-06 14:35:12  graziano
// added api for CM
//
// Revision 1.2  2013-09-24 08:48:37  graziano
// support for HdbEventData
//
// Revision 1.1  2013-09-02 12:25:36  graziano
// libhdb refurbishing
//
//
//
//=============================================================================

#ifndef _LIB_HDB_H
#define _LIB_HDB_H

#include <tango.h>
#include <vector>


class AbstractDB
{

public:


	virtual int insert_Attr(Tango::EventData *data) = 0;

	virtual int configure_Attr(string name, int type/*DEV_DOUBLE, DEV_STRING, ..*/, int format/*SCALAR, SPECTRUM, ..*/, int write_type/*READ, READ_WRITE, ..*/) = 0;

	virtual int remove_Attr(string name) = 0;

	virtual int start_Attr(string name) = 0;

	virtual int stop_Attr(string name) = 0;

	virtual ~AbstractDB() {}

};

class DBFactory
{

public:

	virtual AbstractDB* create_db(string host, string user, string password, string dbname, int port) = 0;

};

class HdbClient
{

private:
	AbstractDB *db;
	DBFactory *db_factory;

	DBFactory *getDBFactory();

public:
#if _DB_AT_RUNTIME
	HdbClient(string dbtype,string host, string user, string password, string dbname, int port);
#else
	HdbClient(string host, string user, string password, string dbname, int port);
#endif

	int insert_Attr(Tango::EventData *data);

	int configure_Attr(string name, int type/*DEV_DOUBLE, DEV_STRING, ..*/, int format/*SCALAR, SPECTRUM, ..*/, int write_type/*READ, READ_WRITE, ..*/);

	int remove_Attr(string name);

	int start_Attr(string name);

	int stop_Attr(string name);

	~HdbClient();

};


/*//MYSQL:
class HdbMySQLFactory : public DBFactory
{

public:
	virtual AbstractDB* create_db(string host, string user, string password, string dbname, int port);

};

//TODO: create factories for other DB engine*/




#endif