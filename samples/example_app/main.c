#include <stdlib.h>
#include <stdio.h>

#include "api/include/trie.h"

int main() {
//	foo();
	char buf[512];
	printf("%s\n", getcwd(buf, 512));
	trie_t* new_trie = trie_new("test");
	printf("trie_insert: %d\n", trie_insert(new_trie, "apples"));
	trie_free(new_trie);
	return 0;
}

