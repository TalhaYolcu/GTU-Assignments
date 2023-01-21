#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "romulus.h"


void test(const char*pt) {
    unsigned long long messageLen;
    unsigned long long len;

    unsigned char plaintext[BYTESOFCRYPTO];
    unsigned char c[BYTESOFCRYPTO];
    unsigned char n[ROMULUS_NPUBBYTES]="";
    unsigned char relatedData[ROMULUS_BYTES]="";
    unsigned char ns[ROMULUS_BYTES]="";

    unsigned char k[ROMULUS_KEYLEN];

    char pl[BYTESOFCRYPTO];
    char chex[BYTESOFCRYPTO]="";
    char hex[2*ROMULUS_KEYLEN+1]="0123456789ABCDEF0123456789ABCDEF";
    char nonce[2*ROMULUS_NPUBBYTES+1]="000000000000111111111111";
    char additional[ROMULUS_BYTES]="YakupTalhaYolcu";
    strcpy(pl,pt);

    strcpy(plaintext,pl);
    strcpy(relatedData,additional);
    hextobyte(hex,k);
    hextobyte(nonce,n);

    printf("Test of the Romulus light-weight cipher\n");
    printf("Plaintext: %s\n",plaintext);
    printf("Key: %s\n",hex);
    printf("Nonce: %s\n",nonce);
    printf("Additional Information: %s\n\n",relatedData);

    printf("Plaintext: %s\n",plaintext);


    int keep = romulusEncryption(c,&len,plaintext,strlen(plaintext),relatedData,strlen(relatedData),ns,n,k);


    s2h(c,len,hex);

    printf("Cipher: %s, Len: %llu\n",hex, len);

    keep = romulusDecryption(plaintext,&messageLen,ns,c,len,relatedData,strlen(relatedData),n,k);

    plaintext[messageLen]='\0';
    printf("Plaintext: %s, Len: %llu\n",plaintext, messageLen);

    if (keep==0) {
        printf("Romulus Cipher passed from the test successfully!\n");
    }

}

void testCBCMode(const char*pt) {
    unsigned long long messageLen;
    unsigned long long len;

    unsigned char plaintext[BYTESOFCRYPTO];
    unsigned char c[BYTESOFCRYPTO];
    unsigned char n[ROMULUS_NPUBBYTES]="";
    unsigned char relatedData[ROMULUS_BYTES]="";
    unsigned char ns[ROMULUS_BYTES]="";

    unsigned char k[ROMULUS_KEYLEN];

    char pl[BYTESOFCRYPTO];
    char chex[BYTESOFCRYPTO]="";
    char hex[2*ROMULUS_KEYLEN+1]="0123456789ABCDEF0123456789ABCDEF";
    char nonce[2*ROMULUS_NPUBBYTES+1]="000000000000111111111111";
    char additional[ROMULUS_BYTES]="YakupTalhaYolcu";

    strcpy(pl,pt);

    strcpy(plaintext,pl);
    strcpy(relatedData,additional);
    hextobyte(hex,k);
    hextobyte(nonce,n);

    printf("Test of the Romulus Algorithm with Cipher Block Chaining (CBC) mode\n");
    printf("Plaintext: %s\n",plaintext);
    printf("Key: %s\n",hex);
    printf("Nonce: %s\n",nonce);
    printf("Additional Information: %s\n\n",relatedData);

    printf("Plaintext: %s\n",plaintext);

    CBCMode(c,&len,plaintext,relatedData,ns,n,k);

}

void testOFBMode(const char*pt) {
    unsigned long long messageLen;
    unsigned long long len;

    unsigned char plaintext[BYTESOFCRYPTO];
    unsigned char c[BYTESOFCRYPTO];
    unsigned char n[ROMULUS_NPUBBYTES]="";
    unsigned char relatedData[ROMULUS_BYTES]="";
    unsigned char ns[ROMULUS_BYTES]="";

    unsigned char k[ROMULUS_KEYLEN];

    char pl[BYTESOFCRYPTO];
    char chex[BYTESOFCRYPTO]="";
    char hex[2*ROMULUS_KEYLEN+1]="0123456789ABCDEF0123456789ABCDEF";
    char nonce[2*ROMULUS_NPUBBYTES+1]="000000000000111111111111";
    char additional[ROMULUS_BYTES]="YakupTalhaYolcu";

    strcpy(pl,pt);

    strcpy(plaintext,pl);
    strcpy(relatedData,additional);
    hextobyte(hex,k);
    hextobyte(nonce,n);

    printf("Test of the Romulus Algorithm with Cipher Block Chaining (OFB) mode\n");
    printf("Plaintext: %s\n",plaintext);
    printf("Key: %s\n",hex);
    printf("Nonce: %s\n",nonce);
    printf("Additional Information: %s\n\n",relatedData);

    printf("Plaintext: %s\n",plaintext);

    OFBMode(c,&len,plaintext,relatedData,ns,n,k);

}


// TEST
int main (int argc, char *argv[]) {

    test("YakupTalhaYolcu");
    test("GebzeTechnicalUniversity");



    testCBCMode("YakupTalha");
    testOFBMode("YakupTalhaYolcu");



	return 0;
}
