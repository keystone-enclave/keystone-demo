#ifndef _CHANNEL_H_
#define _CHANNEL_H_

void channel_init();


unsigned char server_pk[crypto_kx_PUBLICKEYBYTES], server_sk[crypto_kx_SECRETKEYBYTES];
unsigned char client_pk[crypto_kx_PUBLICKEYBYTES];
unsigned char rx[crypto_kx_SESSIONKEYBYTES];
unsigned char tx[crypto_kx_SESSIONKEYBYTES];


#endif /* _CHANNEL_H_ */
