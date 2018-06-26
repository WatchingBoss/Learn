#ifndef AST_H
#define AST_H

typedef struct Expr Expr;
typedef struct Stmt Stmt;
typedef struct Decl Decl;
typedef struct Typespec Typespec;

typedef struct StmtBlock
{
	Stmt **stmts;
	size_t num_stmts;
} StmtBlock;

typedef enum eTypespecKind
{
	TYPESPEC_NONE,
	TYPESPEC_NAME,
	TYPESPEC_FUNC,
	TYPESPEC_ARRAY,
	TYPESPEC_PTR,
} eTypespecKind;

typedef struct FuncTypespec
{
	size_t num_args;
	Typespec **args;
	Typespec *ret;
} FuncTypespec;

typedef struct PtrTypespec
{
	Typespec *elem;
} PtrTypespec;

typedef struct ArrayTypespec
{
	Typespec *elem;
	Expr *size;
} ArrayTypespec;

struct Typespec
{
	eTypespecKind kind;
	union
	{
		const char *name;
		FuncTypespec func;
		ArrayTypespec array;
		PtrTypespec ptr;
	};
};

typedef enum eDeclKind
{
	DECL_NONE,
	DECL_ENUM,
	DECL_STRUCT,
	DECL_UNION,
	DECL_VAR,
	DECL_CONST,
	DECL_TYPEDEF,
	DECL_FUNC,
} eDeclKind;

typedef struct FuncParam
{
	const char *name;
	Typespec *type;
} FuncParam;

typedef struct FuncDecl
{
	FuncParam *params;
	size_t num_params;
	Typespec *ret_type;
	StmtBlock block;
} FuncDecl;

typedef struct EnumItem
{
	const char *name;
	Expr *expr;
} EnumItem;

typedef struct EnumDecl
{
	EnumItem *items;
	size_t num_items;
} EnumDecl;

typedef struct AggregateItem
{
	const char **names;
	size_t num_names;
	Typespec *type;
} AggregateItem;

typedef struct AggregateDecl
{
	AggregateItem *items;
	size_t num_items;
} AggregateDecl;

typedef struct TypedefDecl
{
	Typespec *type;
} TypedefDecl;

typedef struct VarDecl
{
	Typespec *type;
	Expr *expr;
} VarDecl;

typedef struct ConstDecl
{
	Expr *expr;
} ConstDecl;

struct Decl
{
	eDeclKind kind;
	const char *name;
	union
	{
		EnumDecl enum_decl;
		AggregateDecl aggregate;
		FuncDecl func;
		TypedefDecl typedef_decl;
		VarDecl var;
		ConstDecl const_decl;
	};
};

typedef enum eExprKind
{
	EXPR_NOME,
	EXPR_INT,
	EXPR_FLOAT,
	EXPR_STR,
	EXPR_NAME,
	EXPR_CAST,
	EXPR_CALL,
	EXPR_INDEX,
	EXPR_FIELD,
	EXPR_COMPOUND,
	EXPR_UNARY,
	EXPR_BINARY,
	EXPR_TERNARY,
} eExprKind;

typedef struct CompoundExpr
{
	Typespec *type;
	Expr **args;
	size_t num_args;
} CompoundExpr;

typedef struct CastExpr
{
	Typespec *type;
	Expr *expr;
} CastExpr;

typedef struct UnaryExpr
{
	eTokenKind op;
	Expr *expr;
} UnaryExpr;

typedef struct BinaryExpr
{
	eTokenKind op;
	Expr *left;
	Expr *right;
} BinaryExpr;

typedef struct TernaryExpr
{
	Expr *cond;
	Expr *then_expr;
	Expr *else_expr;
} TernaryExpr;

typedef struct CallExpr
{
	Expr *expr;
	Expr **args;
	size_t num_args;
} CallExpr;

typedef struct IndexExpr
{
	Expr *expr;
	Expr *index;
} IndexExpr;

typedef struct FieldExpr
{
	Expr *expr;
	const char *name;
} FieldExpr;

struct Expr
{
	eExprKind kind;

	union
	{
		uint64_t int_val;
		double float_val;
		const char *str_val;
		const char *name;
		CompoundExpr compound;
		CastExpr cast;
		UnaryExpr unary;
		BinaryExpr binary;
		TernaryExpr ternary;
		CallExpr call;
		IndexExpr index;
		FieldExpr field;
	};
};

typedef enum eStmtKind
{
	STMT_NONE,
	STMT_RETURN,
	STMT_BREAK,
	STMT_CONTINUE,
	STMT_BLOCK,
	STMT_IF,
	STMT_WHILE,
	STMT_DO_WHILE,
	STMT_FOR,
	STMT_SWITCH,
	STMT_ASSIGN,
	STMT_INIT,
	STMT_EXPR,
} eStmtKind;

typedef struct ReturnStmt
{
	Expr *expr;
} ReturnStmt;;

typedef struct ElseIf
{
	Expr *cond;
	StmtBlock block;
} ElseIf;

typedef struct IfStmt
{
	Expr *cond;
	StmtBlock then_block;
	ElseIf *elseifs;
	size_t num_elseifs;
	StmtBlock else_block;
} IfStmt;

typedef struct WhileStmt
{
	Expr *cond;
	StmtBlock block;
} WhileStmt;

typedef struct ForStmt
{
	Stmt *init;
	Expr *cond;
	Stmt *next;
	StmtBlock block;
} ForStmt;

typedef struct SwitchCase
{
	Expr **exprs;
	size_t num_exprs;
	bool is_default;
	StmtBlock block;
} SwitchCase;

typedef struct SwitchStmt
{
	Expr *expr;
	SwitchCase *cases;
	size_t num_cases;
} SwitchStmt;

typedef struct AssignStmt
{
	eTokenKind op;
	Expr *left;
	Expr *right;
} AssignStmt;

typedef struct InitStmt
{
	const char *name;
	Expr *expr;
} InitStmt;

struct Stmt
{
	eStmtKind kind;
	union
	{
		ReturnStmt return_stmt;
		IfStmt if_stmt;
		WhileStmt while_stmt;
		ForStmt for_stmt;
		SwitchStmt switch_stmt;
		StmtBlock block;
		AssignStmt assign;
		InitStmt init;
		Expr *expr;
	};
};

extern Typespec *typespec_new(eTypespecKind);
extern Typespec *typespec_name(const char *);
extern Typespec *typespec_ptr(Typespec *);
extern Typespec *typespec_array(Typespec *, Expr *);
extern Decl *decl_new(eDeclKind, const char *);
extern Decl *decl_enum(const char *, EnumItem *, size_t);
extern Decl *decl_struct(const char *, AggregateItem *, size_t);
extern Decl *decl_union(const char *, AggregateItem *, size_t);
extern Decl *decl_var(const char *name, Typespec *type, Expr *);
extern Decl *decl_func(const char *, FuncParam *, size_t, Typespec *, StmtBlock);
extern Decl *decl_const(const char *, Expr *);
extern Decl *decl_typedef(const char *, Typespec *);
extern Expr *expr_new(eExprKind);
extern Expr *expr_int(uint64_t);
extern Expr *expr_float(double);
extern Expr *expr_str(const char *);
extern Expr *expr_name(const char *);
extern Expr *expr_compound(Typespec *, Expr **, size_t);
extern Expr *expr_cast(Typespec *, Expr *);
extern Expr *expr_call(Expr *, Expr **, size_t);
extern Expr *expr_index(Expr *, Expr *);
extern Expr *expr_field(Expr *, const char *);
extern Expr *expr_unary(eTokenKind, Expr *);
extern Expr *expr_binary(eTokenKind, Expr *, Expr *);
extern Expr *expr_ternary(Expr *, Expr *, Expr *);
extern Stmt *stmt_new(eStmtKind);
extern Stmt *stmt_return(Expr *);
extern Stmt *stmt_break();
extern Stmt *stmt_continue();
extern Stmt *stmt_block(StmtBlock);
extern Stmt *stmt_if(Expr *, StmtBlock , ElseIf *, size_t , StmtBlock);
extern Stmt *stmt_while(Expr *, StmtBlock);
extern Stmt *stmt_do_while(Expr *, StmtBlock);
extern Stmt *stmt_for(StmtBlock, Expr *, StmtBlock , StmtBlock);
extern Stmt *stmt_switch(Expr *, SwitchCase *, size_t);
extern Stmt *stmt_assign(eTokenKind, Expr *, Expr *);
extern Stmt *stmt_init(const char *, Expr *);
extern Stmt *stmt_expr(Expr *);

extern void print_test();

#endif
