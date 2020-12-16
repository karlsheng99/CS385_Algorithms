#!/bin/bash

file=powergrid.cpp
MAXTIME=1.0

if [ ! -f "$file" ]; then
    echo -e "Error: File '$file' not found.\nTest failed."
    exit 1
fi

num_right=0
total=0
line="________________________________________________________________________"
compiler=
interpreter=
language=
extension=${file##*.}
if [ "$extension" = "py" ]; then
    if [ ! -z "$PYTHON_PATH" ]; then
        interpreter=$(which python.exe)
    else
        interpreter=$(which python3.6)
    fi
    command="$interpreter $file"
    echo -e "Testing $file\n"
elif [ "$extension" = "java" ]; then
    language="java"
    command="java ${file%.java}"
    echo -n "Compiling $file..."
    javac $file
    echo -e "done\n"
elif [ "$extension" = "c" ] || [ "$extension" = "cpp" ]; then
    language="c"
    command="./${file%.*}"
    echo -n "Compiling $file..."
    results=$(make 2>&1)
    if [ $? -ne 0 ]; then
        echo -e "\n$results"
        exit 1
    fi
    echo -e "done\n"
fi

# Use this on Macs that do not have the shell utility timeout available.
timeout_e() {
    time=$1

    # start the command in a subshell to avoid problem with pipes
    # (spawn accepts one command)
    cmd="/bin/bash -c \"$2\""

    expect -c "set echo \"-noecho\"; set timeout -1; set timeout $time; spawn -noecho $cmd; expect timeout { exit 1 } eof { exit 0 }"

    if [ $? -eq 1 ]; then
        return 0
    fi
    return 1
}

run_test_args() {
    (( ++total ))
    echo -n "Running test $total..."
    expected=$2
    local ismac=0
    date --version >/dev/null 2>&1
    if [ $? -ne 0 ]; then
       ismac=1
    fi
    local start=0
    if (( ismac )); then
        start=$(python -c 'import time; print time.time()')
    else
        start=$(date +%s.%N)
    fi
    timeout $MAXTIME bash -c "$command $1 2>error.txt | tr -d '\r' > tmp.txt"
    # 124 is returned if timeout needs to kill the process
    if [ $? -eq 124 ]; then
        # Make sure it's really terminated, otherwise rm does not work.
        killall -9 $command >/dev/null 2>&1
        echo "failure [timed out after $MAXTIME seconds]"
    else
        local end
        if (( ismac )); then
            end=$(python -c 'import time; print time.time()')
        else
            end=$(date +%s.%N)
        fi
        received=$(cat tmp.txt)
        error=$(cat error.txt)
        if [ ! -z "$error" ]; then
            if [ -z "$received" ]; then
                received="$error"    
            else
                received="$received\n$error"
            fi
        fi
        local elapsed=$(echo "scale=3; $end - $start" | bc | awk '{printf "%.3f", $0}') 
        if [ "$expected" != "$received" ]; then
            echo -e "failure\n\nExpected$line\n$expected\n"
            echo -e "Received$line\n$received\n"
        else
            echo "success [$elapsed seconds]"
            (( ++num_right ))
        fi
    fi
    rm -f tmp.txt error.txt
}

set -bm
trap "echo SIGSEGV" SIGSEGV

# Test 1
run_test_args "" "Usage: ./powergrid <input file>"

# Test 2
run_test_args "file1.txt file2.txt" "Usage: ./powergrid <input file>"

# Test 3
run_test_args "notfound.txt" "Error: Cannot open file 'notfound.txt'."

# Test 4
(cat << ENDOFTEXT
-3
1,2,110,Maple Ave.
1,3,90,Summit Ave.
2,240,Main St.
ENDOFTEXT
) > graph.txt
run_test_args "graph.txt" "Error: Invalid number of vertices '-3' on line 1."
rm -f graph.txt

# Test 5
(cat << ENDOFTEXT
3
1,2,110,Maple Ave.
1,3,90,Summit Ave.
2,240,Main St.
ENDOFTEXT
) > graph.txt
run_test_args "graph.txt" "Error: Invalid edge data '2,240,Main St.' on line 4."
rm -f graph.txt

# Test 6
(cat << ENDOFTEXT
3
1,2,110,Maple Ave.
4,3,90,Summit Ave.
2,3,240,Main St.
ENDOFTEXT
) > graph.txt
run_test_args "graph.txt" "Error: Starting vertex '4' on line 3 is not among valid values 1-3."
rm -f graph.txt

# Test 7
(cat << EOF
3
1,2,110,Maple Ave.
1,x,90,Summit Ave.
2,3,240,Main St.
EOF
) > graph.txt
run_test_args "graph.txt" "Error: Ending vertex 'x' on line 3 is not among valid values 1-3."
rm -f graph.txt

# Test 8
(cat << EOF
3
1,2,110,Maple Ave.
1,3,90,Summit Ave.
2,3,-240,Main St.
EOF
) > graph.txt
run_test_args "graph.txt" "Error: Invalid edge weight '-240' on line 4."
rm -f graph.txt

# Test 9
(cat << EOF
3
1,2,110,Maple Ave.
EOF
) > graph.txt
run_test_args "graph.txt" "No solution."
rm -f graph.txt

# Test 10
(cat << EOF
3
1,2,110,Maple Ave.
1,3,90,Summit Ave.
2,3,240,Main St.
EOF
) > graph.txt
run_test_args "graph.txt" $'Total wire length (meters): 200\nMaple Ave. [110]\nSummit Ave. [90]'
rm -f graph.txt

# Test 11
(cat << EOF
4
1,2,110,Maple Ave.
3,4,200,Hancock Ave.
EOF
) > graph.txt
run_test_args "graph.txt" "No solution."
rm -f graph.txt

# Test 12
(cat << EOF
15
1,13,1,Z.
3,6,2,Y.
7,13,3,X.
4,11,4,W.
15,7,5,V.
6,10,6,U.
5,14,7,T.
12,14,8,S.
2,4,9,R.
8,10,10,Q.
6,14,11,P.
15,4,12,O.
13,5,13,N.
12,13,14,M.
1,8,15,L.
9,2,16,K.
9,10,17,J.
7,5,18,I.
11,10,19,H.
3,11,20,G.
8,15,21,F.
1,12,22,E.
2,3,23,D.
14,11,24,C.
3,13,25,B.
4,3,26,A.
EOF
) > graph.txt
run_test_args "graph.txt" "Total wire length (meters): 107
K. [16]
N. [13]
O. [12]
P. [11]
Q. [10]
R. [9]
S. [8]
T. [7]
U. [6]
V. [5]
W. [4]
X. [3]
Y. [2]
Z. [1]"
rm -f graph.txt

echo -e "\nTotal tests run    : $total"
echo -e "Number correct     : $num_right"
echo -n "Percent correct    : "
echo "scale=2; 100 * $num_right / $total" | bc

if [ "$language" = "java" ]; then
    echo -e -n "\nRemoving class files..."
    rm -f *.class
    echo "done"
elif [ $language = "c" ]; then
    echo -e -n "\nCleaning project..."
    make clean > /dev/null 2>&1
    echo "done"
fi
