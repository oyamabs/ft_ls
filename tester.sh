#!/bin/bash

rm -rf /goinfre/$USER/failed_tests
mkdir -p /goinfre/$USER/failed_tests

make

function check_leak()
{
	valgrind ./ft_ls $1 $2 $3 $4 >/tmp/ft_leak 2>&1
	grep -q "All heap blocks were freed" /tmp/ft_leak
	ret=$?
	((ret == 0)) && printf "" || printf "🚿 Leaks "
}

function do_test()
{
		printf "Testing \e[0;33m$1\e[0m... "
		/bin/ls $2 $3 $4 $5 > /tmp/true_ls 2>/dev/null
		./ft_ls $2 $3 $4 $5 > /tmp/ft_ls 2>/dev/null
		diff /tmp/true_ls /tmp/ft_ls > /dev/null
		DIFFRET=$?
		check_leak $2 $3 $4 $5
		if [[ $DIFFRET -eq 1 ]]; then
			printf "❌ \e[0;31mFailed\e[0m\nDiff file: /goinfre/$USER/failed_tests/$1.diff\n"
			diff -u /tmp/true_ls /tmp/ft_ls > /goinfre/$USER/failed_tests/$1.diff
#			exit
		else
			printf "✅ \e[0;32mSuccess\e[0m\n"
		fi
		diff -u /tmp/true_ls /tmp/ft_ls > /goinfre/$USER/failed_tests/$1.diff
}

cat << 'EOF'
   ___  __             ___               __                   __                   
 /'___\/\ \__         /\_ \             /\ \__               /\ \__                
/\ \__/\ \ ,_\        \//\ \     ____   \ \ ,_\    __    ____\ \ ,_\    __   _ __  
\ \ ,__\\ \ \/          \ \ \   /',__\   \ \ \/  /'__`\ /',__\\ \ \/  /'__`\/\`'__\
 \ \ \_/ \ \ \_          \_\ \_/\__, `\   \ \ \_/\  __//\__, `\\ \ \_/\  __/\ \ \/ 
  \ \_\   \ \__\         /\____\/\____/    \ \__\ \____\/\____/ \ \__\ \____\\ \_\ 
   \/_/    \/__/  _______\/____/\/___/      \/__/\/____/\/___/   \/__/\/____/ \/_/ 
                 /\______\                                                         
                 \/______/                                                         
EOF

echo "fa - full argument (ie --all, --reverse...)"
printf "\t⚠️ the only full arguments not covered by ls are -l and -t\n"

do_test "simple"
do_test "simple_with_hidden_files" -a
do_test "simple_with_hidden_files_fa" --all
do_test "simple_list" -l
# do_test "simple_list_fa" --list # ls doesn't have a --list
do_test "simple_recursive" -R
do_test "simple_recursive_fa" --recursive
do_test "simple_reverse" -r
do_test "simple_reverse_fa" --reverse
do_test "simple_time" -t
do_test "mixed_flags_la" -la
do_test "mixed_flags_lat" -lat
do_test "mixed_flags_laR" -laR
do_test "mixed_flags_taR" -taR
do_test "mixed_flags_taRr" -taRr
do_test "mixed_flags_ltaRr" -ltaRr
# do_test "simple_time_fa" --time # same lol
do_test "single_file" "" README.md
do_test "single_file_six_month_old" "" /sgoinfre/goinfre/Perso/tchampio/Public/ft_ls/six_month_file
do_test "single_file_six_month_future" "" /sgoinfre/goinfre/Perso/tchampio/Public/ft_ls/future_more
do_test "single_file_less_six_month_future" "" /sgoinfre/goinfre/Perso/tchampio/Public/ft_ls/future_less
do_test "multiple_files" "" README.md ft_ls
do_test "multiple_files_six_month_old" "" README.md /sgoinfre/goinfre/Perso/tchampio/Public/ft_ls/six_month_file
do_test "file_and_directory" "" README.md src
do_test "more_files_and_directory" "" README.md src TODO.md
do_test "recursive_on_src" -R src
do_test "mixed_flags_on_src" -Rla src
do_test "mixed_flags_on_src_and_files" -Rla src README.md TODO.md
do_test "symlink" -l /sgoinfre/goinfre/Perso/tchampio/Public/ft_ls/link
#do_test "block_device" -l /dev/nvme0n1p1 # not managed
#do_test "character_device" -l /dev/nvme0 # not managed
printf "⚠️ Uses /run/docker.sock change if necessary using find /run -type s 2>/dev/null\n"
do_test "socket_file" -l /run/docker.sock
do_test "FIFO_named_pipe" -l /run/initctl
do_test "single_hidden_file" "" .gitignore
do_test "multiple_hidden_file" "" .gitignore ./libft/objects/.gitkeep
do_test "mixed_directories_hidden_file" "" .gitignore src ./libft/objects/.gitkeep
#
# --- PARSING & FLAGS ---
do_test "flag_invalid" -z
do_test "flag_duplicates" -llll -aaaa

# --- ERRORS & PERMISSIONS ---
do_test "error_non_existent" non_existent_file
do_test "error_mixed_existent" README.md non_existent src

# --- SPECIAL FILES & SYMLINKS ---
do_test "symlink_dir_noslash" -l /sgoinfre/goinfre/Perso/tchampio/Public/ft_ls/linkdir
do_test "symlink_dir_slash" -l /sgoinfre/goinfre/Perso/tchampio/Public/ft_ls/linkdir/

# --- SPECIAL DIRECTORIES & RECURSIVE ---
do_test "dir_dot_dotdot" -la . ..
do_test "dir_empty" empty_dir
do_test "dir_empty_la" -la empty_dir

# --- MULTI-ARGUMENTS ORDERING ---
do_test "multi_mixed_time" -lt src README.md Makefile

echo "Doing benchmark with hyperfine."
echo "Benchmarking (./ft_)ls -laR ."
/sgoinfre/goinfre/Perso/tchampio/Private/.cargo/bin/hyperfine "./ft_ls -laR ."
/sgoinfre/goinfre/Perso/tchampio/Private/.cargo/bin/hyperfine "ls -laR ."
echo "Benchmarking (./ft_)ls -laR .."
/sgoinfre/goinfre/Perso/tchampio/Private/.cargo/bin/hyperfine "./ft_ls -laR .."
/sgoinfre/goinfre/Perso/tchampio/Private/.cargo/bin/hyperfine "ls -laR .."
