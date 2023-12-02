#include <stdio.h>


int main()
{
   char message,plaintext,ciphertext; 
   int len,count,key,choice;

   printf("\n Enter the length of message:");
   scanf("%d",&len);
   printf("\n Enter the choice 1)Encryption 2)Decryption of message:");
   scanf("%d",&choice);
   printf("\n Enter the secret key:");
   scanf("%d",&key);
   count=1;
   while (count<=len)
   {
      printf("\n\n Enter the message:");
      scanf("%c",&message);
      scanf("%c",&message);
      switch (choice)
      {
          case 1:/* Encryption*/
        {   
            if (message!=' ')
            {
                printf("\n plaintext:%c", message);   /*ASCII message*/
                message=message-65;/*remove ASCII format*/     
                ciphertext=((message+key)%26);
                message=ciphertext+65; /*convert back to ASCII*/
                printf("\n ciphertext:%c",message);
            }
            else
            {
                printf("\n plaintext:%c",message);/*message is a whitespace*/
                printf("\n ciphertext:%c",message);/*message is a whitespace*/
            }
            break;
        }/*end of case1*/
        case 2:/* Decryption*/
        {      
            if (message!=' ')
            {
               printf("\n ciphertext:%c",message); /*ASCII message*/
               message=message-65;/*remove ASCII format*/ 
               if ((message)<=(key-1))
               {
                   plaintext=((message-key)+26)%26; /*if C-K is negative*/
               } /*end of if*/
               else
               {
                   plaintext=((message-key)%26);
               }/*end of else*/
               message=plaintext+65;/*convert back to ASCII*/
               printf("\n plaintext:%c",message);
            }
            else
            {
                printf("\n plaintext:%c",message);/*message is a whitespace*/
                printf("\n ciphertext:%c",message);/*message is a whitespace*/
            }
            break;
        }/*end of case2*/
      }/*end of switch*/
    count=count+1; 
   }/*end of while*/
}/*end of main*/