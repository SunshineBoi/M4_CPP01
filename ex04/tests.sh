#!/bin/bash
# Black-box tests for find_and_replace.
# Builds the binary, then drives it purely through argv + files on disk —

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
BIN="$SCRIPT_DIR/find_and_replace"
WORKDIR="$(mktemp -d)"
PASS=0
FAIL=0

cleanup() {
	rm -rf "$WORKDIR"
}
trap cleanup EXIT

make -C "$SCRIPT_DIR" >/dev/null || { echo "build failed"; exit 1; }

# check_content <description> <actual_file> <expected_content>
check_content() {
	local desc="$1" file="$2" expected="$3"
	if [ -f "$file" ] && [ "$(cat "$file")" = "$expected" ]; then
		echo "PASS: $desc"
		PASS=$((PASS + 1))
	else
		echo "FAIL: $desc"
		echo "  expected: [$expected]"
		echo "  actual:   [$(cat "$file" 2>/dev/null)]"
		FAIL=$((FAIL + 1))
	fi
}

# check_exit <description> <expected_exit_code> -- <cmd...>
check_exit() {
	local desc="$1" expected="$2"
	shift 2
	[ "$1" = "--" ] && shift
	"$@" >/dev/null 2>&1  #  running "$@" as a command runs whatever program name is in $1 with the rest as its arguments.
	local actual=$?
	if [ "$actual" -eq "$expected" ]; then
		echo "PASS: $desc"
		PASS=$((PASS + 1))
	else
		echo "FAIL: $desc (expected exit $expected, got $actual)"
		FAIL=$((FAIL + 1))
	fi
}

cd "$WORKDIR" || exit 1

# 1. basic replace, multiple occurrences
printf 'hello world hello' > t1.txt
"$BIN" t1.txt hello bye >/dev/null
check_content "basic replace" t1.txt.replace "bye world bye"

# 2. adjacent / overlapping matches
printf 'aaaa' > t2.txt
"$BIN" t2.txt aa b >/dev/null
check_content "adjacent matches" t2.txt.replace "bb"

# 3. match at the very start and end of the file
printf 'XaXbX' > t3.txt
"$BIN" t3.txt X Y >/dev/null
check_content "match at start and end" t3.txt.replace "YaYbY"

# 4. no occurrences at all
printf 'nothing here' > t4.txt
"$BIN" t4.txt zzz qqq >/dev/null
check_content "no occurrences" t4.txt.replace "nothing here"

# 5. empty input file
printf '' > t5.txt
"$BIN" t5.txt a b >/dev/null
check_content "empty file" t5.txt.replace ""

# 6. s1 longer than s2
printf 'foofoofoo' > t6.txt
"$BIN" t6.txt foo x >/dev/null
check_content "s1 longer than s2" t6.txt.replace "xxx"

# 7. s1 shorter than s2
printf 'xxx' > t7.txt
"$BIN" t7.txt x foo >/dev/null
check_content "s1 shorter than s2" t7.txt.replace "foofoofoo"

# 8. multiline file, newlines preserved
printf 'line1\nline2 hello\nline3' > t8.txt
"$BIN" t8.txt hello hi >/dev/null
check_content "newline preservation" t8.txt.replace "line1
line2 hi
line3"

# 9. s1 == s2 (should be a no-op, content unchanged)
printf 'same same same' > t9.txt
"$BIN" t9.txt same same >/dev/null
check_content "s1 equals s2" t9.txt.replace "same same same"

# 10. wrong number of arguments
check_exit "wrong arg count" 1 -- "$BIN" t1.txt only_one_arg

# 11. nonexistent input file
check_exit "nonexistent input file" 1 -- "$BIN" does_not_exist.txt a b

# 12. empty s1 is rejected, not an infinite loop
printf 'abc' > t12.txt
check_exit "empty s1 rejected" 1 -- timeout 2 "$BIN" t12.txt "" x

echo
echo "$PASS passed, $FAIL failed"
[ "$FAIL" -eq 0 ]  # is fail == 0 ? 1 : 0; it also represents bash exit status as last line.
