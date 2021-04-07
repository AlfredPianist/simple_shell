#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void printenv(char **env);
int _setenv(char **env, char *varN, char* varV, int overwrite);
char **copyEnv(char **env);

int main(int ac, char **av, char **env_org)
{
        int i = 0;
        char **env = copyEnv(env_org);

        printenv(env);
        printf("----------------------------\n");
        _setenv(env, "NEWVAR1", "asdasdojieijoijowejiewrwer", 1);
        _setenv(env, "NEWVAR2", "asdasdojieijoijowejiewrwer", 1);
        // _setenv(env, "NEWVAR3", "asdasdojieijoijowejiewrwer", 1);
        // _setenv(env, "NEWVAR4", "asdasdojieijoijowejiewrwer", 1);
        // _setenv(env, "NEWVAR5", "asdasdojieijoijowejiewrwer", 1);
        // _setenv(env, "NEWVAR6", "asdasdojieijoijowejiewrwer", 1);
        // _setenv(env, "NEWVAR7", "asdasdojieijoijowejiewrwer", 1);
        // _setenv(env, "NEWVAR8", "asdasdojieijoijowejiewrwer", 1);
        // _setenv(env, "NEWVAR9", "asdasdojieijoijowejiewrwer", 1);
        // _setenv(env, "NEWVAR10", "asdasdojieijoijowejiewrwer", 1);
        printenv(env);

        while(env[i])
        {
                printf("%p => %s\n", env[i], env[i]);
                free(env[i]), i++;
        }

        free(env);

        return (0);
}

char **copyEnv(char **env)
{
        unsigned int i = 0, j=0;
        char **newEnv;

        while(env[i])
                i++;
        
        newEnv = malloc(sizeof(char*) * i);

        for(i = 0; env[i]; i++)
        {
                newEnv[i] = malloc(sizeof(char) * strlen(env[i]));
                
                // for (j = 0; j < strlen(env[i]); j++)
                //         newEnv[i][j] = env[i][j];
                // newEnv[i][j] = 0;
                memcpy(newEnv[i], env[i], strlen(env[i]));
                
                printf("cpy=%p, org=%p\n", newEnv[i], env[i]);
        }

       // newEnv[i] = 0;

        return newEnv;
}

int _setenv(char **env, char *varN, char* varV, int overwrite)
{
        int i;
        int buff_size = strlen(varN) + strlen(varV) + 2;
        char *buff = malloc(buff_size * sizeof(char));
        
        strcat(buff, varN);
        strcat(buff, "=");
        strcat(buff, varV);
        buff[buff_size - 1] = 0;

        for (i = 0; env[i]; i++)
                if (strncmp(env[i], varN, strlen(varN)) == 0)
                {
                        env[i] = buff;
                        return (1);
                }
        env = realloc(env, sizeof(char *) * i);

        env[i] = buff;
        env[i + 1] = 0;
        return (1);
}

void printenv(char **env)
{
        int i = 0;

        while (env[i])
                printf("%s\n", env[i++]);
}
