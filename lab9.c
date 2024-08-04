#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"

// Implement these functions
void handleInsert(LinkedList*);
void handleRemove(LinkedList*);
void handleCurrentCal(LinkedList*, int);
void handleVoltage(LinkedList*, int);
void handlePrint(LinkedList*);
void handleQuit(LinkedList*);

int main(void) {
  LinkedList circuit;
  initList(&circuit);
  char command = '\0';
  printf("Welcome to our circuit simulator\n");
  // Enter the source voltage!
  printf("What is the source of the voltage?\n");
  int voltage;
  readInputNumber(&voltage);

  while (command != 'Q') {
    command = getCommand();

    switch (command) {
      case 'I':
        handleInsert(&circuit);
        break;
      case 'R':
        handleRemove(&circuit);
        break;
      case 'C':
        handleCurrentCal(&circuit, voltage);
        break;
      case 'V':
        handleVoltage(&circuit, voltage);
        break;
      case 'P':
        handlePrint(&circuit);
        break;
      case 'Q':
        handleQuit(&circuit);
        break;
    }
  }
  return 0;
}

// I

Node* createNode(int value, char name[]) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  if (newNode != NULL) {
    newNode->value = value;
    strcpy(newNode->name, name);
    newNode->next = NULL;
  }
  return newNode;
}

void insertAtFront(LinkedList* circuit, int value, char name[]) {
  Node* temp = createNode(value, name);

  if (temp == NULL) {
    return;
  }
  temp->next = circuit->head;
  circuit->head = temp;
  return;
}

void handleInsert(LinkedList* circuit) {
  int resistance = 0;
  printf("What's the value of the resistor: ");
  readInputNumber(&resistance);
  printf("What's the label of the resistor: ");
  char labelName[STRING_MAX];
  readInputString(labelName, STRING_MAX);

  // TODO: Implement the insert into ordered list function
  Node* current = circuit->head;

  if (current == NULL) {
    insertAtFront(circuit, resistance, labelName);
    return;
  }

  int compareValue = strcmp(labelName, current->name);
  if (compareValue < 0) {
    insertAtFront(circuit, resistance, labelName);
    return;
  } else if (compareValue == 0) {
    printf("A resistor with %s label already exists.\n", labelName);
    return;
  }

  while (current->next != NULL) {
    compareValue = strcmp(labelName, current->next->name);

    if (compareValue == 0) {
      printf("A resistor with %s label already exists.\n", labelName);
      return;
    } else {
      current = current->next;
    }
  }

  Node* newNode = createNode(resistance, labelName);
  if (newNode == NULL) {
    printf("Could not allocate memory");
    return;
  }

  newNode->next = current->next;
  current->next = newNode;
  return;
}

// R

void deleteFront(LinkedList* circuit) {
  if (circuit->head == NULL) {
    return;
  }
  Node* newHead = circuit->head->next;
  free(circuit->head);
  circuit->head = newHead;
}

void handleRemove(LinkedList* circuit) {
  // TODO: Implement the remove function
  printf("What's the label of the resistor you want to remove: ");
  char labelName[STRING_MAX];
  readInputString(labelName, STRING_MAX);

  if (circuit->head == NULL) {
    printf("The resistor with %s label does not exist.\n", labelName);
    return;
  }

  if (strcmp(labelName, circuit->head->name) == 0) {
    deleteFront(circuit);
    return;
  }

  Node* current = circuit->head;
  while (current->next != NULL && strcmp(labelName, current->next->name) != 0) {
    current = current->next;
  }

  if (current->next != NULL) {
    Node* temp = current->next;
    current->next = temp->next;
    free(temp);
    return;
  }
  printf("The resistor with %s label does not exist.\n", labelName);
  return;
}

// C

void handleCurrentCal(LinkedList* circuit, int voltage) {
  // TODO: Implement the function that prints the value of current in the
  // circuit
  double resistanceTotal = 0;
  double currentTotal = 0;
  Node* current = circuit->head;

  while (current != NULL) {
    resistanceTotal = resistanceTotal + current->value;
    current = current->next;
  }

  currentTotal = voltage / resistanceTotal;
  printf("The current in the circuit is %.6fA\n", currentTotal);
  return;
}

// V

Node* findResistor(LinkedList* circuit, char name[]) {
  Node* current = circuit->head;

  while (current != NULL) {
    if (strcmp(name, current->name) == 0) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

void handleVoltage(LinkedList* circuit, int voltage) {
  // TODO: Implement the function that prints the potential difference across a
  // resistor

  double resistanceTotal = 0;
  double currentTotal = 0;
  double voltageAcrossR = 0;
  Node* current = circuit->head;

  while (current != NULL) {
    resistanceTotal = resistanceTotal + current->value;
    current = current->next;
  }

  currentTotal = voltage / resistanceTotal;

  printf(
      "What's the label of the resistor you want to find the voltage across: ");
  char labelName[STRING_MAX];
  readInputString(labelName, STRING_MAX);

  Node* chosenResistor = findResistor(circuit, labelName);

  if (chosenResistor == NULL) {
    printf("The resistor with %s label does not exist.\n", labelName);
  } else {
    voltageAcrossR = currentTotal * (chosenResistor->value);
    printf("Voltage across resistor is %.6fV", voltageAcrossR);
  }
}

// P

void handlePrint(LinkedList* circuit) {
  Node* current = circuit->head;

  while (current != NULL) {
    printf("%s  %d Ohms\n", current->name, current->value);
    current = current->next;
  }
}

// Q

void handleQuit(LinkedList* circuit) {
  // TODO: Implement the quit function

  printf("Removing all resistors in the circuit...\n");
  while (circuit->head != NULL) {
    printf("%s  %d Ohms\n", circuit->head->name, circuit->head->value);
    deleteFront(circuit);
  }

  circuit->head = NULL;
  return;
}
