#include <stdio.h>
#include <string.h>
#include <assert.h>
// #define NDEBUG

#define SEARCH_MODE
// #define REMOVE_MODE

#include "MyDualCircularLinkedListsWithSentinels.h"

#define MAX_QUERY_CNT 1024
#define MAX_DATA_RECORD_CNT 1024 * 128

// #define debug_mode

int main(int argc, char **argv) {
    if(argc != 4)
    {
        printf("The number of command line arguments is incorrect.\n");
        return 1;
    }
    // for storing queries
    char official_suburb_name_query_keys[MAX_QUERY_CNT][128];
    memset(official_suburb_name_query_keys, 0, MAX_QUERY_CNT * 128);

    int i;
    // clear
    for(i = 0; i < MAX_QUERY_CNT; i++)
    {
        official_suburb_name_query_keys[i][0] = '\0';
    }

    // read queries in commands
    i = 0;
    do
    {
        fgets(official_suburb_name_query_keys[i], 128, stdin);
        official_suburb_name_query_keys[i][strlen(official_suburb_name_query_keys[i]) - 1] = '\0';
        i++;
    } while (*official_suburb_name_query_keys[i - 1]);
    int query_count = i - 1;

    // read csv
    char * input_file_name = argv[2];
    FILE *rfp = fopen(input_file_name, "r");
    if (!rfp) {
        printf("Can't open file %s for reading\n", input_file_name);
        return 1;
    }
#ifdef debug_mode
printf("before reading data\n");
#endif
    MyInfo* data_records = malloc(sizeof(MyInfo) * MAX_DATA_RECORD_CNT);
    if(!data_records)
    {
        printf("Insufficient Memory\n");
        return 1;
    }

    memset(data_records, 0, sizeof(MyInfo) * MAX_DATA_RECORD_CNT);

    char buf[1024];
    i = 0;
    while (fgets(buf, 1024, rfp)) {
        char *field = strtok(buf, ",");
        char data_items[100][128];
        int j = 0;
        while(field) {
            strcpy(data_items[j], field);
            field = strtok(NULL, ",");
            j++;
        }
        int data_item_cnt = j;

        // contract, concat items lying in the same pair of quotes
        int start = 0;
        while(data_item_cnt > 10) // conditions indicating that contraction is needed
        {
            int k;
            for(k = start; k < data_item_cnt; k++)
            {
// printf("start: %s\n", data_items[k]);
                if(data_items[k][0] == '"')
                    break;
            }
            int l;
            for(l = k + 1; l < data_item_cnt; l++)
            {
// printf("end: %s\n", data_items[l]);
                if(data_items[l][strlen(data_items[l]) - 1] == '"')
                    break;
            }
            int data_item_canceled_cnt = (l - k);
            start = k + 1;
            for(int m = k + 1; m <= l; m++)
            {
// printf("strcat\n");
                strcat(data_items[k], ",");
                strcat(data_items[k], data_items[m]);
            }
            for(int m = k + 1; l + 1 < data_item_cnt; m++, l++)
            {
                strcpy(data_items[m], data_items[l+1]);
            }
            data_item_cnt -= data_item_canceled_cnt;
// printf("data_item_cnt: %d\n", data_item_cnt);
        }
        if(i == 0)
        {
            i++;
            continue;
        }
        data_records[i].comp20003_code = atoi(data_items[0]);
        data_records[i].official_suburb_code = atoi(data_items[1]);
        strcpy(data_records[i].official_suburb_name, data_items[2]);
        data_records[i].year = atoi(data_items[3]);
        strcpy(data_records[i].official_state_code, data_items[4]);
        strcpy(data_records[i].official_state_name, data_items[5]);
        if(data_items[6][0] == '"' && data_items[6][strlen(data_items[6]) - 1] == '"')
            strncpy(data_records[i].official_local_gov_area_code, data_items[6] + 1, strlen(data_items[6]) - 2);
        else
            strcpy(data_records[i].official_local_gov_area_code, data_items[6]);
        if(data_items[7][0] == '"' && data_items[7][strlen(data_items[7]) - 1] == '"')
            strncpy(data_records[i].official_local_gov_area_name, data_items[7] + 1, strlen(data_items[7]) - 2);
        else
            strcpy(data_records[i].official_local_gov_area_name, data_items[7]);
        data_records[i].latitude = atof(data_items[8]);
        data_records[i].longitude = atof(data_items[9]);
#ifdef debug_mode
// printf("after recording %dth data\n", i);
#endif
    // printf("data_items[5], data_items[6], data_items[7], data_items[8]: %s, %s, %s, %s\n", data_items[5], data_items[6], data_items[7], data_items[8]);
        i++;
    }

    int record_cnt = i - 1;

    My_Du_Linked_List lst = NULL;

#ifdef debug_mode
printf("before creating lists from head to tail\n");
#endif
    create_list_from_head_to_tail_from_array(&lst, data_records + 1, record_cnt); // 
#ifdef debug_mode
printf("after creating lists from head to tail\n");
#endif

    MyDuNode** qualified_node_pointers = malloc(sizeof(MyDuNode*) * 1024);
    if(!qualified_node_pointers)
    {
        printf("Insufficient Memory\n");
        return 1;
    }
    memset(qualified_node_pointers, 0, sizeof(MyDuNode*) * 1024);
    int qualified_node_pointer_count;
    MyInfo key;
    initialize_info(&key);

    char * output_file_name = argv[3];
    FILE *wfp = fopen(output_file_name, "w");
    if(!wfp)
    {
        printf("cannot open file %s for writing\n", output_file_name);
        return 1;
    }

    // fprint_list(lst, wfp);

    for(int i = 0; i < query_count; i++)
    {
        char * query = official_suburb_name_query_keys[i];
#ifdef debug_mode
printf("%dth query key\n", i + 1);
assert(*query);
printf("to search for key %s\n", query);
#endif
        strcpy(key.official_suburb_name, query);
#ifdef debug_mode
printf("before locating all qualified elements\n");
#endif
        locate_all_elements(lst, &key, &qualified_node_pointers, &qualified_node_pointer_count);
#ifdef debug_mode
printf("after locating all qualified elements\n");
#endif

        if(qualified_node_pointer_count)
        {
            printf("%s --> %d records ", query, qualified_node_pointer_count);
#ifdef SEARCH_MODE
            printf("found\n");
#endif
#ifdef REMOVE_MODE
            printf("deleted\n");
#endif
        } 
        else
        {
            printf("%s --> NOTFOUND\n", query);
        }

#ifdef SEARCH_MODE
        fprintf(wfp, "%s -->\n", query);
        for(int j = 0; j < qualified_node_pointer_count; j++)
        {
            fprint_info_1(qualified_node_pointers[j]->ptr_to_record, wfp);
        }
#endif

#ifdef REMOVE_MODE
        for(int j = 0; j < qualified_node_pointer_count; j++)
        {
            list_delete_pointed_element(lst, qualified_node_pointers[j]);
        }   
#endif
    }

#ifdef REMOVE_MODE
        fprint_list_to_csv_2(lst, wfp);  
#endif

    destroy_list(lst);

    free(qualified_node_pointers);
    free(data_records);

    if(fclose(wfp))
    {
        printf("cannot close file %s\n", output_file_name);
        return 1;
    }
    if(fclose(rfp))
    {
        printf("cannot close %s\n", input_file_name);
        return 1;
    }
    return 0;
}