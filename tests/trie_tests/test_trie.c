#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../include/api/trie.h"

Test(trie, new)
{
    trie_t* test1 = trie_new("test1");
    cr_assert_not_null(test1, "trie_new failed\n");
}

Test(trie, insert)
{
    trie_t* test1 = trie_new("test1");
    cr_assert_neq(trie_insert(test1, "hello"),1,"trie_insert does not work");
    cr_assert_neq(trie_insert(test1,"bye bye"),1,"trie_insert does not work");
    cr_assert_neq(trie_insert(test1,"I wish I could quit you"),1,"trie_insert does not work");
}

Test(trie, contains)
{
    trie_t* test1 = trie_new("test1");
    trie_insert(test1,"hello");
    trie_insert(test1, "bye bye");
    cr_assert_neq(trie_contains(test1, "hello"),-1,"trie_contains does not work");
    cr_assert_neq(trie_contains(test1,"bye bye"),-1,"trie_containes does not work");
    cr_assert_eq(trie_contains(test1,"uuu"),-1,"trie_contains does not work");
} 
