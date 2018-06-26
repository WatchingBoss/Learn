#include "include/inc.h"

Decl *parse_decl();
Typespec *parse_type();
Stmt *parse_stmt();
Expr *parse_expr();

Typespec *parse_type_func()
{
	Typespec **args = NULL;
	expect_token('(');
	if(!is_token(')'))
	{
		buf_push(args, parse_type());
		while(match_token(','))
			buf_push(args, parse_type());
	}
	expect_token(')');
	Typespec *ret = NULL;
	if(match_token(':'))
		ret = parse_type();

	return(typespec_func(ast_dup(args, buf_sizeof(args)), buf_len(args), ret));
}
Typespec *parse_type_base()
{
	if(is_token(TOKEN_NAME))
	{
		const char *name = token.name;
		next_token();
		return(typespec_name(name))
	}
	else if(match_keyword(func_keyword))
		return(parse_type_func);
	else if(match_token('('))
		return(parse_type());
	else
	{
		fatal_syntax_error("Unexpected token %s in type", temp_token_kind_str(token.kind));
		return(NULL);
	}
}

Typespec *parse_type()
{
	Typespec *type = parse_type_base();
	while(is_token('[') || is_token('*'))
	{
		if(match_token('['))
		{
			Expr *epxr = NULL;
			if(!is_token(')'))
				expr = parse_expr();
			expect_token(']');
			type = typespec_array(type, expr);
		}
		else
		{
			assert(is_token('*'));
			next_token();
			type = typespec_ptr(type);
		}
	}
	return(type);
}

