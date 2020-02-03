/* @filename : three.c
 * @date : 01/29/2020
 * @author : Antara Prakash Pavan Shiralagi
 * @description : Tests a character code for certain features and prints them out in a specified formatas described in the assignment
 */

#include <stdio.h>

#include <ctype.h>

/*	Gets the case of the character	*/
const char * get_case(int c){

        if(c<=90 && c>=65){

            return "Upper Case";

        }

        else if(c<=122 && c>=97){

            return "Lower Case";

        }

        else if(c<=57 && c>=48){

            return "Digit";

        }

        else{

            if((c<=47 && c>=33) || (c<=64 && c>=58) || (c<=96 && c>=91) || (c<=126 && c>=123)){

                return "Special Character";

            }

            else{

                int result = isspace((char)c);

                if(result == 0){

                    return "Invalid Input";

                }

                else

                    return "White Space";//Checks for white spaces

            }

        }

    }

int main(int argc, const char * argv[]) {

    int code[20] = {66,114,117,99,101,32,83,97,121,115,32,72,105,33,7,9,50,48,49,57};//Inputs provided in assignment

    for(int i = 0;i<20; i++){

        const char * value = get_case(code[i]);

        printf("Code:%d \t\t Type:%s \t\t ASCII Char:%c \n", code[i], value, (char)code[i]);

    }

    return 0;

}