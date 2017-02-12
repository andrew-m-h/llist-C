#include <stdlib.h>
#include <stdio.h>

#include "llist.h"
#if 0
#include "custom.h"

#define print print_i
#define new_llist new_llist_i
#define reverse reverse_i
#define llist llist_i_t
#define free_llist free_llist_i

int main(){
	int tmp[] = {1,2,3,4,5,6,7,8,9,10};
	llist* lst = new_llist(tmp, 10);
	print(lst);

	llist* rev = NULL;
	rev = reverse(lst);
	print(rev);

	int total = sum_i(lst);
	printf("%d\n", total);
	total = product_i(lst);
	printf("%d\n", total);

	free_llist(lst);
	free_llist(rev);

	llist_custom_t* clist = NULL, *rev_c = NULL;
	custom_t c = {.c='a', .i=32};
	clist = append_custom(clist, c);
	c.i++;
	clist = append_custom(clist, c);
	print_custom(clist);

	rev_c = reverse_custom(clist);
	print_custom(rev_c);

	free_llist_custom(clist);
	free_llist_custom(rev_c);
	return 0;
}
#endif
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
