#include <fstream>
#include <iostream>
#include <string>

#include <sys/stat.h>
#include <sys/types.h>

static std::string dir       = "folder";
static std::string file_name = "folder/sample";

static void linux_dir( const char *name ) { mkdir( name, S_IRWXU | S_IRWXG | S_IRWXO ); }

static void creat_dir( ) {
#ifdef _WIN32
	// win_dir();
#else
	linux_dir( dir.c_str( ) );
#endif
}

static void write_file( int num ) {
	std::ofstream stream( file_name, std::ios::out | std::ios::binary );

	if ( !stream ) {
		creat_dir( );
		stream.open( file_name, std::ios::out | std::ios::binary );
	}

	stream.write( reinterpret_cast<char *>( &num ), sizeof num );

	stream.close( );
}

static void read_file( ) {
	std::ifstream stream( file_name, std::ios::in | std::ios::binary );

	if ( !stream ) puts( "No such file" );

	int num = 0;

	stream.read( reinterpret_cast<char *>( &num ), sizeof num );

	std::printf( "Number: %d\n", num );

	stream.close( );
}

int main( ) {
	write_file( 25 );

	read_file( );

	return 0;
}
