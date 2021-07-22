#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

char* get_stock_symbol(char* url, char* API_KEY) {
  char* symbol = malloc(sizeof(char) * 5);

  // make sure the strings are clean
  strcpy(url, "");
  strcpy(API_KEY, "");

  // set the default values
  // api key for alphavantage.co
  strcpy(API_KEY, key);
  strcpy(
      url,
      "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=");

  // get a symbol
  sprintf(symbol, "%s", gtk_entry_get_text(GTK_ENTRY(gtk_stock_symbol_entry)));

  // check the length of the symbol
  if (strlen(symbol) > 5) {
    strcpy(symbol, "");
  }

  // put symbol in all caps
  for (int i = 0; i < strlen(symbol); i++) {
    if (symbol[i] > 96) {
      symbol[i] -= 32;
    }
  }

  // build the url string
  strcat(url, symbol);
  strcat(url, API_KEY);

  return symbol;
}
