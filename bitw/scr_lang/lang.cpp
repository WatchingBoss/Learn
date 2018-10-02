#include <cctype>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

void error(const char *str) {
	perror(str);
	exit(EXIT_FAILURE);
}

void errorf(const char *format, ...) {
	char buffer[1024];

	va_list args;
	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	error(buffer);
}

const char *code;

enum { MAX_SYMBOLS = 256 };

const char *symbols[MAX_SYMBOLS];
size_t      num_symbols;

const char *intern(const char *start, const char *end) {
	for (size_t i = 0; i < num_symbols; ++i) {
		const char *symbol = symbols[i];
		const char *string = start;
		while (*symbol && string != end && *symbol == *string) {
			++symbol;
			++string;
		}
		if (!*symbol && string == end) { return (symbols[i]); }
	}

	if (num_symbols == MAX_SYMBOLS) error("symbol table overflow");

	size_t size       = end - start + 1;
	char * new_symbol = (char *)malloc(size);
	memcpy(new_symbol, start, size);
	new_symbol[size - 1] = 0;
	symbols[num_symbols] = new_symbol;
	++num_symbols;
	return (new_symbol);
}

typedef enum {
	LIT,
	GET,
	SET,
	POP,
	JMP,
	BRZ,
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,
	NEG,
	RET
} opcode_t;

char *emit_pointer;

void emit(uint8_t data) { *emit_pointer++ = data; }

void emit4(uint32_t data) {
	*(uint32_t *)emit_pointer = data;
	emit_pointer += 4;
}

char *ip;
int * sp;
int * fp;

int execute() {
	for (;;) {
		int op = *ip++;
		switch (op) {
			case LIT:
				*sp++ = *(uint32_t *)ip;
				ip += 4;
				break;
			case GET:
				*sp++ = fp[*ip];
				++ip;
				break;
			case SET:
				fp[*ip] = sp[-1];
				++ip;
				--sp;
				break;
			case POP: --sp; break;
			case JMP: ip += *(uint32_t *)ip; break;
			case BRZ:
				if (sp[-1] == 0)
					ip += *(uint32_t *)ip;
				else
					ip += 4;
				--sp;
				break;
			case ADD:
				sp[-2] += sp[-1];
				--sp;
				break;
			case SUB:
				sp[-2] -= sp[-1];
				--sp;
				break;
			case MUL:
				sp[-2] *= sp[-1];
				--sp;
				break;
			case DIV:
				sp[-2] /= sp[-1];
				--sp;
				break;
			case MOD:
				sp[-2] %= sp[-1];
				--sp;
				break;
			case NEG: sp[-1] = -sp[-1]; break;
			case RET: return (sp[-1]); break;
			default: break;
		}
	}
}

typedef enum {
	TOKEN_NUMBER = 128,
	TOKEN_IDENTIFIER,
	TOKEN_EQUALS,
	TOKEN_IF,
	TOKEN_ELSEIF,
	TOKEN_ELSE,
	TOKEN_WHILE,
	TOKEN_FOR,
	TOKEN_RETURN
} token_t;

token_t     token;
int         token_number;
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

typedef struct {
	const char *identifier;
	token_t     token;
} keyword_t;

enum { MAX_KEYWORDS = 16 };

const char *keyword_if;
const char *keyword_else;
const char *keyword_elseif;
const char *keyword_while;
const char *keyword_for;
const char *keyword_return;

keyword_t keywords[MAX_KEYWORDS];
size_t    num_keywords;

#define INTERN_KEYWORD(name, tok)                                              \
	const char string_##name[] = #name;                                        \
	keyword_##name =                                                           \
	    intern(string_##name, string_##name + sizeof(string_##name) - 1);      \
	keywords[num_keywords].identifier = keyword_##name;                        \
	keywords[num_keywords].token      = tok;                                   \
	++num_keywords;

void initialize_keywords() {
	num_keywords = 0;
	INTERN_KEYWORD(if, TOKEN_IF);
	INTERN_KEYWORD(else, TOKEN_ELSE);
	INTERN_KEYWORD(elseif, TOKEN_ELSEIF);
	INTERN_KEYWORD(while, TOKEN_WHILE);
	INTERN_KEYWORD(for, TOKEN_FOR);
	INTERN_KEYWORD(return, TOKEN_RETURN);

	/*
	    const char string_if[] = "if";
	    const char string_while[] = "while";
	    const char string_for[] = "for";
	    const char string_return[] = "return";

	    keyword_if = intern(string_if, string_if + sizeof(string_if) - 1);
	    keyword_while = intern(string_while, string_while + sizeof(string_while)
	   - 1); keyword_for = intern(string_for, string_for + sizeof(string_for) -
	   1); keyword_return = intern(string_return, string_return +
	   sizeof(string_return) - 1);
	*/
}

void next_token() {
	while (isspace(*code)) ++code;

	if (isdigit(*code)) {
		token_number = 0;
		while (isdigit(*code)) {
			token_number *= 10;
			token_number += *code - '0';
			++code;
		}
		token = TOKEN_NUMBER;
	} else if (isalpha(*code)) {
		const char *start = code;
		while (isalnum(*code)) { ++code; }
		const char *end  = code;
		token_identifier = intern(start, end);

		token = TOKEN_IDENTIFIER;
		for (size_t i = 0; i < num_keywords; ++i) {
			if (keywords[i].identifier == token_identifier)
				token = keywords[i].token;
			break;
		}
		if (!token) token = TOKEN_IDENTIFIER;
		/*
		        if(token_identifier == keyword_if)
		            token = TOKEN_IF;
		        else if(token_identifier == keyword_else)
		            token = TOKEN_ELSE;
		        else if(token_identifier == keyword_elseif)
		            token = TOKEN_ELSEIF;
		        else if(token_identifier == keyword_while)
		            token = TOKEN_WHILE;
		        else if(token_identifier == keyword_for)
		            token = TOKEN_FOR;
		        else if(token_identifier == keyword_return)
		            token = TOKEN_RETURN;
		        else
		            token = TOKEN_IDENTIFIER;
		*/
	} else {
		switch (*code) {
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
			case '{':
			case '}':
			case ';':
				token = (token_t)*code;
				++code;
				break;
			case '=': {
				++code;
				if (*code == '=') {
					++code;
					token = TOKEN_EQUALS;
				} else
					token = (token_t)'=';
			} break;
			default:
				errorf("Unexpected initial token character: \'%c\'", *code);
				break;
		}
	}
}

void expect_token(int expected_token) {
	if (token != expected_token)
		errorf("Expected token %d, got %d", expected_token, token);
	next_token();
}

char find_variable(const char *identifier) {
	for (size_t i = 0; i < num_symbols; ++i) {
		if (symbols[i] == identifier) return (i);
	}
	error("This should never happen");
	return (-1);
}

void expr();

void expr2() {
	if (token == TOKEN_NUMBER) {
		next_token();
		emit(LIT);
		emit4(token_number);
	} else if (token == TOKEN_IDENTIFIER) {
		int variable = find_variable(token_identifier);
		next_token();
		if (token == '=') {
			next_token();
			expr();
			emit(SET);
			emit((char)variable);
		}

		emit(GET);
		emit((char)variable);
	} else if (token == '(') {
		next_token();
		expr();
		expect_token((token_t)')');
	} else if (token == '-') {
		next_token();
		expr2();  // -2 * 3
		emit(NEG);
	} else
		errorf("Unexpected token at beginning of expression");
}

void expr1() {
	expr2();
	while (token == '*' || token == '/' || token == '%') {
		token_t op = token;
		next_token();
		expr2();
		if (op == '*') {
			emit(MUL);
		} else if (op == '/') {
			emit(DIV);
		} else {
			emit(MOD);
		}
	}
}

void expr() {
	expr1();
	while (token == '+' || token == '-') {
		token_t op = token;
		next_token();
		expr1();
		if (op == '+') {
			emit(ADD);
		} else {
			emit(SUB);
		}
	}
}

// void stmt();

void stmtBlock() {
	void stmt();
	expect_token('{');
	while (token && token != '}') stmt();
	expect_token('}');
}

void stmt() {
	if (token == TOKEN_IF) {
		next_token();
		expr();

		emit(BRZ);
		char *next_alternative_offset = emit_pointer;
		emit4(0);
		stmtBlock();
		char *end_offset = NULL;
		while (token == TOKEN_ELSEIF) {
			next_token();
			emit(JMP);
			char *previous_end_offset = end_offset;
			end_offset                = emit_pointer;
			emit4(previous_end_offset - emit_pointer);
			*(int32_t *)next_alternative_offset =
			    emit_pointer - next_alternative_offset;
			expr();
			emit(BRZ);
			next_alternative_offset = emit_pointer;
			emit4(0);
			stmtBlock();
		}

		if (token == TOKEN_ELSE) {
			next_token();
			emit(JMP);
			char *previous_offset = emit_pointer;
			emit4(0);
			char *previous_end_offset = end_offset;
			end_offset                = emit_pointer;
			emit4(previous_end_offset - emit_pointer);
			*(int32_t *)next_alternative_offset =
			    emit_pointer - next_alternative_offset;
			stmtBlock();
		}

		while (end_offset != NULL) {
			int32_t previous_end_offset = *(int32_t *)end_offset;
			*(int32_t *)end_offset      = emit_pointer - end_offset;
			end_offset += previous_end_offset;
		}
	} else if (token == TOKEN_WHILE) {
		next_token();
		char *loop_offset = emit_pointer;
		expr();
		emit(BRZ);
		char *done_offset = emit_pointer;
		emit4(0);
		stmtBlock();
		emit(JMP);
		emit4(loop_offset - emit_pointer);
		*(int32_t *)done_offset = emit_pointer - done_offset;
	} else if (token == TOKEN_RETURN) {
		next_token();
		expr();
		expect_token(';');
		emit(RET);
	} else if (token == '{') {
		stmtBlock();
	} else {
		expr();
		emit(POP);
		expect_token(';');
	}
}

int main() {
	char emit_buffer[1024];
	emit_pointer = emit_buffer;

	initialize_keywords();
	//	code = "{x = 42; y = 3 + 2; z = 4 * 3 + 1; return  x + y + z}";
	//	code = "{ x = 1; if 1 { x + 2; return x+2 }";
	code = "{ x = 1; n = 3; while n { x = x * 2; n = n - 1; } return x; }";

	next_token();

	int frame[1024];
	int stack[1024];
	ip = emit_buffer;
	fp = frame;
	sp = stack;

	int val = execute();

#if 0
	for(int i = 0; i < 10; ++i)
		printf("%d\n", fp[i]);
	printf("\n");
	for(int i = 0; i < 10; ++i)
		printf("%d\n", sp[i]);
	printf("\nval is %d\n", val);
#endif

	return (0);
}
