#include <stdio.h>
#include <limits.h>


int n;

//----------------------------------------------------------First method-------------------------------------------------------
/* adavantages:
In this method I used recursive way which does not take development time,it is code is simple as the code written
is the same as the function given in the question.

disadvantages:
the code time complexity is O(2^n) which too much.
the code will cause a stack overflow because if the number of function calls will exceed the memory allowed for stack.
variable overflow occurs at big values of n.
*/
int getVal_1(int num){
        //base case.
        if(num <= 2) return num;
        return getVal_1(num-2) + getVal_1(num-3);
    }
void firstMethod(){
    printf("Result = %d\n",getVal_1(n));
}


//----------------------------------------------------------Second method-------------------------------------------------------
/*
in this method I solved the problem of memor encountered in method 1.

advantages:
time complexity is O(n) which is appropriate.
I used memoization so that for each distinct n, f(n) is calculated just once.
keeps track of all values of n from 0 to n, so if f(n) is calculated before it will get returned in O(1).

disadvantages:
it takes O(n) memory which might not be always available.
variable overflow occurs at big values of n.

*/
#define MAX_ARRAY_SIZE 10000000 //assign it the maximum number your IDE allows you to give to an array
unsigned int F[MAX_ARRAY_SIZE + 1LL];
int getVal_2(int num){
        
        
        //base case.
        if(num <= 2) return num;

        //if the F[num] is not zero then it has been calculated before, so return it, if not, calculate it in the following code.
        if(F[num]) return F[num];
        return F[num] = getVal_2(num-2) + getVal_2(num-3);
    }
void secondMethod(){
    F[0] = 0;
    F[1] = 1;
    F[2] = 2;
    printf("Result = %d\n",getVal_2(n));
}

//----------------------------------------------------------Third method-------------------------------------------------------

/*
The most reliable method: it gives correct values for any value of n, but takes much time for n > 10^5.

advantages:
it needs memory sufficient for just 4 variables.
it can get correct F(i) of any number without variable overflow as I used string addition, as F(i) grows so fast and C integer data
types can not hold such big numbers.


disadvantages:
each time you call this function it will calculate all f(n) from 3 to n, because we do not use memoization in order to 
optimize memory complexity.
time complexity O(n * (max number)). so it takes much time for n > 10^5.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* addStrings(char* num1, char* num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int maxSize = (len1 > len2 ? len1 : len2) + 1; // Add 1 for possible cFy
    char* result = (char*)malloc((maxSize + 1) * sizeof(char)); // Add 1 for null-terminating character
    result[maxSize] = '\0'; // Null-terminate the result string
    int carry = 0;
    int i = 0;
    int j = 0;
    for(i=0;i<maxSize;i++){
        int digit1,digit2;
        digit1 = (i < len1)? num1[len1 - i -1]-'0':0;
        digit2 = (i < len2)? num2[len2 - i -1]-'0':0;

        int digitSum = digit1 + digit2 + carry;
        if((digitSum%10) == 0 && (i == maxSize-1)) {
            
        }
        result[maxSize - i -1] = digitSum%10 + '0';
        carry = digitSum/10;
    }

    //eliminating the first 0 by resizing.
    if(result[0] == '0'){
        char* newResult = (char*)malloc((maxSize) * sizeof(char));
        for(i=0;i<(maxSize-1);i++){
            newResult[i] = result[i+1];
        }
        newResult[maxSize-1] = '\0';
        result = newResult;
    }

    // printf("%s + %s = ",num1,num2);
    // printf("%s\n",result);
    return result;
}

void thirdMehtod(){
    char** F = (char**)malloc((4) * sizeof(char*));
    F[0] = (char*)malloc(2 * sizeof(char));
    F[1] = (char*)malloc(2 * sizeof(char));
    F[2] = (char*)malloc(2 * sizeof(char));

    F[0][0] = '0';
    F[0][1] = '\0';
    F[1][0] = '1';
    F[1][1] = '\0';
    F[2][0] = '2';
    F[2][1] = '\0';

    for (int i = 3; i <= n; i++) {        
        F[i%4] = addStrings(F[(i - 2)%4], F[(i - 3)%4]);
    }

    printf("Result = %s\n",F[n%4]);
    
    for (int i = 0; i < 4; i++) {
        free(F[i]);
    }

    free(F); 
}


int main(){
    
    printf("Enter n to get F(n) for: ");
    fflush(stdout);
    scanf("%d",&n);

    //method 1 takes too much time for n > 32 , uncomment it to use it.
    // firstMethod();
    
    //method 2 overflows for n > 70, uncomment it to use it
    // secondMethod();
    
    //the most reliable method is method 3, it takes long time for n > 100000, but gives correct values without overflow.
    thirdMehtod();

    return 0;
}