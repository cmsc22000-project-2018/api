__ PLEASE READ THIS __

In order for the example API to run correctly, you will need to
install Redis and Hiredis. We'll guide you through this. We will
be using a uniform environment for the sake of avoiding nasty
system dependency errors. For this reason, everyone should run
their tests on a CS Virtual Machine. For more information about
CS VM's, please refer to: https://howto.cs.uchicago.edu/vm:index

# Installing Redis

Run the following commands:
```
$ wget http://download.redis.io/redis-stable.tar.gz  
$ tar xvzf redis-stable.tar.gz  
$ cd redis-stable  
$ make  
$ sudo make install  
```

# Installing Hiredis

Run the following commands:
```
$ git clone https://github.com/redis/hiredis.git  
$ cd hiredis  
$ make  
$ sudo make install  
$ sudo ldconfig  
```

# Testing out the API

Run the following commands:  
```
$ make  
$ ./example  
```

# Notes
* zset_add & zset_rem will print "(null)", but rest assured that they went
through to the Redis server.
* If it doesn't compile, let the API team know in the Facebook/Slack groups.
* Any questions? Let us know in the Facebook/Slack groups!

- API Team
