#include <stdlib.h>
#include <assert.h>
#include "backpatch.h"
#include "icode.h"

labelList* newlist(unsigned label) {
    labelList* list = (labelList*)malloc(sizeof(labelList));
    list->label = label;
    list->next = NULL;
    return list;
}

labelList* mergelists(labelList* l1, labelList* l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    labelList* temp = l1;
    while (temp->next)
        temp = temp->next;
    temp->next = l2;
    return l1;
}

void backpatch(labelList* list, unsigned quadLabel) {
    while (list) {
        assert(list->label < currQuad);
        quads[list->label].label = quadLabel;
        list = list->next;
    }
}
