#include <notcurses/notcurses.h>
#include "ui.h"

int main() {
  struct notcurses_options opts = {
    .flags = NCOPTION_SUPPRESS_BANNERS
  };
  struct notcurses* nc = notcurses_init(&opts, NULL);

  if (!nc) return -1;

  UI ui;
  ui_init(&ui, nc);
  ui_render(&ui);
  notcurses_render(nc);

  struct ncinput ni;

  while(1) {
    int ret = notcurses_get_blocking(nc, &ni);
    if (ret < 0) {
      break;
    }

    ui_handle_input(&ui, &ni);
    ui_render(&ui);
    notcurses_render(nc);
  }

  notcurses_stop(nc);
  return 0;
}
