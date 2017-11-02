#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct _employee {
    char name[32];
    unsigned char age;
} Employee;
typedef struct _node {
    void *data;
    struct _node *next;
} Node;
typedef struct _linkedList {
    Node *head;
    Node *tail;
    Node *current;
} LinkedList;

typedef void (*Display)(void *);

void displayEmployee(Employee *e) {
    printf("%s\t%d\n", e->name, e->age);
}

void initialLinkedList(LinkedList *list) {
    list->head = list->tail = list->current = NULL;
}

void addHead(LinkedList *list, void *data) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = data;
    if (list->head == NULL) {
        list->tail = node;
        node->next = NULL;
    } else {
        node->next = list->head;
    }
    list->head = node;
}

void addTail(LinkedList *list, void *data) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = data;
    if (list->head == NULL) {
        list->head = node;
    } else {
        list->tail->next = node;
    }
    list->tail = node;
    node->next = NULL;
}

typedef int (*Compare)(void *, void *);

int compareEmployee(Employee *e1, Employee *e2) {
    return strcmp(e1->name, e2->name);
}
int compareNode(Employee *e1, Employee *e2) {
    return 1;
}

Node *getNode(LinkedList *list, void *data, Compare compare) {
    Node *tmp = list->head;
    while (compare(tmp->data, data)) {
        tmp = tmp->next;
    }
    return tmp;
}

void displayLinkedList(LinkedList *list, Display display) {
    Node *tmp;
    tmp = list->head;
    while (tmp != NULL) {
        display(tmp->data);
        tmp = tmp->next;
    }
}

void deleteNode(LinkedList *list, Node *node) {
    Node *tmp = list->head;
    if (list->head == node) {
        list->head = list->head->next;
    } else {
        while (tmp->next != node) {
            tmp = tmp->next;
        }
        tmp->next = node->next;
    }
    free(node);
}

//Queue
typedef LinkedList Queue;

void initializeQueue(LinkedList *queue) {
    initialLinkedList(queue);
}

void enQueue(LinkedList *queue, void *data) {
    addHead(queue, data);
}

void *deQueue(LinkedList *queue) {
    Node *tmp = queue->head;
    void *data = NULL;
    if (queue->head == NULL) {
        data = NULL;
    } else if (queue->head == queue->tail) {
        data = queue->head->data;
        queue->head = queue->tail = NULL;
        free(tmp);
    } else {
        while (tmp->next != queue->tail) {
            tmp = tmp->next;
        }
        queue->tail = tmp;
        data = tmp->next->data;
        tmp->next = NULL;
        free(tmp->next);
    }
    return data;
}

//stack
typedef LinkedList Stack;

void initializeStack(LinkedList *stack) {
    initialLinkedList(stack);
}

void push(LinkedList *stack, void *data) {
    addHead(stack, data);
}

void *pop(LinkedList *stack) {
    Node *tmp = stack->head;
    void *data;
    if (stack->head == NULL) {
        data = NULL;
    } else if (stack->head == stack->tail) {
        data = tmp->data;
        stack->head = stack->tail = NULL;
        free(tmp);
    } else {
        stack->head = stack->head->next;
        data = tmp->data;
        free(tmp);
    }
    return data;
}

//模仿strlen
size_t stringLength(char *string) {
    size_t len = 0;
    while (*(string++)) {
        len++;
//            string++;
    }
    return len;
}

char *stringToLower(char *string) {
    char *tmp = (char *) malloc(strlen(string) + 1);
    char *start = tmp;
    while (*string != 0) {
        *(tmp++) = (char) tolower(*(string++));
    }
    *tmp = 0;
    return start;

}

typedef int (Operation)(const char *, const char *);

int compareStr(const char *s1, const char *s2) {
    return strcmp(s1, s2);
}

int compareIgnoreCase(const char *s1, const char *s2) {
    char *t1 = stringToLower((char *) s1);
    char *t2 = stringToLower((char *) s2);
    int result;
    result  = strcmp(t1,t2);
    free(t1);
    free(t2);
    return result;
}
void sort(char* stringArr[],Operation operation,int size){
    int flag =1;
    while(flag){
        flag=0;
        for(int i=0;i<size-1;i++){
            if(operation(stringArr[i],stringArr[i+1])>0){
                flag=1;
                char *tmpe=stringArr[i];
                stringArr[i]=stringArr[i+1];
                stringArr[i+1]=tmpe;

            }
        }
    }
}
void displaynames(char* names[],int size){
    for(int i=0;i<size;i++){
        printf("%s\n", names[i]);
    }
}

//tree
typedef struct _tree{
    void *data;
    struct _tree *left;
    struct _tree *right;
}TreeNode;
void insertNode(TreeNode **root,void *data,Compare compareNode){
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->data = data;
    node->left=NULL;
    node->right=NULL;

    if(*root==NULL){
        *root = node;
        return;
    }
    printf("%p",(*root)->data);

    while(1){
        if(compareNode((*root)->data,data)>0){
            if((*root)->left!=NULL){
                *root = (*root)->left;
            } else{
                (*root)->left = node;
                break;
            }
        } else{
            if((*root)->right!=NULL){
                *root = (*root)->right;
            } else{
                (*root)->right=node;
                break;
            }
        }

    }
}


int main() {
    //创建LinkedList
    LinkedList *list;
    list = (LinkedList *) malloc(sizeof(LinkedList));
    initialLinkedList(list);
    Employee *susan;
    //问题1 susan->name = "susan";
    susan = (Employee *) malloc(sizeof(Employee));
    //指针与字符串
    strcpy(susan->name, "susan");
    susan->age = 56;
    Employee *emily;
    //问题1 susan->name = "susan";
    emily = (Employee *) malloc(sizeof(Employee));
    //指针与字符串
    strcpy(emily->name, "emily");
    emily->age = 34;
    Employee *jack;
    //问题1 susan->name = "susan";
    jack = (Employee *) malloc(sizeof(Employee));
    //指针与字符串
    strcpy(jack->name, "jack");
    jack->age = 100;

    addTail(list, susan);
    addTail(list, emily);
    addTail(list, jack);
    displayLinkedList(list, (Display) displayEmployee);
    Node *node = getNode(list, jack, (int (*)(void *, void *)) compareEmployee);
    deleteNode(list, node);
    //queue 先进先出
    Queue queue;
    initializeQueue(&queue);
    enQueue(&queue, susan);
    enQueue(&queue, emily);
    enQueue(&queue, jack);
    void *data = deQueue(&queue);
    displayLinkedList(&queue, (Display) displayEmployee);
    //stack 先进后出
    Stack stack;
    initializeStack(&stack);
    push(&stack, susan);
    push(&stack, emily);
    push(&stack, jack);
    pop(&stack);
    //多重引用
    char *title[] = {"HarryPorrt", "JackSparrow", "Titanic", "Avanda"};
    char *bestTitle[1];
    char *badTitle[3];
    bestTitle[0] = title[0];
    badTitle[0] = title[1];
    badTitle[1] = title[2];
    badTitle[2] = title[3];
    //字符串
    char* namese[] = {"Alice","Dakl","Huise","back"};
    sort(namese,compareStr,4);
    displaynames( namese, 4);
    printf("%s",bestTitle[0]);

    //Tree
    TreeNode *tree=NULL;
    insertNode(&tree, jack,(Compare)compareEmployee);
    insertNode(&tree,susan,(Compare)compareEmployee);
    insertNode(&tree,emily,(Compare)compareEmployee);

    printf("xxx");
}
