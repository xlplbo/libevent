#include <stdio.h>
#include <assert.h>
#include <WinSock2.h>

int main(int argc, char **argv)
{

#ifdef WIN32
	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);
#endif

	struct sockaddr_in server_address;
	memset( &server_address, 0, sizeof( server_address ) );
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_address.sin_port = htons( 9995 );

	int sockfd = socket( PF_INET, SOCK_STREAM, 0 );
	assert( sockfd >= 0 );
	if ( connect( sockfd, ( struct sockaddr* )&server_address, sizeof( server_address ) ) < 0 )
	{
		printf( "connection failed\n" );
	}
	else
	{
		printf( "send oob data out\n" );
		const char* oob_data = "abc";
		const char* normal_data = "123";
		send( sockfd, normal_data, strlen( normal_data ), 0 );
		send( sockfd, oob_data, strlen( oob_data ), MSG_OOB );
		send( sockfd, normal_data, strlen( normal_data ), 0 );
	}
	return 0;
}
