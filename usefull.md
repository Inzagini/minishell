cd ~/Work/minishell/libft  // check what happens if you exit directly after (without additional args). exit code 1 seems fine, but still weird?
ls | cat -e > test
cd ~/Work
ls
ls | cat -e | echo '
ls | cat -e |
ls | cat -e >

VAR$=$VAR  ==> VAR$=cat
$-
echo $(cat $(echo "-e main.c")) == echo $($VAR $(echo "-e main.c") | $(cat -e))
echo eabc$VAR"$VAR"$VAR'abc'

echo $(find . -name "*.c" | grep -v "libft" |sed 's/.\///')
