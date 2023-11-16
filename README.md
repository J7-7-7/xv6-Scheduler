# xv6-Scheduler
Implementing lottery based scheduler on top of the default round robin scheduler in xv6. The processes can change the scheduler on runtime with a system call.

# Part 1 - Nice System Call
Having policies is the first step in implementing a non-trivial scheduler. For the sake of simplicity, you can implement the nice UNIX API as an extra system call. A higher nice value means lower priority. For more information type – man 2 nice on Linux system. Implement the nice system call in xv6.

# Part 2 - Random Number Generator
Lottery scheduling is a randomized heuristic. Hence, we need to design a pseudo-random number generator (PRNG). Since xv6 does not include a PNRG, you need to design one. This does not require strong randomness such as in cryptographic algorithms but a decent PRNG will do. Implement an in-kernel PRNG.

# Part 3 - Scheduler
Lottery scheduling works by assigning tickets to each of the processes in the system. Then, in each time slice, it randomly picks a ‘winning’ ticket. It is up to you to decide how many more tickets to assign less nice processes and vice versa. Implement lottery scheduling in xv6.
