# minishell

This project is to create a simple shell. Concepts about processes and file descriptors are introduced.

Working on this project allows you to travel through time and come back to problems people faced when Windows didn't exist.

Technical considerations
The following elements need to work like in bash

Show a prompt when waiting for a new command

Search and launch the right executable (based on the $PATH variable or by using relative or absolute path)

Implement the below builtins:

echo with option ā-nā
cd with only a relative or absolute path
pwd without any options
export without any options
unset without any options
env without any options and any arguments
exit without any options
; to separate commands

Pipes |

' and " except for multiline commands

Redirections < > >> except for file descriptor aggregation

Environment variables ($ followed by characters)

$? to store exit status of the previous command

ctrl-C, ctrl-D and ctrl-\

