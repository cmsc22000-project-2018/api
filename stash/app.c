#include <stdio.h>
#include <stdlib.h>

#include "app.h"
#include "api.h"

/* see app.c */
leaderboard_t *new_leaderboard()
{
  leaderboard_t *l;
  
  l = malloc(sizeof(leaderboard_t));

  if (l == NULL)
  {
    fprintf(stderr, "error leaderboard_new: could not allocate mem\n");
    return NULL;
  }

  l->session = NULL;

  return l;
}

int add_player(session_t *s, char *name)
{
  if (name != NULL)
  {
    int rt = set_add(s, name);

    if (rt == 1)
    {
      printf("user succesfully added to leaderboard!\n");
      return 1;
    }
    else
    {
      fprintf(stderr, "error add_player: something wrong with addUser()!\n");
      return 0;
    }
  }

  else
  {
    fprintf(stderr, "error add_player: name is null!\n");
    return 0; //FAILURE
  }
}

int remove_player(session_t *s, char *name)
{
  if (name != NULL)
  {
    int rt = set_rem(s, name);

    if (rt == 1)
    {
      printf("user succesfully removed from leaderboard!\n");
      return 1;
    }
    else
    {
      fprintf(stderr, "error remove_player: something wrong with removeUser()!\n");
      return 0;
    }
  }

  else
  {
    fprintf(stderr, "error remove_player: name is null!\n");
    return 0;
  }
}

/*

int main() 
{
  leaderboard_t *l = new_leaderboard();

  add_player(l->session, "Lil Pump");
  add_player(l->session, "Big Pump");
  add_player(l->session, "Too Chainz");
  remove_player(l->session, "Big Pump");
}

*/
