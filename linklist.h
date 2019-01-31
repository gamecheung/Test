#ifndef LINKLIST_H
#define LINKLIST_H

#include "global.h"

typedef struct
{
    int m_data;
}ElemType;

typedef struct Node
{
    ElemType            d;
    struct Node*      next;
}Node,*PNode;


STATUS get_elem(PNode list,int i,ElemType* e)
{
    if(list->next == nullptr)
        return False;

    PNode next = list->next;
    while(--i)
    {
        next = next->next;
        if(!next)
            return False;
    }
    *e = next->d;

    return True;
}

STATUS insert_list(PNode node1,PNode node2,PNode insert_node)
{
    insert_node->next = node2;
    node1->next = insert_node;
    return True;
}

STATUS delete_list(PNode list,PNode delete_node)
{
    PNode next_node = list->next;
    while(next_node && next_node != delete_node)
    {
        next_node = next_node->next;
    }

    if(next_node == delete_node)
        next_node = delete_node->next;

    return True;
}
void test()
{
    ElemType e1;
    e1.m_data = 80;

    ElemType e2;
    e2.m_data = 88;

    ElemType e3;
    e3.m_data = 89;

    ElemType e4;
    e4.m_data = 222;
    Node node;
    Node node2;
    Node node3;
    Node node4;

    Node insert_node;
    insert_node.d = e4;
    node.next = &node2;

    node2.d = e1;
    node2.next = &node3;

    node3.d = e2;
    node3.next = &node4;

    node4.d = e3;
    node4.next = nullptr;

//    insert_list(&node2,&node3,&insert_node);
    delete_list(&node,&node2);
    ElemType e;
    if(!get_elem(&node,2,&e))
        qDebug() << "get elem failed!";
    else
        qDebug() << e.m_data;

    getchar();
}
#endif // LINKLIST_H
