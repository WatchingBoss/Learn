#ifndef COMMON_H
#define COMMON_H

extern void *xrealloc(void *, size_t);
extern void *xmalloc(size_t);
extern void *xcalloc(size_t, size_t);

extern void fatal(const char *, ...);
extern void syntax_error(const char *, ...);

typedef struct BufferHeader
{
	size_t len;
	size_t cap;
	char buf[];
} BufferHeader;

#define BUF(x) x

#define buf__hdr(b) ((BufferHeader *)((char *)(b) - offsetof(BufferHeader, buf)))

#define buf_len(b) ((b) ? buf__hdr(b)->len : 0)
#define buf_cap(b) ((b) ? buf__hdr(b)->cap : 0)
#define buf_end(b) ((b) + buf_len(b))

#define buf_free(b) ((b) ? (free(buf__hdr(b)), (b) = NULL) : 0)
#define buf__fit(b, n) ((n) <= buf_cap(b)			\
						? 0 : ((b) = buf__grow((b), (n), sizeof(*(b)))))
#define buf_push(b, ...) (buf__fit((b), 1), (b)[buf__hdr(b)->len++] = (__VA_ARGS__))

extern void *buf__grow(const void *, size_t, size_t);
extern void buf_test();


extern const char *str_intern_range(const char *, const char *);
extern const char *str_intern(const char *);


extern void str_intern_test();
extern void common_test();

#endif
