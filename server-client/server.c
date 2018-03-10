#include <netdb.h>
#include <netinet/in.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "colors.h"

static void doProcessing(int sock);
static void doLogging();
static void led();

int 
main(int argc, char *argv[]) 
{
   	int sockfd; 
	int newsockfd;
	int portno = 5001;
	int clilen;
	struct sockaddr_in serv_addr, cli_addr;
	pid_t pid;
   
   	/* First call to socket() function */
   	sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   	if (sockfd < 0) {
      		perror("["RED"ERROR"RESET"] opening socket");
      		exit(1);
   	}
   
   	/* Initialize socket structure */
   	memset((char *) &serv_addr, 0, sizeof(serv_addr));
   
   	serv_addr.sin_family = AF_INET;
   	serv_addr.sin_addr.s_addr = INADDR_ANY;
   	serv_addr.sin_port = htons(portno);
  	
   	/* Now bind the host address using bind() call.*/
   	if (bind(sockfd, (struct sockaddr *)&serv_addr, 
            sizeof(serv_addr)) < 0) {
      		perror("ERROR on binding");
      		exit(1);
   	}
   	
   	/* Now start listening for the clients, here
      	*  process will go in sleep mode and will wait
      	*  for the incoming connection
   	*/
   
   	listen(sockfd, 5);
   	clilen = sizeof(cli_addr);
  	
   	while (1) {
      		newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, 
				   (unsigned int *)&clilen);
		
      		if (newsockfd < 0) {
         		perror("ERROR on accept");
         		exit(1);
      		}
      
      		/* Create child process */
      		pid = fork();
		
      		if (pid < 0) {
         		perror("ERROR on fork");
         		exit(1);
      		}
      
      		if (pid == 0) {
         		/* This is the client process */
         		close(sockfd);
			while (1) doProcessing(newsockfd);
         		exit(0);
      		} else {
         		close(newsockfd);
      		}
		
	} /* end of while */

	return 0;	
}


static void 
doProcessing(int sock) 
{
   	int errno;
   	char buffer[256] = {0};
	char hostname[128] = {0};
		
 	memset(&buffer, 0, sizeof(char));
   	errno = read(sock, buffer, 255);
   
   	if (errno < 0) {
      		perror("ERROR reading from socket");
      		exit(1);
   	}
   	
	gethostname(hostname, sizeof(hostname));
   	printf("%s: %s\n", hostname, buffer);
	doLogging(&hostname, &buffer);
	led();
   	errno = write(sock,"I got your message",18);
   
   	if (errno < 0) {
      		perror("ERROR writing to socket");
      		exit(1);
   	}
		
	return;	
}

static void
doLogging(char *hostname, char *message)
{
	FILE *fp;
	time_t current_time;
	char *c_time_string;

	fp = fopen("./logs/mails.xml", "a+");

	current_time = time(NULL);
	c_time_string = ctime(&current_time);

	if (current_time == ((time_t) - 1)) { 
		fprintf(stderr, "Failure to obtain the current time.\n");
	} else if (c_time_string == NULL)
		fprintf(stderr, "Failure to convert the current time.\n");
	
	c_time_string[strcspn(c_time_string, "\n")] = 0;
	message[strcspn(message, "\n")] = 0;

	fprintf(fp, "<mail>\n");
	fprintf(fp, "\t<from>%s</from>\n", hostname);
	fprintf(fp, "\t<time>%s</time>\n", c_time_string);
	fprintf(fp, "\t<message>%s</message>\n", message);
	fprintf(fp, "</mail>\n");	

	fclose(fp);

	return;
}

static void
led()
{
	FILE *fp;
	
	fp = fopen("../ledStat", "w+");
	fprintf(fp, "1");
	fclose(fp);

	return;
}
