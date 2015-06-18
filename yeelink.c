/*
* yeelink.c
*
*  Created on: 2013年11月13日
*      Author: xukai
*/

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <windows.h>

/*
typedef struct hostent {
char *h_name;
char **h_aliases;
short h_addrtype;
short h_length;
char **h_addr_list;
}
h_name 主机官方名称
h_aliases 主机别名，主机可能存在多个别名，主机别名以NULL结尾
h_addrtype  主机地址类型
h_length    主机长度
h_addr_list 主机地址，主机可能存在多个地址，主机地址以NULL结尾。
*/

int main(int argc, char **argv)
{
    WSADATA wsaData;
    int result_id;
    int socket_id;
    
    // HTTP请求
    char send_buf[] =
    "GET /v1.0/device/1949/sensor/2511/datapoints HTTP/1.1\r\n"
    "U-ApiKey: ffa3826972d6cc7ba5b17e104ec59fa3\r\n"
    "Host: api.yeelink.net\r\n\r\n";
    // HTTP响应
    char receive_buf[1024];

    struct hostent *yeelink_host;               // yeelink主机DNS解析结构体
    char *host_name = "api.yeelink.net";        // yeelink域名
    struct in_addr yeelink_ipaddr;              // yeelink IP地址
    struct sockaddr_in yeelink_sockaddr;        // yeelink 连接套接字
    
    // Winsows下启用socket
    result_id = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result_id != 0) {
        printf("WSAStartup failed: %d\n", result_id);
        return 1;
    }

    // 第一步 DNS地址解析
    printf("calling gethostbyname with: %s\r\n", host_name);
    yeelink_host = gethostbyname(host_name);

    if (yeelink_host == NULL)
    {
        // DNS解析失败
        printf("error\r\n");        
    }
    else
    {
        // DNS解析正确
        yeelink_ipaddr.s_addr = *(u_long *) yeelink_host->h_addr_list[0];
        printf("Yeelink IP Address %s\r\n" , inet_ntoa(yeelink_ipaddr));
    }

    // 第二步 创建套接字
    socket_id = socket(AF_INET, SOCK_STREAM, 0);
    yeelink_sockaddr.sin_family = AF_INET;
    yeelink_sockaddr.sin_port = htons(80);          // 设置端口号
    yeelink_sockaddr.sin_addr = yeelink_ipaddr;      // 设置IP地址
    memset(&(yeelink_sockaddr.sin_zero), 0, sizeof(yeelink_sockaddr.sin_zero));

    // 第三步 连接yeelink
    result_id = connect( socket_id, (struct sockaddr *)&yeelink_sockaddr, sizeof(struct sockaddr));
    if( result_id == SOCKET_ERROR )
    {
        printf("connect ok\r\n");
    }
    printf("Http request:\r\n%s\r\n",send_buf);
    
    // 第四步 发送HTTP请求
    send(socket_id , send_buf,strlen(send_buf), 0);

    // 第五步 接收HTTP响应
    int bytes_received = 0;
    bytes_received = recv( socket_id , receive_buf , 1024 , 0);
    receive_buf[ bytes_received ] = '\0';
    printf("Receive Message:\r\n%s\r\n",receive_buf );

    closesocket(socket_id);         // 关闭套接字
    WSACleanup();                   // windows下释放套接字

    getchar();                      // 保持控制台窗口
    return 0;
}

