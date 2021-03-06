#!/bin/bash
# Unit tester for Minishell

export CWD=temp

rm -rf $CWD
mkdir -p $CWD

RESET="\033[0m"
BLACK="\033[1m\033[30m"
RED="\033[1m\033[31m"
GREEN="\033[1m\033[32m"
YELLOW="\033[1m\033[33m"
BLUE="\033[1m\033[34m"
MAGENTA="\033[1m\033[35m"
CYAN="\033[1m\033[36m"
WHITE="\033[1m\033[37m"

# make -C ../ > /dev/null
# cp ../minishell .
# chmod 755 minishell

cleanup() {
	if [ "$FILESTATE_SET" -eq 0 ]; then
		ls > .filestate_before
		FILESTATE_SET=1
	else
		ls > .filestate_after
		FILESTATE_DIFF=$(diff .filestate_before .filestate_after | grep ">" | sed "s|> ||g" | tr '\n' ' ')
		rm $FILESTATE_DIFF .filestate_before .filestate_after
	fi
}

MSHELL_PATH=../

#$1 = color, ${@:2} is string
printf_color() {
	1>&2 printf $1
	printf "${@:2}"
	1>&2 printf $RESET
}

echo_color() {
	1>&2 printf $1
	echo "$2"
	echo "$3"
	1>&2 printf $RESET
}

parse_options() {
	CAT=0
	for var in $@; do
		if [ "$var" = "-e" ]; then
			CAT=1
		fi
	done
}

get_test() {
	if ! [ -f "${MSHELL_PATH}minishell" ]; then
		printf "${RED}ERROR${RESET}: Minishell path doesn't contain 'minishell' executable\nMinishell path is currently set to: \"${MSHELL_PATH}\"\nChange the MSHELL_PATH variable in the script to set the path\n"
		exit 1
	fi
	PASS=0
	FAIL=0
	for var in $@; do
		if [ "${var::1}" = "-" ]; then
			continue
		fi
		if [ ! -f "$var" ]; then
			printf "File '$var' does not exist\n"
			continue
		fi
		while IFS= read -r line; do
			run_test $line
		done < "$var"
	done
	echo ----- Finished Tests -----
	printf "\nPassed = "
	echo $PASS
	printf "\nFailed = "
	echo $FAIL
}

# cd temp; unset OLDPWD; echo 'base64 < echo.txt | head -c 100 | cat -e'; exit | ../minishell 2>/dev/null

run_test() {
	FLAG=0
	RESULT=$(cd $CWD; unset OLDPWD; echo $line "; exit" | ${MSHELL_PATH}minishell 2>/dev/null)
	EXIT_MS=$?
	EXPECTED=$(cd $CWD; echo $line "; exit" | bash 2>/dev/null)
	EXIT_BASH=$?
	if [ "$RESULT" = "$EXPECTED" ] && [ "$EXIT_MS" = "$EXIT_BASH" ]; then
		printf_color $GREEN "[OK]"
		let PASS++
	else
		printf_color $RED "[KO]"
		let FAIL++
	fi
	echo " "$line
	if [ "$RESULT" != "$EXPECTED" ]; then
		FLAG=1
		if [ "$CAT" = 1 ]; then
			echo_color $RED "Your output :" "$(echo $RESULT | cat -e)"
		else
			echo_color $RED "Your output :" "$(echo $RESULT)"
		fi
		if [ "$CAT" = 1 ]; then
			echo_color $GREEN "Bash output :" "$(echo $EXPECTED | cat -e)"
		else
			echo_color $GREEN "Bash output :" "$(echo $EXPECTED)"
		fi
	fi
	if [ "$EXIT_MS" != "$EXIT_BASH" ]; then
		echo
		FLAG=1
		printf_color $RED "Your exit status : $EXIT_MS\n"
		printf_color $GREEN "Bash exit status : $EXIT_BASH\n"
	fi
	if [ $FLAG -eq 1 ]; then
		printf_color $YELLOW '\n %s NEW CMD %s\n\n' '---' '---'
		sleep 0.1
	fi
}

if [ $# -eq 0 ]; then
	printf "${RED}ERROR${RESET}: Please provide atleast one argument\nUsage: ./unit_tester.sh <TEST_FILES>... [OPTIONS]\n"
	exit 1
fi

parse_options $@

FILESTATE_SET=0
cleanup
get_test $@
cleanup
# rm file1 file2 file3 doethet newfile.txt newfile test1 test2 test3 test4 x1 x2 x3 y1 y2 ilovewords.txt hardesttest.txt
