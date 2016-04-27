#ifndef OPTION_HPP
#define OPTION_HPP

#include <getopt.h>
#include <vector>
#include <iostream>

#include "typedefs.h++"


namespace ia
{
	typedef std::vector<string_t>		optvalues;

	class option
	{
		public:

		enum class requires : byte_t
		{
			none		= byte_t( no_argument ) ,
			require		= byte_t( required_argument ) ,
			optional	= byte_t( optional_argument )
		};

		enum class types : byte_t
		{
			unknown		= byte_t( 0x00 ) ,
			app			= byte_t( 0x01 ) ,
			arg			= byte_t( 0x02 ) ,
			opt			= byte_t( 0x04 ) ,
			flag		= byte_t( 0x08 ) ,
			nil			= byte_t( 0x10 ) ,
		};


		public:

		option( void );

		option( const char_t &					little ,
				const string_t &				big ,
				const ia::option::requires &	require ,
				const ia::option::types &		type );

		virtual ~option( void );


		char_t							little( void ) const;
		void							little( const char_t & value );

		string_t						big( void ) const;
		void							big( const string_t & value );

		ia::option::requires			require( void ) const;
		void							require( const ia::option::requires & value );

		ia::option::types				type( void ) const;
		void							type( const ia::option::types & value );

		::option						getgnuopt( void ) const;

		void							addoptvalue( const string_t & value );


		string_t						str( void ) const;

		friend std::ostream &			operator <<( std::ostream &			stream ,
													 const ia::option &		opt );


		private:

		char_t							option__little;
		string_t						option__big;
		ia::option::requires			option__require;
		ia::option::types				option__type;
		ia::optvalues					option__values;
	};
}

inline constexpr ia::option::types operator&( ia::option::types left , ia::option::types right )
{
	return static_cast<ia::option::types>( static_cast<byte_t>( left ) & static_cast<byte_t>( right ) );
}

inline constexpr ia::option::types operator|( ia::option::types left , ia::option::types right )
{
	return static_cast<ia::option::types>( static_cast<byte_t>( left ) | static_cast<byte_t>( right ) );
}

inline constexpr ia::option::types operator^( ia::option::types left , ia::option::types right )
{
	return static_cast<ia::option::types>( static_cast<byte_t>( left ) ^ static_cast<byte_t>( right ) );
}

inline constexpr ia::option::types operator~( ia::option::types left )
{
	return static_cast<ia::option::types>( ~static_cast<byte_t>( left ) );
}

inline ia::option::types & operator&=( ia::option::types & left , ia::option::types right )
{
	left = left & right;
	return left;
}

inline ia::option::types & operator|=( ia::option::types & left , ia::option::types right )
{
	left = left | right;
	return left;
}

inline ia::option::types & operator^=( ia::option::types & left , ia::option::types right )
{
	left = left ^ right;
	return left;
}


#endif // OPTION_HPP