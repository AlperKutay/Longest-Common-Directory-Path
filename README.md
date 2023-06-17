# Longest-Common-Directory-Path

In this project we get inputs with arguments
Therefore you should run the program with arguments 

Firstly compile with 
```
gcc -o main main.c
```
then run with that example
```
./main  /bob/john/betty/clark /bob/harry/../john/./betty/david /bob/john/betty/../betty/tom/mark /bob///john///betty///brad///martin
```
DO NOT Forget the enter the directory of the project firstly 


Everything related with project and functions are explained in the code script

My algorithm has O(n) time complexity because all functions has n times loop and there is nothing more
My algorithm has O(n) space complexity becase all variables need memory with n takes up space

n represent path variable. There can be a question about 'How does the effect of lenght of path?'. In the question max path lenght is given as 1024 so that since path arrays 
takes memory of 1024, it does not affect at all.

I believe my code is working very well. I tried with every example and I got correct results
I want to mention related with my algorithm. I could have made better because there is a area that can be fixed
I mentioned in the code. My order of function to get correct result is such like remove_multiple_slashes,destination_path and compare
Since I have done a planning mistake, I have done the compare funciton before destination_path funciton so that I adjust the output of destination_path funciton according to compare funciton
because input of the compare funciton has different size of array
Also I can get input as a pointer but I did not do that because In the first of the my journey I got some errors and I solved it that way
After I realized that I could not change my entire code because of my school work.




Alper Kutay ÖZBEK
ODTÜ EEE
BsC Student
