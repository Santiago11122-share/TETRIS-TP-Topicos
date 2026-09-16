#include <stdio.h>
#include <stdlib.h>
int mejorpuntaje()
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
        fwrite(&puntaje,sizeof(int),1,f);
    }
    else
    {
        fseek(f,0,SEEK_SET);
        fread(&puntaje,sizeof(int),1,f);
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

void guardarpuntaje(int puntaje)
{
    FILE *f = fopen("puntaje.dat", "rb+");
    int puntajehistorico = 0;

    if(f == NULL)
    {
        // Si no existe, se crea
        f = fopen("puntaje.dat", "wb+");

        if(f == NULL)
        {
            printf("Error al abrir archivo\n");
            return;
        }
    }

    fseek(f,0,SEEK_SET);

    fread(&puntajehistorico, sizeof(int), 1, f);

    if(puntaje > puntajehistorico)
    {
        fseek(f, 0, SEEK_SET);

        fwrite(&puntaje, sizeof(int), 1, f);
    }

    fclose(f);
}

