#include <cstring>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <list>
#include <netdb.h>

#include "typedefs.h++"
#include "option.h++"
#include "readopts.h++"


struct senddata_t
{
	senddata_t( sockaddr_in * ServerAddress , int_t Number )
			:
			serveradr( ServerAddress ) ,
			number( Number )
	{ }

	sockaddr_in * serveradr;
	int_t number;
};

void * threadworker( void * data );

int main( const int_t argc , const char_t * const argv[] , const char_t * const envp[] )
{
	int_t margc = 0;
	while ( ( argc - margc ) > 0 )
	{
		std::cout << argv[margc++] << std::endl;
	}


	// Обработка опций и аргументов
	ia::option hostopt( 'h' , "host" , ia::option::requires::require ,
						ia::option::types::opt | ia::option::types::arg );
	ia::option portopt( 'p' , "port" , ia::option::requires::require ,
						ia::option::types::opt | ia::option::types::arg );

	ia::readopts ro( argc , argv );
	ro.addopt( &hostopt );
	ro.addopt( &portopt );

	ro.run( );

	std::cout << "Параметры командной строки" << std::endl;
	std::cout << hostopt << std::endl;
	std::cout << portopt << std::endl;

	string_t host;
	host = hostopt.str( );

	int_t port;
	port = std::stoi( portopt.str( ) );


	// Структуры для сокета
	hostent * srv = ::gethostbyname( host.c_str( ) );
	if ( srv == NULL )
	{
		::perror( "Host not found" );
		return EXIT_FAILURE;
	}
	sockaddr_in srvadr;
	srvadr.sin_family = AF_INET;
	::strncpy( ( char * )&srvadr.sin_addr.s_addr , srv->h_addr , size_t( srv->h_length ) );
	srvadr.sin_port = ::htons( word_t( port ) );


	// Основной цикл программы
	int                     result;
	std::list<pthread_t>    threadslist;
	std::list<senddata_t *> dataslist;
	while ( true )
	{
		std::cout << "Enter:" << std::endl;
		int_t input;
		while ( std::cin >> input )
		{
			senddata_t * sd = new senddata_t( { &srvadr , input } );
			dataslist.push_back( sd );

			pthread_t pt;
			result = ::pthread_create( &pt , NULL , threadworker , dataslist.back( ) );
			if ( result != 0 )
			{
				::perror( "Creating the thread" );
				return EXIT_FAILURE;
			}

			threadslist.push_back( pt );
		}
		if ( std::cin.fail( ) )
		{
			break;
		}
	}


	// Ждём присоединения потоков
	for ( std::list<pthread_t>::iterator it = threadslist.begin( ) ; it != threadslist.end( ) ; ++it )
	{
		::printf( "Start joining thread\n" );
		result = ::pthread_join( *it , NULL );
		if ( result != 0 )
		{
			::perror( "Joining thread" );
			return EXIT_FAILURE;
		}
	}

	// Очищаем данные
	for ( std::list<senddata_t *>::iterator it = dataslist.begin( ) ; it != dataslist.end( ) ; ++it )
	{
		delete *it;
	}
	::printf( "Done\n" );


	return EXIT_SUCCESS;
}
/// Функция потока ( создание, открытие, отправка, получение и закрытие )
void * threadworker( void * data )
{
	// Наши данные
	senddata_t d = *( static_cast<senddata_t *>( data ) );

	// Создаём сокет
	int_t sock                  = ::socket( AF_INET , SOCK_STREAM , 0 );
	if ( sock < 0 )
	{
		error_t error = errno;
		std::cout << "Can't create socket: " << error << std::endl;
		return nullptr;
	}

	// Подключаем сокет
	if ( ::connect( sock , ( sockaddr * )d.serveradr , sizeof( *d.serveradr ) ) < 0 )
	{
		error_t error = errno;
		std::cout << "Can't connect socket: " << error << std::endl;
		::close( sock );

		return nullptr;
	}

	// Отправим данные на сервер
	if ( ::send( sock , &d.number , sizeof( d.number ) , 0 ) < 0 )
	{
		error_t error = errno;
		std::cout << "Can't send data: " << error << std::endl;
		::close( sock );

		return nullptr;
	}

	// Получим данные с сервера
	std::vector<byte_t> reply( 2000 );
	ssize_t             recvlen = 0;
	recvlen = ::recv( sock , reply.data( ) , 2000 , 0 );
	if ( recvlen < 0 )
	{
		error_t error = errno;
		std::cout << "Can't recive data: " << error << std::endl;
		::close( sock );

		return nullptr;
	}

	std::cout << "Server reply: ";
	for ( std::vector<byte_t>::iterator i = reply.begin( ) ; ( i != reply.end( ) ) && ( recvlen-- > 0 ) ; ++i )
	{
		std::cout << char( *i );
	}
	std::cout << std::endl;

	// Закрываемся
	::close( sock );
	return nullptr;
}