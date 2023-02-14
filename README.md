# pipex

## Check

use `valgrind --track-fds=yes` to check if all fds are properly closed.

check memory leak when error encountered.

## Fact

every process has their own file descriptor system, including STDIN and STDOUT 

`open("file", O_CREAT | O_WRONLY | O_TRUNC)` is the same as `creat("file")`

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

## execve

`exec` family replace the process image, statment after `exec` will only be executed in case of error

```
if (execve(SOMETHING) == -1)
  perror("error");
```
## access()

`int access(const char *pathname, int mode);`

`F_OK` check for the existence of the file

`W_OK` `R_OK` `X_OK` check for write, read and execute permission respectively

`access` return 0 on success, -1 when fail for mode check (the file does not exist when F_OK is flagged)

## Useful link

https://blog.csdn.net/wh128341/article/details/125906940 dup2 redirection, fd system, linux file system, inode, hard soft link, hard disk principle, (Chinese)


