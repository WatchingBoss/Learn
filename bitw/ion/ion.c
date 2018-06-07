#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

/* 
 * Stretcy buffers 
 */

#define MAX(x, y) ((x > y) ? (x) : (y))

typedef struct BufferHeader
{
	size_t len;
	size_t cap;
	char buf[0];
} BufferHeader;

#define buf__hdr(b) ((BufferHeader *)((char *)b - offsetof(BufferHeader, buf)))
#define buf__fits(b, n) (buf_len(b) + (n) <= buf_cap(b))
#define buf__fit(b, n) (buf__fits(b, n) ? 0 : ((b) = buf__grow((b), buf_len(b) + (n), sizeof(*(b)))))
#define buf_free(b) ((b) ? free(buf__hdr(b)) : 0)

#define buf_len(b) ((b) ? buf__hdr(b)->len : 0)
#define buf_cap(b) ((b) ? buf__hdr(b)->cap : 0)
#define buf_push(b, x) (buf__fit(b, 1), (b)[buf_len(b)] = (x), buf__hdr(b)->len++)

void *buf__grow(const void *buf, size_t new_len, size_t elem_size)
{
	size_t new_cap = MAX(1 + 2 * buf_cap(buf), new_len);

	assert(new_len <= new_cap);
	size_t new_size = offsetof(BufferHeader, buf) + new_cap * elem_size;
	BufferHeader *new_header;

	if(buf)
		new_header = realloc(buf__hdr(buf), new_size);
	else
	{
		new_header = malloc(new_size);
		new_header->len = 0;
	}

	new_header->cap = new_cap;

	return(new_header->buf);
}

/* lexing: translating char stream to token stream */

typedef enum eTokenKind
{
	TOKEN_INT = 128,
	TOKEN_NAME
} eTokenKind;

typedef struct Token
{
	eTokenKind kind;
	union
	{
		uint64_t val;
		struct
		{
			const char *start;
			const char *end;
		};
	};
} Token;

Token token;
const char *stream;

/* 1234 (x+y) -> '1234' '(' 'x' '+' 'y' ')' */
void next_token()
{
	switch(*stream)
	{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		{
			uint64_t val = 0;
			while(isdigit(*stream))
			{
				val *= 10;
				val += *stream++ - '0';
			}
			token.kind = TOKEN_INT;
			token.val = val;
		} break;
		
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case 'a':
		case 'b':
	    case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
		case '_':
		{
			const char *start = stream++;
			while(isalnum(*stream) || *stream == '_')
			{
				++stream;
			}
			token.kind = TOKEN_NAME;
			token.start = start;
			token.end = stream;
		} break;

		default:
			token.kind = *stream++;
			break;
	}
}

void buf_test()
{
	int *buf = NULL;
	enum{ N = 1024 };

	for(int i = 0; i < N; ++i)
		buf_push(buf, i);

	assert(buf_len(buf) == N);

	for(int i = 0; i < buf_len(buf); ++i)
		assert(buf[i] == i);
	
	buf_free(buf);	
}

void print_token(Token token)
{
	switch(token.kind)
	{
		case TOKEN_INT:
			printf("TOKEN INT: %lu\n", token.val);
			break;
		case TOKEN_NAME:
			printf("TOKEN NAME: %.*s\n", (int)(token.end - token.start), token.start);
			break;
		default:
			printf("TOKEN \'%c\'\n", token.kind);
			break;
	}
}

void lex_test()
{
	char *source = "+()_STRING,123FOO!4+554";
	stream = source;
	next_token();
	while(token.kind)
	{
		print_token(token);
		next_token();
	}
}

int main()
{
	buf_test();
	lex_test();
	
	return(0);
}
