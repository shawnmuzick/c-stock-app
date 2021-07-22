#include <gtk/gtk.h>
#include <string.h>
#include "headers.h"

void plot(struct node* head, char* symbol, char* member) {
  // open gnuplot
  FILE* gnuplot_pipe = popen("gnuplot", "w");
  char source[20];
  strcpy(source, member);
  strcat(source, symbol);
  strcat(source, ".png");

  // set title, png terminal, output file name
  const char name[] = "My Chart";
  fprintf(gnuplot_pipe, "set title '%s'\n", symbol);
  fprintf(gnuplot_pipe, "set terminal png\n");
  fprintf(gnuplot_pipe, "set output '%s'\n", source);

  // fill it with data
  fprintf(gnuplot_pipe, "plot '-' with linespoints ls 1\n");

  struct node* tmp = head;
  int i = 0;
  // walk the list, plotting the fields
  while (tmp != NULL) {
    // get the field we're requesting
    double result = linked_list_parse_member(tmp, member);
    printf("result: %f", result);
    fprintf(gnuplot_pipe, "%zu %f\n", i, member);
    i++;
    tmp = tmp->next;
  }

  fprintf(gnuplot_pipe, "e\n");

  // refresh can probably be omitted
  fprintf(gnuplot_pipe, "refresh\n");
  pclose(gnuplot_pipe);

  image1 = gtk_image_new_from_file(source);

  gtk_container_add(GTK_CONTAINER(fixed1), image1);
  gtk_widget_show(image1);
  gtk_fixed_move(GTK_FIXED(fixed1), image1, 100, 100);
  printf("\ndone plotting\n");
}
