/*MyDualCircularLinkedListsWithSentinels.c*/
#include "MyDualCircularLinkedListsWithSentinels.h"
#include <string.h>

#define HEAD_LINE "COMP20003 Code,Official Code Suburb,Official Name Suburb,Year,Official Code State,Official Name State,\
Official Code Local Government Area,Official Name Local Government Area,Latitude,Longitude"



int print_list_1(My_Du_Linked_List list)
/*给定带哨兵结点的循环双链表list，输出各个元素的值*/
{
    if(!list)
    {
        return ERROR;
    }
    MyDuNode* p = list->next;
    while(p != list)
    {
        print_info_1(p->ptr_to_record);
        p = p->next;
    }
    return OK;
}

int print_list_2(My_Du_Linked_List list)
/*给定带哨兵结点的循环双链表list，输出各个元素的值*/
{
    if(!list)
    {
        return ERROR;
    }
    MyDuNode* p = list->next;
    while(p != list)
    {
        print_info_2(p->ptr_to_record);
        p = p->next;
    }
    return OK;
}

int fprint_list_1(My_Du_Linked_List list, FILE *wfp)
/*给定带哨兵结点的循环双链表list，输出各个元素的值到文件中*/
{
    if(!list)
    {
        return ERROR;
    }
    MyDuNode* p = list->next;
    while(p != list)
    {
        fprint_info_1(p->ptr_to_record, wfp);
        p = p->next;
    }
    return OK;
}

int fprint_list_2(My_Du_Linked_List list, FILE *wfp)
/*给定带哨兵结点的循环双链表list，输出各个元素的值到文件中*/
{
    if(!list)
    {
        return ERROR;
    }
    MyDuNode* p = list->next;
    while(p != list)
    {
        fprint_info_2(p->ptr_to_record, wfp);
        p = p->next;
    }
    return OK;
}

int fprint_list_to_csv_1(My_Du_Linked_List list, FILE *wfp)
/*给定带哨兵结点的循环双链表list，输出各个元素的值到csv文件中*/
{
    fprintf(wfp, "%s", HEAD_LINE"\n");
    if(!list)
    {
        return ERROR;
    }
    MyDuNode* p = list->next;
    while(p != list)
    {
        fprint_line_1(p->ptr_to_record, wfp);
        p = p->next;
    }
    return OK;    
}

int fprint_list_to_csv_2(My_Du_Linked_List list, FILE *wfp)
/*给定带哨兵结点的循环双链表list，输出各个元素的值到csv文件中*/
{
    fprintf(wfp, "%s", HEAD_LINE"\n");
    if(!list)
    {
        return ERROR;
    }
    MyDuNode* p = list->next;
    while(p != list)
    {
        fprint_line_2(p->ptr_to_record, wfp);
        p = p->next;
    }
    return OK;    
}

int initialize_list(My_Du_Linked_List *ptr_to_list)
{
    // 创建哨兵结点
    *ptr_to_list = (MyDuNode*) malloc (sizeof(MyDuNode));
    if(!*ptr_to_list)
    {
        printf("insufficient space\n");
        exit(1);
    }
    (*ptr_to_list)->next = *ptr_to_list;
    (*ptr_to_list)->prev = *ptr_to_list;
    return OK;
}

int get_element(const My_Du_Linked_List list, int i, MyInfo ** const ptr_to_v)
//在带哨兵结点的循环双链表list中，
//根据序号i获取元素的值，返回链表中第i个数据元素索引的数据记录，该记录的地址保存在*ptr_to_v中
{
    MyDuNode* p = list->next; // 指向第一个有效结点
    while(i > 1 && p != list) // 未定位到i处并且p指向有效元素
    {
        p = p->next; // 指向下一元素
        i--; // 
    }
    if(p == list) // 已经到达链末端 
    {
        return ERROR; 
    }   
    *ptr_to_v = p->ptr_to_record; // 获取数据
    return OK;
}

inline static int int_match(int n1, int n2) // 0 match any int
{
    if(n1 && n2 && n1 != n2)
    {
        return 0;
    }
    return 1;
}

inline static int year_match(int n1, int n2)
{
    // printf("determining year match, n1: %d, n2: %d\n", n1, n2);
    return int_match(n1, n2);
}

inline static int double_match(double d1, double d2) // DBL_MAX match any dbl
{
    if(d1 != DBL_MAX && d2 != DBL_MAX && d1 != d2) // literals of Type Double with few sinigficant digits can be saved exactly
    {
        return 0;
    }
    return 1;
}

inline static int str_match(char* s1, char* s2) // empty string can match any string
{
    if(*s1 && *s2 && strcmp(s1, s2))
    {
        return 0;
    }
    return 1;
}

inline static int official_suburb_name_match(char* s1, char* s2, int *pCompCnt)
{
    *pCompCnt = 0;
    if(!s1 || !s2)
    {
        return 1;
    }
    char * t1 = s1, *t2 = s2;

    while(*t1 && *t2)
    {
        (*pCompCnt)++;
        if(*t1 != *t2)
        {
            return 0;
        }
        t1++; t2++;
    }
    if(*t1 || *t2)
    {
        (*pCompCnt)++;
        return 0;
    }
    (*pCompCnt)++;
    return 1;    
}

inline static int info_match(MyInfo* p, MyInfo* q, int * pCompCnt)
{
    // check comp20003_code
    if(!int_match(p->comp20003_code, q->comp20003_code)) // 
    {
        return 0;
    }
// printf("comp20003_code match\n");
    // check official_suburb_code
    if(!int_match(p->official_suburb_code, q->official_suburb_code))
    {
        return 0;
    }
// printf("official_suburb_code match\n");
    // check official_suburb_name
// printf("checking info match:\n");
// printf("%s\n", p->official_suburb_name);
// printf("%s\n", q->official_suburb_name);
    if(!official_suburb_name_match(p->official_suburb_name, q->official_suburb_name, pCompCnt))
    {
        return 0;
    }
// printf("official_suburb_name match\n");
    // check year
    if(!year_match(p->year, q->year))
    {
        return 0;
    }
// printf("year match\n");
    // check official_state_code
    if(!str_match(p->official_state_code, q->official_state_code))
    {
        return 0;
    }
    // check official_state_name
    if(!str_match(p->official_state_name, q->official_state_name))
    {
        return 0;
    }
// printf("official_state_name match\n");
    // check official_local_gov_area_code
    if(!str_match(p->official_local_gov_area_code, q->official_local_gov_area_code))
    {
        return 0;
    }
    // check official_local_gov_area_name
    if(!str_match(p->official_local_gov_area_name, q->official_local_gov_area_name))
    {
        return 0;
    }
// printf("official_local_gov_area_name match\n");
    // check latitude
    if(!double_match(p->latitude, q->latitude))
    {
        return 0;
    }
    // check longitude
    if(!double_match(p->longitude, q->longitude))
    {
        return 0;
    }
    return 1;
}

MyDuNode *locate_element(const My_Du_Linked_List list,  MyInfo* ptr_to_info, int *pCompCnt)
//在带哨兵结点的循环双链表list中，查找值与*ptr_to_v的有效属性匹配的!第一个元素，如找到返回结点的地址，否则返回NULL
{
    MyDuNode* p = list->next; // 指向第一个有效结点
    while(p != list && !info_match(p->ptr_to_record, ptr_to_info, pCompCnt)) // 仍指向有效元素，且未找到数据
    {
        p = p->next; 
    }
    if(info_match(p->ptr_to_record, ptr_to_info, pCompCnt))
    {
        return p;
    }
    return NULL;
}

void locate_all_elements(const My_Du_Linked_List list, MyInfo *ptr_to_v, MyDuNode *** ptr_to_qualified_node_pointers, int *ptr_to_cnt, int *pCompCnt, int *pStrCompCnt, int *pNodeCheckedCnt)
//在带哨兵结点的循环双链表list中，查找值与*ptr_to_v的有效属性匹配的全部元素，把指向相关链表结点的指针保存在*ptr_to_qualified_node_pointers数组中，数量保存在*ptr_to_cnt
{
    MyDuNode* p = list->next; // 指向第一个有效结点
    int qualified_node_pointer_cnt = 0;
    *pCompCnt = 0;
    *pNodeCheckedCnt = 0;
    *pStrCompCnt = 0;
    while(p != list) // 仍指向有效元素，且未找到数据
    {
// printf("locate_all_elements:\n");
// printf("%s\n", p->ptr_to_record->official_suburb_name);
// printf("%s\n", ptr_to_v->official_suburb_name);
        int comp_cnt_of_the_word;
        if(info_match(p->ptr_to_record, ptr_to_v, &comp_cnt_of_the_word))
        {
            (*ptr_to_qualified_node_pointers)[qualified_node_pointer_cnt++] = p;
        }
        (*pCompCnt) += comp_cnt_of_the_word;
        (*pNodeCheckedCnt)++;
        (*pStrCompCnt)++;
        p = p->next; 
    }
    *ptr_to_cnt = qualified_node_pointer_cnt;
}

int list_insert(My_Du_Linked_List *ptr_to_list, int i, MyInfo *ptr_to_info)
//在带哨兵结点的循环双链表中，第i个位置插入值为v的新结点
{
    MyDuNode* p = *ptr_to_list;
    MyDuNode* q = (MyDuNode*) malloc (sizeof(MyDuNode));
    if(!q)
    {
        return ERROR;
    }
    q->ptr_to_record = ptr_to_info;
    q->prev = NULL;
    q->next = NULL;

    do{
        p = p->next;
        i--;
    }while(i > 0 && p != *ptr_to_list); // 最多移动i次指针，p可以取值为list，但这应该是最后的尝试
    if(!p) // 已经到达链表末端
    {
        return ERROR;
    }
    q->prev = p->prev;
    q->next = p;
    p->prev->next = q;
    p->prev = q;
    
    return OK;
}

int list_delete_ith_element(My_Du_Linked_List list, int i)
//在带哨兵结点的循环双链表中，删除第i个元素
{
    MyDuNode* p = list->next; // p用于指向待删除元素，已经定位第一个元素
    while(i > 1 && p != list) // 哨兵结点不能被删除，后面最多移动i-1次指针
    {
        p = p->next;
        i--;
    }
    if(p == list) // 已经到达链表末端
    {
        return ERROR;
    }
    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);
    return OK;
}

int create_list_from_tail_to_head_from_array(My_Du_Linked_List *ptr_to_list, MyInfo* data_array, int n)
//逆位序输入元素的值，建立带表哨兵结点的循环双链表list，数据来自于迭代器
{
    MyDuNode* p = (MyDuNode*) malloc (sizeof(MyDuNode));
    if(!p) // 分配空间失败
    {
        return ERROR;
    }
    (*ptr_to_list) = p;
    (*ptr_to_list)->prev = (*ptr_to_list);
    (*ptr_to_list)->next = (*ptr_to_list);
    for(int i = 0; i < n; i++)
    {
        p = (MyDuNode*) malloc (sizeof(MyDuNode));
        if(!p)
        {
            return ERROR;
        }
        (p->ptr_to_record) = &data_array[i];
        if(!list_insert_before(p, (*ptr_to_list)->next)) // before the first element
        {
            return ERROR;
        }
    }
    return OK;
}


int create_list_from_head_to_tail_from_array(My_Du_Linked_List * ptr_to_list, MyInfo* data_array, int n)
// 顺序输入元素的值，建立带表哨兵结点的循环双链表list，数据来自于迭代器
{
    MyDuNode* p = (MyDuNode*) malloc (sizeof(MyDuNode));
    if(!p)
    {
        return ERROR;
    }
    (*ptr_to_list) = p;
    (*ptr_to_list)->prev = (*ptr_to_list);
    (*ptr_to_list)->next = (*ptr_to_list);
    for(int i = 0; i < n; i++)
    {
        p = (MyDuNode*) malloc (sizeof(MyDuNode));
        if(!p)
        {
            return ERROR;
        }
        p->ptr_to_record = &data_array[i];
        if(!list_insert_after(p, (*ptr_to_list)->prev))
        {
            return ERROR;
        }
    }
    return OK;   
}


int destroy_list(My_Du_Linked_List list)
/*给定带哨兵结点的循环双链表list，销毁它并回收空间*/
{
    if(!list)
    {
        return ERROR;
    }
    MyDuNode* p = list;
    do{
        MyDuNode *q = p;
        p = p->next;
        free(q);
    }while(p != list);
    return OK;
}