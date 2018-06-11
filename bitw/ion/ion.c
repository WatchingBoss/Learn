#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

/* 
 * Stretcy buffers 
 */

#define MAX(x, y) ((x > y) ? (x) : (y))

void *xrealloc(void *ptr, size_t num_bytes)
{
	ptr = realloc(ptr, num_bytes);
	if(!ptr)
	{
		perror("xrealloc failed");
		exit(1);
	}
	return(ptr);
}

void *xmalloc(size_t num_bytes)
{
	void *ptr = malloc(num_bytes);
	if(!ptr)
	{
		perror("xmalloc failed");
		exit(1);
	}
	return(ptr);
}

void fatal(const char *fmt, ...)
{
	char buf[256];
	va_list args;
	va_start(args, fmt);
	printf("FATAL: ");
	vsprintf(buf, fmt, args);
	printf("\n");
	va_end(args);
	exit(1);
}

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
		new_header = xmalloc(new_size);
		new_header->len = 0;
	}

	new_header->cap = new_cap;

	return(new_header->buf);
}

void buf_test()
{
	int *buf = NULL;
	assert(buf_len(buf) == 0);
	enum{ N = 1024 };

	for(int i = 0; i < N; ++i)
		buf_push(buf, i);

	assert(buf_len(buf) == N);

	for(int i = 0; i < buf_len(buf); ++i)
		assert(buf[i] == i);
	
	buf_free(buf);
	assert(buf == NULL);
	assert(buf_len(buf) == NULL);
}

/*
 * ...
 */
typedef struct InternString
{
	size_t len;
	const char *str;
} InternString;

static InternString *interns;

const char *str_intern_range(const char *start, const char *end)
{
	size_t len = end - start;
	for(size_t i = 0; i < buf_len(interns); ++i)
	{
		if(interns[i].len == len && strncmp(interns[i].str, start, len) == 0)
			return(interns[i].str);
	}
	char *str = xmalloc(len + 1);
	memcpy(str, start, len);
	str[len] = 0;

	buf_push(interns, ((InternString){len, str}));

	return(str);
}

const char *str_intern(const char *str)
{
	return(str_intern_range(str, str + strlen(str)));
}

void str_intern_test()
{
	char x[] = "hello";
	char y[] = "hello";

	assert(x != y);

	const char *px = str_intern(x);
	const char *py = str_intern(y);

	assert(px == py);
}

/* 
 * Lexing: translating char stream to token stream 
 */

typedef enum eTokenKind
{
	TOKEN_INT = 128,
	TOKEN_NAME
} eTokenKind;

// This return a pointer to a static internal buffer, so it will be over
const char *token_kind_name(eTokenKind kind)
{
	static char buf[ 256];
	switch(kind)
	{
		case TOKEN_INT:
			sprintf(buf, "interger");
			break;
		case TOKEN_NAME:
			sprintf(buf, "name");
			break;
		default:
			if(kind < 128 && isprint(kind))
				sprintf(buf, "%c", kind);
			else
				sprintf(buf, "<ASCII %d>", kind);
	}
	
	return(buf);
}

typedef struct Token
{
	eTokenKind kind;
	const char *start;
	const char *end;

	union
	{
		uint64_t val;
		const char *name;
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
			while(isalnum(*stream) || *stream == '_')
				++stream;
			token.kind = TOKEN_NAME;
			token.name = str_intern_range(token.start, stream);
			break;
		default:
			token.kind = *stream++;
			break;
	}
	token.end = stream;
}

void init_stream(const char *str)
{
	stream = str;
	next_token();
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

inline bool is_token(eTokenKind kind)
{
	return(token.kind == kind);
}

inline bool is_token_name(const char *name)
{
	return(token.kind == TOKEN_NAME && token.name == name);
}

inline bool match_token(eTokenKind kind)
{
	if(is_token(kind))
	{
		next_token();
		return(true);
	}
	else
		return(false);
}

inline bool expect_token(eTokenKind kind)
{
	if(is_token(kind))
	{
		next_token();
		return(true);
	}
	else
	{
		fatal("expected token %s, got %s", token_kind_name(kind), token_kind_name(token.kind));
		return(false);
	}
}

void lex_test()
{
	char *source = "XY+(XY)+()_STRING,123FOO!4+554";
	stream = source;
	next_token();
	while(token.kind)
	{
		print_token(token);
		next_token();
	}
}

void parse_expr();

void parse_expr3()
{
	if(is_token(TOKEN_INT))
		next_token();
	else if(match_token('('))
	{
		parse_expr();
		expect_token(')');
	}
	else
		fatal("expected integer of (, got %s", token_kind_name(token.kind));
}

void parse_expr2()
{
	if(match_token('-'))
		parse_expr3();
	else
		parse_expr3();
}

void parse_expr1()
{
	parse_expr2();
	while(is_token('*') || is_token('/'))
	{
		char op = token.kind;
		next_token();
		parse_expr2();
	}
}

void parse_expr0()
{
	parse_expr2();
	while(is_token('+') || is_token('-'))
	{
		char op = token.kind;
		next_token();
		parse_expr2();
	}
}

void parse_test()
{
	const char *expr = "(1)";
	init_stream(expr);
	parse_expr();
}

int main()
{
	buf_test();
	lex_test();
	str_intern_test();
	parse_test();
	
	return(0);
}
