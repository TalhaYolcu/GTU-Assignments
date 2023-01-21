
#include <stdio.h>
#include "tinyjambu.h"
#include <string.h>  
#include <stdlib.h>


int main(int argc, char const *argv[])
{

	printf("PART A \n\n");
	printf("File 'plaintext.txt' reading \n");
	char *filename = "plaintext.txt";
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    const int MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];
	char tempbuffer[MAX_LENGTH];
	memset( buffer, 0, MAX_LENGTH );
	memset( tempbuffer, 0, MAX_LENGTH );

    while (fgets(tempbuffer, MAX_LENGTH, fp))
        strcat(buffer,tempbuffer);
    fclose(fp);
	
	printf("First plaintext : %s",buffer);

	char* chiper = (char*)malloc(sizeof(char)*10000);
	long int chiperlen; 
	long long messagelen = strlen(buffer)*sizeof(char);
	char* associativeData = "assoc_data";
	long int associativeDatalen = sizeof(char)*strlen(associativeData);
	char* npub = "1234567890123456";
	char* key = "12345678901234567890123456789";

	encryption(chiper, &chiperlen,buffer, messagelen, associativeData, associativeDatalen, npub,key	);

	printf("First plaintext Encrypted : %s \n", chiper);
	printf("First plaintext Encrypted Length : %ld\n",chiperlen);

	char* decmessage = (char*)malloc(sizeof(char)*10000);
	long long decmessagelen;
	
	decryption(decmessage, &decmessagelen, chiper, chiperlen, associativeData, associativeDatalen, npub, key);
	printf("First plaintext Decrypted: %s\n", decmessage);



 	char* message= "Yakup Talha Yolcu";
	char* chiper2 = (char*)malloc(sizeof(char)*10000);

	printf("Second plaintext : %s\n",message);
	long long messagelen2 = strlen(message)*sizeof(char);
	long int chiperlen2; 
	encryption(chiper2, &chiperlen2, message, messagelen2, associativeData, associativeDatalen, npub, key);
	printf("Second plaintext Encrypted : %s \n",chiper2);
	printf("Second plaintext Encrypted Length : %ld\n",chiperlen2);

	char* decmessage2 = (char*)malloc(sizeof(char)*10000);
	long long decmessagelen2;
	
	decryption( decmessage2, &decmessagelen2, chiper2, chiperlen2,associativeData,associativeDatalen, npub, key);
	printf("Second plaintext Decrypted: %s\n", decmessage2);

	printf("\nPART B\n");
	char* message2 = "GEBZETECHNICALUNIVERSITY";
	CBCmode(message2,key,npub,5);

	myOFBmode(message2,key,npub,5);
}
