minishell -> 
(echo) hi
hi  (9)
  
  (1)
    echo  (9)




minishell -> (echo)hi
hi  (9)
  echo  (9)




minishell -> ^C
┌───(ayel-mou@itami)-[~/Desktop/Minishell][main*] 
└─$ bash                 
ayel-mou@c4r2p10:~/Desktop/Minishell$ 
(echo) hi
bash: syntax error near unexpected token `hi'


minishell -> (echo) hi hi (9)

(1) echo (9)

minishell -> (echo)hi hi (9) echo (9)





ayel-mou@c4r2p10:~/Desktop/Minishell$ 
(echo) hi
bash: syntax error near unexpected token `hi'
ayel-mou@c4r2p10:~/Desktop/Minishell$ (echo hi && ((echo hi && (echo hi) && echo hi)))
hi
bash: ((: echo hi && (echo hi) && echo hi: syntax error in expression (error token is "hi && (echo hi) && echo hi")
ayel-mou@c4r2p10:~/Desktop/Minishell$ ./
bonus/       execute_all/ includes/    minishell    .vscode/
bulutins/    .git/        lib/         utils/       
ayel-mou@c4r2p10:~/Desktop/Minishell$ ./minishell 
minishell -> (echo hi && ((echo hi && (echo hi) && echo hi)))
Segmentation fault (core dumped)
ayel-mou@c4r2p10:~/Desktop/Minishell$ 



minishell -> ls | cat << stop | ls -la > out0| cat << stop1 | ls | cat << stop2 | ls -la >> out | cat << stop3
9
syntax error

cat < Makefile > out >> out1 | wc -l out1 > out2 


./minishell
minishell -> 
[1]    306031 segmentation fault (core dumped)  ./minishell


ayel-mou@c4r2p10:~/Desktop/Minishell$ /bin/echo /bin/echo
/bin/echo

