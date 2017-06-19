#include "stringlib.h"
#include "shellcommands.h"

#define OK 0
#define NOT_EXIST 1
#define ERROR_ARGS 2
#define COMMAND_AMOUNT (sizeof(commands)/sizeof(commands[0]))

typedef struct {
	const char * command;  /* Nombre del comando */
	int (*function) (const char *str);  /* Funcion correspondiente al comando */
} commandstruct;

static commandstruct commands[]= {{"help", help},{"clear", clear},{"echo", echo},{"time", currentTime}//Agregar comandos aca
												};



int executecommand(const char *command, const char ** args){
	int i;
	for (i=0; i<COMMAND_AMOUNT; i++){
		if(strcmp(command, commands[i].command)==0){
			return (*commands[i].function)(args);
		}
	}
	return NOT_EXIST;
}

int execute_cmd(command_t cmd){
  int i;
  for (i=0; i<COMMAND_AMOUNT; i++){
    if(strcmp(cmd.command, commands[i].command)==0){
      return (*commands[i].function)(cmd.args, cmd.args_num);
    }
  }
  return NOT_EXIST;
}

static int help(const char ** args, int args_num){
  if (args[0][0] != '\0'){
  	return ERROR_ARGS;
  } else{
  	printf("help: Display information about every existent command\n");
 	printf("echo [args...]: Display the arguments spaced on the screen\n");
	printf("clear:  Clear the screen.\n");
	printf(" time: Display current time on the screen (24hr format [hh:mm:ss])\n");
  return OK;
	}
}

static int currentTime(const char *args, int args_num) {
  int h = hour(), m = minutes(), s = seconds();
  printf("Current time: ");
  printTime(h);
  printf(":");
  printTime(m);
  printf(":");
  printTime(s);
  printf("\n");
  return OK;
}

/* Imprime un numero en formato [xx]*/
static void printTime(unsigned int n) {
    if (n < 10){
        printf("0");
    }    
    printf("%d", n);
}

static int clear(const char *args, int args_num) {
  return usr_clear();
}


static int echo(const char ** args, int args_num) {
  int i;
  for(i=0; i< args_num ; i++){
    printf("%s\n", args[i]);  
  }
  
  return OK;
}




	 
  