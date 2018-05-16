#include <stdio.h>
#include "api.h"
#include <string.h>
#include <stdlib.h>
#include "./hiredis/hiredis.h"

int main()
{
	session_t *s = malloc(sizeof(session_t));
	s->context = connect("127.0.0.1", 6379);
	if(connected(s)){
		set_add(s, "movies", "rear window", 8.9);
		set_add(s, "movies", "akira",8.2);
		set_add(s, "movies", "brokeback mountain",9.7);
		set_rem(s, "movies","rear window");
		set_incr(s,"movies","akira",1);
		set_decr(s,"movies","rear window",2); 	
	}
}
