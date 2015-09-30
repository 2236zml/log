#ifndef __LOG_H__
#define __LOG_H__

#include <cassert>
#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>
using namespace std;

#include <boost/thread.hpp>
#include <boost/date_time.hpp>
#include <boost/timer.hpp>

/*
	1.Display log information on cout or into log file.
	2.Thread safety.
	3.Include time, lose time, thread id, file line and log level
	for information.
   */

enum LogLevel{
	Trace,
	Debug,
	Info,
	Warn,
	Error,
	Fatal
};

class log_t{
public:
	log_t();
	log_t& test();
	log_t& set_log_file( 
			const string& log_file_name 
			);

	log_t& use_log_file();
	log_t& unuse_log_file();
	log_t& use_cout();
	log_t& unuse_cout();

	log_t& set_level(
			LogLevel log_level
			);

	log_t& output_level();

	template <typename T>
	log_t& operator()( const T& t )
	{
		if( _is_use_cout )
		{
			cout << t;
			cout.flush();
		}
		
		if( _is_use_log_file )
		{
			if( !_log_file )
				throw "Can not open log file.";

			_log_file << t;
			_log_file.flush();
		}

		_last_log_info << t;

		return *this;
	}

	log_t& operator()();

private:
	//	Return log level string.
	string _get_level_str();

private:
	LogLevel		_level;
	//	Output log to cout by default.
	bool			_is_use_log_file;
	bool			_is_use_cout;
	//	Output log information to this file.
	ofstream		_log_file;	
	//	Record last log information for opeator();
	ostringstream	_last_log_info;
};

typedef log_t Log;

class log_singleton{
public:
	static Log& get_instance();
private:
	log_singleton();
	log_singleton( const log_singleton& );
	log_singleton& operator = ( const log_singleton& );
	static Log _log;
};


#define glog log_singleton::get_instance()

#define log_trace	glog.set_level( Trace ).output_level()( " File:" )( __FILE__ )( " Line:" )( __LINE__ )( " " )
#define log_debug	glog.set_level( Debug ).output_level()( " File:" )( __FILE__ )( " Line:" )( __LINE__ )( " " )
#define log_info	glog.set_level( Info ).output_level()( " File:" )( __FILE__ )( " Line:" )( __LINE__ )( " " )
#define log_warn	glog.set_level( Warn ).output_level()( " File:" )( __FILE__ )( " Line:" )( __LINE__ )( " " )
#define log_error	glog.set_level( Error ).output_level()( " File:" )( __FILE__ )( " Line:" )( __LINE__ )( " " )
#define log_fatal	glog.set_level( Fatal ).output_level()( " File:" )( __FILE__ )( " Line:" )( __LINE__ )( " " )

#endif 
