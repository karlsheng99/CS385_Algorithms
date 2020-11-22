#!/bin/bash

echo "Make project..."
make

echo "Running tests. Run individual test with --verbose to debug."


echo ---------- CASE 1----------
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./testrbt




echo ---------- CASE 2 ----------
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./testrbt 50




echo ---------- CASE 3 ----------
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./testrbt 50 60




echo ---------- CASE 4 ----------
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./testrbt 50 60 70




echo ---------- CASE 5 ----------
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./testrbt 50 60 70 40 30 20 50




echo ---------- CASE 6 ----------
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./testrbt 23 56 -8 90 25 18 42 99 -5




echo ---------- CASE 7 ----------
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./testrbt 109 17 12 452 19 123 581 49




echo ---------- CASE 8 ----------
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./testrbt Jim Connie Mike Michelle John Amy Bill Kyle Jill Mike Jill




echo ---------- CASE 9 ----------
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./testrbt A Z B Y C X D W E V F U G T H S I R J Q K P L O M N




echo ---------- CASE 10 ----------
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./testrbt 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30




echo ---------- CASE 11 ----------
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./testrbt 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1




echo ---------- CASE 12 ----------
valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./testrbt Engling Borowski Duggan Naumann Damopoulos Wetzel Nicolosi Ateniese Bonelli Mordohai Klappholz Kleinberg Portokalidis Wang Compagnoni

