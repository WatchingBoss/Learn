#ifndef LEX_H
#define LEX_H

extern const char *typedef_keyword;
extern const char *enum_keyword;
extern const char *struct_keyword;
extern const char *union_keyword;
extern const char *var_keyword;
extern const char *const_keyword;
extern const char *func_keyword;
extern const char *sizeof_keyword;
extern const char *break_keyword;
extern const char *continue_keyword;
extern const char *return_keyword;
extern const char *if_keyword;
extern const char *else_keyword;
extern const char *while_keyword;
extern const char *do_keyword;
extern const char *for_keyword;
extern const char *switch_keyword;
extern const char *case_keyword;
extern const char *default_keyword;

extern const char *first_keyword;
extern const char *last_keyword;
extern const char **keywords;

typedef enum eTokenKind
{
	TOKEN_EOF = 0,
	TOKEN_LAST_CHAR = 127,
	TOKEN_KEYWORD,
	TOKEN_INT,
	TOKEN_FLOAT,
	TOKEN_STR,
	TOKEN_NAME,
	TOKEN_LSHIFT,
	TOKEN_RSHIFT,
	TOKEN_EQ,
	TOKEN_NOTEQ,
	TOKEN_LTEQ,
	TOKEN_GTEQ,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_INC,
	TOKEN_DEC,
	TOKEN_COLON_ASSIGN,
	TOKEN_ADD_ASSIGN,
	TOKEN_FIRST_ASSIGN = TOKEN_ADD_ASSIGN,
	TOKEN_SUB_ASSIGN,
	TOKEN_OR_ASSIGN,
	TOKEN_AND_ASSIGN,
	TOKEN_XOR_ASSIGN,
	TOKEN_LSHIFT_ASSIGN,
	TOKEN_RSHIFT_ASSIGN,
	TOKEN_MUL_ASSIGN,
	TOKEN_DIV_ASSIGN,
	TOKEN_MOD_ASSIGN,
	TOKEN_LAST_ASSIGN = TOKEN_MOD_ASSIGN,
} eTokenKind;

typedef enum eTokenMod
{
	TOKENMOD_NONE,
	TOKENMOD_HEX,
	TOKENMOD_BIN,
	TOKENMOD_OCT,
	TOKENMOD_CHAR,
} eTokenMod;

extern size_t copy_token_kind_str(char *, size_t, eTokenKind);

extern const char *temp_token_kind_str(eTokenKind);

extern bool is_token(eTokenKind);
extern bool is_token_eof();
extern bool is_token_name(const char *);
extern bool is_keyword(const char *);
extern bool match_keyword(const char *);
extern bool match_token(eTokenKind);
extern bool expect_token(eTokenKind);

extern void scan_int();
extern void scan_float();
extern void scan_char();
extern void scan_str();

extern void next_token();

typedef struct Token
{
	eTokenKind kind;
	eTokenMod mod;
	const char *start;
	const char *end;

	union
	{
		uint64_t int_val;
		double float_val;
		const char *str_val;
		const char *name;
	};
} Token;

extern Token token;
extern const char *stream;

extern void init_stream(const char *);
extern void print_token(Token);

extern void lex_test();

#endif
