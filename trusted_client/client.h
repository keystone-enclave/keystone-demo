#ifndef _CLIENT_H_
#define _CLIENT_H_

void send_buffer(byte* buffer, size_t len);
byte* recv_buffer(size_t* len);

#endif /* _CLIENT_H_ */
