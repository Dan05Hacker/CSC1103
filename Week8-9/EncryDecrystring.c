#include <stdio.h>
#include <string.h>
#define max_size 100

void cryto(int key,int choice,char c_message []);
int main()
{
   char message [max_size];
   char c_message[max_size]; /*Copy message*/
   int  key,choice;

   puts("\nEnter the message:\n");
   gets(message);
   printf("\n Enter the choice 1)Encryption 2)Decryption of message:");
   scanf("%d",&choice);
   printf("\n Enter the secret key:");
   scanf("%d",&key);
   strcpy(c_message,message); /*duplicate the message*/
   cryto(key,choice,c_message);
   if (choice==1)/*choice is encryption*/
   {
      printf("\nThe plaintext message is: ");
      puts(message);
      printf("\nThe ciphertext message is: ");
      puts(c_message);
   }
   else /*choice is decryption*/
   {
      printf("\nThe ciphertext message is: ");
      puts(message);
      printf("\nThe plaintext message is: ") ;
      puts(c_message);
   }
}/*end of main*/

void cryto(int key,int choice,char *p_message)
{
   while (*(p_message)!='\0')
   {
      switch (choice)
      {
         case 1:/* Encryption*/
         {   
            if (*p_message!=' ')
            {
               *p_message=*p_message-65;/*remove ASCII format*/     
               *p_message=((*p_message)+key)%26;
               *p_message=*p_message+65; /*convert back to ASCII*/
            }
            break;
         }/*end of case1*/
         case 2:/* Decryption*/
         {      
            if (*p_message!=' ')
            {
               *p_message=*p_message-65;/*remove ASCII format*/ 
               if ((*p_message)<=(key-1))
               {
                  *p_message=((*p_message-key)+26)%26; /*if C-K is negative*/
               } /*end of if*/
               else
               {
                  *p_message=((*p_message-key)%26);
               }/*end of else*/
               *p_message=*p_message+65;/*convert back to ASCII*/
            }
            break;
         }/*end of case2*/
      }/*end of switch*/
      ++p_message;
   }/*end of while*/
} 
   