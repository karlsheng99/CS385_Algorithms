#!/bin/bash

echo "Make project..."
make

echo "Running tests. Run individual test with --verbose to debug."


echo ---------- CASE 1----------
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./shortestpaths




echo ---------- CASE 2 ----------
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./shortestpaths notfound.txt




echo ---------- CASE 3 ----------
(cat << ENDOFTEXT
0
X Y 1
Y Z 4
ENDOFTEXT
) > graph.txt
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./shortestpaths graph.txt
rm -f graph.txt



echo ---------- CASE 4 ----------
(cat << ENDOFTEXT
three
X Y 1
Y Z 4
ENDOFTEXT
) > graph.txt
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./shortestpaths graph.txt
rm -f graph.txt



echo ---------- CASE 5 ----------
(cat << ENDOFTEXT
4
A C 2
A D 10
B A 7
B C
B D 1
C B 3
D A 2
D B 6
D C 6
ENDOFTEXT
) > graph.txt
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./shortestpaths graph.txt
rm -f graph.txt



echo ---------- CASE 6 ----------
(cat << ENDOFTEXT
3
X Y 1
Y Z 4
ENDOFTEXT
) > graph.txt
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./shortestpaths graph.txt
rm -f graph.txt



echo ---------- CASE 7 ----------
(cat << ENDOFTEXT
4
A C 2
A D 10
B A 7
B C 5
b D 1
C B 3
D A 2
D B 6
D C 6
ENDOFTEXT
) > graph.txt
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./shortestpaths graph.txt
rm -f graph.txt



echo ---------- CASE 8 ----------
(cat << ENDOFTEXT
4
A C 2
A D 10
B A 7
B C 5
Hoboken Weehawken 1
C B 3
D A 2
D B 6
D C 6
ENDOFTEXT
) > graph.txt
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./shortestpaths graph.txt
rm -f graph.txt



echo ---------- CASE 9 ----------
(cat << ENDOFTEXT
6
A C 2
A . 10
B A 7
B C 5
B D 1
C B 3
D A 2
D B 6
D C 6
E F 8
ENDOFTEXT
) > graph.txt
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./shortestpaths graph.txt
rm -f graph.txt



echo ---------- CASE 10 ----------
(cat << ENDOFTEXT
4
A C 2
A D 10
B A 7
B C 5
B D 1
C B 3
D A 2
D B 6
D NYC 6
ENDOFTEXT
) > graph.txt
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./shortestpaths graph.txt
rm -f graph.txt



echo ---------- CASE 11 ----------
(cat << ENDOFTEXT
4
A C 2
A D 10
B A -7
B C 5
B D 1
C B 3
D A 2
D B 6
D C 6
ENDOFTEXT
) > graph.txt
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./shortestpaths graph.txt
rm -f graph.txt



echo ---------- CASE 12 ----------
(cat << ENDOFTEXT
4
A C 2
A D 10
B A 7
B C 5
B D 1
C B 3
D A 0
D B 6
D C 6
ENDOFTEXT
) > graph.txt
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./shortestpaths graph.txt
rm -f graph.txt


echo ---------- CASE 13 ----------
(cat << ENDOFTEXT
4
A C 2
A D 10
B A 7
B C 5
B D 1
C B 3
D A 2
D B sixteen
D C 6
ENDOFTEXT
) > graph.txt
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./shortestpaths graph.txt
rm -f graph.txt


echo ---------- CASE 14 ----------
(cat << ENDOFTEXT
1
ENDOFTEXT
) > graph.txt
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./shortestpaths graph.txt
rm -f graph.txt


echo ---------- CASE 15 ----------
(cat << ENDOFTEXT
4
A C 2
A D 10
B A 7
B C 5
B D 1
C B 3
D A 2
D B 6
D C 6
ENDOFTEXT
) > graph.txt
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./shortestpaths graph.txt
rm -f graph.txt


echo ---------- CASE 16 ----------
(cat << ENDOFTEXT
5
A C 2
A D 10
A E 13
B A 7
B C 5
B D 1
B E 5
C B 3
C D 4
D A 2
D B 6
D C 6
D E 8
ENDOFTEXT
) > graph.txt
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./shortestpaths graph.txt
rm -f graph.txt


echo ---------- CASE 17 ----------
(cat << ENDOFTEXT
5
A C 2
A E 13
B A 7
B C 5
B D 2147483647
B E 5
C B 3
D A 2
D B 6
D C 6
D E 8
E B 2147483647
ENDOFTEXT
) > graph.txt
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./shortestpaths graph.txt
rm -f graph.txt


echo ---------- CASE 18 ----------
(cat << ENDOFTEXT
7
A B 11
A D 13
B A 7
B C 4
D E 8
D G 9
E A 9
E F 10
E G 2
F B 12
F C 19
G E 29
G C 5
ENDOFTEXT
) > graph.txt
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./shortestpaths graph.txt
rm -f graph.txt


echo ---------- CASE 19 ----------
(cat << ENDOFTEXT
8
A B 11
A D 13
B A 7
B C 4
B H 33
C A 8
C B 18
C E 22
D E 8
D G 9
E A 9
E F 10
E G 2
F B 12
F C 19
G E 29
G C 5
H A 1
H B 4
H D 9
ENDOFTEXT
) > graph.txt
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./shortestpaths graph.txt
rm -f graph.txt


echo ---------- CASE 20 ----------
(cat << ENDOFTEXT
10
A B 111
A D 113
B A 17
B C 14
B H 133
B J 90
C A 8
C B 118
C E 22
D E 8
D G 19
D I 15
E A 19
E F 110
E G 2
F B 12
F C 119
G E 129
G C 5
H A 11
H B 14
H D 19
I A 23
I G 9
I H 77
J B 112
J D 83
J F 54
J I 18
ENDOFTEXT
) > graph.txt
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./shortestpaths graph.txt
rm -f graph.txt