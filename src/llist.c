#include <stdlib.h>
#include <stdio.h>

#include "llist.h"

#ifndef __STDC__VERSION__
#define inline
#endif

#define LLIST_MACRO(suffix, type) \
	llist ## suffix ## _t* append ## suffix(llist ## suffix ## _t* list, type elem) { \
		llist ## suffix ## _t* tmp = list; \
		llist ## suffix ## _t* last = (llist ## suffix ## _t*)malloc(sizeof(llist ## suffix ## _t)); \
		last->data = elem; \
		last->next = NULL; \
		if (!list){ \
			return last; \
		} \
		while(tmp->next){ \
			tmp = tmp->next; \
		} \
		tmp->next = last; \
		return list; \
	}
#include "llist.def"
#undef LLIST_MACRO

#define LLIST_MACRO(suffix, type) \
	llist ## suffix ## _t* prepend ## suffix(llist ## suffix ## _t* list, type elem) { \
		llist ## suffix ## _t* head = (llist ## suffix ## _t*)malloc(sizeof(llist ## suffix ## _t)); \
		head->data = elem; \
		head->next = list; \
		return head; \
	}
#include "llist.def"
#undef LLIST_MACRO

#define LLIST_PRINT(suffix, print, type) \
	void fprint ## suffix(FILE* file, llist ## suffix ## _t* list) { \
		llist ## suffix ## _t* tmp = list; \
		fprintf(file, "[ "); \
		while (tmp) { \
			print(tmp->data, file); \
			fprintf(file, " "); \
			tmp = tmp->next; \
		} \
		fprintf(file, "]\n"); \
	}
#include "llist.def"
#undef LLIST_PRINT

#define LLIST_PRINT(suffix, _, type) \
	inline void print ## suffix(llist ## suffix ## _t* list) { \
		fprint ## suffix(stdout, list); \
	}
#include "llist.def"
#undef LLIST_PRINT

#define LLIST_MACRO(suffix, type) \
	llist ## suffix ## _t* concat ## suffix(llist ## suffix ## _t* listA, llist ## suffix ## _t* listB) { \
		llist ## suffix ## _t* tmp = listA; \
		if (!listA){ \
			return listB; \
		} \
		while (tmp->next){ \
			tmp = tmp->next; \
		} \
		tmp->next = listB; \
		return listA; \
	}
#include "llist.def"
#undef LLIST_MACRO

#define LLIST_MACRO(suffix, type) \
	llist ## suffix ## _t* map ## suffix(llist ## suffix ## _t* list, unary_func ## suffix f) { \
		llist ## suffix ## _t* tmp = list; \
		while (tmp) { \
			tmp->data = f(tmp->data); \
		} \
		return list; \
	}
#include "llist.def"
#undef LLIST_MACRO

#define LLIST_MACRO(suffix, type) \
	llist ## suffix ## _t* new_llist ## suffix(type* arr, int len) { \
		llist ## suffix ## _t* output = NULL; \
		int i; \
		for (i = len-1; i >= 0; i--){ \
			output = prepend ## suffix(output, arr[i]); \
		} \
		return output; \
	}
#include "llist.def"
#undef LLIST_MACRO

#define LLIST_MACRO(suffix, type) \
	llist ## suffix ## _t* reverse ## suffix(llist ## suffix ## _t* list) { \
		llist ## suffix ## _t* output = NULL, *tmp = list; \
		while(tmp){ \
			output = prepend ## suffix(output, tmp->data); \
			tmp = tmp->next; \
		} \
		return output; \
	}
#include "llist.def"
#undef LLIST_MACRO

#define LLIST_MACRO(suffix, type) \
	void free_llist ## suffix(llist ## suffix ## _t* list) { \
		llist ## suffix ## _t* tmp = list, *_tmp; \
		while (tmp){ \
			_tmp = tmp->next; \
			free(tmp); \
			tmp = _tmp; \
		} \
	}
#include "llist.def"
#undef LLIST_MACRO

#define LLIST_MACRO(suffix, type) \
	size_t length ## suffix(llist ## suffix ## _t* list) { \
		llist ## suffix ## _t* tmp = list; \
		size_t count = 0;\
		while(tmp){ \
			tmp = tmp->next; \
			count++; \
		} \
		return count; \
	}
#include "llist.def"
#undef LLIST_MACRO

#define LLIST_MACRO(suffix, type) \
	type foldl ## suffix(type acc_begin, llist ## suffix ## _t* list, binary_func ## suffix f) { \
		type acc = acc_begin; \
		llist ## suffix ## _t* tmp = list; \
		while(tmp){ \
			acc = f(acc, tmp->data); \
			tmp = tmp->next; \
		} \
		return acc; \
	}
#include "llist.def"
#undef LLIST_MACRO

#define LLIST_NUMERICAL(suffix, type) \
	static type add ## suffix(type a, type b){ return a + b; } \
	type sum ## suffix(llist ## suffix ## _t* list){ \
		return foldl ## suffix(0, list, add ## suffix);\
	}
#include "llist.def"
#undef LLIST_NUMERICAL

#define LLIST_NUMERICAL(suffix, type) \
	static type mult ## suffix(type a, type b){ return a * b; } \
	type product ## suffix(llist ## suffix ## _t* list){ \
		return foldl ## suffix(1, list, mult ## suffix);\
	}
#include "llist.def"
#undef LLIST_NUMERICAL
