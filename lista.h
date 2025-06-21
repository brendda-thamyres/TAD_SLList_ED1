/*-----------------------------------------
lista.h
Arquivo com a especificação para o TAD Lista,
tipo de dado para uma coleção genérica.
Exemplo do curso: Estrutura de Dados I
___________________________________________
Autora: Brendda Thamyres Mendes Rodrigues
Data: Junho/2025
Professor: Anselmo Cardoso de Paiva (ACP)
------------------------------------------*/

#ifndef _LISTA_H_
#define _LISTA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*___________________________________________
# Estrutura SLNode:
    É o nó da lista, contendo um ponteiro para os dados
    e um ponteiro para o próximo nó

# Estrutura SLList:
    É a coleção, contendo um ponteiro para o primeiro nó
    e o número de elementos da lista
_____________________________________________*/

typedef struct SLNode {
    void *data;
    struct SLNode *next;
}SLNode;

typedef struct SLList{
    SLNode *first;
    int nElms;
}SLList;

// Funções que implementam as operações da lista
#ifdef _LISTA_C_

    SLList *SLLCreate();
    int SLLInsert(SLList *l, void *data);
    void *SLLRemove(SLList *l, void *key, int(*cmp)(void*, void*));
    void *SLLQuery(SLList *l, void *key, int(*cmp)(void*, void*));
    void SLLList(SLList *l, void(*show)(void*));
    int SLLDestroy(SLList *l);
    void SLLEmpty(SLList *l, void(*freel)(void*));

#else
    extern SLList *SLLCreate();
    extern int SLLInsert(SLList *l, void *data);
    extern void *SLLRemove(SLList *l, void *key, int(*cmp)(void*, void*));
    extern void *SLLQuery(SLList *l, void *key, int(*cmp)(void*, void*));
    extern void SLLList(SLList *l, void(*show)(void*));
    extern int SLLDestroy(SLList *l);
    extern void SLLEmpty(SLList *l, void(*freel)(void*));

    #endif
#endif

/*_____________________________________________________________
SLLCreate: Cria a coleção
SLLInsert: Insere um elemento à lista
SLLRemove: Remove um elemento da lista
SLLQuery: Consulta um elemento da lista
SLLDestroy: Destrói a lista se ela estiver vazia
SLLEmpty: esvazia a lista

*/

