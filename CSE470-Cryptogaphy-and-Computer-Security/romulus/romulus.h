#define LENGTH_MSG 16
#define DATA_LEN_ODD 16
#define DATA_LEN_EVEN 16
#define ROMULUS_KEYLEN 16
#define ROMULUS_NPUBBYTES 16
#define ROMULUS_BYTES 16
#define BYTESOFCRYPTO 64
#define byte char

void *hextobyte(char *hex, unsigned char* bytes);
int romulusEncryption (
			 unsigned char* c, unsigned long long* clen,
			 const unsigned char* m, unsigned long long mlen,
			 const unsigned char* ad, unsigned long long adlen,
			 const unsigned char* nsec,
			 const unsigned char* npub,
			 const unsigned char* k
			 );
void s2h(unsigned char* in, int len, char* out);
int romulusDecryption(
unsigned char *m,unsigned long long *mlen,
unsigned char *nsec,
const unsigned char *c,unsigned long long clen,
const unsigned char *ad,unsigned long long adlen,
const unsigned char *npub,
const unsigned char *k
);
void CBCMode(unsigned char*c,unsigned long long* clen,
			 const unsigned char* m,const unsigned char* ad,
              unsigned char* nsec,
			 const unsigned char* npub,
			 const unsigned char* k);             

void OFBMode(unsigned char*c,unsigned long long* clen,
			 const unsigned char* m,const unsigned char* ad,
             unsigned char* nsec,
			 const unsigned char* npub,
			 const unsigned char* k);			 