/*  Fluent Bit
 *  ==========
 *  Copyright (C) 2019      The Fluent Bit Authors
 *  Copyright (C) 2015-2018 Treasure Data Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>
#include "mk_list.h"

struct data {
	int id;
	struct mk_list mk_list_head;
};

/* Add a Node */
void add(int arg, struct mk_list *head)
{
    struct data *headPtr = (struct data *)malloc(sizeof(struct data));
    headPtr->id = arg;
    mk_list_add(&headPtr->mk_list_head, head);
}

/* Delete a Node */
int delete(int arg, struct mk_list *head)
{
    struct mk_list *iter, *q;
    struct data *objPtr;

    mk_list_foreach_safe(iter, q, head) {
        objPtr = mk_list_entry(iter, struct data,mk_list_head);
        if(objPtr->id == arg) {
            mk_list_del(&objPtr->mk_list_head);
            free(objPtr);
            return 1;
        }
    }
    return 0;
}

/* Print List */
void print(struct mk_list *head)
{
    struct mk_list *iter, *q;
    struct data *objPtr;

    mk_list_foreach_safe(iter, q, head) {
        objPtr = mk_list_entry(iter, struct data,mk_list_head);
        printf("%d ", objPtr->id);
    }
    printf("\n");
}

/* Destroy safely traverses through the list, and deletes the nodes */
void destroy(struct mk_list *head)
{
    struct mk_list *iter, *q;
    struct data *objPtr;

    mk_list_foreach_safe(iter, q, head) {
        objPtr = mk_list_entry(iter, struct data,mk_list_head);
        mk_list_del(&objPtr->mk_list_head);
        free(objPtr);
    }
}

int main() 
{
    struct mk_list fooHead;
    int i = 0;
    mk_list_init(&fooHead);

    /* Add nodes to linked list */
    for(i = 1; i <=10; i++)
        add(i,&fooHead);
    
    /* The Linked List after inserting nodes */
    printf("Original Linked List:\n");
    print(&fooHead);

    /* The Linked List after deleting node with id 5 */
    printf("Linked List after deleted node 5:\n");
    delete(5, &fooHead);
    print(&fooHead); 

    /* Free the memory allocated to nodes */
    destroy(&fooHead);
}
