# pipex

## Fact

every process has their own file descriptor system, including STDIN and STDOUT 

## pipe()

first initialize a `int fd[2]`, then make it a pipe `pipe(fd)`

the pipe is a ONE way communication tool.

`fd[0]` refers to the read end of the pipe. (IN)

`fd[1]` refers to the write end of the pipe. (OUT)

`pipe()` returns 0 on success, returns -1 on error.

## fork()

fork() returns the child pid in parent process, returns 0 in the child process

##dup2()

`dup2(fd[1], STDOUT_FILENO)` redirect the stdout to fd[1], so whatever originally output to the terminal(stdout) will go to the pipe.
