#include "stdio.h"
#include "shellcommands.h"
#include "shell.h"

#define BUFF_SIZE 256
#define OK 0
#define NOT_EXIST 1
#define ERROR_ARGS 2

typedef struct {
	char * command;  /* Nombre del comando */
	char ** args;
	int args_num;
} command_t;

int shell(){
	int loop=1;
	char buff[BUFF_SIZE];
	int commandlen;
	char command[BUFF_SIZE];
	int hasarguments=0;
	int error;

	int i=0;
	char c;
	command_t cmd;
	

	//
	//load en pantalla ?
	//


	while(loop ){
		prints(STDOUT, "[User@gatOS]$ ");
		while ( c=getchar() != '\n'){
			if(i == BUFF_SIZE){
				i = 0;
			}
			buff[i++]=c;
			putchar(c);
		}
		putchar('\n');
		cleanBuffer(buff);
		cmd = parseCmd(buff);
		error = execute_cmd(cmd);
		printErrorMsg(error);
	}
	// while(loop){
	// 	printString("[User@gatOS]$ ");
	// 	readRowAndClear(buff, len);
	// 	if(buff[0] != '\0'){
	// 		commandlen = interpret(buff, command);
	// 		if(buff[commandlen] != '\0'){
	// 			hasarguments = 1 ;
	// 		}	
	// 		error = executeCommand(command, buff+commandlen+hasarguments);
	// 		printErrorMsg(error);
	// 	}
	// }

	return 0;
}

static int interpret(const char * buffer, char * command){
	int i;
	for (i=0; buffer[i]!='\0' && buffer[i]!=' '; i++){
		command[i]=buffer[i];
	}
	command[i]= '\0';
	return i;
}

static void printErrorMsg(int error){
	switch(error){
		case ERROR_ARGS:
			printf("%s", "Invalid arguments \n");
			break;
		case NOT_EXIST:
			printf("%s", "Command does not exist" );
			break;
	}

}

/* come espacios y aplica los backspace */
static void cleanBuffer(char* buffer){
	int i;
	int j;
	for (i=0; buffer[i] != '\0' ; i++){
		if( buffer[i] == '\b' ){
			if(i != 0){
				for(j=i; buffer[j+1] != '\0' ; j++ ){ // revisar para eficiencia
					buffer[j]=buffer[j+2];
				}
				buffer[j]='\0';
			}
			else{
				buffer[i]='\0';
				return;
			}
		}
		while( buffer[i] == ' ' ){ // come espacios
			buffer[i]=buffer[i+1];
		}
	}
}

/* Toma el input y separa el comando y los argumentos .*/
static command_t parseCmd( const char * buffer ){
	int i;
	int j=0;
	int n=0;
	command_t cmd;
	for ( i=0; buffer[i] != '\0'; i++ ){ //copia el command
		if(buffer[i] == ' '){ //separa cmd de args
			i++;
			while(buffer[i] != '\0'){ //copia los args
				if(buffer [i] == ' '){ //separa los args
					args[n][j]='\0';
					n++;
					j=0;
				}
				cmd.args[n][j++]=buffer[i++];
			}
		}
		cmd.command[i]=buffer[i];
		if(cmd.command[i] == '\0'){ //puede que salga del while anidado con un '\0'
			i--;
		}
	}
	cmd.args_num=n;
	return cmd;
}
