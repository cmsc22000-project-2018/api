#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "trie.h"

Test(trie, new)
{
    trie_t* test_trie = trie_new("test");
    cr_assert_not_null(test_trie, "trie_new() failed");
    trie_free(test_trie); 
}

Test(trie, init)
{
    trie_t *test_trie = trie_new("test"); 
    cr_assert_not_null(test_trie, "trie_new() failed"); 
    int rc = trie_init(test_trie, "test"); 

    cr_assert_neq(rc, 1, "trie_init() failed");
    
    trie_free(test_trie); 
}

Test(trie, free)
{
    trie_t *test_trie = trie_new("test"); 
    cr_assert_not_null(test_trie, "trie_new() failed");
    int rc = trie_free(test_trie); 

    cr_assert_neq(rc, 1, "trie_free() failed"); 
}
    
    
Test(trie, insert)
{
    trie_t* test_trie = trie_new("test");
    cr_assert_not_null(test_trie, "trie_new() failed");

    int rc_1 = trie_insert(test_trie, "hello"); 
    int rc_2 = trie_insert(test_trie,"bye bye"); 
    int rc_3 = trie_insert(test_trie, "I wish I could quit you"); 

    cr_assert_eq(rc_1, 0, "trie_insert() failed");
    cr_assert_eq(rc_2, 0, "trie_insert() failed");
    cr_assert_eq(rc_3, 0, "trie_insert() failed");
 
    trie_free(test_trie); 
}
 
Test(trie, contains)
{
    trie_t* test_trie = trie_new("test");
    cr_assert_not_null(test_trie, "trie_new() failed");

    trie_insert(test_trie,"hi");
    trie_insert(test_trie, "bye bye");

    int rc_1 = trie_contains(test_trie, "hi"); 
    int rc_2 = trie_contains(test_trie, "bye bye"); 
    int rc_3 = trie_contains(test_trie, "uuu"); 

    cr_assert_eq(rc_1, 0,"trie_contains() does not work");
    cr_assert_eq(rc_2, 0,"trie_contains() does not work");
    cr_assert_eq(rc_3, 1,"trie_contains() does not work");
    
    trie_free(test_trie); 
} 
/*
Test(trie, completions) {
    trie_t* test_trie = trie_new("test");
    cr_assert_not_null(test_trie, "trie_new() failed");

    trie_insert(test_trie,"app");
    trie_insert(test_trie,"apple");
    trie_insert(test_trie,"apples");

    int rc_1 = trie_completions(test_trie, "a");
    int rc_2 = trie_completions(test_trie, "appl");
    int rc_3 = trie_completions(test_trie, "b");

    cr_assert_eq(rc_1, 3,"trie_completions() does not work");
    cr_assert_eq(rc_2, 2,"trie_completions() does not work");
    cr_assert_eq(rc_3, 0,"trie_completions() does not work");
    
    trie_free(test_trie); 
} 
*/
