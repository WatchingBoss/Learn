#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>

void error(const char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void errorf(const char *format, ...)
{
	char buffer[1024];
	
	va_list args;
	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	error(buffer);
}

const char *code;

enum
{
	MAX_SYMBOLS = 256
};

const char *symbols[MAX_SYMBOLS];
size_t num_symbols;

const char *intern(const char *start, const char *end)
{
	for(size_t i = 0; i < num_symbols; ++i)
	{
		const char *symbol = symbols[i];
		const char *string = start;
		while(*symbol && string != end && *symbol == *string)
		{
			++symbol;
			++string;
		}
		if(!*symbol && string == end)
		{
			return(symbols[i]);
		}
	}

	if(num_symbols == MAX_SYMBOLS)
		error("symbol table overflow");

	size_t size = end - start + 1;
	char *new_symbol = (char *)malloc(size);
	memcpy(new_symbol, start, size);
	new_symbol[size - 1] = 0;
	symbols[num_symbols] = new_symbol;
	++num_symbols;
	return(new_symbol);
}

const char *keyword_if;
const char *keyword_while;
const char *keyword_for;

void initialize()
{
	const char string_if[] = "if";
	const char string_while[] = "while";
	const char string_for[] = "for";

	keyword_if = intern(string_if, string_if + sizeof(string_if) - 1);
	keyword_while = intern(string_while, string_while + sizeof(string_while) - 1);
	keyword_for = intern(string_for, string_for + sizeof(string_for) - 1);
}

typedef enum
{
	TOKEN_NUMBER = 128,
	TOKEN_IDENTIFIER,
	TOKEN_EQUALS,
	TOKEN_IF,
	TOKEN_WHILE,
	TOKEN_FOR
} token_t;

token_t token;
int token_number;
const char *token_identifier;

#if 0
const char *token_to_identifier()
{
	char buffer[128];
	if(token < 128)
		sprintf(buffer, "%c", token);
	else if(token == TOKEN_NUMBER)
		sprintf(buffer, "%d", token_number);
	else if(token == TOKEN_IDENTIFIER)
		sprintf(buffer, "%s", token_identifier);
	else if(token == TOKEN_IF)
		sprintf(buffer, "if");
	else if(token == TOKEN_WHILE)
		sprintf(buffer, "while");
	else if(token == TOKEN_FOR)
		sprintf(buffer, "for");
	return(buffer);
}
#endif

void next_token()
{
	while(isspace(*code))
		++code;

	if(isdigit(*code))
	{
		token_number = 0;
		while(isdigit(*code))
		{
			token_number *= 10;
			token_number += *code - '0';
			++code;
		}
		token = TOKEN_NUMBER;
	}
	else if(isalpha(*code))
	{
		const char *start = code;
		while(isalnum(*code))
		{
			++code;
		}
		const char *end = code;
		token_identifier = intern(start, end);

		if(token_identifier == keyword_if)
			token = TOKEN_IF;
		else if(token_identifier == keyword_while)
			token = TOKEN_WHILE;
		else if(token_identifier == keyword_for)
			token = TOKEN_FOR;
		else
			token = TOKEN_IDENTIFIER;
	}
	else
	{
		switch(*code)
		{
			case 0:
			case '+':
			case '-':
			case '*':
			case '/':
			case '%':
			case '&':
			case '|':
			case '^':
			case '~':
			case '!':			
			case '(':
			case ')':			
				token = (token_t)*code;
				++code;
				break;
			case '=':
			{
				++code;
				if(*code == '=')
				{
					++code;
					token = TOKEN_EQUALS;
				}
				else
					token = (token_t)'=';
			} break;
			default:
				errorf("Unexpected initial token character: \'%c\'", *code);
				break;
		}
	}
}

void expect_token(token_t expected_token)
{
	if(token != expected_token)
		errorf("Expected token %d, got %d", expected_token, token);
	next_token();
}

void expr();

void expr2()
{
	if(token == TOKEN_NUMBER)
	{
		next_token();
		// code for constant
	}
	else if(token == TOKEN_IDENTIFIER)
	{
		next_token();
		// code for reading variable
	}
	else if(token == '(')
	{
		next_token();
		expr();
		expect_token((token_t)')');
	}
	else if(token == '-')
	{
		next_token();
		expr2(); // -2 * 3
	}
	else
		errorf("Unexpected token at beginning of expression");
}

void expr1()
{
	expr2();
	while(token == '*' || token == '/' || token == '%')
	{
		token_t op = token;
		next_token();
		expr2();
		if(op == '*')
		{
			// multiplication
		}
		else if(op == '/')
		{
			// division
		}
		else
		{
			// modulo
		}
	}
}

void expr()
{
	expr1();
	while(token == '+' || token == '-')
	{
		token_t op = token;
		next_token();
		expr1();
		if(op == '+')
		{
			// addition	
		}
		else
		{
			// substruction
		}
	}
}

int main()
{
	

	return(0);
}
