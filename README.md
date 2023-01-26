# pipex

## pipe()

first initialize a `int fd[2]`, then make it a pipe `pipe(fd)`

the pipe is a ONE way communication tool.

`fd[0]` refers to the read end of the pipe.

`fd[1]` refers to the write end of the pipe.

`pipe()` returns 0 on success, returns -1 on error.

## fork()

fork() returns the child pid in parent process, returns 0 in the child process

