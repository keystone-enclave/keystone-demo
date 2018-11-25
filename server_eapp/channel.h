#ifndef _CHANNEL_H_
#define _CHANNEL_H_

void channel_init();
void channel_establish();
int channel_recv(unsigned char* msg_buffer, size_t len, size_t* datalen);
size_t channel_get_send_size(size_t len);
void channel_send(unsigned char* msg, size_t len, unsigned char* ctx);
unsigned char server_pk[crypto_kx_PUBLICKEYBYTES], server_sk[crypto_kx_SECRETKEYBYTES];
unsigned char client_pk[crypto_kx_PUBLICKEYBYTES];
unsigned char rx[crypto_kx_SESSIONKEYBYTES];
unsigned char tx[crypto_kx_SESSIONKEYBYTES];


#endif /* _CHANNEL_H_ */
