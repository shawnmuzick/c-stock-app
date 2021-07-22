#include <curl/curl.h>
#include <gtk/gtk.h>
#include <json-c/json.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

char API_KEY[100];
static char url[200];

GtkBuilder* builder;
GtkWidget* window;
GtkWidget* gtk_stock_symbol_submit;
GtkWidget* gtk_stock_symbol_entry;
GtkWidget* fixed1;
GtkWidget* image1;
CURL* curl;
struct node* head;

// a struct to hold the response
struct MemoryStruct chunk;

static size_t writeMemory(void* contents,
                          size_t size,
                          size_t nmemb,
                          void* userp) {
  // size * memory in bytes
  size_t realsize = size * nmemb;
  // create a new structure
  struct MemoryStruct* mem = (struct MemoryStruct*)userp;

  // reallocate structure memory to new size
  char* ptr = realloc(mem->memory, mem->size + realsize + 1);
  // if realloc failed to return a pointer, we don't have enough memory
  if (!ptr) {
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  // otherwise, set the struct's memory property to the returned pointer
  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  //   update the size
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

void on_submit(GtkButton* b) {
  // get and format symbol from the UI
  char* symbol = get_stock_symbol(url, API_KEY);

  // initialize curlEasy
  curl_global_init(CURL_GLOBAL_ALL);
  CURL* curl = curl_easy_init();

  // initalize linked list for storage
  head = NULL;

  chunk.memory = malloc(1);
  chunk.size = 0;

  // if curl was initialized without error
  if (curl) {
    CURLcode res;
    // specify the url
    curl_easy_setopt(curl, CURLOPT_URL, url);
    // specify the function to send data to for writing
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeMemory);
    // pass the chunk struct to the function above
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
    res = curl_easy_perform(curl);

    // parse the json
    struct json_object* parsed_json;
    struct json_object* records;
    parsed_json = json_tokener_parse(chunk.memory);

    // get records from the parsed jason (removing headers, etc)
    json_object_object_get_ex(parsed_json, "Time Series (Daily)", &records);

    // walk the object properties
    json_object_object_foreach(records, key, val) {
      // create a new node and add to SLL head
      struct node* newP = malloc(sizeof(struct node));
      newP = linked_list_node_from_json(newP, key, val);
      head = linked_list_add(head, newP);
    }

    // cleanup curl stuff and print list
    curl_easy_cleanup(curl);
    plot(head, symbol, "open");
    plot(head, symbol, "close");
  }
}

int main(int argc, char* argv[]) {
  // initialize GTK and get main window
  gtk_init(&argc, &argv);
  builder = gtk_builder_new_from_file("main.glade");
  window = GTK_WIDGET(gtk_builder_get_object(builder, "main"));
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_builder_connect_signals(builder, NULL);
  gtk_stock_symbol_submit =
      GTK_WIDGET(gtk_builder_get_object(builder, "gtk_stock_symbol_submit"));
  gtk_stock_symbol_entry =
      GTK_WIDGET(gtk_builder_get_object(builder, "gtk_stock_symbol_entry"));
  fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
  gtk_widget_show_all(window);
  gtk_main();
  return 0;
}
