#define _LISTA_C_
#include "lista.h"

// Cria a lista 
SLList *SLLCreate() {
    SLList *l = (SLList *)malloc(sizeof(SLList));
    if (l != NULL) {
        l->first = NULL;
        l->nElms = 0;
    }
    return l;
}

// Insere um elemento no início da lista
int SLLInsert(SLList *l, void *data) {
    if (l == NULL) return -1;

    SLNode *newnode = (SLNode *)malloc(sizeof(SLNode));
    if (newnode == NULL) return -1;

    newnode->data = data;
    newnode->next = l->first;
    l->first = newnode;
    l->nElms++;

    return 0;
}

// Remove elemento especificado
void *SLLRemove(SLList *l, void *key, int (*cmp)(void *, void *)) {
    if (l == NULL || l->first == NULL) return NULL;

    SLNode *cur = l->first;
    SLNode *prev = NULL;

    while (cur != NULL && cmp(key, cur->data) != 1) {
        prev = cur;
        cur = cur->next;
    }

    if (cur == NULL) return NULL; 

    void *data = cur->data;

    if (prev == NULL) {
        l->first = cur->next;
    } else {
        prev->next = cur->next;
    }

    free(cur);
    l->nElms--;

    return data;
}

// Consulta um elemento pela chave
void *SLLQuery(SLList *l, void *key, int (*cmp)(void *, void *)) {
    if (l == NULL) return NULL;

    SLNode *cur = l->first;
    while (cur != NULL) {
        if (cmp(key, cur->data) == 1) {
            return cur->data;
        }
        cur = cur->next;
    }
    return NULL;
}

// Lista todos os elementos 
void SLLList(SLList *l, void (*show)(void *)) {
    if (l == NULL) return;

    SLNode *cur = l->first;
    while (cur != NULL) {
        show(cur->data);
        cur = cur->next;
    }
}

// Esvazia a lista 
void SLLEmpty(SLList *l, void (*freel)(void *)) {
    if (l == NULL) return;

    SLNode *cur = l->first;
    while (cur != NULL) {
        SLNode *next = cur->next;
        if (freel != NULL) freel(cur->data);
        free(cur);
        cur = next;
    }
    l->first = NULL;
    l->nElms = 0;
}

// Destroi a lista (se estiver vazia)
int SLLDestroy(SLList *l) {
    if (l == NULL) return -1;
    if (l->nElms != 0) return -1;

    free(l);
    return 0;
}