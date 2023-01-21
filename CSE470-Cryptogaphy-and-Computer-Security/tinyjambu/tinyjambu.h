#define byte char

#define FrameBitsIV  0x10  
#define FrameBitsAD  0x30  
#define FrameBitsPC  0x50       
#define FrameBitsFinalization 0x70       

void stateUpdate(int *state, const char *key, int n);
void initialization(const char *key, const char *iv, int *state);
void processAssociatedData(const char *k, const char *ad, long long adlen, int *state);
int encryption(char *c,long int *clen, const char *m, long long mlen, const char *ad, long long adlen, const char *npub, const char *k);
int decryption(char *m, long long *mlen, const char *c, long long clen, const char *ad, long long adlen, const char *npub, const char *k);

void get_byte_array(const char *sourceText, byte *byteArray);
void xor_byte_arrays(const byte *in1, const byte *in2, byte *out,long BLOCK_SIZE);
void bytecpy(byte *dest, const byte *src,long BLOCK_SIZE); 
void CBCmode(const char* plain_text, const char* key, const char* IV, long block_n);
void OFBmode(const char* plain_text, const char* key, const char* IV, long block_n);
void myOFBmode(const char* plain_text, const char* key, const char* IV, long block_n);