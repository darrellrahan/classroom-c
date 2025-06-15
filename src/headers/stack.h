#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "structs.h"

// stacks untuk undo dan redo
NavigationStack* undo_stack;
NavigationStack* redo_stack;

// Stack Operations
NavigationStack* create_stack();
bool is_empty(NavigationStack* stack);
bool is_full(NavigationStack* stack);
void push(NavigationStack* stack, const char* menu_name, void* data);
StackNode* pop(NavigationStack* stack);
StackNode* peek(NavigationStack* stack);
void clear_stack(NavigationStack* stack);
void init_navigation();
void cleanup_navigation();
void navigate_to(const char* menu_name, void* data);
bool undo_navigation(char* prev_menu, void** prev_data);
bool redo_navigation(char* next_menu, void** next_data);

#endif // STACK_H
