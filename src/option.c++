#include "option.h++"


namespace ia
{
	option::option( void )
			:
			option__little	( 0 ) ,
			option__big		( string_t( ) ) ,
			option__require	( ia::option::requires::none ) ,
			option__type	( ia::option::types::unknown ) ,
			option__values	( )
	{ }

	option::option( const char_t &					little ,
					const string_t &				big ,
					const ia::option::requires &	require ,
					const ia::option::types &		type )
			:
			option__little	( little ) ,
			option__big		( big ) ,
			option__require	( require ) ,
			option__type	( type ) ,
			option__values	( )
	{ }

	option::~option( void )
	{ }

	char_t option::little( void ) const
	{
		return option__little;
	}

	void option::little( const char_t & value )
	{
		option__little = value;
	}

	string_t option::big( void ) const
	{
		return option__big;
	}

	void option::big( const string_t & value )
	{
		option__big = value;
	}

	ia::option::requires option::require( void ) const
	{
		return option__require;
	}

	void option::require( const ia::option::requires & value )
	{
		option__require = value;
	}

	ia::option::types option::type( void ) const
	{
		return option__type;
	}

	void option::type( const ia::option::types & value )
	{
		option__type = value;
	}

	::option option::getgnuopt( void ) const
	{
		::option opt = { nullptr , 0 , nullptr , 0 };

		if ( option__little )
		{
			opt.name    = ( option__big.empty( ) ) ? ( nullptr ) : ( option__big.c_str( ) );
			opt.has_arg = static_cast<int_t>( option__require );
			opt.flag    = nullptr;
			opt.val     = option__little;
		}

		return opt;
	}

	void option::addoptvalue( const string_t & value )
	{
		option__values.insert( option__values.end( ) , value );
	}

	string_t option::str( void ) const
	{
		string_t optstr;
		string_t delim( ( option__values.size( ) > size_t( 1 ) ) ? ( " " ) : ( "" ) );
		for ( ia::optvalues::const_iterator i = option__values.cbegin( ) ; i != option__values.cend( ) ; ++i )
		{
			optstr = optstr + ( *i ) + delim;
		}

		return optstr;
	}

	std::ostream & operator <<( std::ostream & stream , const ia::option & opt )
	{
		stream << opt.option__big << " :";
		for ( ia::optvalues::const_iterator i = opt.option__values.cbegin( ) ; i != opt.option__values.cend( ) ; ++i )
		{
			stream << ' ' << ( *i );
		}

		return stream;
	}
}