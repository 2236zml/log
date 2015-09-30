#include "log.h"

log_t::log_t()
	:_level( Trace ),
	_is_use_log_file( false ),
	_is_use_cout( true )
{
}

log_t& log_t::test()
{
	cout << "test start" << endl;

	return *this;
}

log_t& log_t::set_log_file( 
	const string& log_file_name 
	)
{
	assert( !log_file_name.empty()	
			&& "log_t::set_log_file::log_file_name didn't empty." );

	if( _log_file.is_open() )
		_log_file.close();
	
	_log_file.open( log_file_name.c_str() );
	
	if( !_log_file )
		throw "Can not open log file.";

	assert( _log_file.is_open()
			&& "log_t::set_log_file::log_file_name should be open now.");

	return *this;
}

log_t& log_t::use_log_file()
{
	if( !_log_file.is_open() )
		_log_file.open( "default.log" );	

	if( !_log_file )
		throw "Can not open file default.log";

	_is_use_log_file = true;

	return *this;
}

log_t& log_t::unuse_log_file()
{
	_is_use_log_file = false;

	return *this;
}

log_t& log_t::use_cout()
{
	_is_use_cout = true;	

	return *this;
}

log_t& log_t::unuse_cout()
{
	_is_use_cout = false;	
	
	return *this;
}


log_t& log_t::set_level(
			LogLevel log_level
			)
{
	_level = log_level;

	return *this;
}

log_t& log_t::output_level()
{
	if( _is_use_cout )
	{
		cout << _get_level_str();	
		cout.flush();
	}

	if( _is_use_log_file )
	{
		if( !_log_file )
			throw "Cannot open log file";

		_log_file << _get_level_str();
		_log_file.flush();
	}

	return *this;
}


log_t& log_t::operator()()
{
	operator()( "\n" );

	if( Fatal <= _level )
	{
		throw runtime_error( 
				string( "Fatal log:" ) +  
				_last_log_info.str()
				);
	}

	_last_log_info.str( "" );
	_last_log_info.clear();

	return *this;
}

string log_t::_get_level_str()
{
	if( Trace == _level )
		return "Trace";
	else if( Debug == _level )
		return "Debug";
	else if( Info == _level )
		return "Info";
	else if( Warn == _level )
		return "Warn";
	else if( Error == _level )
		return "Error";
	else if( Fatal == _level )
		return "Fatal";
	else
		throw "Error log level.";
}

//	---	log_singletion	---

Log& log_singleton::get_instance()
{
	return _log;
}

Log log_singleton::_log;

