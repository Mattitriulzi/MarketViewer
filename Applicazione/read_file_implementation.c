#ifdef __cplusplus
extern "C" {
#endif
#include "stock.h"


char *read_file(FILE *file, int length)
{
    char *s = (char *) calloc(length + 1, sizeof(char));
    if (!s)
    {
        perror("Unable to allocate memory");
        return NULL;
    }
    char *buffer = (char *) calloc(length + 1, sizeof(char));
    if (!buffer)
    {
        perror("Unable to allocate memory");
        return NULL;
    }
    int n = 0; // number of iterations

    size_t read;
    while ((read = fread(&buffer, sizeof(char), length, file)) > 0)
    {
        *(buffer + read) = '\0';
        if (!n)
        {
            strcpy(s, buffer);
        }
        else 
        {
            s = (char *)realloc(s, (strlen(s) +  strlen(buffer)) * sizeof(char));
            if (!s)
            {
                perror("Unable to allocate memory");
                return NULL;
            }
            strcat(s, buffer);
        }
        n++;
    }
    free(buffer);
    return s;
}
#ifdef __cplusplus
}
#endif