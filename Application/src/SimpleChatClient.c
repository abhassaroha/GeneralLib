#include "SimpleChatClient.h"

#include <stdio.h>
#include <stdlib.h>

#include "Client.h"
#include "Server.h" 

// TODO: support some basic commands
int parse_command(char* line)
{
	int command_code = -1, count = 0;
	char buf[64];
	// all commands begin with /
	if (line[0] == '/') {
		while(*line != '\0' && *line != '\t' && *line != ' ')
			buf[count++] = *line++;	
		buf[count] = '\0';
		printf("Command: %s\n", buf);
	}
	return command_code;
}

void execute_command(int command_code)
{
}
// todo_end

int main(int argc, char** argv)
{
	if(argc == 1) {
		printf("No arguments\n");
		return 1; 
	}

	if (argv[1][0] == 's') {
		server_start();
	}
	else {
		client_connect("localhost", SERVER);
	}
	return 0;
	/** TODO: add command running capability
		size_t buf_size = 1024;
		int code;
		char* buffer = (char*) malloc(sizeof(char) * buf_size);
		while(getline(&buffer, &buf_size, stdin) != -1) {
			if ((code = parse_command(buffer)) != -1)
				execute_command(code);
		}
		free(buffer);
		return 0;
	**/
}
