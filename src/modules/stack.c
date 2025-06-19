#include "../headers/stack.h"

NavigationStack* create_stack() {
    NavigationStack* stack = (NavigationStack*)malloc(sizeof(NavigationStack));
    if (stack) {
        stack->top = NULL;
        stack->size = 0;
    }
    return stack;
}

bool is_empty(NavigationStack* stack) {
    return stack == NULL || stack->top == NULL;
}

bool is_full(NavigationStack* stack) {
    return stack != NULL && stack->size >= MAX_STACK_SIZE;
}

void push(NavigationStack* stack, const char* menu_name, void* data) {
    if (stack == NULL || is_full(stack)) return;
    
    StackNode* new_node = (StackNode*)malloc(sizeof(StackNode));
    if (new_node) {
        if (strlen(menu_name) >= MAX_STRING) return;
        strcpy(new_node->menu_name, menu_name);
        new_node->data = data;
        new_node->next = stack->top;
        stack->top = new_node;
        stack->size++;
    }
}

StackNode* pop(NavigationStack* stack) {
    if (is_empty(stack)) return NULL;
    
    StackNode* temp = stack->top;
    stack->top = stack->top->next;
    stack->size--;
    return temp;
}

StackNode* peek(NavigationStack* stack) {
    if (is_empty(stack)) return NULL;
    return stack->top;
}

void clear_stack(NavigationStack* stack) {
    if (stack == NULL) return;
    
    while (!is_empty(stack)) {
        StackNode* temp = pop(stack);
        free(temp);
    }
}

// *
// * NAVIGATION FUNCTIONS
// *
void init_navigation() {
    undo_stack = create_stack();
    redo_stack = create_stack();
}

void cleanup_navigation() {
    clear_stack(undo_stack);
    clear_stack(redo_stack);
    free(undo_stack);
    free(redo_stack);
}

void initialize_current_menu(const char* menu_name, void* data) {
    // Clear redo stack when making new navigation
    clear_stack(redo_stack);
    
    // Push current state to undo stack
    push(undo_stack, menu_name, data);
}

bool undo_navigation(char* prev_menu, void** prev_data) {
    if (is_empty(undo_stack)) return false;
    
    StackNode* current = pop(undo_stack);
    if (current) {
        // Push to redo stack
        push(redo_stack, current->menu_name, current->data);
        
        // Get previous menu if exists
        StackNode* prev = peek(undo_stack);
        if (prev) {
            strcpy(prev_menu, prev->menu_name);
            *prev_data = prev->data;
            free(current);
            return true;
        } else {
            // If no previous menu, go to main menu
            strcpy(prev_menu, MAIN_MENU);
            *prev_data = NULL;
            free(current);
            return true;
        }
    }
    return false;
}

bool redo_navigation(char* next_menu, void** next_data) {
    if (is_empty(redo_stack)) return false;
    
    StackNode* next = pop(redo_stack);
    if (next) {
        // Push back to undo stack
        push(undo_stack, next->menu_name, next->data);
        
        strcpy(next_menu, next->menu_name);
        *next_data = next->data;
        free(next);
        return true;
    }
    return false;
}