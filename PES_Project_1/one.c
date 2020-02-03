/* @filename : one.c
 * @date : 01/29/2020
 * @author : Antara Prakash and Pavan Shiralagi
 * @references : www.tutorialspoint.com/c_standard_library/c_function_strtol.htm
 * www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
 * www.geeksforgeeks.org/program-decimal-hexadecimal-conversion/
 * www.geeksforgeeks.org/1s-2s-complement-binary-number/
 * geeksforgeeks.org/convert-binary-number-octal/
 * geeksforgeeks.org/program-binary-decimal-conversion/
 * rosettacode.org/wiki/Determine_if_a_string_is_numeric
 * @description : This program performs necessary bit and byte manipulations on a hex value as described in the 
 *					Spring 2020 PES assignment 1
 * @note : one.c requires 3 inputs, Value | Radix | Operand Size	Comma seperated values without spaces is required
 */

#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <ctype.h>

#include <math.h>


char * ip[3];

int i=0;

long int string_length;

int Value, Radix, Operand_Size, octal_v;

int binaryNum[20], one_complement[32], two_complement[32], signedmag[32], one_comp[20];

char hex_num[20];

char hexaDeciNum[20]= "000000000";

int octalNum[20];


/*********************************Check Correct Octal input******************************************************************************************************************/

int check_octal(int i){

    int temp = i;

    while(temp != 0){

        if((temp%10) > 7){

            return 0;

        }else

            temp = temp/10;

    }

    return 1;

}


/*********************************Check Correct hexadecimal input******************************************************************************************************************/


int check_hex(char * c){

    if(c[0] == '0' && (c[1] == 'x' || c[1] == 'X')){

        return 1;

    }else{

            return 0;

    }

}



/*************************************Convert Character input to Integer Values**************************************************************************************************************/


int convert_char(char * c, int i){

    int octal_value;

    int decimal_value;

    int hex_value;

    char temp[5];

    int j=2, k=0;

    

    if(i==8){

        octal_value = (int)strtol(c, NULL, 8);

        return octal_value;

    }else if(i==10){

        decimal_value = atoi(c);

        return decimal_value;

    }else{

        string_length = strlen(c);

        if(c[0] == '0' && (c[1] == 'x' || c[1] == 'X')){

            while(c[j]!='\0'){

                temp[k] = c[j];

                j++;

                k++;

            }

        }

        hex_value = (int)strtol(temp, NULL, 16);

        return hex_value;

    }


}


/***********************************************Check if inputs have valid radix****************************************************************************************/

int check_radix(int i){

    if(i==8 || i==10 || i==16){

        return 1;

    }

    else

        return 0;

}

/***********************************************Check if inputs have valid operand****************************************************************************************/

int check_operand(int i){

    if(i==4 || i==8 || i==16){

        return 1;

    }

    else

        return 0;

}


/***************************************************Check if inputs are correct***************************************************************************************************/

int isNumeric (const char * s)

{

    if (s == NULL || *s == '\0' || isspace(*s))

      return 0;

    char * p;

    strtod (s, &p);

    return *p == '\0';

}

/***************************************************Absolute Maximum value integer can take*************************************************************************************/

int max_abs_value(int i){

    if(i==4){

        return 15;

    }else if(i == 8){

        return 255;

    }else{

        return 65535;

    }

}

/************************************************Absolute Maximum Signed Value integer can take****************************************************************************/

int max_signed_value(int i){

    if(i==4){

        return 7;//-8

    }else if(i == 8){

        return 127;

    }else{

        return 32767;

    }

}

/***********************************************Absolute Minimum Value an integer can take********************************************************************************/

int min_signed_value(int i){

    if(i==4){

        return -8;

    }else if(i == 8){

        return -128;

    }else{

        return -32768;

    }

}


//https://www.geeksforgeeks.org/program-decimal-binary-conversion/


/***************************************Convert Decimal to binary*************************************************************************************************************/

void decToBinary(int n)

{

    // array to store binary number

    n= abs(n);

    int i = 0;

    if(n==0){

        for(i=0;i<Operand_Size;i++)

            binaryNum[i] = 0;

    }

    // counter for binary array

    else{

        while (n > 0) {

        // storing remainder in binary array

            binaryNum[i] = n % 2;

            n = n / 2;

            i++;

        }

    }

}


//https://www.geeksforgeeks.org/program-decimal-octal-conversion/


/***************************************Convert Decimal to Octal**************************************************************************************************************/

void decToOctal(int n)

{

    n= abs(n);

    // counter for octal number array

    int i = 0;

    if(n==0){

        for(i=0;i<Operand_Size/2;i++)

            octalNum[i] = 0;

    }else{

        while (n != 0) {

        // storing remainder in octal array

            octalNum[i] = n % 8;

            n = n / 8;

            i++;

        }

    }

}



/******************************************Convert Decimal to Hexadecimal*****************************************************************************************************/

void decToHexa(int n)

{

    n= abs(n);

    // counter for hexadecimal number array

    int i = 0;

    if(n==0){

        for(i=0;i<Operand_Size/4;i++)

            hexaDeciNum[i] = '0';

    }else{

        while(n!=0)

        {

        // temporary variable to store remainder

            int temp  = 0;

          

        // storing remainder in temp variable.

            temp = n % 16;

          

        // check if temp < 10

            if(temp < 10)

            {

                hexaDeciNum[i] = temp + 48;

                i++;

            }

            else

                {

                    hexaDeciNum[i] = temp + 55;

                    i++;

                }

          

            n = n/16;

        }

    }

}

/******************************One's complement of a number for binatry number***************************************************************************************************************/

void onesComplement()

{

    for(int i = 0;i <Operand_Size; i++)

    {

        if(binaryNum[i] == 0){

            one_comp[i] = 1;

        }

        else{

            one_comp[i] = 0;

        }

    }

}

/*********** Signed Two's Complement [9] ***********/

void twosComplement()

{

    int c = 1;

    for(int i = 0;i < Operand_Size;i++)

    {

        if(one_comp[i] == 1 && c == 1)

            two_complement[i] = 0;

        else if(one_comp[i] == 0 && c == 1)

        {

            two_complement[i] = 1;

            c = 0;

        }

        else

            two_complement[i] =  one_comp[i];

    }

}

/*********** Sign-Magnitude Complement ***********/

void signed_mag(int bin[])

{

    for(int size = 0; size <Operand_Size; size++)

        signedmag[size] = bin[size];

    signedmag[Operand_Size-1] = 1;

}

/******************************print statement to reverse print array*****************************************/

void print_num(){

    for (int j = Operand_Size - 1; j >= 0; j--)

      printf("%d", binaryNum[j]);

}

void print_oct(){

    for (int j = (Operand_Size/2) - 1; j >= 0; j--)

      printf("%d", octalNum[j]);

}

void print_hex(){

    for (int j = (Operand_Size/4) - 1; j >= 0; j--)

      printf("%c", hexaDeciNum[j]);

}

void print_onecomp(){

    for(int j=Operand_Size-1; j>=0; j--)

      printf("%d", one_comp[j]);

}

void print_twocomp(){

    for(int j=Operand_Size-1; j>=0; j--)

      printf("%d", two_complement[j]);

}

void print_signmag(){

    for(int j=Operand_Size-1; j>=0; j--)

      printf("%d", signedmag[j]);

}



/*********************************main function************************************/

int main(int argc, const char * argv[]) {

    // insert code here...

    char input[15];

    int flag=0;

    printf("Enter Value,Radix,Operand Size: ");
	
	fgets(input, 15, stdin);    //Input as string

    char* token = strtok(input, ",");

    /* Parse string to get 3 different inputs*/

    while(token != NULL){

        ip[i] = token;

        token = strtok(NULL, ",");

        i++;

    }

    

    Radix = atoi(ip[1]);//Assigning Radix value

    Operand_Size = atoi(ip[2]);//Assigning operand Size

    

    if(check_radix(Radix) == 0){        /*Radix Check Function*/

        printf("Invalid Radix \n");

        return 0;

    }

    

    if(check_operand(Operand_Size) == 0){   /*Operand Size Function*/

        printf("Invalid Operand \n");

        return 0;

    }

    

    

    if(Radix == 10){        /*Checking for valid Inputs*/

        if(isNumeric(ip[0]) == 0){

            printf("Invalid Input \n");

            return 0;

        }

        else if(atoi(ip[0]) > 0 && atoi(ip[0]) > max_abs_value(Operand_Size)){

            printf("Input Out of Range\n");

            return 0;

        }

    }

    

    if(Radix == 8){     /*Checking for valid Inputs*/

        octal_v = atoi(ip[0]);

        if(check_octal(octal_v)==0){

            printf("Invalid Input \n");

            return 0;

        }

    }

    

    if(Radix == 16){        /*Checking for valid Inputs*/

        if(check_hex(ip[0]) == 0){

            printf("Invalid Input \n");

            return 0;

        }

    }

    

    Value = convert_char(ip[0], Radix);//Convert string value to integer

    

    /*Checking valid inputs based on operand size*/

    if(abs(Value) > max_abs_value(Operand_Size)){

        printf("Input Out of Range\n");

        return 0;

    }

    if(Value<0){

        if(Value > max_signed_value(Operand_Size) || Value < min_signed_value(Operand_Size)){

            printf("Input Out of Range\n");

            return 0;

        }

    }

    if(Value>max_signed_value(Operand_Size) && Value<max_abs_value(Operand_Size)){

        flag=1;

    }else

        flag=0;

    

    /*Printing the table*/

    printf("Input: \t Value %s \t Radix %d \t Operand Size %d \n",ip[0], Radix, Operand_Size);

    printf("Output:\t\t\t\tValue\t\t\tMaximum\t\t\tMinimum\n");

    

    

    /*Binary Value Print*/

    if(Operand_Size==4){

        printf("Binary(abs)\t\t\t0b");

    }

    if(Operand_Size==8){

        printf("Binary(abs)\t\t\t0b");

    }

    if(Operand_Size==16){

        printf("Binary(abs)\t\t\t0b");

    }

    

    decToBinary(Value);

    print_num();

    

    if(Operand_Size==4){

        printf("\t\t\t0b");

    }

    if(Operand_Size==8){

        printf("\t\t0b");

    }

    if(Operand_Size==16){

        printf("\t0b");

    }

    

    for(int j=0;j<Operand_Size;j++){

        printf("1");

    }

    if(Operand_Size==4){

        printf("\t\t\t0b");

    }

    if(Operand_Size==8){

        printf("\t\t0b");

    }

    if(Operand_Size==16){

        printf("\t0b");

    }

    

    for(int j=0;j<Operand_Size;j++){

        printf("0");

    }

    printf("\n");

    

    

    /*Octal absolute value print*/

    if(Operand_Size==4){

        printf("Octal(abs)\t\t\t");

    }

    if(Operand_Size==8){

        printf("Octal(abs)\t\t\t");

    }

    if(Operand_Size==16){

        printf("Octal(abs)\t\t\t");

    }

    

    decToOctal(convert_char(ip[0], Radix));

    print_oct();

    

    if(Operand_Size==4){

         printf("\t\t\t");

    }

    if(Operand_Size==8){

        printf("\t\t\t");

    }

    if(Operand_Size==16){

        printf("\t\t");

    }

    

    decToOctal(max_abs_value(Operand_Size));

    print_oct();

    

    if(Operand_Size==4){

        printf("\t\t\t");

    }

    if(Operand_Size==8){

        printf("\t\t\t");

    }

    if(Operand_Size==16){

        printf("\t\t");

    }

    

    for(int j=0;j<Operand_Size/2;j++){

        printf("0");

    }

    printf("\n");

    

    /*Decimal absolute Value Print*/

    if(Operand_Size==4){

        printf("Decimal(abs)\t\t\t%d\t\t\t0\t\t\t%d\n", abs(Value), max_abs_value(Operand_Size));

    }

    if(Operand_Size==8){

        printf("Decimal(abs)\t\t\t%d\t\t\t0\t\t\t%d\n", abs(Value), max_abs_value(Operand_Size));

    }

    if(Operand_Size==16){

        printf("Decimal(abs)\t\t\t%d\t\t\t0\t\t\t%d\n", abs(Value), max_abs_value(Operand_Size));

    }

    

    

    

    /*Hexadecimal absolute Value Print*/

    if(Operand_Size==4){

        printf("Hexadecimal(abs)\t\t0x");

    }

    if(Operand_Size==8){

        printf("Hexadecimal(abs)\t\t0x");

    }

    if(Operand_Size==16){

        printf("Hexadecimal(abs)\t\t0x");

    }

    

    decToHexa(Value);

    print_hex();

    

    if(Operand_Size==4){

        printf("\t\t\t0x");

    }

    if(Operand_Size==8){

        printf("\t\t\t0x");

    }

    if(Operand_Size==16){

        printf("\t\t\t0x");

    }

    

        for(int j=0;j<Operand_Size/4;j++){

            printf("F");

        }

    if(Operand_Size==4){

        printf("\t\t\t0x");

    }

    if(Operand_Size==8){

        printf("\t\t\t0x");

    }

    if(Operand_Size==16){

        printf("\t\t\t0x");

    }

    

    for(int j=0;j<Operand_Size/4;j++){

        printf("0");

    }

    

    printf("\n");

    

    /*Signed One's Complement print*/

    if(Operand_Size==4){

        printf("Signed One's Compliment\t\t");

    }

    if(Operand_Size==8){

        printf("Signed One's Compliment\t\t");

    }

    if(Operand_Size==16){

        printf("Signed One's Compliment\t\t");

    }

    

    if(flag == 0){

        printf("0b");

        onesComplement();

        print_onecomp();

    }else{

        printf("Error");

    }

    if(Operand_Size==4){

        printf("\t\t\t");

    }

    if(Operand_Size==8){

        printf("\t\t");

    }

    if(Operand_Size==16){

        printf("\t");

    }

    

    if(flag == 0){

        printf("0b");

        for(int j=0;j<Operand_Size;j++){

            printf("0");

        }

    }else{

        if(Operand_Size==4){

            printf("Error");

        }

        if(Operand_Size==8){

            printf("\tError");

        }

        if(Operand_Size==16){

             printf("\t\tError");

         }

    }

    if(Operand_Size==4){

        printf("\t\t\t");

    }

    if(Operand_Size==8){

        printf("\t\t");

    }

    if(Operand_Size==16){

        printf("\t");

    }

    

    if(flag == 0){

        printf("0b");

        for(int j=0;j<Operand_Size;j++){

            printf("1");

        }

    }else{

        if(Operand_Size==4){

            printf("Error");

        }

        if(Operand_Size==8){

            printf("\tError");

        }

        if(Operand_Size==16){

             printf("\t\tError");

         }

    }

    printf("\n");

    

    /*Signed two's comlement print*/

    if(Operand_Size==4){

        printf("Signed Two's Compliment\t\t");

    }

    if(Operand_Size==8){

        printf("Signed Two's Compliment\t\t");

    }

    if(Operand_Size==16){

        printf("Signed Two's Compliment\t\t");

    }

    

    if(flag == 0){

        printf("0b");

        twosComplement();

        print_twocomp();

    }else{

        printf("Error");

    }

    if(Operand_Size==4){

        printf("\t\t\t");

    }

    if(Operand_Size==8){

        printf("\t\t");

    }

    if(Operand_Size==16){

         printf("\t");

     }

    

    if(flag == 0){

        printf("0b");

        for(int j=0;j<Operand_Size;j++){

            printf("0");

        }

    }else{

        if(Operand_Size==4){

            printf("Error");

        }

        if(Operand_Size==8){

            printf("\tError");

        }

        if(Operand_Size==16){

             printf("\t\tError");

         }

    }

    if(Operand_Size==4){

        printf("\t\t\t");

    }

    if(Operand_Size==8){

        printf("\t\t");

    }

    if(Operand_Size==16){

        printf("\t");

    }

    

    if(flag == 0){

        printf("0b");

        for(int j=0;j<Operand_Size-1;j++){

            printf("0");

        }

        printf("1");

    }else{

        if(Operand_Size==4){

            printf("Error");

        }

        if(Operand_Size==8){

            printf("\tError");

        }

        if(Operand_Size==16){

             printf("\t\tError");

         }

    }

    printf("\n");

    

    /*Signed Magnitude print*/

    if(Operand_Size==4){

        printf("Signed Magnitude\t\t");

    }

    if(Operand_Size==8){

        printf("Signed Magnitude\t\t");

    }

    if(Operand_Size==16){

        printf("Signed Magnitude\t\t");

    }

    

    if(flag == 0){

        printf("0b");

        signed_mag(binaryNum);

        print_signmag();

    }else{

        printf("Error");

    }

    if(Operand_Size==4){

        printf("\t\t\t");

    }

    if(Operand_Size==8){

        printf("\t\t");

    }

    if(Operand_Size==16){

        printf("\t");

    }

    

    if(flag == 0){

        printf("0b");

        printf("0");

        for(int j=1;j<Operand_Size;j++){

            printf("1");

        }

    }else{

        if(Operand_Size==4){

            printf("Error");

        }

        if(Operand_Size==8){

            printf("\tError");

        }

        if(Operand_Size==16){

             printf("\t\tError");

         }

    }

    if(Operand_Size==4){

        printf("\t\t\t");

    }

    if(Operand_Size==8){

        printf("\t\t");

    }

    if(Operand_Size==16){

        printf("\t");

    }

    

    if(flag == 0){

        printf("0b");

        printf("1");

        for(int j=1;j<Operand_Size;j++){

            printf("0");

        }

    }else{

        if(Operand_Size==4){

            printf("Error");

        }

        if(Operand_Size==8){

            printf("\tError");

        }

        if(Operand_Size==16){

             printf("\t\tError");

         }

    }


    

    printf("\n");

    

    return 0;

}