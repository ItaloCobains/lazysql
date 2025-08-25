#include "ui.h"
#include <string.h>

void ui_init(UI* ui, struct notcurses* nc) {
    int rows, cols;
    notcurses_stddim_yx(nc, &rows, &cols);

    int left_width = cols / 4;
    int bottom_height = 3;
    int right_width = cols - left_width;
    int right_height = rows - bottom_height;

    struct ncplane_options opts = {0};

    // Left pane (tables)
    opts.y = 0;
    opts.x = 0;
    opts.rows = rows - bottom_height;
    opts.cols = left_width;
    opts.name = "left";
    opts.flags = 0;
    ui->left = ncplane_create(notcurses_stdplane(nc), &opts);

    // Right pane (query results)
    opts.y = 0;
    opts.x = left_width;
    opts.rows = right_height;
    opts.cols = right_width;
    opts.name = "right";
    ui->right = ncplane_create(notcurses_stdplane(nc), &opts);

    // Bottom pane (status bar)
    opts.y = rows - bottom_height;
    opts.x = 0;
    opts.rows = bottom_height;
    opts.cols = cols;
    opts.name = "bottom";
    ui->bottom = ncplane_create(notcurses_stdplane(nc), &opts);

    ui->mode = NORMAL;
    ui->cursor = 0;
}

void ui_render(UI* ui) {
    ncplane_erase(ui->left);
    ncplane_erase(ui->right);
    ncplane_erase(ui->bottom);

    // Left pane - Tables List
    const char* tables[] = {"Table1", "Table2", "Table3", "Table4"};
    int n_tables = sizeof(tables) / sizeof(tables[0]);

    for (int i = 0; i < n_tables; i++) {
        if (i == ui->cursor) {
            ncplane_set_styles(ui->left, NCSTYLE_BOLD);
            ncplane_set_bg_rgb(ui->left, 0x0055AA);
            ncplane_set_fg_rgb(ui->left, 0xFFFFFF);
        } else {
            ncplane_set_styles(ui->left, NCSTYLE_NONE);
            ncplane_set_bg_default(ui->left);
            ncplane_set_fg_default(ui->left);
        }
        ncplane_putstr_yx(ui->left, i, 0, tables[i]);
    }

    // Right pane - Placeholder
    ncplane_putstr(ui->right, "Query results will appear here\n");

    // Bottom pane - Mode line
    if (ui->mode == NORMAL)
        ncplane_putstr_yx(ui->bottom, 1, 2, "-- NORMAL --");
    else
        ncplane_putstr_yx(ui->bottom, 1, 2, "-- INSERT --");

    // Reset styles
    ncplane_set_styles(ui->left, NCSTYLE_NONE);
    ncplane_set_styles(ui->right, NCSTYLE_NONE);
    ncplane_set_styles(ui->bottom, NCSTYLE_NONE);
}

void ui_handle_input(UI* ui, struct ncinput* ni) {
    const char* tables[] = {"Table1", "Table2", "Table3", "Table4"};
    int n_tables = sizeof(tables) / sizeof(tables[0]);

    if (ui->mode == NORMAL) {
        switch (ni->id) {
            case 'j':
                ui->cursor++;
                if (ui->cursor > n_tables - 1) ui->cursor = n_tables - 1;
                break;
            case 'k':
                ui->cursor--;
                if (ui->cursor < 0) ui->cursor = 0;
                break;
            case 'i':
                ui->mode = INSERT;
                break;
            case 'q':
                exit(0);
        }
    } else if (ui->mode == INSERT) {
        if (ni->id == 27) { // ESC
            ui->mode = NORMAL;
        }
    }
}
