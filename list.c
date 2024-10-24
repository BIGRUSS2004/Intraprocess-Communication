#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Include string.h for strcat, strcpy, etc.
#include "list.h"

// Rest of the code follows...


// Create and initialize a new list
list_t* list_alloc() {
    list_t* list = (list_t*)malloc(sizeof(list_t));
    list->head = NULL;
    return list;
}

// Free the list and its elements
void list_free(list_t* list) {
    node_t* current = list->head;
    node_t* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

// Add a node to the front of the list
void list_add_to_front(list_t* list, int value) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->data = value;
    new_node->next = list->head;
    list->head = new_node;
}

// Add a node to the back of the list
void list_add_to_back(list_t* list, int value) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->data = value;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        node_t* temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

// Add a node at a specific index
void list_add_at_index(list_t* list, int index, int value) {
    if (index == 0) {
        list_add_to_front(list, value);
        return;
    }
    node_t* temp = list->head;
    for (int i = 0; i < index - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) return; // Index out of bounds

    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->data = value;
    new_node->next = temp->next;
    temp->next = new_node;
}

// Remove the front node of the list
int list_remove_from_front(list_t* list) {
    if (list->head == NULL) return -1; // List is empty

    node_t* temp = list->head;
    int value = temp->data;
    list->head = list->head->next;
    free(temp);
    return value;
}

// Remove the back node of the list
int list_remove_from_back(list_t* list) {
    if (list->head == NULL) return -1; // List is empty

    node_t* temp = list->head;
    if (temp->next == NULL) {
        int value = temp->data;
        free(temp);
        list->head = NULL;
        return value;
    }

    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    int value = temp->next->data;
    free(temp->next);
    temp->next = NULL;
    return value;
}

// Remove a node at a specific index
int list_remove_at_index(list_t* list, int index) {
    if (index == 0) {
        return list_remove_from_front(list);
    }

    node_t* temp = list->head;
    for (int i = 0; i < index - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) return -1; // Index out of bounds

    node_t* to_remove = temp->next;
    int value = to_remove->data;
    temp->next = to_remove->next;
    free(to_remove);
    return value;
}

// Get the number of nodes in the list
int list_length(list_t* list) {
    int count = 0;
    node_t* temp = list->head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Get the element at a specific index
int list_get_elem_at(list_t* list, int index) {
    node_t* temp = list->head;
    for (int i = 0; i < index && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) return -1; // Index out of bounds
    return temp->data;
}

// Convert the list to a string for printing
char* listToString(list_t* list) {
    char* result = (char*)malloc(1024); // Make sure the buffer is big enough
    result[0] = '\0'; // Start with an empty string

    node_t* temp = list->head;
    while (temp != NULL) {
        char buffer[12]; // Buffer to store each number
        sprintf(buffer, "%d -> ", temp->data);
        strcat(result, buffer);
        temp = temp->next;
    }
    strcat(result, "NULL");
    return result;
}
