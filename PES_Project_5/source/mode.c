/*
 * mode.c
 *
 *  Created on: Apr 10, 2020
 *      Author: Pavan and Antara
 *
 *	Reference: https://javatutoring.com/c-program-count-frequency-of-each-character-in-string/
 */

#include "mode.h"
/********String manipulation in polling mode********/
void string_manipulation_poll(uint8_t*c)
{
	uint32_t i,j,count=0,n;
	uint8_t s[1000];

	for(j=0;c[j];j++)
		 s[j] = c[j];

	n=j;



    for(i=0;i<n;i++){
     	count=1;
    	if(s[i]){
    		for(j=i+1;j<n;j++){
    			if(s[i]==s[j]){
    				count++;
    				s[j]='\0';
    			}
    		}
    		Send_String_Poll(" \n\r ");
    		UART0_Transmit_Poll(s[i]);
    		Send_String_Poll(" - ");
    		Send_Number(count);
        }
 	}
}

/***********String Manipulation in interrupt mode************/
void string_manipulation_int(uint8_t *c)
{
	uint32_t i,j,count=0,n;

	uint8_t s[1000];

		for(j=0;c[j];j++)
			 s[j] = c[j];

		n=j;

    for(i=0;i<n;i++){
     	count=1;
    	if(s[i]){
    		for(j=i+1;j<n;j++){
    			if(s[i]==s[j]){
    				count++;
    				s[j]='\0';
    			}
    		}
    		Send_String_Poll(" \n\r ");
    		UART0_Transmit_Poll(s[i]);
    		Send_String_Poll(" - ");
    		Send_Number(count);
        }
 	}
    Send_String_Poll(" \n\n\r ");
}
