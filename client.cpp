#include<netinet/in.h>  // sockaddr_in 
#include<sys/types.h>  // socket 
#include<sys/socket.h>  // socket 
#include<stdio.h>    // printf 
#include<stdlib.h>    // exit 
#include<string.h>    // bzero 
#include <unistd.h>
#include<arpa/inet.h>
#include <unistd.h> 
#define SERVER_PORT 3389 
#define BUFFER_SIZE 1024 
#define FILE_NAME_MAX_SIZE 512 
  
int main(void) 
{ 

  // 声明并初始化一个客户端的socket地址结构 
  struct sockaddr_in client_addr; 
  bzero(&client_addr, sizeof(client_addr)); 
  client_addr.sin_family = AF_INET; 
  client_addr.sin_addr.s_addr = htons(INADDR_ANY); 
  client_addr.sin_port = htons(0); 
  
  // 创建socket，若成功，返回socket描述符 
  int client_socket_fd = socket(AF_INET, SOCK_STREAM, 0); 
  
  if(client_socket_fd < 0) 
  { 
    perror("Create Socket Failed:"); 
    exit(1); 
  }
  sleep(0.5);
   printf("Create Socket succeed!\n");
  
  // 绑定客户端的socket和客户端的socket地址结构 非必需 
  if(-1 == (bind(client_socket_fd, (struct sockaddr*)&client_addr, sizeof(client_addr)))) 
  { 
    perror("Client Bind Failed:"); 
    exit(1); 
  }
  printf("Bind Socket succeed!\n");
  
  // 声明一个服务器端的socket地址结构，并用服务器那边的IP地址及端口对其进行初始化，用于后面的连接 
  struct sockaddr_in server_addr; 
  bzero(&server_addr, sizeof(server_addr)); 
  server_addr.sin_family = AF_INET; 
  if(inet_pton(AF_INET, "39.108.98.29", &server_addr.sin_addr) == 0) 
  { 
    perror("Server IP Address Error:"); 
    exit(1); 
  }
  printf("Server IP Address succeed!\n");
  server_addr.sin_port = htons(SERVER_PORT); 
  socklen_t server_addr_length = sizeof(server_addr); 
  
  // 向服务器发起连接，连接成功后client_socket_fd代表了客户端和服务器的一个socket连接 
  if(connect(client_socket_fd, (struct sockaddr*)&server_addr, server_addr_length) < 0) 
  { 
    perror("Can Not Connect To Server IP:"); 
    exit(0); 
  } 
  printf("???\n");
  // 输入文件名 并放到缓冲区buffer中等待发送 
  char file_name[FILE_NAME_MAX_SIZE+1]; 
  bzero(file_name, FILE_NAME_MAX_SIZE+1); 
  printf("Please Input File Name On Server:\t"); 
  scanf("%s", file_name); 
  
  char buffer[BUFFER_SIZE]; 
  bzero(buffer, BUFFER_SIZE); 
  strncpy(buffer, file_name, strlen(file_name)>BUFFER_SIZE?BUFFER_SIZE:strlen(file_name)); 
    
  // 向服务器发送buffer中的数据 
  if(send(client_socket_fd, buffer, BUFFER_SIZE, 0) < 0) 
  { 
    perror("Send File Name Failed:"); 
    exit(1); 
  } 
  
  // 打开文件，准备写入 
  FILE *fp = fopen(file_name, "w"); 
  if(NULL == fp) 
  { 
    printf("File:\t%s Can Not Open To Write\n", file_name); 
    exit(1); 
  } 
  
  // 从服务器接收数据到buffer中 
  // 每接收一段数据，便将其写入文件中，循环直到文件接收完并写完为止 
  bzero(buffer, BUFFER_SIZE); 
  int length = 0; 
  while((length = recv(client_socket_fd, buffer, BUFFER_SIZE, 0)) > 0) 
  { 
    if(fwrite(buffer, sizeof(char), length, fp) < length) 
    { 
      printf("File:\t%s Write Failed\n", file_name); 
      break; 
    } 
    bzero(buffer, BUFFER_SIZE); 
  } 
  
  // 接收成功后，关闭文件，关闭socket 
  printf("Receive File:\t%s From Server IP Successful!\n", file_name); 
  fclose(fp); 
  close(client_socket_fd); 
  return 0; 
} 
