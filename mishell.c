#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "leercadena.h"
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char* argv[]) {
    	char command[256];
    	char **comando;
	pid_t  ids[32];
	int  idN=0;
    	while (1) {
            	printf("> ");
            	leer_de_teclado(256, command);
            	if (strcmp(command,"salir") == 0)break;
		if (strcmp(command,"tareas") == 0){
		 int t=0;
		 while(ids[t]){
		    printf("proceso en background numero %i con id: %d\n",t,ids[t]);
		    t++;
		 }
		}
            	comando = de_cadena_a_vector(command);
              int i = 0;
              while(comando[i]){
                i++;
              }
              

	      if(strcmp(comando[0],"detener") == 0){
		  int pidc = atoi(comando[1]);
		  kill(pidc,SIGKILL);
		  int o=0;
		  while(ids[o]){
		   if(ids[o]==pidc) {
		     int a = o;
		     while(ids[a]){
		       ids[a]=ids[a+1];
		       a++;
		     }
		   }
		   o++;
     		  }
		}

              int bg=0;
		pid_t wpid;
              if(strcmp(comando[i-1],"&")==0){
                comando[i-1]=NULL; 
                bg=1;
              }
		int status;
            	int rc = fork();
            	assert(rc >= 0);
            	if (rc == 0){//proceso hijo
		  execvp(comando[0], comando); 
            	}
		else{
                  if(bg==0){
                    wpid=waitpid(rc, &status, 0);
		    printf("\n"); 
                    //wait(NULL);
		   }
		   else{
		     ids[idN]=getpid();
		     idN++;
		     continue;
		  } 
		}
    	}
    	return 0;
}
