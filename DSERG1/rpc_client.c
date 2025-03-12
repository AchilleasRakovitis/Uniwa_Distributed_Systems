#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include "askisi1.h"

static void serve(int);

#define PORT 6060
int newchild;

main( int argc, char **argv )
{int lsd; /* Listening socket */
struct sockaddr_in sin; /* Binding struct */
int sin_size=sizeof(sin);
int sd; /* Socket to accept new connexion */
/* Create listening socket */
if ( (lsd=socket(AF_INET, SOCK_STREAM, 0)) < 0 )
{
 fprintf(stderr, "%s: cannot create listening socket: ", argv[0]);
 perror(0);
 exit(1);
}

/* Prepare binding structure sin */
sin.sin_family = AF_INET;
sin.sin_port = htons(PORT);
sin.sin_addr.s_addr = htonl(INADDR_ANY);

if ( bind(lsd, &sin, sin_size) < 0 )
{
 fprintf(stderr, "%s: cannot bind listening socket: ", argv[0]);
 perror(0);
 exit(1);
}

/* Initiate a listen queue */
if ( listen(lsd, 5) < 0 )
{
 fprintf(stderr, "%s: cannot listen on socket: ", argv[0]);
 perror(0);
 exit(1);
}

/* Take care of the SIGPIPE signal - ignore it signal(SIGPIPE, SIG_IGN); */

while ( 1 )
{
 if ( (sd=accept(lsd, &sin, &sin_size)) < 0 )
   {
    fprintf(stderr, "%s: cannot accept a new connect request from socket: ", argv[0]);
    exit(errno);
   }
if ( (newchild=fork()) <0 )
{
 fprintf(stderr, "%s: cannot create a new child to serve request: ", argv[0]);
 perror(0);
 exit(1);
}
if (newchild == 0) /* child */
{
 fprintf(stdout, "New child %d was created from parent server %d %s to serve request\n", getpid(), getppid(), argv[0]);
 serve(sd);
 shutdown(sd, 2);
 close(sd);
 exit(0);
}
}
}
void serve(int sd)
{
 int plithos, operator;
 CLIENT *clnt;
 float  *result_from_server;
 data  dedomena;
 apotelesma *apotelesmata;
 char *host;
 int i;
 int megel[2];

 host = "localhost";
 // Pernoyme to plithos meso socket
 read(sd,&plithos, sizeof(plithos));
 
 //Kanoyme allocate mnimi gia ta stoixeia toy vector y
 dedomena.y.y_val = malloc(plithos * sizeof(int));
  
 // Pairnoyme tis times toy vector 
 read(sd,dedomena.y.y_val, plithos * sizeof(int));
 
 // Pairnoyme operator meso socket
 read(sd,&operator, sizeof(operator));

 // Thetoyme to plithos sto y_len
 dedomena.y.y_len = plithos;
 

   #ifndef      DEBUG
   clnt = clnt_create ("localhost", ASKISI1, ASKISI1_VERS, "udp");
   if (clnt == NULL) {
      clnt_pcreateerror (host);
      exit (1);
   }
   #endif       /* DEBUG */

 if (operator == 1)
 {

   result_from_server = mo_1(&dedomena, clnt);
   
   if (result_from_server == (float *) NULL) {
     clnt_perror (clnt, "call failed"); } 
   else {
     printf("MO = %.2f\n", *result_from_server);

     //Stelnoyme apotelesma meso socket
     write(sd,result_from_server,sizeof(*result_from_server));  
   }
   
   #ifndef	DEBUG
      clnt_destroy (clnt);
   #endif	 /* DEBUG */
  }

 if (operator == 2)
  {
   apotelesmata = megel_1(&dedomena, clnt);

   if (apotelesmata == NULL) {
     clnt_perror (clnt, "call failed"); 
   } else {    

     megel[0] = apotelesmata->minmax.minmax_val[0];

     megel[1] = apotelesmata->minmax.minmax_val[1];

      printf("Megisto: %d\n", megel[0]);

      printf("Elaxisto: %d\n", megel[1]);


      // Stelnoyme me socket to Megisto-Elaxisto
      write(sd,megel, sizeof(int)*2); 
    }

   #ifndef      DEBUG
      clnt_destroy (clnt);
   #endif        /* DEBUG */
  }

  if (operator == 3)
  { 
    //Pairnoyme to "a" apo to socket
    read(sd,&dedomena.a, sizeof(float));

    float ginomeno[plithos];

    apotelesmata = ginom_1(&dedomena, clnt);
    
    

    if (apotelesmata->vec.vec_val == NULL){
     
      clnt_perror (clnt, "call failed");
    } else {

      printf("Dianysma a*y: \n");

      for(i=0; i<plithos; i++){

        ginomeno[i] = apotelesmata->vec.vec_val[i];
        
        printf("%.2f\n",apotelesmata->vec.vec_val[i]);
      
      }

      //Stelnoyme apotelesma meso socket
      write(sd, ginomeno, sizeof(float)*plithos);
    }


   #ifndef      DEBUG
      clnt_destroy (clnt);
   #endif        /* DEBUG */
  }

 printf("writing result to socket_client through the socket\n");
 
 free(dedomena.y.y_val);
 return;
}






