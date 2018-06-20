#include "inc.h"

Typespec *typespec_new(eTypespecKind kind)
{
	Typespec *t = xcalloc(1, sizeof(Typespec));
	t->kind = kind;
	return(t);
}

Typespec *typespec_name(const char *name)
{
	Typespec *t = typespec_new(TYPESPEC_NAME);
	t->name = name;
	return(t);
}

Typespec *typespec_ptr(Typespec *elem)
{
	Typespec *t = typespec_new(TYPESPEC_PTR);
	t->ptr.elem = elem;
	return(t);
}

Typespec *typespec_array(Typespec *elem, Expr *size)
{
	Typespec *t = typespec_new(TYPESPEC_ARRAY);
	t->array.elem = elem;
	t->array.size = size;
	return(t);
}

Typespec *typespec_func(Typespec **args, size_t num_args, Typespec *ret)
{
	Typespec *t = typespec_new(TYPESPEC_FUNC);
	t->func.args = args;
	t->func.num_args = num_args;
	t->func.ret = ret;
	return(t);
}

Decl *decl_new(eDeclKind kind, const char *name)
{
	Decl *d = xcalloc(1, sizeof(Decl));
	d->kind = kind;
	d->name = name;
	return(d);
}

Decl *decl_enum(const char *name, EnumItem *items, size_t num_items)
{
	Decl *d = decl_new(DECL_ENUM, name);
	d->enum_decl.items = items;
	d->enum_decl.num_items = num_items;
	return(d);
}

Decl *decl_struct(const char *name, AggregateItem *items, size_t num_items)
{
	Decl *d = decl_new(DECL_STRUCT, name);
	d->aggregate.items = items;
	d->aggregate.num_items = num_items;
	return(d);
}

Decl *decl_union(const char *name, AggregateItem *items, size_t num_items)
{
	Decl *d = decl_new(DECL_UNION, name);
	d->aggregate.items = items;
	d->aggregate.num_items = num_items;
	return(d);
}

Decl *decl_var(const char *name, Typespec *type, Expr *expr)
{
	Decl *d = decl_new(DECL_VAR, name);
	d->var.type = type;
	d->var.expr = expr;
	return(d);
}

Decl
*decl_func(const char *name, FuncParam *params, size_t num_params, Typespec *ret_type, StmtBlock block)
{
	Decl *d = decl_new(DECL_FUNC, name);
	d->func.params = params;
	d->func.num_params = num_params;
	d->func.ret_type = ret_type;
	d->func.block = block;
	return(d);
}

Decl *decl_const(const char *name, Expr *expr)
{
	Decl *d = decl_new(DECL_CONST, name);
	d->const_decl.expr = expr;
	return(d);
}

Decl *decl_typedef(const char *name, Typespec *type)
{
	Decl *d = decl_new(DECL_TYPEDEF, name);
	d->typedef_decl.type = type;
	return(d);
}

Expr *expr_new(eExprKind kind)
{
	Expr *e = xcalloc(1, sizeof(Expr));
	e->kind = kind;
	return(e);
}

Expr *expr_int(uint64_t int_val)
{
	Expr *e = expr_new(EXPR_INT);
	e->int_val = int_val;
	return(e);
}

Expr *expr_float(double float_val)
{
	Expr *e = expr_new(EXPR_FLOAT);
	e->float_val = float_val;
	return(e);
}

Expr *expr_str(const char *str_val)
{
	Expr *e = expr_new(EXPR_STR);
	e->str_val = str_val;
	return(e);
}

Expr *expr_name(const char *name)
{
	Expr *e = expr_new(EXPR_NAME);
	e->name = name;
	return(e);
}

Expr *expr_compound(Typespec *type, Expr **args, size_t num_args)
{
	Expr *e = expr_new(EXPR_COMPOUND);
	e->compound.type = type;
	e->compound.args = args;
	e->compound.num_args = num_args;
	return(e);
}

Expr *expr_cast(Typespec *type, Expr *expr)
{
	Expr *e = expr_new(EXPR_CAST);
	e->cast.type = type;
	e->cast.expr = expr;
	return(e);
}

Expr *expr_call(Expr *expr, Expr **args, size_t num_args)
{
	Expr *e = expr_new(EXPR_CALL);
	e->call.expr = expr;
	e->call.args = args;
	e->call.num_args = num_args;
	return(e);
}

Expr *expr_index(Expr *expr, Expr *index)
{
	Expr *e = expr_new(EXPR_INDEX);
	e->index.expr = expr;
	e->index.index = index;
	return(e);
}

Expr *expr_field(Expr *expr, const char *name)
{
	Expr *e = expr_new(EXPR_FIELD);
	e->field.expr = expr;
	e->field.name = name;
	return(e);
}

Expr *expr_unary(eTokenKind op, Expr *expr)
{
	Expr *e = expr_new(EXPR_UNARY);
	e->unary.op = op;
	e->unary.expr = expr;
	return(e);
}

Expr *expr_binary(eTokenKind op, Expr *left, Expr *right)
{
	Expr *e = expr_new(EXPR_BINARY);
	e->binary.op = op;
	e->binary.left = left;
	e->binary.right = right;
	return(e);
}

Expr *expr_ternary(Expr *cond, Expr *if_true, Expr *if_false)
{
	Expr *e = expr_new(EXPR_TERNARY);
	e->ternary.cond = cond;
	e->ternary.if_true = if_true;
	e->ternary.if_false = if_false;
	return(e);
}

Stmt *stmt_new(eStmtKind kind)
{
	Stmt *s = xcalloc(1, sizeof(Stmt));
	s->kind = kind;
	return(s);
}

Stmt *stmt_return(Expr *expr)
{
	Stmt *s = stmt_new(STMT_RETURN);
	s->return_stmt.expr = expr;
	return(s);
}

Stmt *stmt_break()
{
	return(stmt_new(STMT_BREAK));
}

Stmt *stmt_continue()
{
	return(stmt_new(STMT_CONTINUE));
}

Stmt *stmt_block(StmtBlock block)
{
	Stmt *s = stmt_new(STMT_BLOCK);
	s->block = block;
	return(s);
}

Stmt
*stmt_if(Expr *cond, StmtBlock then_block, ElseIf *elseifs, size_t num_elseifs, StmtBlock else_block)
{
	Stmt *s = stmt_new(STMT_IF);
	s->if_stmt.cond = cond;
	s->if_stmt.then_block = then_block;
	s->if_stmt.elseifs = elseifs;
	s->if_stmt.num_elseifs = num_elseifs;
	s->if_stmt.else_block = else_block;
	return(s);
}


Stmt *stmt_while(Expr *cond, StmtBlock block)
{
	Stmt *s = stmt_new(STMT_WHILE);
	s->while_stmt.cond = cond;
	s->while_stmt.block = block;
	return(s);
}

Stmt *stmt_do_while(Expr *cond, StmtBlock block)
{
	Stmt *s = stmt_new(STMT_DO_WHILE);
	s->while_stmt.cond = cond;
	s->while_stmt.block = block;
	return(s);
}

Stmt *stmt_for(StmtBlock init, Expr *cond, StmtBlock next, StmtBlock block)
{
	Stmt *s = stmt_new(STMT_FOR);
	s->for_stmt.init = init;
	s->for_stmt.cond = cond;
	s->for_stmt.next = next;
	s->for_stmt.block = block;
	return(s);
}

Stmt *stmt_switch(Expr *expr, SwitchCase *cases, size_t num_cases)
{
	Stmt *s = stmt_new(STMT_SWITCH);
	s->switch_stmt.expr = expr;
	s->switch_stmt.cases = cases;
	s->switch_stmt.num_cases = num_cases;
	return(s);
}

Stmt *stmt_assign(eTokenKind op, Expr *left, Expr *right)
{
	Stmt *s = stmt_new(STMT_ASSIGN);
	s->assign.op = op;
	s->assign.left = left;
	s->assign.right = right;
	return(s);
}

Stmt *stmt_init(const char *name, Expr *expr)
{
	Stmt *s = stmt_new(STMT_INIT);
	s->init.name = name;
	s->init.expr = expr;
	return(s);
}

Stmt *stmt_expr(Expr *expr)
{
	Stmt *s = stmt_new(STMT_EXPR);
	s->expr = expr;
	return(s);
}

void print_expr(Expr *expr);
void print_stmt(Stmt *stmt);
void print_decl(Decl *decl);

int indent;

void print_newline()
{
	printf("\n%.*s", 2*indent, "                                                          ");
}

void print_typespec(Typespec *type)
{
	Typespec *t = type;
	switch(t->kind)
	{
		case TYPESPEC_NAME:
			printf("%s", t->name);
			break;
		case TYPESPEC_FUNC:
			printf("func (");
			for(Typespec **it = t->func.args; it != t->func.args + t->func.num_args; ++it)
			{
				printf(" ");
				print_typespec(*it);
			}
			printf(") ");
			print_typespec(t->func.ret);
			printf(")");
			break;
		case TYPESPEC_ARRAY:
			printf("(array ");
			print_typespec(t->array.elem);
			printf(" ");
			print_expr(t->array.size);
			printf(")");
			break;
		case TYPESPEC_PTR:
			printf("(ptr ");
			print_typespec(t->ptr.elem);
			printf(")");
			break;
		default:
			assert(0);
			break;
	}
}

void print_stmt_block(StmtBlock block, bool newlines)
{
	assert(block.num_stmts != 0);
	printf("(block ");
	++indent;
	for(Stmt **it = block.stmts; it != block.stmts + block.num_stmts; ++it)
	{
		if(newlines)
			print_newline();
		else
			printf(" ");
		print_stmt(*it);
	}
	--indent;
	printf(")");
}

void print_stmt(Stmt *stmt)
{
	Stmt *s = stmt;
	switch(s->kind)
	{
		case STMT_RETURN:
			printf("(return ");
			print_expr(s->return_stmt.expr);
			printf(")");
			break;
		case STMT_BREAK:
			printf("(break)");
			break;
		case STMT_CONTINUE:
			printf("(continue)");
			break;
		case STMT_BLOCK:
			print_stmt_block(s->block, true);
			break;
		case STMT_IF:
			printf("(if ");
			print_expr(s->if_stmt.cond);
			++indent;
			print_newline();
			print_stmt_block(s->if_stmt.then_block, true);
			for(ElseIf *it = s->if_stmt.elseifs;
				it != s->if_stmt.elseifs + s->if_stmt.num_elseifs; ++it)
			{
				print_newline();
				printf("(elseif ");
				print_expr(it->cond);
				print_newline();
				print_stmt_block(it->block, true);
			}
			if(s->if_stmt.else_block.num_stmts != 0)
			{
				print_newline();
				printf("(else ");
				print_newline();
				print_stmt_block(s->if_stmt.else_block, true);
			}
			printf(")");
			--indent;
			break;
		case STMT_WHILE:
			printf("(while ");
			print_expr(s->while_stmt.cond);
			++indent;
			print_newline();
			print_stmt_block(s->while_stmt.block, true);
			--indent;
			printf(")");
			break;
		case STMT_DO_WHILE:
			printf("(do-while ");
			print_expr(s->while_stmt.cond);
			++indent;
			print_newline();
			print_stmt_block(s->while_stmt.block, true);
			--indent;
			printf(")");
			break;
		case STMT_FOR:
			printf("(for ");
			print_stmt_block(s->for_stmt.init, false);
			print_expr(s->for_stmt.cond);
			print_stmt_block(s->for_stmt.next, false);
			++indent;
			print_newline();
			print_stmt_block(s->for_stmt.block, true);
			--indent;
			printf(")");
			break;
		case STMT_SWITCH:
			printf("(switch ");
			print_expr(s->switch_stmt.expr);
			++indent;
			for(SwitchCase *it = s->switch_stmt.cases;
				it != s->switch_stmt.cases + s->switch_stmt.num_cases; ++it)
			{
				print_newline();
				printf("(case (");
				if(it->is_default)
					printf("default");
				else
					printf("nil");
				for(Expr **expr = it->exprs; expr != it->exprs + it->num_exprs; ++it)
				{
					printf(" ");
					print_expr(*expr);
				}
				printf(") ");
				++indent;
				print_newline();
				print_stmt_block(it->block, true);
				--indent;
			}
			printf(")");
			--indent;
			break;
		case STMT_ASSIGN:
//			printf("%s ", token_kind_names[s->assign.op]);
			print_expr(s->assign.left);
			printf(" ");
			print_expr(s->assign.right);
			printf(")");
			break;
		case STMT_INIT:
			printf("(:= %s ", s->init.name);
			print_expr(s->init.expr);
			printf(")");
			break;
		case STMT_EXPR:
			print_expr(s->expr);
			break;
		default:
			assert(0);
			break;
	}
}

void print_expr(Expr *expr)
{
	Expr *e = expr;
	switch(e->kind)
	{
		case EXPR_INT:
			printf("%" PRIu64, e->int_val);
			break;
		case EXPR_FLOAT:
			printf("%f", e->float_val);
			break;
		case EXPR_STR:
			printf("\"%s\"", e->str_val);
			break;
		case EXPR_NAME:
			printf("%s", e->name);
			break;
		case EXPR_CAST:
			printf("(cast ");
			print_typespec(e->cast.type);
			printf(" ");
			print_expr(e->cast.expr);
			printf(")");
			break;
		case EXPR_CALL:
			printf("(");
			print_expr(e->call.expr);
			for(Expr **it = e->call.args; it != e->call.args + e->call.num_args; ++it)
			{
				printf(" ");
				print_expr(*it);
			}
			printf(")");
			break;
		case EXPR_INDEX:
			printf("(index ");
			print_expr(e->index.expr);
			printf(" ");
			print_expr(e->index.index);
			printf(")");
			break;
		case EXPR_FIELD:
			printf("(field ");
			print_expr(e->field.expr);
			printf(" %s)", e->field.name);
			break;
		case EXPR_COMPOUND:
			printf("(compound ");
			if(e->compound.type)
				print_typespec(e->compound.type);
			else
				printf("nil");
			for(Expr **it = e->compound.args; it != e->compound.args + e->compound.num_args; ++it)
			{
				printf(" ");
				print_expr(*it);
			}
			printf(")");
			break;
		case EXPR_UNARY:
			printf("(%c ", e->unary.op);
			print_expr(e->unary.expr);
			printf(")");
			break;
		case EXPR_BINARY:
			printf("(%c ", e->binary.op);
			print_expr(e->binary.left);
			printf(" ");
			print_expr(e->binary.right);
			printf(")");
			break;
		case EXPR_TERNARY:
			printf("(if ");
			print_expr(e->ternary.cond);
			printf(" ");
			print_expr(e->ternary.if_true);
			printf(" ");
			print_expr(e->ternary.if_false);
			printf(")");
			break;
		default:
			assert(0);
			break;
	}
}

void print_aggregate_decl(Decl *decl)
{
	Decl *d = decl;
	for(AggregateItem *it = d->aggregate.items;
		it != d->aggregate.items + d->aggregate.num_items; ++it)
	{
		print_newline();
		printf("(");
		print_typespec(it->type);
		for(const char **name = it->names; name != it->names + it->num_names; ++name)
			printf(" %s", *name);
		printf(")");
	}
}

void print_decl(Decl *decl)
{
	Decl *d = decl;
	switch(d->kind)
	{
		case DECL_ENUM:
			printf("(enum %s", d->name);
			++indent;
			for(EnumItem *it = d->enum_decl.items;
				it != d->enum_decl.items + d->enum_decl.num_items; ++it)
			{
				print_newline();
				printf("(%s ", it->name);
				if(it->expr)
					print_expr(it->expr);
				else
					printf("nil");
				printf(")");
			}
			--indent;
			printf(")");
			break;
		case DECL_STRUCT:
			printf("(struct %s", d->name);
			++indent;
			print_aggregate_decl(d);
			--indent;
			printf(")");
			break;
		case DECL_UNION:
			printf("(union %s", d->name);
			++indent;
			print_aggregate_decl(d);
			--indent;
			printf(")");
			break;
		case DECL_VAR:
			printf("(var %s", d->name);
			print_typespec(d->var.type);
			printf(" ");
			print_expr(d->var.expr);
			printf(")");
			break;
		case DECL_CONST:
			printf("(cosnt %s", d->name);
			print_expr(d->var.expr);
			printf(")");
			break;
		case DECL_TYPEDEF:
			printf("(typedef %s", d->name);
			print_typespec(d->typedef_decl.type);
			printf(")");
			break;
		case DECL_FUNC:
			printf("(func %s", d->name);
			printf("(");
			for(FuncParam *it = d->func.params;
				it != d->func.params + d->func.num_params; ++it)
			{
				printf(" %s", it->name);
				print_typespec(it->type);
			}
			printf(" ) ");
			print_typespec(d->func.ret_type);
			++indent;
			print_newline();
			print_stmt_block(d->func.block, true);
			--indent;
			printf(")");
			break;
		default:
			assert(0);
			break;
	}
}

void expr_test()
{
	Expr *exprs[] = { expr_binary('+', expr_int(1), expr_int(2)),
					  expr_unary('-', expr_float(3.14)),
					  expr_ternary(expr_name("flag"), expr_str("true"), expr_str("false")),
					  expr_field(expr_name("person"), "name"),
					  expr_call(expr_name("fact"), (Expr*[]){expr_int(42)}, 1),
					  expr_index(expr_field(expr_name("person"), "sibling"), expr_int(3)),
					  expr_cast(typespec_ptr(typespec_name("int")), expr_name("void_ptr")),
					  expr_compound(typespec_name("Vector"), (Expr*[]){expr_int(1), expr_int(2)}, 2) };
	for(Expr **it = exprs; it != exprs + sizeof(exprs) / sizeof(*exprs); ++it)
	{
		print_expr(*it);
		printf("\n");
	}
}

void stmt_test()
{
	Stmt *stmts[] = {
		stmt_return(expr_int(42)),
        stmt_break(),
        stmt_continue(),
        stmt_block((StmtBlock){(Stmt*[]){stmt_break(), stmt_continue()},2,}),
        stmt_expr(expr_call(expr_name("print"), (Expr*[]){expr_int(1), expr_int(2)}, 2)),
        stmt_init("x", expr_int(42)),
        stmt_if(expr_name("flag1"),
				(StmtBlock){
					(Stmt*[]){
						stmt_return(expr_int(1))},1,},
				(ElseIf[]){
					expr_name("flag2"),
						(StmtBlock){
							(Stmt*[]){stmt_return(expr_int(2))},1,}},1,
				(StmtBlock){
					(Stmt*[]){stmt_return(expr_int(3))},1,}),
        stmt_while(
            expr_name("running"),
            (StmtBlock){
                (Stmt*[]){
                    stmt_assign(TOKEN_ADD_ASSIGN, expr_name("i"), expr_int(16)),},1,}),
        stmt_switch(
            expr_name("val"),
            (SwitchCase[]){
                {
                    (Expr*[]){expr_int(3), expr_int(4)},2,false,
															(StmtBlock){
																(Stmt*[]){
																	stmt_return(expr_name("val"))},
																	1,},},
                {
                    (Expr*[]){expr_int(1)},1,true,
											   (StmtBlock){
												   (Stmt*[]){stmt_return(expr_int(0))},
													   1,},},},2),
	};
	for(Stmt **it = stmts; it != stmts + sizeof(stmts) / sizeof(*stmts); ++it)
	{
		print_stmt(*it);
		printf("\n");
	}
}

void decl_test()
{
	
}

void ast_test()
{
	expr_test();
	stmt_test();
	decl_test();
}
