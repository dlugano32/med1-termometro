/*
 * myString.c
 *
 *  Created on: 7 dic. 2021
 *      Author: d_lugano
 */

#include "myString.h"

void my_revstr (uint8_t *str, uint8_t *str_r)
{
       int i=0, j=0, length=0;

       while(*(str+i)!='\0')
       {
              i++;
       }
       length=i;

       for(i=0, j= (length-1) ; i < length ; i++, j--)
       {
              *(str_r+i)=*(str+j); //copio en str_r el string invertido
       }

       str_r[length]= '\0'; //le seteo el null

}

void my_strcat (uint8_t *destino, uint8_t *origen)
{
       int length=0, i=0;

       while(*(destino+i)!='\0')
       {
              i++;
       }
       length=i;

       for(i=0; *(origen+i)!='\0'; i++)
       {
              *(destino+ (length+i) )= *(origen+i); //piso el NULL en la primera pasada
       }

       destino[length+i]='\0';
}

uint8_t my_strlen(uint8_t* str1)
{
        uint8_t i=0;

    while(*(str1+i)!= '\0')
    	i++;

    return i;
}

int my_strcmp (uint8_t *str1, uint8_t *str2)
{
       int fin=1, dif=0, i=0;

       while ( (*(str1 +i) == *(str2 + i) ) && fin==1)
       {
              if(*(str1 +i) == '\0' && *(str2 + i)=='\0')
              {
                     dif=0;
                     fin=0;
              }
              i++;
       }

       if(fin ==1)
       {
              dif= *(str1+i) - *(str2+i);
       }

       return dif;
}
