#!/bin/bash

RESET="\033[0m"
RED="\033[31;1m"
GREEN="\033[32;1m"
YELLOW="\033[33;1m"
BLUE="\033[34;1m"
MAGENTA="\033[35;1m"
CYAN="\033[36;1m"

echo -e $YELLOW "========== TEST 1 ==========" $RESET
echo
echo -e $YELLOW "Without argument :" $RESET
echo -e $YELLOW "> ./ft_ls :" $RESET
echo

./ft_ls > /tmp/user.txt
ls > /tmp/expected.txt

diff /tmp/user.txt /tmp/expected.txt > /tmp/logs

if [[ $? -ne 0 ]]; then
	echo -e $RED "Diff KO :" $RESET
	diff -au --color=always /tmp/user.txt /tmp/expected.txt
else
	echo -e $GREEN "Diff OK !" $RESET
fi

echo
echo -e $YELLOW "Valgrind check :" $RESET
echo

valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls 2> /tmp/valgrind_logs > /tmp/logs

cat /tmp/valgrind_logs | grep -q "All heap blocks were freed -- no leaks are possible" && \
cat /tmp/valgrind_logs | grep -q "ERROR SUMMARY: 0 errors from 0 contexts" && \
cat /tmp/valgrind_logs | grep -q "FILE DESCRIPTORS: 3 open (3 std) at exit."

if [[ $? -ne 0 ]]; then
	echo -e $RED "Valgrind KO :"
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls > /tmp/logs
	echo -ne $RESET
else
	echo -e $GREEN "Valgrind OK !" $RESET
fi



echo
echo -e $YELLOW "========== TEST 2 ==========" $RESET
echo
echo -e $YELLOW "With a file :" $RESET
echo -e $YELLOW "> ./ft_ls ft_ls :" $RESET
echo

./ft_ls ft_ls > /tmp/user.txt
ls ft_ls > /tmp/expected.txt

diff /tmp/user.txt /tmp/expected.txt > /tmp/logs

if [[ $? -ne 0 ]]; then
	echo -e $RED "Diff KO :" $RESET
	diff -au --color=always /tmp/user.txt /tmp/expected.txt
else
	echo -e $GREEN "Diff OK !" $RESET
fi

echo
echo -e $YELLOW "Valgrind check :" $RESET
echo

valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls ft_ls 2> /tmp/valgrind_logs > /tmp/logs

cat /tmp/valgrind_logs | grep -q "All heap blocks were freed -- no leaks are possible" && \
cat /tmp/valgrind_logs | grep -q "ERROR SUMMARY: 0 errors from 0 contexts" && \
cat /tmp/valgrind_logs | grep -q "FILE DESCRIPTORS: 3 open (3 std) at exit."

if [[ $? -ne 0 ]]; then
	echo -e $RED "Valgrind KO :"
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls ft_ls > /tmp/logs
	echo -ne $RESET
else
	echo -e $GREEN "Valgrind OK !" $RESET
fi



echo
echo -e $YELLOW "========== TEST 3 ==========" $RESET
echo
echo -e $YELLOW "With a file and a directory :" $RESET
echo -e $YELLOW "> ./ft_ls ft_ls libft/ :" $RESET
echo

./ft_ls ft_ls libft/ > /tmp/user.txt
ls ft_ls libft/ > /tmp/expected.txt

diff /tmp/user.txt /tmp/expected.txt > /tmp/logs

if [[ $? -ne 0 ]]; then
	echo -e $RED "Diff KO :" $RESET
	diff -au --color=always /tmp/user.txt /tmp/expected.txt
else
	echo -e $GREEN "Diff OK !" $RESET
fi

echo
echo -e $YELLOW "Valgrind check :" $RESET
echo

valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls ft_ls libft/ 2> /tmp/valgrind_logs > /tmp/logs

cat /tmp/valgrind_logs | grep -q "All heap blocks were freed -- no leaks are possible" && \
cat /tmp/valgrind_logs | grep -q "ERROR SUMMARY: 0 errors from 0 contexts" && \
cat /tmp/valgrind_logs | grep -q "FILE DESCRIPTORS: 3 open (3 std) at exit."

if [[ $? -ne 0 ]]; then
	echo -e $RED "Valgrind KO :"
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls ft_ls libft/ > /tmp/logs
	echo -ne $RESET
else
	echo -e $GREEN "Valgrind OK !" $RESET
fi



echo
echo -e $YELLOW "========== TEST 4 ==========" $RESET
echo
echo -e $YELLOW "With 3 files :" $RESET
echo -e $YELLOW "> ./ft_ls a b c :" $RESET
echo

touch a b c
./ft_ls a b c > /tmp/user.txt
ls a b c > /tmp/expected.txt

diff /tmp/user.txt /tmp/expected.txt > /tmp/logs

if [[ $? -ne 0 ]]; then
	echo -e $RED "Diff KO :" $RESET
	diff -au --color=always /tmp/user.txt /tmp/expected.txt
else
	echo -e $GREEN "Diff OK !" $RESET
fi

echo
echo -e $YELLOW "Valgrind check :" $RESET
echo

valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls a b c 2> /tmp/valgrind_logs > /tmp/logs

cat /tmp/valgrind_logs | grep -q "All heap blocks were freed -- no leaks are possible" && \
cat /tmp/valgrind_logs | grep -q "ERROR SUMMARY: 0 errors from 0 contexts" && \
cat /tmp/valgrind_logs | grep -q "FILE DESCRIPTORS: 3 open (3 std) at exit."

if [[ $? -ne 0 ]]; then
	echo -e $RED "Valgrind KO :"
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls a b c > /tmp/logs
	echo -ne $RESET
else
	echo -e $GREEN "Valgrind OK !" $RESET
fi

rm a b c



echo
echo -e $YELLOW "========== TEST 5 ==========" $RESET
echo
echo -e $YELLOW "With -l option :" $RESET
echo -e $YELLOW "> ./ft_ls -l :" $RESET
echo

./ft_ls -l > /tmp/user.txt
ls -l > /tmp/expected.txt

diff /tmp/user.txt /tmp/expected.txt > /tmp/logs

if [[ $? -ne 0 ]]; then
	echo -e $RED "Diff KO :" $RESET
	diff -au --color=always /tmp/user.txt /tmp/expected.txt
else
	echo -e $GREEN "Diff OK !" $RESET
fi

echo
echo -e $YELLOW "Valgrind check :" $RESET
echo

valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls -l 2> /tmp/valgrind_logs > /tmp/logs

cat /tmp/valgrind_logs | grep -q "All heap blocks were freed -- no leaks are possible" && \
cat /tmp/valgrind_logs | grep -q "ERROR SUMMARY: 0 errors from 0 contexts" && \
cat /tmp/valgrind_logs | grep -q "FILE DESCRIPTORS: 3 open (3 std) at exit."

if [[ $? -ne 0 ]]; then
	echo -e $RED "Valgrind KO :"
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls -l > /tmp/logs
	echo -ne $RESET
else
	echo -e $GREEN "Valgrind OK !" $RESET
fi



echo
echo -e $YELLOW "========== TEST 6 ==========" $RESET
echo
echo -e $YELLOW "With -a option :" $RESET
echo -e $YELLOW "> ./ft_ls -a :" $RESET
echo

./ft_ls -a > /tmp/user.txt
ls -a > /tmp/expected.txt

diff /tmp/user.txt /tmp/expected.txt > /tmp/logs

if [[ $? -ne 0 ]]; then
	echo -e $RED "Diff KO :" $RESET
	diff -au --color=always /tmp/user.txt /tmp/expected.txt
else
	echo -e $GREEN "Diff OK !" $RESET
fi

echo
echo -e $YELLOW "Valgrind check :" $RESET
echo

valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls -a 2> /tmp/valgrind_logs > /tmp/logs

cat /tmp/valgrind_logs | grep -q "All heap blocks were freed -- no leaks are possible" && \
cat /tmp/valgrind_logs | grep -q "ERROR SUMMARY: 0 errors from 0 contexts" && \
cat /tmp/valgrind_logs | grep -q "FILE DESCRIPTORS: 3 open (3 std) at exit."

if [[ $? -ne 0 ]]; then
	echo -e $RED "Valgrind KO :"
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls -a > /tmp/logs
	echo -ne $RESET
else
	echo -e $GREEN "Valgrind OK !" $RESET
fi



echo
echo -e $YELLOW "========== TEST 7 ==========" $RESET
echo
echo -e $YELLOW "With -r option :" $RESET
echo -e $YELLOW "> ./ft_ls -r :" $RESET
echo

./ft_ls -r > /tmp/user.txt
ls -r > /tmp/expected.txt

diff /tmp/user.txt /tmp/expected.txt > /tmp/logs

if [[ $? -ne 0 ]]; then
	echo -e $RED "Diff KO :" $RESET
	diff -au --color=always /tmp/user.txt /tmp/expected.txt
else
	echo -e $GREEN "Diff OK !" $RESET
fi

echo
echo -e $YELLOW "Valgrind check :" $RESET
echo

valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls -r 2> /tmp/valgrind_logs > /tmp/logs

cat /tmp/valgrind_logs | grep -q "All heap blocks were freed -- no leaks are possible" && \
cat /tmp/valgrind_logs | grep -q "ERROR SUMMARY: 0 errors from 0 contexts" && \
cat /tmp/valgrind_logs | grep -q "FILE DESCRIPTORS: 3 open (3 std) at exit."

if [[ $? -ne 0 ]]; then
	echo -e $RED "Valgrind KO :"
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls -r > /tmp/logs
	echo -ne $RESET
else
	echo -e $GREEN "Valgrind OK !" $RESET
fi



echo
echo -e $YELLOW "========== TEST 8 ==========" $RESET
echo
echo -e $YELLOW "With -t option :" $RESET
echo -e $YELLOW "> ./ft_ls -t :" $RESET
echo

./ft_ls -t > /tmp/user.txt
ls -t > /tmp/expected.txt

diff /tmp/user.txt /tmp/expected.txt > /tmp/logs

if [[ $? -ne 0 ]]; then
	echo -e $RED "Diff KO :" $RESET
	diff -au --color=always /tmp/user.txt /tmp/expected.txt
else
	echo -e $GREEN "Diff OK !" $RESET
fi

echo
echo -e $YELLOW "Valgrind check :" $RESET
echo

valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls -t 2> /tmp/valgrind_logs > /tmp/logs

cat /tmp/valgrind_logs | grep -q "All heap blocks were freed -- no leaks are possible" && \
cat /tmp/valgrind_logs | grep -q "ERROR SUMMARY: 0 errors from 0 contexts" && \
cat /tmp/valgrind_logs | grep -q "FILE DESCRIPTORS: 3 open (3 std) at exit."

if [[ $? -ne 0 ]]; then
	echo -e $RED "Valgrind KO :"
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls -t > /tmp/logs
	echo -ne $RESET
else
	echo -e $GREEN "Valgrind OK !" $RESET
fi



echo
echo -e $YELLOW "========== TEST 9 ==========" $RESET
echo
echo -e $YELLOW "With -R option :" $RESET
echo -e $YELLOW "> ./ft_ls -R :" $RESET
echo

./ft_ls -R > /tmp/user.txt
ls -R > /tmp/expected.txt

diff /tmp/user.txt /tmp/expected.txt > /tmp/logs

if [[ $? -ne 0 ]]; then
	echo -e $RED "Diff KO :" $RESET
	diff -au --color=always /tmp/user.txt /tmp/expected.txt
else
	echo -e $GREEN "Diff OK !" $RESET
fi

echo
echo -e $YELLOW "Valgrind check :" $RESET
echo

valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls -R 2> /tmp/valgrind_logs > /tmp/logs

cat /tmp/valgrind_logs | grep -q "All heap blocks were freed -- no leaks are possible" && \
cat /tmp/valgrind_logs | grep -q "ERROR SUMMARY: 0 errors from 0 contexts" && \
cat /tmp/valgrind_logs | grep -q "FILE DESCRIPTORS: 3 open (3 std) at exit."

if [[ $? -ne 0 ]]; then
	echo -e $RED "Valgrind KO :"
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls -R > /tmp/logs
	echo -ne $RESET
else
	echo -e $GREEN "Valgrind OK !" $RESET
fi



echo
echo -e $YELLOW "========== TEST 10 ==========" $RESET
echo
echo -e $YELLOW "With -la option :" $RESET
echo -e $YELLOW "> ./ft_ls -la :" $RESET
echo

./ft_ls -la > /tmp/user.txt
ls -la > /tmp/expected.txt

diff /tmp/user.txt /tmp/expected.txt > /tmp/logs

if [[ $? -ne 0 ]]; then
	echo -e $RED "Diff KO :" $RESET
	diff -au --color=always /tmp/user.txt /tmp/expected.txt
else
	echo -e $GREEN "Diff OK !" $RESET
fi

echo
echo -e $YELLOW "Valgrind check :" $RESET
echo

valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls -la 2> /tmp/valgrind_logs > /tmp/logs

cat /tmp/valgrind_logs | grep -q "All heap blocks were freed -- no leaks are possible" && \
cat /tmp/valgrind_logs | grep -q "ERROR SUMMARY: 0 errors from 0 contexts" && \
cat /tmp/valgrind_logs | grep -q "FILE DESCRIPTORS: 3 open (3 std) at exit."

if [[ $? -ne 0 ]]; then
	echo -e $RED "Valgrind KO :"
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls -la > /tmp/logs
	echo -ne $RESET
else
	echo -e $GREEN "Valgrind OK !" $RESET
fi



echo
echo -e $YELLOW "========== TEST 11 ==========" $RESET
echo
echo -e $YELLOW "With -lra option :" $RESET
echo -e $YELLOW "> ./ft_ls -lra :" $RESET
echo

./ft_ls -lra > /tmp/user.txt
ls -lra > /tmp/expected.txt

diff /tmp/user.txt /tmp/expected.txt > /tmp/logs

if [[ $? -ne 0 ]]; then
	echo -e $RED "Diff KO :" $RESET
	diff -au --color=always /tmp/user.txt /tmp/expected.txt
else
	echo -e $GREEN "Diff OK !" $RESET
fi

echo
echo -e $YELLOW "Valgrind check :" $RESET
echo

valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls -lra 2> /tmp/valgrind_logs > /tmp/logs

cat /tmp/valgrind_logs | grep -q "All heap blocks were freed -- no leaks are possible" && \
cat /tmp/valgrind_logs | grep -q "ERROR SUMMARY: 0 errors from 0 contexts" && \
cat /tmp/valgrind_logs | grep -q "FILE DESCRIPTORS: 3 open (3 std) at exit."

if [[ $? -ne 0 ]]; then
	echo -e $RED "Valgrind KO :"
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls -lra > /tmp/logs
	echo -ne $RESET
else
	echo -e $GREEN "Valgrind OK !" $RESET
fi



echo
echo -e $YELLOW "========== TEST 12 ==========" $RESET
echo
echo -e $YELLOW "With -lrat option :" $RESET
echo -e $YELLOW "> ./ft_ls -lrat :" $RESET
echo

./ft_ls -lrat > /tmp/user.txt
ls -lrat > /tmp/expected.txt

diff /tmp/user.txt /tmp/expected.txt > /tmp/logs

if [[ $? -ne 0 ]]; then
	echo -e $RED "Diff KO :" $RESET
	diff -au --color=always /tmp/user.txt /tmp/expected.txt
else
	echo -e $GREEN "Diff OK !" $RESET
fi

echo
echo -e $YELLOW "Valgrind check :" $RESET
echo

valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls -lrat 2> /tmp/valgrind_logs > /tmp/logs

cat /tmp/valgrind_logs | grep -q "All heap blocks were freed -- no leaks are possible" && \
cat /tmp/valgrind_logs | grep -q "ERROR SUMMARY: 0 errors from 0 contexts" && \
cat /tmp/valgrind_logs | grep -q "FILE DESCRIPTORS: 3 open (3 std) at exit."

if [[ $? -ne 0 ]]; then
	echo -e $RED "Valgrind KO :"
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls -lrat > /tmp/logs
	echo -ne $RESET
else
	echo -e $GREEN "Valgrind OK !" $RESET
fi



echo
echo -e $YELLOW "========== TEST 13 ==========" $RESET
echo
echo -e $YELLOW "With -lR option :" $RESET
echo -e $YELLOW "> ./ft_ls -lR :" $RESET
echo

./ft_ls -lR > /tmp/user.txt
ls -lR > /tmp/expected.txt

diff /tmp/user.txt /tmp/expected.txt > /tmp/logs

if [[ $? -ne 0 ]]; then
	echo -e $RED "Diff KO :" $RESET
	diff -au --color=always /tmp/user.txt /tmp/expected.txt
else
	echo -e $GREEN "Diff OK !" $RESET
fi

echo
echo -e $YELLOW "Valgrind check :" $RESET
echo

valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls -lR 2> /tmp/valgrind_logs > /tmp/logs

cat /tmp/valgrind_logs | grep -q "All heap blocks were freed -- no leaks are possible" && \
cat /tmp/valgrind_logs | grep -q "ERROR SUMMARY: 0 errors from 0 contexts" && \
cat /tmp/valgrind_logs | grep -q "FILE DESCRIPTORS: 3 open (3 std) at exit."

if [[ $? -ne 0 ]]; then
	echo -e $RED "Valgrind KO :"
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls -lR > /tmp/logs
	echo -ne $RESET
else
	echo -e $GREEN "Valgrind OK !" $RESET
fi



echo
echo -e $YELLOW "========== TEST 14 ==========" $RESET
echo
echo -e $YELLOW "With -aR option :" $RESET
echo -e $YELLOW "> ./ft_ls -aR :" $RESET
echo

./ft_ls -aR > /tmp/user.txt
ls -aR > /tmp/expected.txt

diff /tmp/user.txt /tmp/expected.txt > /tmp/logs

if [[ $? -ne 0 ]]; then
	echo -e $RED "Diff KO :" $RESET
	diff -au --color=always /tmp/user.txt /tmp/expected.txt
else
	echo -e $GREEN "Diff OK !" $RESET
fi

echo
echo -e $YELLOW "Valgrind check :" $RESET
echo

valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls -aR 2> /tmp/valgrind_logs > /tmp/logs

cat /tmp/valgrind_logs | grep -q "All heap blocks were freed -- no leaks are possible" && \
cat /tmp/valgrind_logs | grep -q "ERROR SUMMARY: 0 errors from 0 contexts" && \
cat /tmp/valgrind_logs | grep -q "FILE DESCRIPTORS: 3 open (3 std) at exit."

if [[ $? -ne 0 ]]; then
	echo -e $RED "Valgrind KO :"
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls -aR > /tmp/logs
	echo -ne $RESET
else
	echo -e $GREEN "Valgrind OK !" $RESET
fi



echo
echo -e $YELLOW "========== TEST 15 ==========" $RESET
echo
echo -e $YELLOW "With empty directory :" $RESET
echo -e $YELLOW "> ./ft_ls empty/ :" $RESET
echo

mkdir empty/
./ft_ls empty/ > /tmp/user.txt
ls empty/ > /tmp/expected.txt

diff /tmp/user.txt /tmp/expected.txt > /tmp/logs

if [[ $? -ne 0 ]]; then
	echo -e $RED "Diff KO :" $RESET
	diff -au --color=always /tmp/user.txt /tmp/expected.txt
else
	echo -e $GREEN "Diff OK !" $RESET
fi

echo
echo -e $YELLOW "Valgrind check :" $RESET
echo

valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls empty/ 2> /tmp/valgrind_logs > /tmp/logs

cat /tmp/valgrind_logs | grep -q "All heap blocks were freed -- no leaks are possible" && \
cat /tmp/valgrind_logs | grep -q "ERROR SUMMARY: 0 errors from 0 contexts" && \
cat /tmp/valgrind_logs | grep -q "FILE DESCRIPTORS: 3 open (3 std) at exit."

if [[ $? -ne 0 ]]; then
	echo -e $RED "Valgrind KO :"
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls empty/ > /tmp/logs
	echo -ne $RESET
else
	echo -e $GREEN "Valgrind OK !" $RESET
fi

rm -rf empty/



echo
echo -e $YELLOW "========== TEST 16 ==========" $RESET
echo
echo -e $YELLOW "With hidden file :" $RESET
echo -e $YELLOW "> ./ft_ls test :" $RESET
echo

mkdir test/
touch test/.a test/b
./ft_ls test > /tmp/user.txt
ls test > /tmp/expected.txt

diff /tmp/user.txt /tmp/expected.txt > /tmp/logs

if [[ $? -ne 0 ]]; then
	echo -e $RED "Diff KO :" $RESET
	diff -au --color=always /tmp/user.txt /tmp/expected.txt
else
	echo -e $GREEN "Diff OK !" $RESET
fi

echo
echo -e $YELLOW "Valgrind check :" $RESET
echo

valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls test 2> /tmp/valgrind_logs > /tmp/logs

cat /tmp/valgrind_logs | grep -q "All heap blocks were freed -- no leaks are possible" && \
cat /tmp/valgrind_logs | grep -q "ERROR SUMMARY: 0 errors from 0 contexts" && \
cat /tmp/valgrind_logs | grep -q "FILE DESCRIPTORS: 3 open (3 std) at exit."

if [[ $? -ne 0 ]]; then
	echo -e $RED "Valgrind KO :"
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls test > /tmp/logs
	echo -ne $RESET
else
	echo -e $GREEN "Valgrind OK !" $RESET
fi

rm -rf test/



echo
echo -e $YELLOW "========== TEST 17 ==========" $RESET
echo
echo -e $YELLOW "With hidden file and -a :" $RESET
echo -e $YELLOW "> ./ft_ls -a test :" $RESET
echo

mkdir test/
touch test/.a test/b
./ft_ls -a test > /tmp/user.txt
ls -a test > /tmp/expected.txt

diff /tmp/user.txt /tmp/expected.txt > /tmp/logs

if [[ $? -ne 0 ]]; then
	echo -e $RED "Diff KO :" $RESET
	diff -au --color=always /tmp/user.txt /tmp/expected.txt
else
	echo -e $GREEN "Diff OK !" $RESET
fi

echo
echo -e $YELLOW "Valgrind check :" $RESET
echo

valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls -a test 2> /tmp/valgrind_logs > /tmp/logs

cat /tmp/valgrind_logs | grep -q "All heap blocks were freed -- no leaks are possible" && \
cat /tmp/valgrind_logs | grep -q "ERROR SUMMARY: 0 errors from 0 contexts" && \
cat /tmp/valgrind_logs | grep -q "FILE DESCRIPTORS: 3 open (3 std) at exit."

if [[ $? -ne 0 ]]; then
	echo -e $RED "Valgrind KO :"
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls -a test > /tmp/logs
	echo -ne $RESET
else
	echo -e $GREEN "Valgrind OK !" $RESET
fi

rm -rf test/



echo
echo -e $YELLOW "========== TEST 18 ==========" $RESET
echo
echo -e $YELLOW "With big directory :" $RESET
echo -e $YELLOW "> ./ft_ls -aR :" $RESET
echo

mkdir big/
for i in $(seq 1 2000); do touch big/file_$i; done
./ft_ls big > /tmp/user.txt
ls big > /tmp/expected.txt

diff /tmp/user.txt /tmp/expected.txt > /tmp/logs

if [[ $? -ne 0 ]]; then
	echo -e $RED "Diff KO :" $RESET
	diff -au --color=always /tmp/user.txt /tmp/expected.txt
else
	echo -e $GREEN "Diff OK !" $RESET
fi

echo
echo -e $YELLOW "Valgrind check :" $RESET
echo

valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls big 2> /tmp/valgrind_logs > /tmp/logs

cat /tmp/valgrind_logs | grep -q "All heap blocks were freed -- no leaks are possible" && \
cat /tmp/valgrind_logs | grep -q "ERROR SUMMARY: 0 errors from 0 contexts" && \
cat /tmp/valgrind_logs | grep -q "FILE DESCRIPTORS: 3 open (3 std) at exit."

if [[ $? -ne 0 ]]; then
	echo -e $RED "Valgrind KO :"
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls big > /tmp/logs
	echo -ne $RESET
else
	echo -e $GREEN "Valgrind OK !" $RESET
fi

rm -rf big/



echo
echo -e $YELLOW "========== TEST 19 ==========" $RESET
echo
echo -e $YELLOW "With -laR option :" $RESET
echo -e $YELLOW "> ./ft_ls -laR :" $RESET
echo

./ft_ls -laR > /tmp/user.txt
ls -laR > /tmp/expected.txt

diff /tmp/user.txt /tmp/expected.txt > /tmp/logs

if [[ $? -ne 0 ]]; then
	echo -e $RED "Diff KO :" $RESET
	diff -au --color=always /tmp/user.txt /tmp/expected.txt
else
	echo -e $GREEN "Diff OK !" $RESET
fi

echo
echo -e $YELLOW "Valgrind check :" $RESET
echo

valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls -laR 2> /tmp/valgrind_logs > /tmp/logs

cat /tmp/valgrind_logs | grep -q "All heap blocks were freed -- no leaks are possible" && \
cat /tmp/valgrind_logs | grep -q "ERROR SUMMARY: 0 errors from 0 contexts" && \
cat /tmp/valgrind_logs | grep -q "FILE DESCRIPTORS: 3 open (3 std) at exit."

if [[ $? -ne 0 ]]; then
	echo -e $RED "Valgrind KO :"
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls -laR > /tmp/logs
	echo -ne $RESET
else
	echo -e $GREEN "Valgrind OK !" $RESET
fi



echo
echo -e $YELLOW "========== TEST 20 ==========" $RESET
echo
echo -e $YELLOW "With symbolic link :" $RESET
echo -e $YELLOW "> ./ft_ls link :" $RESET
echo

ln -s ft_ls link
./ft_ls link -l > /tmp/user.txt
ls link -l > /tmp/expected.txt

diff /tmp/user.txt /tmp/expected.txt > /tmp/logs

if [[ $? -ne 0 ]]; then
	echo -e $RED "Diff KO :" $RESET
	diff -au --color=always /tmp/user.txt /tmp/expected.txt
else
	echo -e $GREEN "Diff OK !" $RESET
fi

echo
echo -e $YELLOW "Valgrind check :" $RESET
echo

valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls link -l 2> /tmp/valgrind_logs > /tmp/logs

cat /tmp/valgrind_logs | grep -q "All heap blocks were freed -- no leaks are possible" && \
cat /tmp/valgrind_logs | grep -q "ERROR SUMMARY: 0 errors from 0 contexts" && \
cat /tmp/valgrind_logs | grep -q "FILE DESCRIPTORS: 3 open (3 std) at exit."

if [[ $? -ne 0 ]]; then
	echo -e $RED "Valgrind KO :"
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls link -l > /tmp/logs
	echo -ne $RESET
else
	echo -e $GREEN "Valgrind OK !" $RESET
fi

rm link



echo
echo -e $YELLOW "========== TEST 21 ==========" $RESET
echo
echo -e $YELLOW "With inexistant file :" $RESET
echo -e $YELLOW "> ./ft_ls nope :" $RESET
echo

./ft_ls nope 2> /tmp/user.txt
ls nope 2> /tmp/expected.txt

cat /tmp/user.txt | grep -q "ls: cannot access 'nope': No such file or directory"

if [[ $? -ne 0 ]]; then
	echo -e $RED "Diff KO :" $RESET
	diff -au --color=always /tmp/user.txt /tmp/expected.txt
else
	echo -e $GREEN "Diff OK !" $RESET
fi

echo
echo -e $YELLOW "Valgrind check :" $RESET
echo

valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls nope 2> /tmp/valgrind_logs > /tmp/logs

cat /tmp/valgrind_logs | grep -q "All heap blocks were freed -- no leaks are possible" && \
cat /tmp/valgrind_logs | grep -q "ERROR SUMMARY: 0 errors from 0 contexts" && \
cat /tmp/valgrind_logs | grep -q "FILE DESCRIPTORS: 3 open (3 std) at exit."

if [[ $? -ne 0 ]]; then
	echo -e $RED "Valgrind KO :"
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls nope > /tmp/logs
	echo -ne $RESET
else
	echo -e $GREEN "Valgrind OK !" $RESET
fi



echo
echo -e $YELLOW "========== TEST 22 ==========" $RESET
echo
echo -e $YELLOW "With no no access directory :" $RESET
echo -e $YELLOW "> ./ft_ls test/ :" $RESET
echo

mkdir test/
chmod 000 test/
./ft_ls test/ 2> /tmp/user.txt
ls test/ 2> /tmp/expected.txt

cat /tmp/user.txt | grep -q "ls: cannot open directory 'test/': Permission denied"

if [[ $? -ne 0 ]]; then
	echo -e $RED "Diff KO :" $RESET
	diff -au --color=always /tmp/user.txt /tmp/expected.txt
else
	echo -e $GREEN "Diff OK !" $RESET
fi

echo
echo -e $YELLOW "Valgrind check :" $RESET
echo

valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls test/ 2> /tmp/valgrind_logs > /tmp/logs

cat /tmp/valgrind_logs | grep -q "All heap blocks were freed -- no leaks are possible" && \
cat /tmp/valgrind_logs | grep -q "ERROR SUMMARY: 0 errors from 0 contexts" && \
cat /tmp/valgrind_logs | grep -q "FILE DESCRIPTORS: 3 open (3 std) at exit."

if [[ $? -ne 0 ]]; then
	echo -e $RED "Valgrind KO :"
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls test/ > /tmp/logs
	echo -ne $RESET
else
	echo -e $GREEN "Valgrind OK !" $RESET
fi

chmod 775 test/
rm -rf test/



echo
echo -e $YELLOW "========== FINAL TEST ==========" $RESET
echo
echo -e $YELLOW "With -laRrt option, various args, with files and big directories :" $RESET
echo -e $YELLOW "> ./ft_ls -laRrt .. -lalala ft_ls nope . ft_ls srcs/ -RRRRRrrrr :" $RESET

echo -e $YELLOW "Valgrind check :" $RESET
echo

valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls -laRrt .. -lalala ft_ls nope . ft_ls srcs/ -RRRRRrrrr 2> /tmp/valgrind_logs > /tmp/logs

cat /tmp/valgrind_logs | grep -q "All heap blocks were freed -- no leaks are possible" && \
cat /tmp/valgrind_logs | grep -q "ERROR SUMMARY: 0 errors from 0 contexts" && \
cat /tmp/valgrind_logs | grep -q "FILE DESCRIPTORS: 3 open (3 std) at exit."

if [[ $? -ne 0 ]]; then
	echo -e $RED "Valgrind KO :"
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./ft_ls -laRrt .. -lalala ft_ls nope . ft_ls srcs/ -RRRRRrrrr > /tmp/logs
	echo -ne $RESET
else
	echo -e $GREEN "Valgrind OK !" $RESET
fi
