# Problem 1

In this problem, we have formulated an algorithm on C that would read through a text file of numbers, and find the 10 hidden keys. they keys are marked as "-1". The code consists of two version, version 1 will execute the code using one process, whil version 2 will execute using multiple. 

## How to Execute our Code

Our file consist of our c program, our makefile, as well as our test files. To execute, input the following command:

```
make
./main <testfile.txt> <version> <H>
```

## Example of Version 1

Input
```
make
./main test5000.txt 1 10
```
Output
```
L = 5000, H = 10, Max = 100, Average = 50.674400
Hi I am process 23846 and I found a hidden key in position A[499]
Hi I am process 23846 and I found a hidden key in position A[999]
Hi I am process 23846 and I found a hidden key in position A[1499]
Hi I am process 23846 and I found a hidden key in position A[1999]
Hi I am process 23846 and I found a hidden key in position A[2499]
Hi I am process 23846 and I found a hidden key in position A[2999]
Hi I am process 23846 and I found a hidden key in position A[3499]
Hi I am process 23846 and I found a hidden key in position A[3999]
Hi I am process 23846 and I found a hidden key in position A[4499]
Hi I am process 23846 and I found a hidden key in position A[4999]
```
As you can see above, only one process is running as the process values is the same in all lines of output

## Example of Version 2

Input
```
make
./main test5000.txt 2 10
```
Output 
```
L = 5000, H = 10, Max = 100, Average = 50.674400
Hi I'm process 23909 and I found the hidden key in position A[499].
Hi I'm process 23910 and my parent is 23909.
Hi I'm process 23910 and I found the hidden key in position A[999].
Hi I'm process 23911 and my parent is 23910.
Hi I'm process 23911 and I found the hidden key in position A[1499].
Hi I'm process 23912 and my parent is 23911.
Hi I'm process 23912 and I found the hidden key in position A[1999].
Hi I'm process 23913 and my parent is 23912.
Hi I'm process 23913 and I found the hidden key in position A[2499].
Hi I'm process 23914 and my parent is 23913.
Hi I'm process 23914 and I found the hidden key in position A[2999].
Hi I'm process 23915 and my parent is 23914.
Hi I'm process 23915 and I found the hidden key in position A[3499].
Hi I'm process 23916 and my parent is 23915.
Hi I'm process 23916 and I found the hidden key in position A[3999].
Hi I'm process 23917 and my parent is 23916.
Hi I'm process 23917 and I found the hidden key in position A[4499].
Hi I'm process 23918 and my parent is 23917.
Hi I'm process 23918 and I found the hidden key in position A[4999].
Hi I'm process 23919 and my parent is 23918.
```
As you can see above, there are 10 different processes that find hidden keys.
