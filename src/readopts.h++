#ifndef READOPTS_HPP
#define READOPTS_HPP

#include <list>
#include <vector>
#include <getopt.h>

#include "typedefs.h++"
#include "option.h++"


namespace ia
{
	typedef std::list<ia::option *>		optslist;
	typedef std::vector<::option> 		gnuoptvec;

	class readopts
	{
		public:

		readopts( void );

		readopts( const int_t &			argc ,
				  const char_t * const	argv[] );

		readopts( const int_t &			argc ,
				  const char_t * const	argv[] ,
				  const char_t * const	envp[] );

		virtual ~readopts( void );


		void							addopt( ia::option * opt );


		void							run( void );


		protected:

		void							getoptarg( const ia::optslist &	list ,
												   string_t &			optstr ,
												   ia::gnuoptvec &		optarr ) const;

		void							getapparg( void );

		void							getargarg( void );


		private:

		ia::optslist					readopts__opts;
		const int_t						readopts__argc;
		char_t * const *				readopts__argv;
		char_t * const *				readopts__envp;
	};
}


#endif // READOPTS_HPP