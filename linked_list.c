#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

struct node* linked_list_add(struct node* head, struct node* newP) {
  if (head == NULL) {
    head = newP;
  } else {
    struct node* tmp = head;
    while (tmp->next != NULL) {
      tmp = tmp->next;
    }
    tmp->next = newP;
  }
  return head;
}

/*Returns one of the double value members of the node structure based on string
 * member name*/
double linked_list_parse_member(struct node* n, char* member) {
  if (strcmp("open", member) == 0)
    return n->open;
  else if (strcmp("high", member) == 0)
    return n->high;
  else if (strcmp("high", member) == 0)
    return n->high;
  else if (strcmp("low", member) == 0)
    return n->low;
  else if (strcmp("close", member) == 0)
    return n->close;
}

/**Cleans the list and returns head = NULL */
struct node* linked_list_empty(struct node* head) {
  struct node* tmp = head;
  struct node* tmp2 = head->next;
  while (tmp2 != NULL) {
    free(tmp);
    tmp = tmp2;
    tmp2 = tmp2->next;
  }
  head = NULL;
  return head;
}
/**Print the contents of the list */
void linked_list_print(struct node* head) {
  struct node* tmp = head;
  printf("printing list...\n");
  while (tmp != NULL) {
    printf("%s\t %f %f %f %f %f\n", tmp->date, tmp->open, tmp->high, tmp->low,
           tmp->close, tmp->volume);
    tmp = tmp->next;
  }
}

/*create a node from json input*/
struct node* linked_list_node_from_json(struct node* newP,
                                        char* key,
                                        struct json_object* val) {
  // build a new node to contain the data
  struct json_object* open;
  struct json_object* high;
  struct json_object* low;
  struct json_object* close;
  struct json_object* volume;

  // retrieve the fields
  json_object_object_get_ex(val, "1. open", &open);
  json_object_object_get_ex(val, "2. high", &high);
  json_object_object_get_ex(val, "3. low", &low);
  json_object_object_get_ex(val, "4. close", &close);
  json_object_object_get_ex(val, "5. volume", &volume);

  // convert data types and assign
  strcpy(newP->date, key);
  newP->open = atof(json_object_get_string(open));
  newP->high = atof(json_object_get_string(high));
  newP->low = atof(json_object_get_string(low));
  newP->close = atof(json_object_get_string(close));
  newP->volume = atof(json_object_get_string(volume));
  newP->next = NULL;
}
