/*
* @Author: chenyizhuo
* @Date:   2020-11-27 10:09:30
* @Last Modified by:   chenyizhuo
* @Last Modified time: 2020-11-27 21:33:44
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
	int value;
	struct Node *next;
} Node;

typedef struct {
	Node *head;
	Node *tail;
	int size;
} DeQueue;

DeQueue *NewQueue() {
	DeQueue *queue = (DeQueue *)malloc(sizeof(DeQueue));
	memset(queue, 0, sizeof(DeQueue));
	return queue;
}

void PrintQueue(DeQueue *queue) {
	Node *p = queue->head;
	for (int i = 0; i < queue->size; i++) {
		printf("%d", p->value);
		p = p->next;
	}
	printf("\n");
}

void PushFront(DeQueue *queue, int value) {
	Node *node = (Node *)malloc(sizeof(Node));
	node->value = value;
	node->next = queue->head;
	queue->head = node;
	queue->size++;
	if (queue->tail == NULL) {
		queue->tail = queue->head;
	}
}

void PushBack(DeQueue *queue, int value) {
	Node *node = (Node *)malloc(sizeof(Node));
	node->value = value;
	queue->size++;
	if (queue->tail == NULL) {
		queue->head = queue->tail = node;
	} else {
		node->next = queue->tail->next;
		queue->tail->next = node;
		queue->tail = node;
	}
}

int PopFront(DeQueue *queue) {
	if (queue->size == 0) {
		return 0;
	}
	queue->size--;
	int value = queue->head->value;
	Node *next = queue->head->next;
	free(queue->head);
	queue->head = next;
	if (next == NULL) {
		queue->tail = NULL;
	}
	return value;
}

typedef struct {
	int *numbers;
	int top;
	int capacity;
} Stack;

Stack *NewStack(int capacity) {
	Stack *s = (Stack *)malloc(sizeof(Stack));
	s->numbers = (int *)malloc(capacity * sizeof(int));
	s->top = 0;
	s->capacity = capacity;
	return s;
}

void Push(Stack *stack, int num) {
	if (stack->top >= stack->capacity) {
		return;
	}
	stack->numbers[stack->top++] = num;
}

int Pop(Stack *stack) {
	if (stack->top == 0) {
		return 1;
	}
	return stack->numbers[--stack->top];
}

Stack *PushNumbers(char *num, int len) {
	Stack *s = NewStack(len);
	for (int i = 0; i < len; i++) {
		Push(s, num[i] - '0');
	}
	return s;
}

void Reverse(char *s, int len) {
	for (int i = 0; i < len / 2; i++) {
		int tmp = s[i];
		s[i] = s[len - i - 1];
		s[len - i - 1] = tmp;
	}
}

char *AddAllNumbers(DeQueue *allQueues[], int allQueuesCount, int *length) {
	char *result = (char *)malloc(sizeof(char) * (allQueues[0]->size + 2));
	int len = 0;

	int carry = 0;
	while (allQueues[0]->size != 0) {
		int res = 0;
		for (int i = 0; i < allQueuesCount; i++) {
			res += PopFront(allQueues[i]);
		}
		res += carry;
		carry = res / 10;
		result[len++] = res % 10 + '0';
	}
	if (carry) {
		result[len++] = carry + '0';
	}
	while (len > 1 && result[len - 1] == '0') {
		len--;
	}
	result[len] = 0;
	*length = len;
	return result;
}

DeQueue *MultiplySingleNumber(Stack *num1, char num2) {
	DeQueue *queue = NewQueue();
	int carry = 0;
	for (int i = num1->top - 1; i >= 0; i--) {
		int mul = num1->numbers[i] * (num2 - '0') + carry;
		carry = mul / 10;
		PushBack(queue, mul % 10);
	}
	while (carry) {
		PushBack(queue, carry % 10);
		carry /= 10;
	}
	return queue;
}

char *multiply(char *num1, char *num2) {
	if (num1 == NULL || num2 == NULL) {
		return NULL;
	}

	int len1 = strlen(num1);
	int len2 = strlen(num2);
	if (len1 == 0 || len2 == 0) {
		return NULL;
	}

	Stack *stack1 = PushNumbers(num1, len1);
	DeQueue **allQueues = (DeQueue **)malloc(sizeof(DeQueue *) * len2);
	int allQueuesCount = 0;

	for (int i = 0; i < len2; i++) {
		for (int i = 0; i < allQueuesCount; i++) {
			PushFront(allQueues[i], 0);
		}
		char n2 = num2[i];
		DeQueue *newQueue = MultiplySingleNumber(stack1, n2);
		allQueues[allQueuesCount++] = newQueue;
	}
	
	int length = 0;
	char *result = AddAllNumbers(allQueues, allQueuesCount, &length);
	Reverse(result, length);

	for (int i = 0; i < allQueuesCount; i++) {
		free(allQueues[i]);
	}
	free(allQueues);
	free(stack1);

	return result;
}

int main() {
	char *num1 = "140";
	char *num2 = "721";
	char *res = multiply(num1, num2);
	printf("%s\n", res);
}