#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define BUFSIZE 1024
#define SERVER_PORT 6060


main( int argc, char **argv )
{int sd; /* Socket descriptor */
struct sockaddr_in server; /* Server to connect */
struct hostent *server_host; /* Host info */
char buf[BUFSIZE];
int nbytes;
int operator;
char *host;
float a;
int y[argc-2];
int i;
float mo;
int megel[2];
float ginom[argc-2];

host="localhost";

/* Create socket */
if ( (sd=socket(AF_INET, SOCK_STREAM, 0)) < 0 )
{ fprintf(stderr, "%s: cannot create socket: ", argv[0]);
  perror(0);
  exit(1);
}
/* Get info on host */
if ( (server_host=gethostbyname(host)) == NULL )
{ fprintf(stderr, "%s: unknown host %s\n", argv[0], argv[1]);
  exit(1);
}
/* Set up struct sockaddr_in */
server.sin_family = AF_INET;
server.sin_port = htons(SERVER_PORT);
bcopy((char*)server_host->h_addr, (char*)&server.sin_addr, server_host->h_length);

/* Connect */
if ( connect(sd, &server, sizeof(server)) < 0 )
{
 fprintf(stderr, "%s: cannot connect to server: ", argv[0]);
 perror(0);
 exit(1);
}

// Orismos arithmon dianismatos
for(i=1; i<= argc-2; i++){
  y[i-1] = atoi(argv[i]);
}

// Orismos operator 
operator = atoi(argv[argc-1]);
printf("Operator used: %d\n", operator);

// Orismos plithous stoixeion vector
int plithos = argc - 2;

for(i=0; i < plithos; i++){
  printf("%d ", y[i]);
}
printf("\n");


// Stelnoyme plithos meso socket
write(sd,&plithos,sizeof(int));

// Stelnoyme vector meso socket
write(sd,y, sizeof(y));

// Stelnoyme ton operator meso socket
write(sd,&operator, sizeof(operator));
 
 
/* Get result */ 
if (operator == 1){
  if ( (nbytes=read(sd, &mo, sizeof(float))) <= 0 )
  { fprintf(stderr, "%s: read failed: ", argv[0]);
    perror(0); exit(1);
  }

  printf("O mesos oros toy vector einai: %.2f\n", mo);
}
else if(operator == 2){
  if ( (nbytes=read(sd, megel, sizeof(int)*2)) <= 0 )
  { fprintf(stderr, "%s: read failed: ", argv[0]);
    perror(0); exit(1);
  }

  printf("To megisto stoixeio einai: %d\n", megel[0]);

  printf("To elaxisto stoixeio einai: %d\n", megel[1]);
}
else if (operator == 3){
  
  printf("Dose float gia polaplasiasmo: ");
  
  scanf("%f",&a);
  
  // Stelnoyme ton float a meso socket
  write(sd,&a, sizeof(a));

  if ( (nbytes=read(sd, ginom, sizeof(float) * plithos)) <= 0 )
  { fprintf(stderr, "%s: read failed: ", argv[0]);
    perror(0); exit(1);
  }

  printf("To vector-apotelesma einai to parakato: \n");

  for(i=0; i<plithos; i++){
    printf("%.2f\n", ginom[i]);
  }
}


close(sd);
exit(0);
}