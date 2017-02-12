#ifndef LLIST_H
#define LLIST_H

#include <stdlib.h>
#include <stdio.h>

#ifndef __GNUC__
#define __attribute__(...)
#endif

#define LLIST_MACRO(suffix, type) \
	typedef struct llist ## suffix { \
		type data; \
		struct llist ## suffix* next; \
	} llist ## suffix ## _t;
#include "llist.def"
#undef LLIST_MACRO

#define LLIST_MACRO(suffix, type) \
	llist ## suffix ## _t* append ## suffix(llist ## suffix ## _t*, type) __attribute__((pure));
#include "llist.def"
#undef LLIST_MACRO

#define LLIST_MACRO(suffix, type) \
	llist ## suffix ## _t* prepend ## suffix(llist ## suffix ## _t*, type) __attribute__((pure));
#include "llist.def"
#undef LLIST_MACRO

#define LLIST_PRINT(suffix, _, type) \
	void fprint ## suffix(FILE*, llist ## suffix ## _t*);
#include "llist.def"
#undef LLIST_PRINT

#define LLIST_PRINT(suffix, _, type) \
	void print ## suffix(llist ## suffix ## _t*);
#include "llist.def"
#undef LLIST_PRINT

#define LLIST_MACRO(suffix, type) \
	llist ## suffix ## _t* concat ## suffix(llist ## suffix ## _t*, llist ## suffix ## _t*) __attribute__((pure));
#include "llist.def"
#undef LLIST_MACRO

#define LLIST_MACRO(suffix, type) \
	typedef type (*unary_func ## suffix)(type);
#include "llist.def"
#undef LLIST_MACRO

#define LLIST_MACRO(suffix, type) \
	llist ## suffix ## _t* map ## suffix(llist ## suffix ## _t*, unary_func ## suffix);
#include "llist.def"
#undef LLIST_MACRO

#define LLIST_MACRO(suffix, type) \
	llist ## suffix ## _t* new_llist ## suffix(type*, int);
#include "llist.def"
#undef LLIST_MACRO

#define LLIST_MACRO(suffix, type) \
	llist ## suffix ## _t* reverse ## suffix(llist ## suffix ## _t*) __attribute__((pure));
#include "llist.def"
#undef LLIST_MACRO

#define LLIST_MACRO(suffix, type) \
	void free_llist ## suffix(llist ## suffix ## _t*);
#include "llist.def"
#undef LLIST_MACRO

#define LLIST_MACRO(suffix, type) \
	size_t length ## suffix(llist ## suffix ## _t*); 
#include "llist.def"
#undef LLIST_MACRO

#define LLIST_MACRO(suffix, type) \
	typedef type (*binary_func ## suffix)(type, type);
#include "llist.def"
#undef LLIST_MACRO

#define LLIST_MACRO(suffix, type) \
	type foldl ## suffix(type, llist ## suffix ## _t*, binary_func ## suffix);
#include "llist.def"
#undef LLIST_MACRO

#define LLIST_NUMERICAL(suffix, type) \
	type sum ## suffix(llist ## suffix ## _t*) __attribute__((pure));
#include "llist.def"
#undef LLIST_NUMERICAL

#define LLIST_NUMERICAL(suffix, type) \
	type product ## suffix(llist ## suffix ## _t*) __attribute__((pure));
#include "llist.def"
#undef LLIST_NUMERICAL

#endif 
