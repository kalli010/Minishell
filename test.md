
(/bin/echo 1 | /bin/echo 2 && ((/bin/echo 3 | /bin/echo 3) | (/bin/echo 4 | /bin/echo 4)))

8
syntax error

(minishell)-> export GHOST=1234
munmap_chunk(): invalid pointer
[1]    550782 IOT instruction (core dumped)  ./minishell


