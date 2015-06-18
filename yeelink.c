/*
* yeelink.c
*
*  Created on: 2013��11��13��
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
h_name �����ٷ�����
h_aliases �����������������ܴ��ڶ������������������NULL��β
h_addrtype  ������ַ����
h_length    ��������
h_addr_list ������ַ���������ܴ��ڶ����ַ��������ַ��NULL��β��
*/

int main(int argc, char **argv)
{
    WSADATA wsaData;
    int result_id;
    int socket_id;
    
    // HTTP����
    char send_buf[] =
    "GET /v1.0/device/1949/sensor/2511/datapoints HTTP/1.1\r\n"
    "U-ApiKey: ffa3826972d6cc7ba5b17e104ec59fa3\r\n"
    "Host: api.yeelink.net\r\n\r\n";
    // HTTP��Ӧ
    char receive_buf[1024];

    struct hostent *yeelink_host;               // yeelink����DNS�����ṹ��
    char *host_name = "api.yeelink.net";        // yeelink����
    struct in_addr yeelink_ipaddr;              // yeelink IP��ַ
    struct sockaddr_in yeelink_sockaddr;        // yeelink �����׽���
    
    // Winsows������socket
    result_id = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result_id != 0) {
        printf("WSAStartup failed: %d\n", result_id);
        return 1;
    }

    // ��һ�� DNS��ַ����
    printf("calling gethostbyname with: %s\r\n", host_name);
    yeelink_host = gethostbyname(host_name);

    if (yeelink_host == NULL)
    {
        // DNS����ʧ��
        printf("error\r\n");        
    }
    else
    {
        // DNS������ȷ
        yeelink_ipaddr.s_addr = *(u_long *) yeelink_host->h_addr_list[0];
        printf("Yeelink IP Address %s\r\n" , inet_ntoa(yeelink_ipaddr));
    }

    // �ڶ��� �����׽���
    socket_id = socket(AF_INET, SOCK_STREAM, 0);
    yeelink_sockaddr.sin_family = AF_INET;
    yeelink_sockaddr.sin_port = htons(80);          // ���ö˿ں�
    yeelink_sockaddr.sin_addr = yeelink_ipaddr;      // ����IP��ַ
    memset(&(yeelink_sockaddr.sin_zero), 0, sizeof(yeelink_sockaddr.sin_zero));

    // ������ ����yeelink
    result_id = connect( socket_id, (struct sockaddr *)&yeelink_sockaddr, sizeof(struct sockaddr));
    if( result_id == SOCKET_ERROR )
    {
        printf("connect ok\r\n");
    }
    printf("Http request:\r\n%s\r\n",send_buf);
    
    // ���Ĳ� ����HTTP����
    send(socket_id , send_buf,strlen(send_buf), 0);

    // ���岽 ����HTTP��Ӧ
    int bytes_received = 0;
    bytes_received = recv( socket_id , receive_buf , 1024 , 0);
    receive_buf[ bytes_received ] = '\0';
    printf("Receive Message:\r\n%s\r\n",receive_buf );

    closesocket(socket_id);         // �ر��׽���
    WSACleanup();                   // windows���ͷ��׽���

    getchar();                      // ���ֿ���̨����
    return 0;
}

