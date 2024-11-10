#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 1024

typedef struct membloc {
    int start;
    int size;
    bool is_allocated;
    struct membloc* next;
} membloc;

membloc* head = NULL;

void ini_mem(int max_size) {
    head = (membloc*)malloc(sizeof(membloc));
    head->start = 0;
    head->size = max_size;
    head->is_allocated = false;
    head->next = NULL;
}

void alloc_mem(int size) {
    membloc* current = head;
    while (current != NULL) {
        if (!current->is_allocated && current->size >= size) {
            if (current->size > size) {
                membloc* new_block = (membloc*)malloc(sizeof(membloc));
                new_block->start = current->start + size;
                new_block->size = current->size - size;
                new_block->is_allocated = false;
                new_block->next = current->next;
                current->next = new_block;
            }
            current->size = size;
            current->is_allocated = true;
            printf("Memory allocated at address %d\n", current->start);
            return;
        }
        current = current->next;
    }
    printf("Not enough memory to allocate %d bytes.\n", size);
}

void free_mem(int start_address) {
    membloc* current = head;
    while (current != NULL) {
        if (current->start == start_address && current->is_allocated) {
            current->is_allocated = false;
            printf("Memory block starting at address %d freed.\n", start_address);
            return;
        }
        current = current->next;
    }
    printf("No allocated block found at address %d.\n", start_address);
}

void rep_mem() {
    int total_allocated = 0, total_free = 0, total_blocks = 0;
    membloc* current = head;
    while (current != NULL) {
        if (current->is_allocated) {
            total_allocated += current->size;
        } else {
            total_free += current->size;
        }
        total_blocks++;
        current = current->next;
    }
    printf("Total memory allocated: %d bytes\n", total_allocated);
    printf("Total memory free: %d bytes\n", total_free);
    printf("Number of memory blocks: %d\n", total_blocks);
}

void vis_mem() {
    membloc* current = head;
    printf("Memory map:\n");
    while (current != NULL) {
        printf("Start: %d, Size: %d, %s\n", current->start, current->size, 
               current->is_allocated ? "Allocated" : "Free");
        current = current->next;
    }
}

void comp_mem() {
    int new_start = 0;
    membloc* current = head;
    membloc* previous = NULL;
    while (current != NULL) {
        if (current->is_allocated) {
            if (current->start != new_start) {
                current->start = new_start;
            }
            new_start += current->size;
        }
        previous = current;
        current = current->next;
    }
    if (previous != NULL && !previous->is_allocated) {
        previous->start = new_start;
        previous->size = MAX - new_start;
        previous->next = NULL;
    } else if (new_start < MAX) {
        membloc* new_block = (membloc*)malloc(sizeof(membloc));
        new_block->start = new_start;
        new_block->size = MAX - new_start;
        new_block->is_allocated = false;
        new_block->next = NULL;
        if (previous != NULL) {
            previous->next = new_block;
        } else {
            head = new_block;
        }
    }
    printf("Memory compacted.\n");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <memory size>\n", argv[0]);
        return 1;
    }
    int max_size = atoi(argv[1]);
    if (max_size > MAX) {
        printf("Error: Maximum allowed memory size is %d bytes.\n", MAX);
        return 1;
    }
    ini_mem(max_size);
    int choice, size, start_address;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Allocate memory\n");
        printf("2. Free memory\n");
        printf("3. Report memory\n");
        printf("4. Visualize memory\n");
        printf("5. Compact memory\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter the size of memory to allocate: ");
                scanf("%d", &size);
                alloc_mem(size);
                break;
            case 2:
                printf("Enter the start address of the memory block to free: ");
                scanf("%d", &start_address);
                free_mem(start_address);
                break;
            case 3:
                rep_mem();
                break;
            case 4:
                vis_mem();
                break;
            case 5:
                comp_mem();
                break;
            case 6:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    }
}
