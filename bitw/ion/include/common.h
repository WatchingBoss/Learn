#ifndef COMMON_H
#define COMMON_H

extern void *xrealloc(void *, size_t);
extern void *xmalloc(size_t);
extern void *xcalloc(size_t, size_t);

extern void fatal(const char *, ...);
extern void syntax_error(const char *, ...);

extern void fatal_syntax_error(const char *, ...);

typedef struct BufferHeader
{
	size_t len;
	size_t cap;
	char buf[];
} BufferHeader;

#define buf__hdr(b) ((BufferHeader *)((char *)(b) - offsetof(BufferHeader, buf)))

#define buf_len(b) ((b) ? buf__hdr(b)->len : 0)
#define buf_cap(b) ((b) ? buf__hdr(b)->cap : 0)
#define buf_end(b) ((b) + buf_len(b))
#define buf_sizeof(b) ((b) ? buf_len(b)*sizeof(*b) : 0)

#define buf_free(b) ((b) ? (free(buf__hdr(b)), (b) = NULL) : 0)
#define buf__fit(b, n) ((n) <= buf_cap(b)			\
						? 0 : ((b) = buf__grow((b), (n), sizeof(*(b)))))
#define buf_push(b, ...) (buf__fit((b), 1), (b)[buf__hdr(b)->len++] = (__VA_ARGS__))

#define ALIGN_DOWN(n, a) ((n) & ~((a) - 1))
#define ALIGN_UP(n, a) ALIGN_DOWN((n) + (a) - 1, (a))
#define ALIGN_DOWN_PTR(p, a) ((void *)ALIGN_DOWN((uintptr_t)(p), (a)))
#define ALIGN_UP_PTR(p, a) ((void *)ALIGN_UP((uintptr_t)(p), (a)))


typedef struct Arens
{
	char *ptr;
	char *end;
	char **blocks;
} Arena;

typedef struct InternString
{
	size_t len;
	const char *str;
} InternString;

extern Arena str_arena;
extern InternString *interns;

#define ARENA_ALIGNMENT 8
#define ARENA_BLOCK_SIZE 1024

extern void arena_grow(Arena *, size_t);
extern void *arena_alloc(Arena *, size_t);
extern void arena_free(Arena *);


extern void *buf__grow(const void *, size_t, size_t);
extern void buf_test();


extern const char *str_intern_range(const char *, const char *);
extern const char *str_intern(const char *);


extern void str_intern_test();
extern void common_test();

#endif
