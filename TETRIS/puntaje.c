#include <stdio.h>
#include <stdlib.h>
long long int mejorpuntaje()
{
    int tamanio;
    long long int puntaje = 0;

    FILE *f = fopen("puntaje.dat","ab+");

    if(f == NULL)
    {
        return 1;
    }

    fseek(f,0,SEEK_END);
    tamanio = ftell(f);

    if(tamanio == 0)
    {
        fwrite(&puntaje,sizeof(long long int),1,f);
    }
    else
    {
        fseek(f,0,SEEK_SET);
        fread(&puntaje,sizeof(long long int),1,f);
    }

    fclose(f);

    return puntaje;
}

int puntaje(int puntajeant,int filaselim)
{
    int puntaje=puntajeant;




    switch(filaselim)
    {
        case 1:
            puntaje+=40;
            break;
        case 2:
            puntaje+=100;
            break;
        case 3:
            puntaje+=300;
            break;
        case 4:
            puntaje+=1200;
            break;
        default:
            break;
    }
    return puntaje;
}


