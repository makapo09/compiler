#ifndef BACKPATCH_H
#define BACKPATCH_H

typedef struct labelList {
    unsigned label;
    struct labelList* next;
} labelList;

labelList* newlist(unsigned label);
labelList* mergelists(labelList* l1, labelList* l2);
void backpatch(labelList* list, unsigned quadLabel);

#endif
