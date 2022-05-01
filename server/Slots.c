#include <malloc.h>
#include "Slots.h"

void AppendSlots(struct Slots **slots){
    struct Slots *newSlot = (struct Slots*)malloc(sizeof(struct Slots));
    newSlot->right = NULL;
    newSlot->ConnectionDescriptor = -1;
    newSlot->Nickname[0] = '\0';

    if((*slots) == NULL){
        (*slots) = newSlot;
        newSlot->left = NULL;
        return;
    }

    struct Slots *runner = (*slots);
    while(runner->right != NULL)
        runner = runner->right;
    runner->right = newSlot;
    newSlot->left = runner;
}