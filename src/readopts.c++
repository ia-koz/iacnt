#include "readopts.h++"


namespace ia
{
	readopts::readopts( void )
			:
			readopts__opts( ) ,
			readopts__argc( int_t( 0 ) ) ,
			readopts__argv( nullptr ) ,
			readopts__envp( nullptr )
	{ }

	readopts::readopts( const int_t & argc ,
						const char_t * const argv[] )
			:
			readopts__opts( ) ,
			readopts__argc( argc ) ,
			readopts__argv( const_cast<char_t * const *>( argv ) ) ,
			readopts__envp( nullptr )
	{ }

	readopts::readopts( const int_t & argc ,
						const char_t * const argv[] ,
						const char_t * const envp[] )
			:
			readopts__opts( ) ,
			readopts__argc( argc ) ,
			readopts__argv( const_cast<char_t * const *>( argv ) ) ,
			readopts__envp( const_cast<char_t * const *>( envp ) )
	{ }

	readopts::~readopts( void )
	{ }

	void readopts::addopt( ia::option * opt )
	{
		readopts__opts.push_back( opt );
	}

	void readopts::getoptarg( const ia::optslist & list , string_t & optstr , ia::gnuoptvec & optarr ) const
	{
		for ( ia::optslist::const_iterator i = readopts__opts.cbegin( ) ; i != readopts__opts.cend( ) ; ++i )
		{
			optarr.push_back( ( *i )->getgnuopt( ) );
			optstr += ( *i )->little( );
			switch ( ( *i )->require( ) )
			{
				case ia::option::requires::require :
				{
					optstr += ':';
					break;
				}
				case ia::option::requires::optional :
				{
					optstr += "::";
					break;
				}
				default:
				{
				}
			}
		}
	}

	void readopts::getapparg( void )
	{
		ia::optslist::iterator optapp;
		for ( ia::optslist::iterator i = readopts__opts.begin( ) ; i != readopts__opts.end( ) ; ++i )
		{
			if ( ( ( *i )->type( ) & ia::option::types::app ) == ia::option::types::app )
			{
				optapp = i;
				break;
			}
		}

		if ( ::optind < readopts__argc )
		{
			( *optapp )->addoptvalue( readopts__argv[::optind++] );
		}
	}

	void readopts::getargarg( void )
	{
		ia::optslist::iterator optapp;
		for ( ia::optslist::iterator i = readopts__opts.begin( ) ; i != readopts__opts.end( ) ; ++i )
		{
			if ( ( ( *i )->type( ) & ia::option::types::arg ) == ia::option::types::arg )
			{
				optapp = i;
				break;
			}
		}

		if ( ::optind < readopts__argc )
		{
			while ( ::optind < readopts__argc )
			{
				( *optapp )->addoptvalue( readopts__argv[::optind++] );
			}
		}
	}

	void readopts::run( void )
	{
		if ( readopts__argc == 0 )
		{
			return;
		}

		string_t gnuoptstr;
		ia::gnuoptvec gnuoptarr;
		getoptarg( readopts__opts , gnuoptstr , gnuoptarr );

		int_t c = int_t( 0 );
		while ( true )
		{
			int option_index = 0;
			c = ::getopt_long( readopts__argc , readopts__argv , gnuoptstr.c_str( ) , gnuoptarr.data( ) ,
							   &option_index );

			if ( c == -1 )
			{
				break;
			}

			bool option_find = false;
			for ( ia::optslist::const_iterator i = readopts__opts.cbegin( ) ; i != readopts__opts.cend( ) ; ++i )
			{
				if ( ( *i )->little( ) == char_t( c ) )
				{
					option_find = true;
					if ( ( *i )->require( ) == ia::option::requires::none )
					{
						( *i )->addoptvalue( "1" );
					}
					else if ( ( *i )->require( ) == ia::option::requires::require )
					{
						( *i )->addoptvalue( ::optarg );
					}
					else if ( ( *i )->require( ) == ia::option::requires::optional )
					{
						( *i )->addoptvalue( ( ( ::optarg ) ? ( ::optarg ) : ( "1" ) ) );
					}
				}
			}
			if ( !option_find )
			{
				::abort( );
			}
		}

		getapparg( );
		getargarg( );
	}
}
