// ==================================================
// FILE: src/modules/utils.c
// ==================================================

#include "../headers/utils.h"
#include "../headers/dataio.h"
#include "../headers/structs.h"

void clear_screen() {
    system("cls");
}

void pause_screen() {
    printf("Press any key to continue...\n");
    getch();
}
