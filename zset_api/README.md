******************* PLEASE READ THIS ****************************

No Makefile because not everyone has installed Redis and configured
Hiredis correctly. This code is dependent on proper setup!

HERE IS HOW TO SET UP REDIS:
https://redis.io/topics/quickstart

HERE IS HOW TO SET UP HIREDIS:
http://yular.github.io/2017/01/28/C-Redis-QuickStart/

When you've done the above two steps, call:

$ gcc -o test main.c api.c -lhiredis

* If it doesn't compile, let us know in the Facebook/Slack groups.

* If it segfaults, trace the call stack down to where the signal occurs,
and let us know in the Facebook/Slack groups!

Any questions? Let us know in the Facebook/Slack groups!

- API Team
