#include <stdio.h>
#include <stdlib.h>

void *xmalloc( int bytes ) {
	void *new_ptr = malloc( bytes );
	if ( !new_ptr ) {
		perror( "xmalloc: malloc error" );
		exit( EXIT_FAILURE );
	}
	return new_ptr;
}

size_t StringLen( const char *str ) {
	size_t length = 0;
	while ( str[length] ) ++length;
	return length;
}

void StringCopy( const char *source, char *dest, size_t dest_buffer ) {
	size_t source_len = StringLen( source );
	if ( dest_buffer - source_len < 1 ) {
		puts( "Destination buffer less than source's length" );
		exit( EXIT_FAILURE );
	}
	size_t i = 0;
	for ( ; i < source_len; ++i ) dest[i] = source[i];
	dest[i] = '\0';
}

typedef struct {
	size_t length;
	char * buffer;
} String;

String *MakeString( const char *str ) {
	size_t buffer_size = StringLen( str );

	String *new_str = (String *)malloc( sizeof( String ) );
	new_str->length = buffer_size;
	new_str->buffer = (char *)malloc( sizeof( char ) * ( buffer_size + 1 ) );
	StringCopy( str, new_str->buffer, new_str->length + 1 );

	return new_str;
}

void PrintStringInfo( const String *str ) {
	printf( "Buffer: %s\n"
	        "Length: %ld\n",
	        str->buffer, str->length );
}

void DeleteString( String *str ) {
	free( str->buffer );
	free( str );
}

String *CatString( const String *const str1, const String *const str2 ) {
	size_t  new_str_len = str1->length + str2->length;
	String *new_str     = (String *)xmalloc( sizeof( String ) );
	new_str->length     = new_str_len;
	new_str->buffer     = (char *)malloc( sizeof( char ) * ( new_str->length + 1 ) );
	size_t i            = 0;
	for ( ; i < str1->length; ++i ) new_str->buffer[i] = str1->buffer[i];
	for ( size_t j = 0; i < new_str->length; ++i ) new_str->buffer[i] = str2->buffer[j++];
	new_str->buffer[i] = '\0';

	return new_str;
}

#define BUF_SIZE 255
String *UserInput( ) {
	char buffer[BUF_SIZE] = { 0 };
	fgets( buffer, BUF_SIZE, stdin );
	return MakeString( buffer );
}
#undef BUF_SIZE

int main( ) {
	String *user_input = UserInput( );
	String *str1 = MakeString("This is afirst string");
	String *str2 = MakeString( "This is a second string" );
	String *str3 = CatString( str1, str2 );

	PrintStringInfo( user_input );
	PrintStringInfo( str1 );
	PrintStringInfo( str2 );
	PrintStringInfo( str3 );

	DeleteString( user_input );
	DeleteString( str1 );
	DeleteString( str2 );
	DeleteString( str3 );

	return 0;
}
