/*MyDualCircularLinkedListsWithSentinels.h*/    
#ifndef MY_DUAL_CIRCULAR_LINKED_LISTS_WITH_SENTINELS_H
#define MY_DUAL_CIRCULAR_LINKED_LISTS_WITH_SENTINELS_H

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>

#define OK 1 // 涉及指针和内存分配的函数，运行正常返回
#define ERROR 0 // 运行异常返回

#define MAX_FIELD_LEN 128

#define BIT_PER_BYTE 8

typedef struct MyInfo{
    int comp20003_code; // 0 means invalid
    int official_suburb_code; // 0 means invalid
    char official_suburb_name[MAX_FIELD_LEN]; // empty string means invalid
    int year; // 0 means invalid
    char official_state_code[MAX_FIELD_LEN]; // empty string means invalid
    char official_state_name[MAX_FIELD_LEN]; // empty string means invalid
    char official_local_gov_area_code[MAX_FIELD_LEN]; // empty string means invalid
    char official_local_gov_area_name[MAX_FIELD_LEN]; // empty string means invalid
    double latitude; // DBL_MAX means invalid
    double longitude; // DBL_MAX means invalid
} MyInfo;

inline static void initialize_info(MyInfo *ptr_to_info)
{
    ptr_to_info->comp20003_code = 0;
    ptr_to_info->official_suburb_code = 0;
    ptr_to_info->official_suburb_name[0] = '\0';
    ptr_to_info->year = 0;
    ptr_to_info->official_state_code[0] = '\0';
    ptr_to_info->official_state_name[0] = '\0';
    ptr_to_info->official_local_gov_area_code[0] = '\0';
    ptr_to_info->official_local_gov_area_name[0] = '\0';
    ptr_to_info->latitude = DBL_MAX;
    ptr_to_info->longitude = DBL_MAX;
}

/*给定record，输出各个成员的值*/
inline static int print_info_1(MyInfo * ptr_to_info)
{
    printf("COMP20003 Code: %d, ", ptr_to_info->comp20003_code);
    printf("Official Code Suburb: %d, Official Name Suburb: %s, ", ptr_to_info->official_suburb_code, ptr_to_info->official_suburb_name);
    printf("Year: %d, ", ptr_to_info->year);
    printf("Official Code State: %s, Official Name State: %s, ", ptr_to_info->official_state_code, ptr_to_info->official_state_name);
    printf("Official Code Local Government Area: %s, Official Name Local Government Area: %s, ", 
            ptr_to_info->official_local_gov_area_code, ptr_to_info->official_local_gov_area_name);
    printf("Latitude: %.7lf, Longitude: %.7lf\n", ptr_to_info->latitude, ptr_to_info->longitude);
    return 0;
}

inline static int print_info_2(MyInfo * ptr_to_info)
{
    printf("COMP20003 Code: %d,", ptr_to_info->comp20003_code);
    printf("Official Code Suburb: %d, Official Name Suburb: %s,", ptr_to_info->official_suburb_code, ptr_to_info->official_suburb_name);
    printf("Year: %d,", ptr_to_info->year);
    printf("Official Code State: %s, Official Name State: %s,", ptr_to_info->official_state_code, ptr_to_info->official_state_name);
    // char *p = strchr(ptr_to_info->official_local_gov_area_code, ' ');
    // if(p && strchr(p + 1, ' '))
    if(strstr(ptr_to_info->official_local_gov_area_code, ", "))
        printf("Official Code Local Government Area: \"%s\",", ptr_to_info->official_local_gov_area_code);
    else
        printf("Official Code Local Government Area: %s,", ptr_to_info->official_local_gov_area_code);

    // p = strchr(ptr_to_info->official_local_gov_area_name, ' ');
    // if(p && strchr(p + 1, ' '))
    if(strstr(ptr_to_info->official_local_gov_area_name, ", "))
        printf("Official Name Local Government Area: \"%s\",", ptr_to_info->official_local_gov_area_name);
    else
        printf("Official Name Local Government Area: %s,", ptr_to_info->official_local_gov_area_name);

    printf("Latitude: %.7lf,Longitude: %.7lf\n", ptr_to_info->latitude, ptr_to_info->longitude);
    return 0;
}

/*给定record，输出各个成员的值到文件中*/
inline static int fprint_info_1(MyInfo * ptr_to_info, FILE *afp)
{
    fprintf(afp, "COMP20003 Code: %d, ", ptr_to_info->comp20003_code);
    fprintf(afp, "Official Code Suburb: %d, Official Name Suburb: %s, ", ptr_to_info->official_suburb_code, ptr_to_info->official_suburb_name);
    fprintf(afp, "Year: %d, ", ptr_to_info->year);
    fprintf(afp, "Official Code State: %s, Official Name State: %s, ", ptr_to_info->official_state_code, ptr_to_info->official_state_name);
    fprintf(afp, "Official Code Local Government Area: %s, Official Name Local Government Area: %s, ", 
        ptr_to_info->official_local_gov_area_code, ptr_to_info->official_local_gov_area_name);
    // fprintf(afp, "Official Code Local Government Area: %s, Official Name Local Government Area: %s, ", 
    //     ptr_to_info->official_local_gov_area_code, ptr_to_info->official_local_gov_area_name);
    fprintf(afp, "Latitude: %.7lf, Longitude: %.7lf\n", ptr_to_info->latitude, ptr_to_info->longitude);
    return 0;
}

inline static int fprint_info_2(MyInfo * ptr_to_info, FILE *afp)
{
    fprintf(afp, "COMP20003 Code: %d, ", ptr_to_info->comp20003_code);
    fprintf(afp, "Official Code Suburb: %d, Official Name Suburb: %s, ", ptr_to_info->official_suburb_code, ptr_to_info->official_suburb_name);
    fprintf(afp, "Year: %d, ", ptr_to_info->year);
    fprintf(afp, "Official Code State: %s, Official Name State: %s, ", ptr_to_info->official_state_code, ptr_to_info->official_state_name);
    // char *p = strchr(ptr_to_info->official_local_gov_area_code, ' ');
    // if(p && strchr(p + 1, ' '))
    if(strstr(ptr_to_info->official_local_gov_area_code, ", "))
        fprintf(afp, "Official Code Local Government Area: \"%s\", ", ptr_to_info->official_local_gov_area_code);
    else
        fprintf(afp, "Official Code Local Government Area: %s, ", ptr_to_info->official_local_gov_area_code);
    // p = strchr(ptr_to_info->official_local_gov_area_name, ' ');
    // if(p && strchr(p + 1, ' '))
    if(strstr(ptr_to_info->official_local_gov_area_name, ", "))
        fprintf(afp, "Official Name Local Government Area: \"%s\", ", ptr_to_info->official_local_gov_area_name);
    else
        fprintf(afp, "Official Name Local Government Area: %s, ", ptr_to_info->official_local_gov_area_name);
    
    fprintf(afp, "Latitude: %.7lf, Longitude: %.7lf\n", ptr_to_info->latitude, ptr_to_info->longitude);
    return 0;
}

/*给定record，输出各个成员的值到文件中*/
inline static int fprint_line_1(MyInfo * ptr_to_info, FILE *afp)
{
    fprintf(afp, "%d, ", ptr_to_info->comp20003_code);
    fprintf(afp, "%d, %s, ", ptr_to_info->official_suburb_code, ptr_to_info->official_suburb_name);
    fprintf(afp, "%d, ", ptr_to_info->year);
    fprintf(afp, "%s, %s, ", ptr_to_info->official_state_code, ptr_to_info->official_state_name);
    fprintf(afp, "%s, %s, ", ptr_to_info->official_local_gov_area_code, ptr_to_info->official_local_gov_area_name);
    fprintf(afp, "%.7lf, %.7lf\n", ptr_to_info->latitude, ptr_to_info->longitude);
    return 0;
}

/*给定record，输出各个成员的值到文件中*/
inline static int fprint_line_2(MyInfo * ptr_to_info, FILE *afp)
{
    fprintf(afp, "%d,", ptr_to_info->comp20003_code);
    fprintf(afp, "%d,%s,", ptr_to_info->official_suburb_code, ptr_to_info->official_suburb_name);
    fprintf(afp, "%d,", ptr_to_info->year);
    fprintf(afp, "%s,%s,", ptr_to_info->official_state_code, ptr_to_info->official_state_name);

    // char *p = strchr(ptr_to_info->official_local_gov_area_code, ' ');
    // if(p && strchr(p + 1, ' '))
    if(strstr(ptr_to_info->official_local_gov_area_code, ", "))
        fprintf(afp, "\"%s\",", ptr_to_info->official_local_gov_area_code);
    else
        fprintf(afp, "%s,", ptr_to_info->official_local_gov_area_code);

    // p = strchr(ptr_to_info->official_local_gov_area_name, ' ');
    // if(p && strchr(p + 1, ' '))
    if(strstr(ptr_to_info->official_local_gov_area_name, ", "))
        fprintf(afp, "\"%s\",", ptr_to_info->official_local_gov_area_name);
    else
        fprintf(afp, "%s,", ptr_to_info->official_local_gov_area_name);

    fprintf(afp, "%.7lf,%.7lf\n", ptr_to_info->latitude, ptr_to_info->longitude);
    return 0;
}

typedef struct MyDuNode{
    MyInfo *ptr_to_record;
    struct MyDuNode* prev;
    struct MyDuNode* next;
} MyDuNode, *My_Du_Linked_List;


/*给定带哨兵结点的循环双链表list，输出各个元素的值*/
int print_list_1(My_Du_Linked_List list);

/*给定带哨兵结点的循环双链表list，输出各个元素的值*/
int print_list_2(My_Du_Linked_List list);

/*给定带哨兵结点的循环双链表list，输出各个元素的值到文件中*/
int fprint_list_1(My_Du_Linked_List list, FILE *afp);

/*给定带哨兵结点的循环双链表list，输出各个元素的值到文件中*/
int fprint_list_2(My_Du_Linked_List list, FILE *afp);

/*给定带哨兵结点的循环双链表list，输出各个元素的值到csv文件中*/
int fprint_list_to_csv_1(My_Du_Linked_List list, FILE *afp);

/*给定带哨兵结点的循环双链表list，输出各个元素的值到csv文件中*/
int fprint_list_to_csv_2(My_Du_Linked_List list, FILE *afp);

/*初始化链表*/
int initialize_list(My_Du_Linked_List *ptr_to_list);

//在带哨兵结点的循环双链表list中，
//根据序号i获取元素的值，返回链表中第i个数据元素索引的数据记录，该记录的地址保存在*ptr_to_v中
int get_element(const My_Du_Linked_List list, int i, MyInfo ** const ptr_to_v);

//在带哨兵结点的循环双链表list中，查找值与*ptr_to_info的有效属性匹配的第一个元素，如找到，则返回该数据元素索引的数据记录的地址，否则返回NULL
MyDuNode *locate_element(const My_Du_Linked_List list, MyInfo * ptr_to_info, int *pCompCnt);

//在带哨兵结点的循环双链表中，第i个位置插入值与*ptr_to_info相等的新结点
int list_insert(My_Du_Linked_List *ptr_to_list, int i, MyInfo *ptr_to_info);

// 在带哨兵结点的循环双链表list中，查找值与*ptr_to_info的有效属性匹配的全部元素，把指向它们的指针保存在qualified_pointers数组中，
// 数量保存在*ptr_to_cnt，the number of comparisons saved in *pCompCnt
void locate_all_elements(const My_Du_Linked_List list, MyInfo *ptr_to_info, MyDuNode *** ptr_to_qualified_pointers, int *ptr_to_cnt, int *pCompCnt, int *pStrCompCnt, int *pNodeCheckedCnt);

inline static int list_insert_before(MyDuNode *p_to_inserted, MyDuNode* p_to_successor)
/*在p_to_successor指针所指的结点之前，插入p_to_inserted指针所指的结点*/
{
    if(!p_to_inserted || !p_to_successor)
    {
        return ERROR;
    }
    p_to_inserted->prev = p_to_successor->prev;
    p_to_inserted->next = p_to_successor;
    p_to_successor->prev->next = p_to_inserted;
    p_to_successor->prev = p_to_inserted;
    return OK;
}

inline static int list_insert_after(MyDuNode *p_to_inserted, MyDuNode* p_to_predecessor)
/*在p_to_predecessor指针所指的结点之后，插入p_to_inserted指针所指的结点*/
{
    if(!p_to_inserted || !p_to_predecessor)
    {
        return ERROR;
    }
    MyDuNode *p_to_successor = p_to_predecessor->next;
    if(list_insert_before(p_to_inserted, p_to_successor))
    {
        return OK;
    }
    else
    {
        return ERROR;
    }
}

//在带哨兵结点的循环双链表中，删除第i个元素
int list_delete_ith_element(My_Du_Linked_List list, int i);

inline static int list_delete_pointed_element(My_Du_Linked_List list, MyDuNode * p_to_deleted)
// preconditions: p_to_deleted points to a valid node in list
{
    p_to_deleted->prev->next = p_to_deleted->next;
    p_to_deleted->next->prev = p_to_deleted->prev;
    free(p_to_deleted);
    return OK;
}

//顺序输入元素的值，建立带表哨兵结点的循环双链表list，数据来自于迭代器
int create_list_from_head_to_tail_from_array(My_Du_Linked_List * ptr_to_list, MyInfo* data_array, int n);

//逆位序输入元素的值，建立带表哨兵结点的循环双链表list，数据来自于迭代器
int create_list_from_tail_to_head_from_array(My_Du_Linked_List *ptr_to_list, MyInfo* data_array, int n);

/*给定带哨兵结点的循环双链表list，销毁它并回收空间*/
int destroy_list(My_Du_Linked_List list);

#endif