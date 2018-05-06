Welcome to the example API provided by AK, Neha, Vanessa, and Alan!

## This *EXAMPLE* API uses an existing Redis data structure called "sorted sets."
  * More information about existing Redis data structures can be found at:
     https://redis.io/topics/data-types
  * The available commands for the sorted set data structure can be found at:
     https://redis.io/commands#sorted_set

# Purpose
The purpose of this example is to allow the application teams (or whoever is using
the trie data structure) to familiarize themselves with what sort of commands are
provided to them.

# Onto the juicy bits...

Suppose we have a game where users are required to defuse a bomb. To defuse the bomb,
each user has to solve six (possibly seven) puzzles. For each puzzle a user defuses,
they get ten points. For each puzzle a user defuses incorrectly, the bomb goes BOOM,
and they lose one point.

Now, let's say you are asked to implement a leaderboard to keep track of how many
phases each user has defused. You will need to have (basic) functionality for:

  1) Adding/removing users to the leaderboard
  2) Incrementing/decrementing scores for each user
  3) Ordering the users by score (in either ascending/descending order)
  4) Find a specific user's score
  5) Determine the number of users who have successfully defused the bomb (solved
     every puzzle)

  (Of course, your leaderboard isn't limited to doing just these three tasks. But,
   let's keep our leaderboard minimal for the sake of simplicity.)

So, in order to write this leaderboard application, you have to access and manipulate
data on the Redis server. That means you have to dive deep into the Redis
documentation and figure out how to download and compile the server files, how to
connect to the server, how to talk to the server, etc - sounds fun, right? Luckily,
an API (application programming interface) simplifies this process because our API
will handle talking to the Redis server for you! So, all you have to do in order
to access and manipulate data on the Redis server is to familiarize yourself
with the functions we provide (which is friendly, I swear!) Furthermore, if our
current library of functions do not offer the functionality you or your team
requires, feel free to holler at us on the #general Slack channel!

# Use Cases
Let's dive into the use cases for the leaderboard of this bomb game:

1) You want to write a function that adds a new user to the leaderboard. How
   do you access and add a new user to the data structure stored on the server?

  - Call our function addUser(char \*name) or removeUser(char \*name), where name is
    the name of the user you want to add to the leaderboard.

2) A user has just correctly (or incorrectly) defused one phase of the bomb! You
   want to write a function that updates the leaderboard to reflect this change.
   How do you manipulate the data associated with this user?

  - To increment the score, call our function incrScore(char \*name), or to decrement
    the score, call our function decrScore(char *name)!

3) You want to write a function that returns the current state of the leaderboard,
   either in ascending or descending order of score. How can you print out every
   entry in the leaderboard data structure?

  - Call our function getAscnd() to get the leaderboard with scores in
    ascending order, or getDscnd() to get the leaderboard with score in
    descending order!

4) You want to find a user's current score.

  - Call our function getScore(char \*name) and it will returns the user's score!

5) You want to figure out who have already defused the bomb.

  - Call our function getDefused() and it will return a list of users who succeded!

# TL;DR TL;DR TL;DR TL;DR TL;DR TL;DR

The point of this example API is to let you know that you don't need to worry about
talking with the Redis server, because we'll do that for you. All you need to do
to access and manipulate data on the Redis server is call the functions we provide.
If our functions don't provide the functionality you desire, let us know on Slack
(or anywhere else) so we can implement it for you!
