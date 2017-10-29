  #include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _employee{
    char name[32];
    unsigned char age;
}Employee;
typedef struct _node{
    void *data;
    struct _node *next;
}Node;
typedef struct _linkedList{
    Node *head;
    Node *tail;
    Node *current;
}LinkedList;
typedef void (*Display)(void*);
void displayEmployee(Employee *e){
    printf("%s\t%d\n",e->name,e->age);
}

void initialLinkedList(LinkedList *list){
    list->head=list->tail=list->current=NULL;
}
void addHead(LinkedList *list,void *data){
    Node *node = (Node*)malloc(sizeof(Node));
    node->data =data;
    if(list->head==NULL){
        list->head=list->tail=node;
        node->next=NULL;
    }
    else{
        node->next=list->head;
    }
    list->head=node;
}
void displayLinkedList(LinkedList *list,Display display){
    Node *tmp;
    tmp = list->head;
    while (tmp!=NULL){
        display(tmp->data);
        tmp=tmp->next;
    }
}
int compareEmployee(Employee *e1,Employee *e2);


int main() {
    //创建LinkedList
    LinkedList *list;
    list = (LinkedList*)malloc(sizeof(LinkedList));
    initialLinkedList(list);
    Employee *susan;
    //问题1 susan->name = "susan";
    susan=(Employee*)malloc(sizeof(Employee));
    //指针与字符串
    strcpy(susan->name,"susan");
    susan->age=56;
    Employee *emily;
    //问题1 susan->name = "susan";
    emily=(Employee*)malloc(sizeof(Employee));
    //指针与字符串
    strcpy(emily->name,"emily");
    emily->age=34;
    Employee *jack;
    //问题1 susan->name = "susan";
    jack=(Employee*)malloc(sizeof(Employee));
    //指针与字符串
    strcpy(jack->name,"jack");
    jack->age=100;

    addHead(list,susan);
    addHead(list,emily);
    addHead(list,jack);
    displayLinkedList(list,(Display)displayEmployee);
    printf("ad");
}
