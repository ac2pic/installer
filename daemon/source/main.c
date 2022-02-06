#include "main.h"
#include <errno.h>
#include <sys/types.h>  
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
	loadInternalModules();
	sceLncUtilRegisterDaemon();
	sceKernelDebugOutText(22, "[DAMN] Registered daemon.\n");
	int sockfd = socket(AF_INET,SOCK_STREAM, 0);
	do {
		char err[500];
		struct sockaddr_in serverAddr;
		memset(&serverAddr, 0, sizeof(struct sockaddr_in));
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
		serverAddr.sin_port = htons(9000);
		int bindResult = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr_in));
		if (bindResult < 0) {
		
			memset(err, 0, sizeof(err));
			sprintf(err, "[DAMN] Failed to bind address. - %d \n", errno);
			sceKernelDebugOutText(22, err);
			break;
		}
		int listenResult = listen(sockfd, 100);
		if (listenResult < 0) {
			memset(err, 0, sizeof(err));
			sprintf(err, "[DAMN] Failed to listen. - %d \n", errno);
			break;
		}
		struct sockaddr_in clientAddr;
		socklen_t addrLen;
		int connfd = accept(sockfd, (struct sockaddr*)&clientAddr, &addrLen); 
		if (connfd < 0) {
			sceKernelDebugOutText(22, "[DAMN] client failed to connect!\n");
			break;
		}
		sceKernelDebugOutText(22, "[DAMN] client connected!\n");
		shutdown(connfd, SHUT_RDWR);
		close(connfd);
	} while(0);
	shutdown(sockfd, SHUT_RDWR);
	close(sockfd);
	sceLncUtilUnregisterDaemon();
	sceKernelDebugOutText(22, "[DAMN] Unregistered daemon.\n");
	abort();
}
