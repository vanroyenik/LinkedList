#include <stdio.h>
#include <stdlib.h>

void printInt(void *value) {
    printf("%d ", *((int*) value));
};

typedef struct _ListListNode {
    void *value;
    struct _ListListNode *next;
    struct _ListListNode *prev;
} ListNode;

typedef struct _LinkedList {
    size_t size;
    ListNode *head;
    ListNode *tail;
} LinkedList;

LinkedList* createLinkedList() {
    LinkedList *tmp = (LinkedList*) malloc(sizeof(LinkedList));
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;

    return tmp;
};

ListNode* getNextNode(LinkedList *list, size_t index) {
    ListNode *tmp = NULL;
    size_t i;

    if (index < list->size/2) {
        i = 0;
        tmp = list->head;
        while (tmp && i < index) {
            tmp = tmp->next;
            i++;
        }
    } else {
        i = list->size - 1;
        tmp = list->tail;
        while (tmp && i > index) {
            tmp = tmp->prev;
            i--;
        }
    }

    return tmp;
};
ListNode* getNth(LinkedList *list, size_t index) {
    ListNode *tmp = list->head;
    size_t i = 0;

    while (tmp && i < index) {
        tmp = tmp->next;
        i++;
    }

    return tmp;
};


void* popFirst(LinkedList *list) {
    ListNode *prev;
    void *tmp;
    if (list->head == NULL) {
        exit(2);
    }

    prev = list->head;
    list->head = list->head->next;
    if (list->head) {
        list->head->prev = NULL;
    }
    if (prev == list->tail) {
        list->tail = NULL;
    }
    tmp = prev->value;
    free(prev);

    list->size--;
    return tmp;
};

void* popLast(LinkedList *list) {
    ListNode *next;
    void *tmp;
    if (list->tail == NULL) {
        exit(4);
    }

    next = list->tail;
    list->tail = list->tail->prev;
    if (list->tail) {
        list->tail->next = NULL;
    }
    if (next == list->head) {
        list->head = NULL;
    }
    tmp = next->value;
    free(next);

    list->size--;
    return tmp;
};


void insert(LinkedList *list, size_t index, void *value) {
    ListNode *elm = NULL;
    ListNode *ins = NULL;
    elm = getNth(list, index);
    if (elm == NULL) {
        exit(5);
    }
    ins = (ListNode*) malloc(sizeof(ListNode));
    ins->value = value;
    ins->prev = elm;
    ins->next = elm->next;
    if (elm->next) {
        elm->next->prev = ins;
    }
    elm->next = ins;

    if (!elm->prev) {
        list->head = elm;
    }
    if (!elm->next) {
        list->tail = elm;
    }

    list->size++;
};

void* deleteNth(LinkedList *list, size_t index) {
    ListNode *elm = NULL;
    void *tmp = NULL;
    elm = getNth(list, index);
    if (elm == NULL) {
        exit(5);
    }
    if (elm->prev) {
        elm->prev->next = elm->next;
    }
    if (elm->next) {
        elm->next->prev = elm->prev;
    }
    tmp = elm->value;

    if (!elm->prev) {
        list->head = elm->next;
    }
    if (!elm->next) {
        list->tail = elm->prev;
    }

    free(elm);

    list->size--;

    return tmp;
};

void deleteLinkedList(LinkedList **list) {
    ListNode *tmp = (*list)->head;
    ListNode *next = NULL;
    while (tmp) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
};

void pushFront(LinkedList *list, void *data) {
    ListNode *tmp = (ListNode*) malloc(sizeof(ListNode));
    if (tmp == NULL) {
        exit(1);
    }
    tmp->value = data;
    tmp->next = list->head;
    tmp->prev = NULL;
    if (list->head) {
        list->head->prev = tmp;
    }
    list->head = tmp;

    if (list->tail == NULL) {
        list->tail = tmp;
    }
    list->size++;
};
void pushBack(LinkedList *list, void *value) {
    ListNode *tmp = (ListNode*) malloc(sizeof(ListNode));
    if (tmp == NULL) {
        exit(3);
    }
    tmp->value = value;
    tmp->next = NULL;
    tmp->prev = list->tail;
    if (list->tail) {
        list->tail->next = tmp;
    }
    list->tail = tmp;

    if (list->head == NULL) {
        list->head = tmp;
    }
    list->size++;
};
void printLinkedList(LinkedList *list, void (*fun)(void*)) {
    ListNode *tmp = list->head;
    while (tmp) {
        fun(tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
};
LinkedList* fromArray(void *arr, size_t n, size_t size) {
    LinkedList *tmp = NULL;
    size_t i = 0;
    if (arr == NULL) {
        exit(7);
    }
    tmp = createLinkedList();
    while (i < n) {
        pushBack(tmp, ((char*)arr + i*size));
        i++;
    }
    return tmp;
};

void main() {
    LinkedList *list = createLinkedList();
    int a, b, c, d, e, f, g, h;
    a = 1;
    b = 2;
    c = 3;
    d = 4;
    e = 5;
    f = 6;
    g = 7;
    h = 8;
    pushFront(list, &a);
    pushFront(list, &b);
    pushFront(list, &c);
    pushBack(list, &d);
    pushBack(list, &e);
    pushBack(list, &f);
    printLinkedList(list, printInt);
    printf("length %d\n", list->size);
    printf("nth 2 %d\n", *((int*)(getNextNode(list, 2))->value));
    printf("nth 5 %d\n", *((int*)(getNextNode(list, 5))->value));
    printf("popFirst %d\n", *((int*)popFirst(list)));
    printf("popFirst %d\n", *((int*)popFirst(list)));
    printf("head %d\n", *((int*)(list->head->value)));
    printf("tail %d\n", *((int*)(list->tail->value)));
    printf("popLast %d\n", *((int*)popLast(list)));
    printf("popLast %d\n", *((int*)popLast(list)));
    printf("length %d\n", list->size);
    printLinkedList(list, printInt);
    insert(list, 1, &g);
    printLinkedList(list, printInt);
    deleteNth(list, 0);
    printLinkedList(list, printInt);
    deleteLinkedList(&list);

    getch();
};









