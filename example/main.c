#include <stdlib.h>
#include <stdio.h>

#include "llist.h"
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
    if (elem_custom(rev_c, c)){
	    printf("c is in rev_c\n");
    } else {
	    printf("elem not working\n");
    }
    free_llist_custom(clist);
    free_llist_custom(rev_c);
    return 0;
}
