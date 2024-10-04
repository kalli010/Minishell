
///////////////////////////////////////////////////ayoub//////////////////////////////////////////

------------------------------------------------------------------------------------------------

fuck my life 
handling error and exit
(minishell)-> ./m
./m  (13)
(null) 
ana hana

------------------------------------------------------------------------------------------------

(minishell)-> cat >| ls 
|  (0)
  >  (0)
    cat  (0)
  ls  (0)
'|'    bonus	  execute_all   lib   Makefile	  signal    tmp
 bin   bulutins   includes      ls    minishell   test.md   utils

------------------------------------------------------------------------------------------------

(minishell)->  sa "|| ||"  > "sa"
>  (0)
  sa  (0)
    || ||  (0)
  sa  (0)

------------------------------------------------------------------------------------------------

(minishell)-> rm -rf /nfs/homes/zelkalai/projects/13_projects/Minishell/fd/
rm  (0)
  -rf  (0)
  /nfs/homes/zelkalai/projects/13_projects/Minishell/fd/  (0)
(minishell)-> pwd
pwd  (0)
minishell : pwd: Could not get cwd

------------------------------------------------------------------------------------------------

//////////////////////////////////////////////////zaki/////////////////////////////////////////////

------------------------------------------------------------------------------------------------
|  (0)
 khassha tkon syntax error 
echo $HOME$NOTHING$USER$

------------------------------------------------------------------------------------------------

(minishell)-> echo ds > "  "

Program received signal SIGSEGV, Segmentation fault.
0x00000000004051fb in count_words (str=0x47db30 "\"") at utils/lparsiiiing.c:303
303	      while(str[++i] != q);
(gdb) 

------------------------------------------------------------------------------------------------

(minishell)-> < /dev/stdin cat | cat > /dev/stdout
>  (5)
  |  (2)
    <  (7)
      /dev/stdin  (13)
      cat  (9)
    cat  (1)
  /dev/stdout  (13)


fi had l case cat not argument khassha tkon command

------------------------------------------------------------------------------------------------
(minishell)-> 

Program received signal SIGSEGV, Segmentation fault.
0x00000000004087e0 in remove_quotes (list=0x0) at utils/lparsiiiing.c:1221
1221	  q_n = count_quotes(list->content);
(gdb) 


(minishell)-> "   hi "'"'
   hi   (0)
minishell:    hi : command not found
free(): invalid pointer
[1]    96584 IOT instruction (core dumped)  ./minishell
FAIL

(minishell)-> "'"
[1]    97070 segmentation fault (core dumped)  ./minishell
FAIL
(minishell)-> "'"
  (0)
minishell : : command not found
(minishell)-> 'malloc(): invalid size (unsorted)
[1]    97117 IOT instruction (core dumped)  ./minishell
FAIL

------------------------------------------------------------------------------------------------

(minishell)-> ls 
ls
ls  (0)
  
ls  (0)
/usr/bin/ls: cannot access ''$'\n''ls': No such file or directory

------------------------------------------------------------------------------------------------

(minishell)-> cat <| ls
|  (0)
  <  (0)
    cat  (0)
  ls  (0)
'|'    bonus	  execute_all   lib   Makefile	  signal    tmp
 bin   bulutins   includes      ls    minishell   test.md   utils

------------------------------------------------------------------------------------------------

(minishell)-> cat > |  ls
|  (0)
  >  (0)
    cat  (0)
  ls  (0)
'|'    bonus	  execute_all   lib   Makefile	  signal    tmp
 bin   bulutins   includes      ls    minishell   test.md   utils

------------------------------------------------------------------------------------------------

(minishell)-> unset HOME
unset  (0)
  HOME  (0)
free(): double free detected in tcache 2
Aborted (core dumped)

------------------------------------------------------------------------------------------------

(minishell)-> cd
cd  (0)
(minishell)-> pwd
pwd  (0)
/
(minishell)-> cd 
cd  (0)
free(): double free detected in tcache 2
Aborted (core dumped)

------------------------------------------------------------------------------------------------

export HOME="\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"
malloc error;

------------------------------------------------------------------------------------------------

(minishell)-> export "asd"="dasd"
free(): invalid pointer
Aborted (core dumped)

------------------------------------------------------------------------------------------------

(minishell)-> export "asdasd"
free(): double free detected in tcache 2
Aborted (core dumped)

------------------------------------------------------------------------------------------------

(minishell)-> echo $: dsa
echo  (0)
    (0)

(minishell)-> export "sda ==========""dfs"
free(): invalid pointer
Aborted (core dumped)

------------------------------------------------------------------------------------------------

(minishell)-> << ls
> dasd
> fefadasd
> ls
Segmentation fault (core dumped)

------------------------------------------------------------------------------------------------

(minishell)-> cat << "das"
> $HOME
> $USER
> das
<  (0)
  cat  (0)
  /tmp/.redfile0  (0)
$HOME
$USER
(minishell)-> cat << das
> $HOME
> $USER
> das
<  (0)
  cat  (0)
  /tmp/.redfile0  (0)
$HOME
$USER

------------------------------------------------------------------------------------------------

(minishell)-> $fsadfsdf << ls
> asd
> ls
  (0)
minishell : : command not found

------------------------------------------------------------------------------------------------

(minishell)->  $gjsdgsdf $vdjghdslk $lfsh ls
  (0)
    (0)
    (0)
  ls  (0)
minishell : : command not found

------------------------------------------------------------------------------------------------

zelkalai@c4r3p10:~/projects/13_projects/Minishell$ export $ls=ls
bash: export: `=ls': not a valid identifier

------------------------------------------------------------------------------------------------

(minishell)-> $ls $op
minishell: malloc.c:4302: _int_malloc: Assertion `(unsigned long) (size) >= (unsigned long) (nb)' failed.
Aborted (core dumped)

------------------------------------------------------------------------------------------------

(minishell)-> ls $gdsgsd $fsdaff $op
ls  (0)
    (0)
    (0)
  -a  (0)
  -s  (0)
/usr/bin/ls: cannot access '': No such file or directory
/usr/bin/ls: cannot access '': No such file or directory

------------------------------------------------------------------------------------------------

(minishell)-> export dat="a b c d"
export $dat="waw"
export
------>normalment export a b c d="waw"
