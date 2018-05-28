#include <stdio.h>
#include <stdlib.h>

#include "trie.h"

int main()
{
	trie_t *test1 = trie_new("test1");

	trie_insert(test1, "hello");
	printf("trie_contains(test1, \"hello\"): %d\n", trie_contains(test1, "hello")); // is a word
	printf("trie_contains(test1, \"helloo\"): %d\n", trie_contains(test1, "helloo")); // not a word
	printf("trie_contains(test1, \"he\"): %d\n", trie_contains(test1, "he")); // is a prefix
	free(test1);

	return 0;
}
