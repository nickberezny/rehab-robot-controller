/****************************************************************************
 * Copyright (C) 2012 by Matteo Franchin                                    *
 *                                                                          *
 * This file is part of Box.                                                *
 *                                                                          *
 *   Box is free software: you can redistribute it and/or modify it         *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   Box is distributed in the hope that it will be useful,                 *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Box.  If not, see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/
/**
 * @file ReadProcessFile.c
 * @author Nick Berezny
 * @date 4 Dec 2023
 * @Exaaaaample
 *
 * Test test
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> 

#include "./include/Parameters.h"
#include "./include/Structures.h"
#include "./include/ReadProcessFile.h"

void ReadSessionFiles(char * sessionDir, struct ControlParams * p)
{

    //first, controllers
    char * temp[20];
    char * temp2[20];
    strcpy(temp, sessionDir);
    char * controllerPath = "/Controllers/";
    char * trajectoryPath = "/Trajectories/";
    strcat(temp,controllerPath);
    printf("%s\n", temp);

    int index = 0;

    DIR *d;
    struct dirent *dir;
    d = opendir(temp);
    if (d) 
    {

        while ((dir = readdir(d)) != NULL) 
        {
            strcpy(temp2, temp);
            strcat(temp2,dir->d_name);
            printf("%s\n", temp2);
            ReadControlFile(temp2, p, index);
            index = index + 1;
        }

        closedir(d);

    }

    strcpy(temp, sessionDir);
    strcat(temp,trajectoryPath);

    index = 0;
    d = opendir(temp);
    if (d) 
    {

        while ((dir = readdir(d)) != NULL) 
        {
            strcpy(temp2, temp);
            strcat(temp2,dir->d_name);
            printf("%s\n", temp2);
            ReadTrajectoryFile(temp2,p,index);
            index = index + 1;
        }

        closedir(d);

    }

}

void ReadProcessFile(char * fullpath, struct ControlParams * p)
{
    FILE* stream = fopen(fullpath,"r");
    char line[1024];
    int j = 0;
    char* tmp;
    char *eptr;
    char* tok;
    double ret;  

    (p->process) = calloc(17, sizeof(double));
    (p->trajectory) = calloc(17, sizeof(double));


    while (fgets(line, 1024, stream))
    {
        tmp = strdup(line);
        
        //read process/ctl number
        tok = strtok(line, ",");
        ret = strtod(tok, &eptr);

        p->process[j] = ret;

        //read traj number
        tok = strtok(NULL, ",");
        ret = strtod(tok, &eptr);

        p->trajectory[j] = ret;

        j = j + 1;
 
    }
}

void ReadTrajectoryFile(char * fullpath, struct ControlParams * p, int index)
{
    printf("%s\n", fullpath);
    FILE* stream = fopen(fullpath,"r");
    printf("%s\n", fullpath);
    char line[1024];
    int j = 0;

    char* tmp;
    char *eptr;

    char* tok = strtok(line, ",");
    tok = strtok(line, ",");

    //int index = atoi(tok);
    
    double ret;

    while (fgets(line, 1024, stream))
    {
        tmp = strdup(line);
        
        //read time
        tok = strtok(line, ",");
        ret = strtod(tok, &eptr);
        printf("%f\n",ret);

        p->t[index][j] = ret;
        
       
        //read x
        tok = strtok(NULL, ",");
        ret = strtod(tok, &eptr);
        p->x[index][j] = ret;
        j = j + 1;

        
    }

}

void ReadControlFile(char * fullpath, struct ControlParams * p, int index)
{

    int n = 7;
    const char paramNames[7][10] = {"Md","Bd","Kd","kp","kv","alpha","delta"};
    double * paramVals[7] = {&(p->paramArray->Md[index]),&(p->Dd),&(p->Kd),&(p->kp),&(p->kv),&(p->alpha),&(p->delta)};
    
    FILE* stream = fopen(fullpath,"r");
    char line[1024];
    int j = 0;
    
    char* tmp = strdup(line);
    char *eptr;

    //read process/ctl number
    char* tok = strtok(line, ",");
    tok = strtok(line, ",");
    
    //int index = atoi(tok);
    
    double ret;

    while (fgets(line, 1024, stream))
    {
        
        tmp = strdup(line);
        
        //read param
        tok = strtok(line, ",");
        
        for(int i = 0; i < n; i++)
        {
            if(strcmp(paramNames[i],tok)==0)
            {
                printf("%s: ",tok);
                tok = strtok(NULL, ",");
                ret = strtod(tok, &eptr);
                *(paramVals[i]) = ret;
                printf("%f\n",tok,ret);
                break;
            }
        }

        j = j + 1;

    }

    printf("Md, Bd, Kd, kv, delta: %f, %f, %f, %f, %f\n", p->Md, p->Dd, p->Kd, p->kv, p->delta);

}





