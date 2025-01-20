cd ~/Work/minishell/libft
ls | cat -e > test
cd ~/Work
ls
ls | cat -e | echo '
ls | cat -e |
VAR$=$VAR  ==> VAR$=cat
$-
echo $(cat $(echo "-e main.c")) == echo $($VAR $(echo "-e main.c") | $(cat -e))
echo eabc$VAR"$VAR"$VAR'abc'

echo $(find . -name "*.c" | grep -v "libft" |sed 's/.\///')
