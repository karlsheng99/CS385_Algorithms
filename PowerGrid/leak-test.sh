#!/bin/bash

echo "Make project..."
make

echo "Running tests. Run individual test with --verbose to debug."


echo ---------- CASE 1----------
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./powergrid




echo ---------- CASE 2 ----------
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./powergrid file1.txt file2.txt




echo ---------- CASE 3 ----------
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./powergrid notfound.txt




echo ---------- CASE 4 ----------
(cat << ENDOFTEXT
-3
1,2,110,Maple Ave.
1,3,90,Summit Ave.
2,240,Main St.
ENDOFTEXT
) > graph.txt
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./powergrid graph.txt
rm -f graph.txt



echo ---------- CASE 5 ----------
(cat << ENDOFTEXT
3
1,2,110,Maple Ave.
1,3,90,Summit Ave.
2,240,Main St.
ENDOFTEXT
) > graph.txt
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./powergrid graph.txt
rm -f graph.txt



echo ---------- CASE 6 ----------
(cat << ENDOFTEXT
3
1,2,110,Maple Ave.
4,3,90,Summit Ave.
2,3,240,Main St.
ENDOFTEXT
) > graph.txt
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./powergrid graph.txt
rm -f graph.txt



echo ---------- CASE 7 ----------
(cat << EOF
3
1,2,110,Maple Ave.
1,x,90,Summit Ave.
2,3,240,Main St.
EOF
) > graph.txt
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./powergrid graph.txt
rm -f graph.txt



echo ---------- CASE 8 ----------
(cat << EOF
3
1,2,110,Maple Ave.
1,3,90,Summit Ave.
2,3,-240,Main St.
EOF
) > graph.txt
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./powergrid graph.txt
rm -f graph.txt



echo ---------- CASE 9 ----------
(cat << EOF
3
1,2,110,Maple Ave.
EOF
) > graph.txt
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./powergrid graph.txt
rm -f graph.txt


echo ---------- CASE 10 ----------
(cat << EOF
3
1,2,110,Maple Ave.
1,3,90,Summit Ave.
2,3,240,Main St.
EOF
) > graph.txt
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./powergrid graph.txt
rm -f graph.txt



echo ---------- CASE 11 ----------
(cat << EOF
4
1,2,110,Maple Ave.
3,4,200,Hancock Ave.
EOF
) > graph.txt
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./powergrid graph.txt
rm -f graph.txt


echo ---------- CASE 12 ----------
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
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./powergrid graph.txt
rm -f graph.txt

