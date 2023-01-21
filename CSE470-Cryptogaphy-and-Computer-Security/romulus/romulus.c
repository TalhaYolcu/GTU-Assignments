#include "romulus.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int romulusTypes[6][3]={{64,64,32},{64,128,36},{64,192,40},{128,128,40},{128,256,48},{128,384,56}};

// Sbox for 4 bit
const unsigned char sbox_4[16] = {12,6,9,0,1,10,2,11,3,8,5,13,4,14,7,15};

// Sbox for 8-bit
const unsigned char sbox_8[256] = {0x65 , 0x4c , 0x6a , 0x42 , 0x4b , 0x63 , 0x43 , 0x6b , 0x55 , 0x75 , 0x5a , 0x7a , 0x53 , 0x73 , 0x5b , 0x7b ,0x35 , 0x8c , 0x3a , 0x81 , 0x89 , 0x33 , 0x80 , 0x3b , 0x95 , 0x25 , 0x98 , 0x2a , 0x90 , 0x23 , 0x99 , 0x2b ,0xe5 , 0xcc , 0xe8 , 0xc1 , 0xc9 , 0xe0 , 0xc0 , 0xe9 , 0xd5 , 0xf5 , 0xd8 , 0xf8 , 0xd0 , 0xf0 , 0xd9 , 0xf9 ,0xa5 , 0x1c , 0xa8 , 0x12 , 0x1b , 0xa0 , 0x13 , 0xa9 , 0x05 , 0xb5 , 0x0a , 0xb8 , 0x03 , 0xb0 , 0x0b , 0xb9 ,0x32 , 0x88 , 0x3c , 0x85 , 0x8d , 0x34 , 0x84 , 0x3d , 0x91 , 0x22 , 0x9c , 0x2c , 0x94 , 0x24 , 0x9d , 0x2d ,0x62 , 0x4a , 0x6c , 0x45 , 0x4d , 0x64 , 0x44 , 0x6d , 0x52 , 0x72 , 0x5c , 0x7c , 0x54 , 0x74 , 0x5d , 0x7d ,0xa1 , 0x1a , 0xac , 0x15 , 0x1d , 0xa4 , 0x14 , 0xad , 0x02 , 0xb1 , 0x0c , 0xbc , 0x04 , 0xb4 , 0x0d , 0xbd ,0xe1 , 0xc8 , 0xec , 0xc5 , 0xcd , 0xe4 , 0xc4 , 0xed , 0xd1 , 0xf1 , 0xdc , 0xfc , 0xd4 , 0xf4 , 0xdd , 0xfd ,0x36 , 0x8e , 0x38 , 0x82 , 0x8b , 0x30 , 0x83 , 0x39 , 0x96 , 0x26 , 0x9a , 0x28 , 0x93 , 0x20 , 0x9b , 0x29 ,0x66 , 0x4e , 0x68 , 0x41 , 0x49 , 0x60 , 0x40 , 0x69 , 0x56 , 0x76 , 0x58 , 0x78 , 0x50 , 0x70 , 0x59 , 0x79 ,0xa6 , 0x1e , 0xaa , 0x11 , 0x19 , 0xa3 , 0x10 , 0xab , 0x06 , 0xb6 , 0x08 , 0xba , 0x00 , 0xb3 , 0x09 , 0xbb ,0xe6 , 0xce , 0xea , 0xc2 , 0xcb , 0xe3 , 0xc3 , 0xeb , 0xd6 , 0xf6 , 0xda , 0xfa , 0xd3 , 0xf3 , 0xdb , 0xfb ,0x31 , 0x8a , 0x3e , 0x86 , 0x8f , 0x37 , 0x87 , 0x3f , 0x92 , 0x21 , 0x9e , 0x2e , 0x97 , 0x27 , 0x9f , 0x2f ,0x61 , 0x48 , 0x6e , 0x46 , 0x4f , 0x67 , 0x47 , 0x6f , 0x51 , 0x71 , 0x5e , 0x7e , 0x57 , 0x77 , 0x5f , 0x7f ,0xa2 , 0x18 , 0xae , 0x16 , 0x1f , 0xa7 , 0x17 , 0xaf , 0x01 , 0xb2 , 0x0e , 0xbe , 0x07 , 0xb7 , 0x0f , 0xbf ,0xe2 , 0xca , 0xee , 0xc6 , 0xcf ,0xe7 , 0xc7 , 0xef , 0xd2 , 0xf2 , 0xde , 0xfe , 0xd7 , 0xf7 , 0xdf , 0xff};

// ShiftAndSwitchRows permutation
const unsigned char P[16] = {0,1,2,3,7,4,5,6,10,11,8,9,13,14,15,12};

// Tweakey permutation
const unsigned char TWEAKEY_P[16] = {9,15,8,13,10,14,12,11,0,1,2,3,4,5,6,7};


// round constants
const unsigned char roundArray[62] = {
		0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3E, 0x3D, 0x3B, 0x37, 0x2F,
		0x1E, 0x3C, 0x39, 0x33, 0x27, 0x0E, 0x1D, 0x3A, 0x35, 0x2B,
		0x16, 0x2C, 0x18, 0x30, 0x21, 0x02, 0x05, 0x0B, 0x17, 0x2E,
		0x1C, 0x38, 0x31, 0x23, 0x06, 0x0D, 0x1B, 0x36, 0x2D, 0x1A,
		0x34, 0x29, 0x12, 0x24, 0x08, 0x11, 0x22, 0x04, 0x09, 0x13,
		0x26, 0x0c, 0x19, 0x32, 0x25, 0x0a, 0x15, 0x2a, 0x14, 0x28,
		0x10, 0x20};

void keyAddingOperation(unsigned char state[4][4], unsigned char keyCells[3][4][4], int ver)
{
	int i, j, k;
	unsigned char pos;
	unsigned char keyCells_tmp[3][4][4];

    for(i = 0; i <= 1; i++)
    {
        for(j = 0; j < 4; j++)
        {
            state[i][j] ^= keyCells[0][i][j];
            if (2*romulusTypes[ver][0]==romulusTypes[ver][1])
                state[i][j] ^= keyCells[1][i][j];
            else if (3*romulusTypes[ver][0]==romulusTypes[ver][1])
               state[i][j] ^= keyCells[1][i][j] ^ keyCells[2][i][j];
        }
    }

    for(k = 0; k <(int)(romulusTypes[ver][1]/romulusTypes[ver][0]); k++){
        for(i = 0; i < 4; i++){
            for(j = 0; j < 4; j++){
                pos=TWEAKEY_P[j+4*i];
                keyCells_tmp[k][i][j]=keyCells[k][pos>>2][pos&0x3];
            }
        }
    }

    for(k = 0; k <(int)(romulusTypes[ver][1]/romulusTypes[ver][0]); k++){
        for(i = 0; i <= 1; i++){
            for(j = 0; j < 4; j++){
                if (k==1)
                {
                    if (romulusTypes[ver][0]==64)
                        keyCells_tmp[k][i][j]=((keyCells_tmp[k][i][j]<<1)&0xE)^((keyCells_tmp[k][i][j]>>3)&0x1)^((keyCells_tmp[k][i][j]>>2)&0x1);
                    else
                        keyCells_tmp[k][i][j]=((keyCells_tmp[k][i][j]<<1)&0xFE)^((keyCells_tmp[k][i][j]>>7)&0x01)^((keyCells_tmp[k][i][j]>>5)&0x01);
                }
                else if (k==2)
                {
                    if (romulusTypes[ver][0]==64)
                        keyCells_tmp[k][i][j]=((keyCells_tmp[k][i][j]>>1)&0x7)^((keyCells_tmp[k][i][j])&0x8)^((keyCells_tmp[k][i][j]<<3)&0x8);
                    else
                        keyCells_tmp[k][i][j]=((keyCells_tmp[k][i][j]>>1)&0x7F)^((keyCells_tmp[k][i][j]<<7)&0x80)^((keyCells_tmp[k][i][j]<<1)&0x80);
                }
            }
        }
    }
    for(k = 0; k <(int)(romulusTypes[ver][1]/romulusTypes[ver][0]); k++){
        for(i = 0; i < 4; i++){
            for(j = 0; j < 4; j++){
                keyCells[k][i][j]=keyCells_tmp[k][i][j];
            }
        }
    }
}


void add(unsigned char current[4][4], int r)
{
	current[0][0] ^= (roundArray[r] & 0xf);
	current[1][0] ^= ((roundArray[r]>>4) & 0x3);
	current[2][0] ^= 0x2;
}

void SubCell4(unsigned char current[4][4])
{
	int a,b;
	for(a = 0; a < 4; a++)
		for(b = 0; b <  4; b++)
			current[a][b] = sbox_4[current[a][b]];
}


void SubCell8(unsigned char state[4][4])
{
	int i,j;
	for(i = 0; i < 4; i++)
		for(j = 0; j <  4; j++)
			state[i][j] = sbox_8[state[i][j]];
}

void ShiftRows(unsigned char current[4][4])
{
	int a,b,loc;

	unsigned char current_tmp[4][4];
    for(a = 0; a < 4; a++)
    {
        for(b = 0; b < 4; b++)
        {
            loc=P[b+4*a];
            current_tmp[a][b]=current[loc>>2][loc&0x3];
        }
    }

    for(a = 0; a < 4; a++)
    {
        for(b = 0; b < 4; b++)
        {
            current[a][b]=current_tmp[a][b];
        }
    }
}

void MixColumn(unsigned char current[4][4])
{
	int b;
  unsigned char keep;

	for(b = 0; b < 4; b++){
        current[1][b]^=current[2][b];
        current[2][b]^=current[0][b];
        current[3][b]^=current[2][b];

        keep=current[3][b];
        current[3][b]=current[2][b];
        current[2][b]=current[1][b];
        current[1][b]=current[0][b];
        current[0][b]=keep;
	}
}

// decryption function
void dec(unsigned char* input, const unsigned char* userkey, int ver)
{
	unsigned char state[4][4];
	unsigned char dummy[4][4]={{0}};
	unsigned char keyCells[3][4][4];
	int i;

    memset(keyCells, 0, 48);
	for(i = 0; i < 16; i++) {
        if (romulusTypes[ver][0]==64){
            if(i&1)
            {
                state[i>>2][i&0x3] = input[i>>1]&0xF;
                keyCells[0][i>>2][i&0x3] = userkey[i>>1]&0xF;
                if (romulusTypes[ver][1]>=128)
                    keyCells[1][i>>2][i&0x3] = userkey[(i+16)>>1]&0xF;
                if (romulusTypes[ver][1]>=192)
                    keyCells[2][i>>2][i&0x3] = userkey[(i+32)>>1]&0xF;
            }
            else
            {
                state[i>>2][i&0x3] = (input[i>>1]>>4)&0xF;
                keyCells[0][i>>2][i&0x3] = (userkey[i>>1]>>4)&0xF;
                if (romulusTypes[ver][1]>=128)
                    keyCells[1][i>>2][i&0x3] = (userkey[(i+16)>>1]>>4)&0xF;
                if (romulusTypes[ver][1]>=192)
                    keyCells[2][i>>2][i&0x3] = (userkey[(i+32)>>1]>>4)&0xF;
            }
        }
        else if (romulusTypes[ver][0]==128){
            state[i>>2][i&0x3] = input[i]&0xFF;

            keyCells[0][i>>2][i&0x3] = userkey[i]&0xFF;
            if (romulusTypes[ver][1]>=256)
                keyCells[1][i>>2][i&0x3] = userkey[i+16]&0xFF;
            if (romulusTypes[ver][1]>=384)
                keyCells[2][i>>2][i&0x3] = userkey[i+32]&0xFF;
        }
    }

    for(i = romulusTypes[ver][2]-1; i >=0 ; i--){
        keyAddingOperation(dummy, keyCells, ver);
    }


    if (romulusTypes[ver][0]==64)
    {
        for(i = 0; i < 8; i++)
            input[i] = ((state[(2*i)>>2][(2*i)&0x3] & 0xF) << 4) | (state[(2*i+1)>>2][(2*i+1)&0x3] & 0xF);
    }
    else if (romulusTypes[ver][0]==128)
    {
        for(i = 0; i < 16; i++)
            input[i] = state[i>>2][i&0x3] & 0xFF;
    }
}


// encryption function of Skinny
void enc(unsigned char* input, const unsigned char* userkey, int ver)
{
	unsigned char state[4][4];
	unsigned char keyCells[3][4][4];
	int i;

	memset(keyCells, 0, 48);
	for(i = 0; i < 16; i++) {
        if (romulusTypes[ver][0]==64){
            if(i&1)
            {
                state[i>>2][i&0x3] = input[i>>1]&0xF;
                keyCells[0][i>>2][i&0x3] = userkey[i>>1]&0xF;
                if (romulusTypes[ver][1]>=128)
                    keyCells[1][i>>2][i&0x3] = userkey[(i+16)>>1]&0xF;
                if (romulusTypes[ver][1]>=192)
                    keyCells[2][i>>2][i&0x3] = userkey[(i+32)>>1]&0xF;
            }
            else
            {
                state[i>>2][i&0x3] = (input[i>>1]>>4)&0xF;
                keyCells[0][i>>2][i&0x3] = (userkey[i>>1]>>4)&0xF;
                if (romulusTypes[ver][1]>=128)
                    keyCells[1][i>>2][i&0x3] = (userkey[(i+16)>>1]>>4)&0xF;
                if (romulusTypes[ver][1]>=192)
                    keyCells[2][i>>2][i&0x3] = (userkey[(i+32)>>1]>>4)&0xF;
            }
        }
        else if (romulusTypes[ver][0]==128){
            state[i>>2][i&0x3] = input[i]&0xFF;
            keyCells[0][i>>2][i&0x3] = userkey[i]&0xFF;
            if (romulusTypes[ver][1]>=256)
                keyCells[1][i>>2][i&0x3] = userkey[i+16]&0xFF;
            if (romulusTypes[ver][1]>=384)
                keyCells[2][i>>2][i&0x3] = userkey[i+32]&0xFF;
        }
	}

	for(i = 0; i < romulusTypes[ver][2]; i++){
        if (romulusTypes[ver][0]==64)
            SubCell4(state);
        else
            SubCell8(state);
        add(state, i);
        keyAddingOperation(state, keyCells, ver);
        ShiftRows(state);
				MixColumn(state);

	}
    if (romulusTypes[ver][0]==64)
    {
        for(i = 0; i < 8; i++)
            input[i] = ((state[(2*i)>>2][(2*i)&0x3] & 0xF) << 4) | (state[(2*i+1)>>2][(2*i+1)&0x3] & 0xF);
    }
    else if (romulusTypes[ver][0]==128)
    {
        for(i = 0; i < 16; i++)
            input[i] = state[i>>2][i&0x3] & 0xFF;
    }
}

void skinny_128_384_enc (unsigned char* input, const unsigned char* userkey) {
  enc(input,userkey,5);
}

// generate test vectors for all the romulusTypes of Skinny
void TestVectors(int ver)
{
	unsigned char p[16];
	unsigned char c[16];
	unsigned char k[48];
	int n;

	for(n = 1; n < 10; n++)
	{
		int i;
		for(i = 0; i < (romulusTypes[ver][0]>>3); i++) c[i] = p[i] = rand() & 0xff;
		for(i = 0; i < (romulusTypes[ver][1]>>3); i++) k[i] = rand() & 0xff;
		enc(c,k,ver);
		dec(c,k,ver);
	}
}


void pad (const unsigned char* m, unsigned char* mp, int l, int len8) {
  int i;

  for (i = 0; i < l; i++) {
    if (i < len8) {
      mp[i] = m[i];
    }
    else if (i == l - 1) {
      mp[i] = (len8 & 0x0f);
    }
    else {
      mp[i] = 0x00;
    }
  }

}

void g8A (unsigned char* s, unsigned char* c) {
  int i;

  for (i = 0; i < 16; i++) {
    c[i] = (s[i] >> 1) ^ (s[i] & 0x80) ^ ((s[i] & 0x01) << 7);
  }

}

void rho_ad (const unsigned char* m,
	     unsigned char* s,
	     int len8,
	     int ver) {
  int i;
  unsigned char mp [16];
  pad(m,mp,ver,len8);

  for (i = 0; i < ver; i++) {
    s[i] = s[i] ^ mp[i];
  }
}

void rho (const unsigned char* m,
	  unsigned char* c,
	  unsigned char* s,
	  int len8,
	  int ver) {
  int i;
  unsigned char mp [16];
  pad(m,mp,ver,len8);
  g8A(s,c);
  for (i = 0; i < ver; i++) {
    s[i] = s[i] ^ mp[i];
    if (i < len8) {
      c[i] = c[i] ^ mp[i];
    }
    else {
      c[i] = 0;
    }
  }

}

void irho (unsigned char* m,
	  const unsigned char* c,
	  unsigned char* s,
	  int len8,
	  int ver) {
  int i;
  unsigned char cp [16];
  pad(c,cp,ver,len8);
  g8A(s,m);
  for (i = 0; i < ver; i++) {
    if (i < len8) {
      s[i] = s[i] ^ cp[i] ^ m[i];
    }
    else {
      s[i] = s[i] ^ cp[i];
    }
    if (i < len8) {
      m[i] = m[i] ^ cp[i];
    }
    else {
      m[i] = 0;
    }
  }
}

void lfsrNull (unsigned char* CNT) {
  CNT[0] = 0x01;
  CNT[1] = 0x00;
  CNT[2] = 0x00;
  CNT[3] = 0x00;
  CNT[4] = 0x00;
  CNT[5] = 0x00;
  CNT[6] = 0x00;
}

void lfsr_gf56 (unsigned char* CNT) {
  unsigned char fb0;

  fb0 = CNT[6] >> 7;

  CNT[6] = (CNT[6] << 1) | (CNT[5] >> 7);
  CNT[5] = (CNT[5] << 1) | (CNT[4] >> 7);
  CNT[4] = (CNT[4] << 1) | (CNT[3] >> 7);
  CNT[3] = (CNT[3] << 1) | (CNT[2] >> 7);
  CNT[2] = (CNT[2] << 1) | (CNT[1] >> 7);
  CNT[1] = (CNT[1] << 1) | (CNT[0] >> 7);
  if (fb0 == 1) {
    CNT[0] = (CNT[0] << 1) ^ 0x95;
  }
  else {
    CNT[0] = (CNT[0] << 1);
  }
}

void compose_tweakey (unsigned char* KT,
		      const unsigned char* K,
		      unsigned char* T,
		      unsigned char* CNT,
		      unsigned char D,
		      int t) {

  int i;

  for (i = 0; i < 7; i++) {
    KT[i] = CNT[i];
  }
  KT[i] = D;
  for (i = 8; i < 16; i++) {
    KT[i] = 0x00;
  }
  for (i = 0; i < t; i++) {
    KT[i+16] = T[i];
  }
  for (i = 0; i < 16; i++) {
    KT[i+16+t] = K[i];
  }

}

void block_cipher(unsigned char* s,
		  const unsigned char* k, unsigned char* T,
		  unsigned char* CNT, unsigned char D, int t, int n) {
  unsigned char KT [48];

  (void)n;
  compose_tweakey(KT,k,T,CNT,D,t);
  skinny_128_384_enc (s,KT);

}

void encryptionOfNonce (const unsigned char* N,
		       unsigned char* CNT,
		       unsigned char*s, const unsigned char* k,
		       int t, int n, unsigned char D) {
  unsigned char T [16];
  int i;

  for (i = 0; i < t; i++) {
    T[i] = N[i];
  }
  //printf("nonce cnt = ");display_vector(CNT,7);
  block_cipher(s,k,T,CNT,D,t,n);

}


unsigned long long msg_encryption (const unsigned char** M, unsigned char** c,
				   const unsigned char* N,
				   unsigned char* CNT,
				   unsigned char*s, const unsigned char* k,
				   unsigned int n, unsigned int t, unsigned char D,
				   unsigned long long mlen) {
  int len8;


  if (mlen >= n) {
    len8 = n;
    mlen = mlen - n;
  }
  else {
    len8 = mlen;
    mlen = 0;
  }
  rho(*M, *c, s, len8, n);
  *c = *c + len8;
  *M = *M + len8;
  lfsr_gf56(CNT);
  if (mlen != 0) {
    encryptionOfNonce(N,CNT,s,k,t,n,D);
  }
  return mlen;
}



unsigned long long msg_decryption (unsigned char** M, const unsigned char** c,
				   const unsigned char* N,
				   unsigned char* CNT,
				   unsigned char*s, const unsigned char* k,
				   unsigned int n, unsigned int t, unsigned char D,
				   unsigned long long clen) {
  int len8;

  if (clen >= n) {
    len8 = n;
    clen = clen - n;
  }
  else {
    len8 = clen;
    clen = 0;
  }
  irho(*M, *c, s, len8, n);
  *c = *c + len8;
  *M = *M + len8;
  lfsr_gf56(CNT);
  encryptionOfNonce(N,CNT,s,k,t,n,D);
  return clen;
}

unsigned long long ad2msg_encryption (const unsigned char** M,
				      unsigned char* CNT,
				      unsigned char*s, const unsigned char* k,
				      unsigned int t, unsigned int n, unsigned char D,
				      unsigned long long mlen) {
  unsigned char T [16];
  int len8;

  if (mlen <= t) {
    len8 = mlen;
    mlen = 0;
  }
  else {
    len8 = t;
    mlen = mlen - t;
  }

  pad (*M,T,t,len8);
  //printf("ad2msg nonce cnt = ");display_vector(CNT,7);
  block_cipher(s,k,T,CNT,D,t,n);
  lfsr_gf56(CNT);
  *M = *M + len8;

  return mlen;

}


unsigned long long ad_encryption (const unsigned char** A, unsigned char* s,
				  const unsigned char* k, unsigned long long adlen,
				  unsigned char* CNT,
				  unsigned char D,
				  unsigned int n, unsigned int t) {

  unsigned char T [16];
  int len8;

  if (adlen >= n) {
    len8 = n;
    adlen = adlen - n;
  }
  else {
    len8 = adlen;
    adlen = 0;
  }
  rho_ad(*A, s, len8, n);
  *A = *A + len8;
  lfsr_gf56(CNT);
  if (adlen != 0) {
    if (adlen >= t) {
      len8 = t;
      adlen = adlen - t;
    }
    else {
      len8 = adlen;
      adlen = 0;
    }
    pad(*A, T, t, len8);
    *A = *A + len8;
    block_cipher(s,k,T,CNT,D,t,n);
    lfsr_gf56(CNT);
  }

  return adlen;
}

int romulusEncryption (
			 unsigned char* c, unsigned long long* clen,
			 const unsigned char* m, unsigned long long mlen,
			 const unsigned char* ad, unsigned long long adlen,
			 const unsigned char* nsec,
			 const unsigned char* npub,
			 const unsigned char* k
			 )
{
  unsigned char s[16];
  unsigned char CNT[7];
  unsigned char T[16];
  const unsigned char* N;
  unsigned int n, t, i;
  unsigned char w;
  unsigned long long xlen;

  (void)nsec;
  N = npub;

  n = DATA_LEN_ODD;
  t = DATA_LEN_EVEN;

  xlen = mlen;

  for (i = 0; i < n; i++) {
    s[i] = 0;
  }
  lfsrNull(CNT);
  //printf("s = ");display_vector(s,16);
  //printf("cnt = ");display_vector(CNT,7);

  w = 48;

  if (adlen == 0) {
    w = w ^ 2;
    if (xlen == 0) {
      w =w ^ 1;
    }
    else if (xlen%(n+t) == 0) {
      w = w ^ 4;
    }
    else if (xlen%(n+t) < t) {
      w = w ^ 1;
    }
    else if (xlen%(n+t) == t) {
      w = w ^ 0;
    }
    else {
      w = w ^ 5;
    }
  }
  else if (adlen%(n+t) == 0) {
    w = w ^ 8;
    if (xlen == 0) {
      w =w ^ 1;
    }
    else if (xlen%(n+t) == 0) {
      w = w ^ 4;
    }
    else if (xlen%(n+t) < n) {
      w = w ^ 1;
    }
    else if (xlen%(n+t) == n) {
      w = w ^ 0;
    }
    else {
      w = w ^ 5;
    }
  }
  else if (adlen%(n+t) < n) {
    w = w ^ 2;
    if (xlen == 0) {
      w =w ^ 1;
    }
    else if (xlen%(n+t) == 0) {
      w = w ^ 4;
    }
    else if (xlen%(n+t) < t) {
      w = w ^ 1;
    }
    else if (xlen%(n+t) == t) {
      w = w ^ 0;
    }
    else {
      w = w ^ 5;
    }
  }
  else if (adlen%(n+t) == n) {
    w = w ^ 0;
    if (xlen == 0) {
      w =w ^ 1;
    }
    else if (xlen%(n+t) == 0) {
      w = w ^ 4;
    }
    else if (xlen%(n+t) < t) {
      w = w ^ 1;
    }
    else if (xlen%(n+t) == t) {
      w = w ^ 0;
    }
    else {
      w = w ^ 5;
    }
  }
  else {
    w = w ^ 10;
    if (xlen == 0) {
      w =w ^ 1;
    }
    else if (xlen%(n+t) == 0) {
      w = w ^ 4;
    }
    else if (xlen%(n+t) < n) {
      w = w ^ 1;
    }
    else if (xlen%(n+t) == n) {
      w = w ^ 0;
    }
    else {
      w = w ^ 5;
    }
  }

  if (adlen == 0) {
    lfsr_gf56(CNT);
  }
  else while (adlen > 0) {
      adlen = ad_encryption(&ad,s,k,adlen,CNT,40,n,t);
    }

  if ((w & 8) == 0) {
    xlen = ad2msg_encryption (&m,CNT,s,k,t,n,44,xlen);
  }
  else if (mlen == 0) {
    lfsr_gf56(CNT);
  }
  while (xlen > 0) {
    xlen = ad_encryption(&m,s,k,xlen,CNT,44,n,t);
  }
  encryptionOfNonce(N,CNT,s,k,t,n,w);
  g8A(s, T);

  m = m - mlen;

  lfsrNull(CNT);

  for (i = 0; i < n; i = i + 1) {
    s[i] = T[i];
  }

  n = LENGTH_MSG;
  *clen = mlen + n;



  if (mlen > 0) {
    encryptionOfNonce(N,CNT,s,k,t,n,36);
    while (mlen > n) {
      mlen = msg_encryption(&m,&c,N,CNT,s,k,n,t,36,mlen);
    }
    rho(m, c, s, mlen, 16);
    c = c + mlen;
    m = m + mlen;
  }

  // Tag Concatenation
  for (i = 0; i < 16; i = i + 1) {
    *(c + i) = T[i];
  }

  c = c - *clen;



  return 0;
}

int romulusDecryption(
unsigned char *m,unsigned long long *mlen,
unsigned char *nsec,
const unsigned char *c,unsigned long long clen,
const unsigned char *ad,unsigned long long adlen,
const unsigned char *npub,
const unsigned char *k
)
{
  unsigned char s[16];
  unsigned char CNT[7];
  unsigned char T[16];
  const unsigned char* N;
  unsigned int n, t, i;
  unsigned char w;
  unsigned long long xlen;
  const unsigned char* mauth;

  (void)nsec;
  mauth = m;

  N = npub;

  n = DATA_LEN_ODD;
  t = DATA_LEN_EVEN;

  xlen = clen-16;

  lfsrNull(CNT);

  for (i = 0; i < 16; i++) {
    T[i] = *(c + clen - 16 + i);
  }

  for (i = 0; i < n; i = i + 1) {
    s[i] = T[i];
  }

  n = LENGTH_MSG;
  clen = clen - 16;
  *mlen = clen;


  if (clen > 0) {
    encryptionOfNonce(N,CNT,s,k,t,n,36);
    while (clen > n) {
      clen = msg_decryption(&m,&c,N,CNT,s,k,n,t,36,clen);
    }
    irho(m, c, s, clen, 16);
    c = c + clen;
    m = m + clen;
  }


  for (i = 0; i < n; i++) {
    s[i] = 0;
  }
  lfsrNull(CNT);

  w = 48;

  if (adlen == 0) {
    w = w ^ 2;
    if (xlen == 0) {
      w =w ^ 1;
    }
    else if (xlen%(n+t) == 0) {
      w = w ^ 4;
    }
    else if (xlen%(n+t) < t) {
      w = w ^ 1;
    }
    else if (xlen%(n+t) == t) {
      w = w ^ 0;
    }
    else {
      w = w ^ 5;
    }
  }
  else if (adlen%(n+t) == 0) {
    w = w ^ 8;
    if (xlen == 0) {
      w =w ^ 1;
    }
    else if (xlen%(n+t) == 0) {
      w = w ^ 4;
    }
    else if (xlen%(n+t) < n) {
      w = w ^ 1;
    }
    else if (xlen%(n+t) == n) {
      w = w ^ 0;
    }
    else {
      w = w ^ 5;
    }
  }
  else if (adlen%(n+t) < n) {
    w = w ^ 2;
    if (xlen == 0) {
      w =w ^ 1;
    }
    else if (xlen%(n+t) == 0) {
      w = w ^ 4;
    }
    else if (xlen%(n+t) < t) {
      w = w ^ 1;
    }
    else if (xlen%(n+t) == t) {
      w = w ^ 0;
    }
    else {
      w = w ^ 5;
    }
  }
  else if (adlen%(n+t) == n) {
    w = w ^ 0;
    if (xlen == 0) {
      w =w ^ 1;
    }
    else if (xlen%(n+t) == 0) {
      w = w ^ 4;
    }
    else if (xlen%(n+t) < t) {
      w = w ^ 1;
    }
    else if (xlen%(n+t) == t) {
      w = w ^ 0;
    }
    else {
      w = w ^ 5;
    }
  }
  else {
    w = w ^ 10;
    if (xlen == 0) {
      w =w ^ 1;
    }
    else if (xlen%(n+t) == 0) {
      w = w ^ 4;
    }
    else if (xlen%(n+t) < n) {
      w = w ^ 1;
    }
    else if (xlen%(n+t) == n) {
      w = w ^ 0;
    }
    else {
      w = w ^ 5;
    }
  }

  if (adlen == 0) {
    lfsr_gf56(CNT);

  }
  else while (adlen > 0) {
      adlen = ad_encryption(&ad,s,k,adlen,CNT,40,n,t);
    }


  if ((w & 8) == 0) {
    xlen = ad2msg_encryption (&mauth,CNT,s,k,t,n,44,xlen);
  }
  else if (clen == 0) {
    lfsr_gf56(CNT);
  }
  while (xlen > 0) {
    xlen = ad_encryption(&mauth,s,k,xlen,CNT,44,n,t);
  }
  encryptionOfNonce(N,CNT,s,k,t,n,w);

  g8A(s, T);
  for (i = 0; i < 16; i++) {
    if (T[i] != (*(c+i))) {
      return -1;
    }
  }

  return 0;
}

int romulusEncryption (
			 unsigned char* c, unsigned long long* clen,
			 const unsigned char* m, unsigned long long mlen,
			 const unsigned char* ad, unsigned long long adlen,
			 const unsigned char* nsec,
			 const unsigned char* npub,
			 const unsigned char* k
     );

void s2h(unsigned char* in, int len, char* out)
 {
     int turn;
     int t;
     t=0;
     turn=0;
     for (t=0;t<len;t+=2){
         sprintf((char*)(out+t),"%02hhX", in[turn]);
         turn+=1;

     }
     //insert NULL at the end of the output string
     out[t++] = '\0';

}

void *hextobyte(char *hex, unsigned char* bytes) {

    int t;

    int len = strlen(hex);

    for (t = 0; t < (len / 2); t++) {
        sscanf(hex + 2*t, "%02hhx", &bytes[t]);
    }

}

void CBCMode(unsigned char*c,unsigned long long* clen,
			 const unsigned char* m,const unsigned char* ad,
             unsigned char* nsec,
			 const unsigned char* npub,
			 const unsigned char* k) {

    //c -> ciphertext
    //clen -> ciphertext len
    //m -> plaintext
    //mlen-> plaintext len
    //ad -> associative data
    //nsec - >
    //npub -> IV
    //k -> key

    int block_n=5;
	int new_plain_text_len=strlen(m);
	char* new_plain_text=(char*)malloc(sizeof(char)*new_plain_text_len);

	for(int i=0;i<new_plain_text_len;i++) {
		new_plain_text[i]='\0';
	}
	for(int i=0;i<strlen(m);i++) {
		new_plain_text[i]=m[i];
	}

	int block_size = ((new_plain_text_len)/block_n);
	byte text_blocks[block_n][block_size];
	for( int i =0; i<block_n; ++i ){
		for(int j = 0; j<block_size; ++j )
			text_blocks[i][j] = (byte)'\0';
	}
	for( int i =0; i<block_n; ++i ){
		for(int j = 0; j<block_size; ++j )
			text_blocks[i][j] = (byte)new_plain_text[i*block_size + j];
	}

    byte xor_results[block_n][block_size*10];
	byte cipher_text[block_n][block_size*10];
    unsigned long long cipher_text_lens[block_n];
	byte second_plain_text[block_n][block_size*10];
    

    for(int i=0;i<block_n;i++) {
        for(int j=0;j<block_size*10;j++) {
            xor_results[i][j]=(byte)'\0';
            cipher_text[i][j]=(byte)'\0';
            second_plain_text[i][j]=(byte)'\0';
        }
    }

    //first block - xor
    for(int j=0;j<block_size;j++) {
        xor_results[0][j]=text_blocks[0][j] ^ npub[j];
    }

    int* keep_array_enc=(int*)(malloc(sizeof(int)*block_n));
    int* keep_array_dec=(int*)(malloc(sizeof(int)*block_n));

    keep_array_enc[0] = romulusEncryption(cipher_text[0],&cipher_text_lens[0],
            xor_results[0],strlen(xor_results[0]),
            ad,strlen(ad),nsec,npub,k
        );

    for(int i=1;i<block_n;i++) {
        //xor
        for(int j=0;j<block_size;j++) {
            xor_results[i][j]=text_blocks[i][j] ^ cipher_text[i-1][j];
        }      

        keep_array_enc[i]=romulusEncryption(cipher_text[i],&cipher_text_lens[i],
            xor_results[i],strlen(xor_results[i]),
            ad,strlen(ad),nsec,npub,k
        );
    }

    printf("Text Encrypted CBC Mode : ");
	for(int i =0; i<block_n; ++i ){
		for(int j=0;j<block_size;j++) {
			printf("%c", cipher_text[i][j]);
		}
	}
	printf("\n");    

	byte decryp_result[block_n+1][block_size*10];
    unsigned long long decryp_result_lens[block_n+1];


    for(int i=0;i<block_n;i++) {
        for(int j=0;j<block_size*100;j++) {
            decryp_result[i][j]='\0';
        }
    }

    //first block decrpytion

    keep_array_dec[0]=romulusDecryption(decryp_result[0],&decryp_result_lens[0],
                                nsec,cipher_text[0],strlen(cipher_text[0]),
                               ad,strlen(ad),npub,k
    );


    //first block xor
    for(int j=0;j<block_size;j++) {
        second_plain_text[0][j]=decryp_result[0][j] ^ npub[j];
    }    


    for(int i=1;i<block_n;i++) {
            keep_array_dec[i]=romulusDecryption(decryp_result[i],&decryp_result_lens[i],
                                nsec,cipher_text[i],strlen(cipher_text[i]),
                               ad,strlen(ad),npub,k);  
   

        for(int j=0;j<block_size;j++) {
            second_plain_text[i][j]=decryp_result[i][j] ^ cipher_text[i-1][j];
        }   
    }
 
    printf("Text Decrypted CBC Mode : ");
    for(int i =0; i<block_n; ++i ){
      for(int j=0;j<block_size;j++) {
        printf("%c", second_plain_text[i][j]);
      }
    }
    printf("\n");     

    int flag=0;
    for(int i=0;i<block_n;i++) {
      for(int j=0;j<block_size;j++) {
        if(second_plain_text[i][j]!=text_blocks[i][j]) {
          flag=1;
          break;
        }
      }      
      if(flag) {
        break;
      }
    }
    if(!flag) {
      printf("Success, test passed\n");
    }

    free(keep_array_enc);
    free(keep_array_dec);
    free(new_plain_text);

}


void OFBMode(unsigned char*c,unsigned long long* clen,
			 const unsigned char* m,const unsigned char* ad,
             unsigned char* nsec,
			 const unsigned char* npub,
			 const unsigned char* k) {

	printf("\nOFB MODE : \n");
	printf("Text plaintext : %s\n",m);

  int block_n=5;

	int new_plain_text_len=strlen(m)+strlen(m)%block_n;
	char* new_plain_text=(char*)malloc(sizeof(char)*new_plain_text_len);


	for(int i=0;i<new_plain_text_len;i++) {
		new_plain_text[i]='\0';
	}
	for(int i=0;i<strlen(m);i++) {
		new_plain_text[i]=m[i];
	}


	int block_size = ((new_plain_text_len)/block_n);
	byte text_blocks[block_n][block_size];
	for( int i =0; i<block_n; ++i ){
		for(int j = 0; j<block_size; ++j )
			text_blocks[i][j] = (byte)'\0';
	}
	for( int i =0; i<block_n; ++i ){
		for(int j = 0; j<block_size; ++j )
			text_blocks[i][j] = (byte)new_plain_text[i*block_size + j];
	}


	unsigned long long encryp_result_lengths[block_n];
	byte encryp_results[block_n][block_size*10];
	byte cipher_text[block_n][block_size*10];

	for( int i =0; i<block_n; ++i ){
		for(int j = 0; j<block_size*10; ++j ){
			encryp_results[i][j] = (byte)'\0';
			cipher_text[i][j] = (byte)'\0';
		}
	}
	
    int* keep_array_enc=(int*)(malloc(sizeof(int)*block_n));
    int* keep_array_dec=(int*)(malloc(sizeof(int)*block_n));  


	//first block

    keep_array_enc[0]=romulusEncryption(encryp_results[0],&encryp_result_lengths[0],
      npub,strlen(npub),ad,strlen(ad),nsec,npub,k
    );

  //first xor
	for(int j=0;j<block_size;j++) {
		cipher_text[0][j]=text_blocks[0][j] ^ encryp_results[0][j];
	}

	for(int i=1;i<block_n;i++) {
    keep_array_enc[i]=romulusEncryption(encryp_results[i],&encryp_result_lengths[i],
      encryp_results[i-1],strlen(encryp_results[i-1]),ad,strlen(ad),nsec,npub,k
    );


		for(int j=0;j<block_size;j++) {
			cipher_text[i][j]=text_blocks[i][j] ^ encryp_results[i][j];
		}
	}

	printf("Text Encrypted OFB mode : ");
	for(int i =0; i<block_n; ++i ){
		for(int j=0;j<block_size;j++) {
			printf("%c", cipher_text[i][j]);
		}
	}
	printf("\n");


	byte plain_text_deciphered[block_n][block_size];

	for(int i=0;i<block_n;i++) {
		for(int j=0;j<block_size;j++) {
			plain_text_deciphered[i][j]=(byte)'\0';
		}
	}


	unsigned long long decryp_result_lengths[block_n];
	byte decryp_results[block_n][block_size*10];
	byte decipher_text[block_n][block_size*10];

	for( int i =0; i<block_n; ++i ){
		for(int j = 0; j<block_size*10; ++j ){
			decryp_results[i][j] = (byte)'\0';
			decipher_text[i][j] = (byte)'\0';
		}
	}
	

	//first block

  keep_array_dec[0]=romulusEncryption(decryp_results[0],&decryp_result_lengths[0],
    npub,strlen(npub),ad,strlen(ad),nsec,npub,k
  );

	for(int j=0;j<block_size;j++) {
		decipher_text[0][j]=cipher_text[0][j] ^ decryp_results[0][j];
	}	

	for(int i=1;i<block_n;i++) {
    keep_array_dec[i]=romulusEncryption(decryp_results[i],&decryp_result_lengths[i],
      decryp_results[i-1],strlen(decryp_results[i-1]),ad,strlen(ad),nsec,npub,k
    );

		for(int j=0;j<block_size;j++) {
			decipher_text[i][j]=cipher_text[i][j] ^ decryp_results[i][j];
		}
	}

	printf("Text Decrypted OFB mode : ");
	for(int i =0; i<block_n; ++i ){
		for(int j=0;j<block_size;j++) {
			printf("%c", decipher_text[i][j]);
		}
	}

  int flag=0;
  for(int i =0; i<block_n; ++i ){
		for(int j=0;j<block_size;j++) {
			if(decipher_text[i][j]!=text_blocks[i][j]) {
        flag=1;
        break;
      }
		}
    if(flag) {
      break;
    }
	}
  printf("\n");
  if(!flag) {
    printf("Test passed\n");
  }

	printf("\n");

	free(new_plain_text);        
  
  free(keep_array_dec);
  free(keep_array_enc);


}




