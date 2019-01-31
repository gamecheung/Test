#ifndef LINEARLIST_H
#define LINEARLIST_H

#include "global.h"

#define LIST_INIT_SIZE 100
#define LIST_INCREMENT 10

typedef struct
{
    int     data_i;
//    double  data_d;
}ElemType;

typedef struct
{
    ElemType*   elem;
    int         length;
    int         listsize;
}SqList;

STATUS init_list(SqList* list)
{
    list->elem = (ElemType*)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
    if(list->elem == nullptr)
        return False;

    list->length = 0;
    list->listsize = LIST_INIT_SIZE;
    return True;
}
STATUS increment_list(SqList* list,int size)
{
    if(size < 0)
        return False;

    list->elem = (ElemType*)realloc(list->elem,sizeof(ElemType)*(list->listsize + LIST_INCREMENT));
    list->listsize += LIST_INCREMENT;

    return True;
}
STATUS insert_list(SqList* list,int pos,ElemType* e)
{
    int i = list->length;
    if(pos <= 0 || pos > list->length + 1)
        return False;

    if(!e) return False;

    if(list->listsize <= 0)
    {
        if(!increment_list(list,LIST_INCREMENT))
            return False;
    }
    for(;i >= pos;--i)
    {
        (list->elem)[i] = (list->elem)[i-1];
    }
    (list->elem)[pos-1] = *e;
    list->length += 1;
    return True;
}

STATUS delete_list(SqList* list,int pos)
{
    if(pos > list->length || pos <= 0)
        return False;

    for(int i = pos;i < list->length;++i)
    {
        (list->elem)[i - 1] = (list->elem)[i];
    }

    list->length -= 1;

    return True;
}

bool compare(const ElemType* e1,const ElemType* e2)
{
    return e1->data_i > e2->data_i;
}
STATUS mergeList(const SqList* list_a,const SqList* list_b,SqList* list_c)
{
    int length_a = list_a->length;
    int length_b = list_b->length;

    init_list(list_c);
    while(length_a + length_b > list_c->listsize)
        increment_list(list_c,LIST_INCREMENT);

    ElemType* pa = list_a->elem;
    ElemType* pb = list_b->elem;
    ElemType* pa_end = list_a->elem + length_a - 1;
    ElemType* pb_end = list_b->elem + length_b -1;
    int k = 1;

    while(pa <= pa_end && pb <= pb_end)
    {
        if(!compare(pa,pb))
        {
            if(!insert_list(list_c,k++,pa++))
                return False;
        }else
        {

            if(!insert_list(list_c,k++,pb++))
                return False;
            //if pa == pb,so add once
            if(pa->data_i == pb->data_i)
            {
                pa++;
            }
        }
    }

    while(pa <= pa_end)
    {
        if(!insert_list(list_c,k++,pa++))
            return False;
    }

    while(pb <= pb_end)
    {
        if(!insert_list(list_c,k++,pb++))
            return False;
    }

    return True;
}


void test()
{
    SqList list;
    SqList list2;
    init_list(&list);
    init_list(&list2);
    for(int i = 0;i < 10;++i)
    {
        ElemType* t = (ElemType*)malloc(sizeof(ElemType));
        t->data_i = i * 2;
        if(!insert_list(&list,i+1,t))
        {
            qDebug() << "insert list failed";
        }
    }
    for(int i = 0;i < 15;++i)
    {
        ElemType* t = (ElemType*)malloc(sizeof(ElemType));
        t->data_i = i + 1;
        if(!insert_list(&list2,i+1,t))
        {
            qDebug() << "insert list failed";
        }
    }
//    ElemType t1;
//    t1.data_i = 100;
//    insert_list(&list,5,&t1);
    qDebug() << "------------list1-----------";
    for(int i = 0;i < list.length;++i)
    {
        qDebug() << ((list.elem)[i]).data_i;
    }
    qDebug() << "-------------list2----------";
    for(int i = 0;i < list2.length;++i)
    {
        qDebug() << ((list2.elem)[i]).data_i;
    }
    SqList list3;
    mergeList(&list,&list2,&list3);
    qDebug() << "-------------list3----------";
    for(int i = 0;i < list3.length;++i)
    {
        qDebug() << ((list3.elem)[i]).data_i;
    }
}
#endif // LINEARLIST_H
