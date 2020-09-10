#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "Logger.h"
#include "SystemVariables.h"
#include "SystemStructures.h"

extern struct controllerData * data; 

void *LoggerThread(void * d)
{
	while(1)
	{
		for(int i = 0; i < BUFFER_SIZE; i++)
		{
			data = &((struct controllerData*)d)[i];
		}
		break;
	}

	return;
}

void openLogFile(FILE * fp)
{

	printf("opening file\n");

    time_t rawtime;
    char * data_file_name;

	time ( &rawtime );
	data_file_name = asctime(localtime ( &rawtime ));
	data_file_name[strlen(data_file_name)-1] = '_';
	const char file_name[] = "/data.txt";
	char folder[1000] = "data/";
	strcat(folder, data_file_name);

	for(int i; i < strlen(folder) - 1; i++)
	{
		if (folder[i] == ' ') 
		    folder[i]='_';
		if (folder[i] == ':')
			folder[i]='-';
	}

	printf("%s\n", folder);
	mkdir(folder,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	strcat(folder, file_name);

    fp = fopen (folder,"w");

	return;

}