#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <cstdio>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include "keystone.h"
#include <edge_call.h>
#include "ocalls.h"
#include "encl_message.h"

#define PRINT_MESSAGE_BUFFERS 1

/* We hardcode these for demo purposes. */
const char* enc_path = "server_eapp.eapp_riscv";
const char* runtime_path = "eyrie-rt";

#define PORTNUM 8067
int fd_clientsock;
#define BUFFERLEN 4096
byte local_buffer[BUFFERLEN];

void send_buffer(byte* buffer, size_t len){
  write(fd_clientsock, &len, sizeof(size_t));
  write(fd_clientsock, buffer, len);
}

byte* recv_buffer(size_t* len){
  read(fd_clientsock, local_buffer, sizeof(size_t));
  size_t reply_size = *(size_t*)local_buffer;
  byte* reply = (byte*)malloc(reply_size);
  read(fd_clientsock, reply, reply_size);
  *len = reply_size;
  return reply;
}

void print_hex_data(unsigned char* data, size_t len){
  unsigned int i;
  std::string str;
  for(i=0; i<len; i+=1){
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << std::hex << (uintptr_t)data[i];
    str += ss.str();
    if(i>0 && (i+1)%8 == 0){
      if((i+1)%32 == 0){
	str += "\n";
      }
      else{
	str += " ";
      }
    }
  }
  printf("%s\n\n",str.c_str());
}

unsigned long print_buffer(char* str){
  printf("[SE] %s",str);
  return strlen(str);
}

void print_value(unsigned long val){
  printf("[SE] value: %u\n",val);
  return;
}

void end_enclave(){
  exit(0);
}

void init_network_wait(){

  int fd_sock;
  struct sockaddr_in server_addr;

  fd_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (fd_sock < 0){
    printf("Failed to open socket\n");
    exit(-1);
  }
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORTNUM);
  if( bind(fd_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
    printf("Failed to bind socket\n");
    exit(-1);
  }
  listen(fd_sock,2);

  struct sockaddr_in client_addr;
  socklen_t client_len = sizeof(client_addr);
  fd_clientsock = accept(fd_sock, (struct sockaddr*)&client_addr, &client_len);
  if (fd_clientsock < 0){
    printf("No valid client socket\n");
    exit(-1);
  }
}

void register_functions();
Keystone enclave;

int main(int argc, char** argv){

  /* Wait for network connection */
  init_network_wait();

  printf("[EH] Got connection from remote client\n");

  Params params;

  if(enclave.init(enc_path, runtime_path, params) != KEYSTONE_SUCCESS){
    printf("HOST: Unable to start enclave\n");
    exit(-1);
  }

  enclave.registerOcallDispatch(incoming_call_dispatch);
  register_functions();
  edge_call_init_internals((uintptr_t)enclave.getSharedBuffer(),
    enclave.getSharedBufferSize());
    
  enclave.run();

  report attestation_report = get_attestation_report();
  send_buffer((byte*)attestation_report.data, 2048);
  
  size_t len;
  if (set_client_pk((pubkey*) recv_buffer(&len))) return 0;
  
  while(1){
    size_t len;
    void* buffer = recv_buffer(&len);

    printf("[EH] Got an encrypted message:\n");
    if( PRINT_MESSAGE_BUFFERS ) print_hex_data((unsigned char*)buffer, len);
   
    encl_message_t message, reply;
    message.host_ptr = buffer;
    message.len = len;
    
    reply = calc_message(message);
    if (!reply.len) return 0;
    printf("[EH] Sending encrypted reply:\n");
    if( PRINT_MESSAGE_BUFFERS ) print_hex_data((unsigned char*)reply.host_ptr, reply.len);
    
    send_buffer((byte*)reply.host_ptr, reply.len);    
  }
  return 0;
}

