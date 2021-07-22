#include <gtk/gtk.h>
#include <json-c/json.h>

struct MemoryStruct {
  char* memory;
  size_t size;
};

struct node {
  char date[12];
  float open;
  float high;
  float low;
  float close;
  float volume;
  struct node* next;
};

extern GtkBuilder* builder;
extern GtkWidget* window;
extern GtkWidget* gtk_stock_symbol_submit;
extern GtkWidget* gtk_stock_symbol_entry;
extern GtkWidget* image1;
extern GtkWidget* fixed1;
extern char key[25];

struct node* linked_list_add(struct node* head, struct node* newP);
struct node* linked_list_empty(struct node* head);
struct node* linked_list_node_from_json(struct node* newP,
                                        char* key,
                                        struct json_object* val);

double linked_list_parse_member(struct node* tmp, char* member);
void linked_list_print(struct node* head);

void on_submit(GtkButton* b);
char* get_stock_symbol();

void plot(struct node* head, char* symbol, char* member);
