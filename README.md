# llist-C: Linked List on raw data
## By Andrew M. Hall
### Overview
For the standard linked list implementation in C, the basic type can is

```c
typedef struct linkedlist {
	void* data;
	struct linkedlist* next;
} linkedlist_t;
```

This implementation, while simple, sacrafices both efficiency and  type safety. For every access to the data field, one must 1) dereference a pointer, possibly incuring cache issues and slowdown, and 2) cast the void to the type it is pointing to.

The obviouse way to get around this issue is to write a linkedlist for each type that is needed, however this quickly becomes cumbersome as the code is long and repetetive. Another problem is that any library, cannot hope to know all the types that a user is going to want to store in a linked list, thus more often than not, the user will be using a void\* inspite of the care that the library writer took to write a linked list for each built in type.

My solution, is to devise a framework around the little used X-Macro functionality of the C preprocessor, this allows me to easily write a linked list implementation for each built in data type, and what's more, a user can specify their own data types to be used in a linked list. This unfortunatly means that this library cannot be precompiled.

### Basic Usage
To start with, I have allowed for most of the inbuilt data types to be utilised as part of a linked list. There are a range of functions that all come in various flavours mapping to each type they act upon.

##### e.g. linked list of long long
The following program prints out the first 10 primes, reverses the list and then sums them. It can be seen that the suffix, \_ll is ubiquitous, if only using one major data type, it would be good practise to ```#define print print_ll```.
```c
#include <stdio.h>
#include "llist.h"

static long long add(long long a, long long b){return a + b;}
int main(){
	signed long long nums[10] = {2,5,7,11,13,17,19,23,29,31}; /*first 10 primes*/
	signed long long sum;
	llist_ll_t* list = new_llist_ll(nums, 10);
	print_ll(list);
	list = reverse_ll(list);
	print_ll(list);
	sum = foldl_ll(1, list, add);
	printf("the sum of the first 10 primes is: %lld\n", sum);
	free_llist_ll(list);
	return 0;
}
```

### User Defined data structures
As alluded to previously, the power of this framework comes from the ability for users to define linked lists that work on their own data types. For this example, we shall use a 'person data type', and observe how to construct linked lists of people. 

##### person.h
```c
#ifndef PERSON_H
#define PERSON_H

typedef struct person {
	unsigned int age;
	unsigned int height;
	char* name;
} person_t;

/*
... any extra function definitions or types ...
*/
#endif
```
##### llist_usertype.def
This is a special file, where a user can specify the type to turn into a linked list.
```c
#include "person.h"
#include <stdio.h>

#ifdef LLIST_MACRO
/*
the first macro argument is its suffix
the second is the type to turn into a linked list
*/
LLIST_MACRO(_p, person_t)
#endif

/*
macro is called when trying to print a person.
if an object is 'unprintable', then leave this declaration and no print functions will be generated.
*/
#ifdef LLIST_PRINT
#define PRINT_PERSON(p, file) fprintf(file, "Name: %s\nAge: %ud\nHeight: %ud\n", p.name, p.age, p.height)
LLIST_PRINT(_p, PRINT_PERSON, person_t)
#undef PRINT_PERSON
#endif
```

And that is it. You can now use print\_p, foldl\_p, reverse\_p, ... and directly operate on your person\_t at will.
