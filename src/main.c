#include <notcurses/notcurses.h>

int main() {
  struct notcurses_options opts = {};
  struct notcurses* nc = notcurses_init(&opts, NULL);

  if (!nc) return -1;

  struct ncplane* stdn = notcurses_stdplane(nc);

  ncplane_putstr(stdn, "Hello, World!");
  notcurses_render(nc);

  struct ncinput ni;
  notcurses_get_blocking(nc, &ni);

  notcurses_stop(nc);
  return 0;
}
