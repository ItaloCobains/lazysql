#pragma once
#include <notcurses/notcurses.h>

typedef enum { NORMAL, INSERT } Mode;

typedef struct {
  struct ncplane* left;
  struct ncplane* right;
  struct ncplane* bottom;
  Mode mode;
  int cursor;
} UI;

void ui_init(UI* ui, struct notcurses* nc);
void ui_render(UI* ui);
void ui_handle_input(UI* ui, struct ncinput* ni);