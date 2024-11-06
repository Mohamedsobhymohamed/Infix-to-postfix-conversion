#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define SIZE 50

typedef struct node {
    float data;
    struct node* next;
} Node;

typedef struct stack {
    Node* top;
} Stack;

Stack* initialize() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

Node* newnode(float x) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = x;
    n->next = NULL;
    return n;
}

int isEmpty(Stack* s) {
    return (s->top == NULL);
}

void push(Stack* s, float value) {
    Node* n = newnode(value);
    n->next = s->top;
    s->top = n;
}

float pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        return NAN; // Return NaN to indicate an error
    }
    Node* temp = s->top;
    float value = temp->data;
    s->top = s->top->next;
    free(temp);
    return value;
}

float peek(Stack* s) {
    return s->top ? s->top->data : NAN;
}

int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    else if (c == '*' || c == '/') return 2;
    else if (c == '^') return 3;
    return -1;
}

char* infixToPostfix(char* infix) {
    Stack* stack = initialize();
    char* postfix = (char*)malloc(SIZE * sizeof(char));
    int i, j = 0, is_negative = 0;

    for (i = 0; i < strlen(infix); i++) {
        if (isdigit(infix[i]) || infix[i] == '.') {
            if (is_negative) postfix[j++] = '-';
            while (isdigit(infix[i]) || infix[i] == '.') {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            is_negative = 0;
            i--;
        } else if (infix[i] == '-') {
            if (i == 0 || infix[i - 1] == '(') is_negative = 1;
            else {
                while (!isEmpty(stack) && precedence(infix[i]) <= precedence(peek(stack))) {
                    postfix[j++] = pop(stack);
                    postfix[j++] = ' ';
                }
                push(stack, infix[i]);
            }
        } else if (strchr("+-*/^", infix[i])) {
            while (!isEmpty(stack) && precedence(infix[i]) <= precedence(peek(stack))) {
                postfix[j++] = pop(stack);
                postfix[j++] = ' ';
            }
            push(stack, infix[i]);
        } else if (infix[i] == '(') {
            push(stack, infix[i]);
        } else if (infix[i] == ')') {
            while (!isEmpty(stack) && peek(stack) != '(') {
                postfix[j++] = pop(stack);
                postfix[j++] = ' ';
            }
            pop(stack); // Remove '('
        } else if (!isspace(infix[i])) {
            printf("Invalid character in infix expression\n");
            free(postfix);
            return NULL;
        }
    }

    while (!isEmpty(stack)) {
        char op = pop(stack);
        if (op == '(' || op == ')') {
            printf("Mismatched parentheses\n");
            free(postfix);
            return NULL;
        }
        postfix[j++] = op;
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';
    return postfix;
}

float evaluatePostfix(char* postfix) {
    Stack* stack = initialize();
    int i = 0;
    while (postfix[i]) {
        if (isdigit(postfix[i]) || postfix[i] == '-') {
            float num = strtof(&postfix[i], &postfix);
            push(stack, num);
            while (isdigit(postfix[i]) || postfix[i] == '.' || postfix[i] == '-') i++;
        } else if (strchr("+-*/^", postfix[i])) {
            float operand2 = pop(stack);
            float operand1 = pop(stack);
            switch (postfix[i]) {
                case '+': push(stack, operand1 + operand2); break;
                case '-': push(stack, operand1 - operand2); break;
                case '*': push(stack, operand1 * operand2); break;
                case '/': push(stack, operand1 / operand2); break;
                case '^': push(stack, pow(operand1, operand2)); break;
            }
        }
        i++;
    }
    return pop(stack);
}

int main() {
    char infix[SIZE];
    printf("Enter infix expression: ");
    fgets(infix, SIZE, stdin);
    infix[strcspn(infix, "\n")] = '\0';

    char* postfix = infixToPostfix(infix);
    if (!postfix) return 1;

    printf("Postfix expression: %s\n", postfix);
    float result = evaluatePostfix(postfix);
    if (isnan(result)) printf("Invalid postfix expression\n");
    else printf("Value: %.2f\n", result);

    free(postfix);
    return 0;
}
