/*
* @Author: chenyizhuo
* @Date:   2020-11-26 12:14:44
* @Last Modified by:   chenyizhuo
* @Last Modified time: 2020-11-26 21:51:55
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	char *key;
	int value;
	struct Node *next;
} Node;

typedef struct {
	Node **nodes;
	int capacity;
} Map;

int Hash(char *key, int capacity) {
	const int p = 31;
	const int m = 1e9 + 9;
	long long value = 0;
	long long power = 1;
	while (*key) {
		value = (value + (*key - 'a' + 1) * power) % m;
		power = (power * p) % m;
		key++;
	}
	return value % capacity;
}

Map *NewMap(int capacity) {
	Map *map = (Map *)malloc(sizeof(Map));
	map->capacity = capacity;
	map->nodes = (Node **)malloc(capacity * sizeof(Node *));
	for (int i = 0; i < capacity; i++) {
		map->nodes[i] = NULL;
	}
	return map;
}

Node *GetNode(Map *map, char *key) {
	int index = Hash(key, map->capacity);
	Node *p = map->nodes[index];
	while (p) {
		if (strcmp(p->key, key) == 0) {
			return p;
		}
		p = p->next;
	}
	return NULL;
}

int Get(Map *map, char *key) {
	Node *p = GetNode(map, key);
	return p == NULL ? 0 : p->value;
}

void PutValue(Node **nodes, int capacity, char *key, int value) {
	int index = Hash(key, capacity);
	Node *p = (Node *)malloc(sizeof(Node));
	p->key = key;
	p->value = value;
	p->next = nodes[index];
	nodes[index] = p;
}

void Put(Map *map, char *key, int value) {
	Node *p = GetNode(map, key);
	if (p) {
		p->value = value;
		return;
	}

	PutValue(map->nodes, map->capacity, key, value);
}

Map *CopyMap(Map *map) {
	Map *new = (Map *)malloc(sizeof(Map));
	new->capacity = map->capacity;
	new->nodes = (Node **)malloc(new->capacity * sizeof(Node *));
	for (int i = 0; i < map->capacity; i++) {
		new->nodes[i] = NULL;
		Node *p = map->nodes[i];
		while (p) {
			PutValue(new->nodes, new->capacity, p->key, p->value);
			p = p->next;
		}
	}
	return new;
}

void FreeMap(Map *map) {
	for (int i = 0; i < map->capacity; i++) {
		Node *p = map->nodes[i];
		while (p) {
			Node *q = p->next;
			free(p);
			p = q;
		}
	}
	free(map->nodes);
	free(map);
}

int *findSubstring(char *s, char **words, int wordSize, int *returnSize) {
	if (s == NULL || wordSize == 0 || words == NULL) {
		*returnSize = 0;
		return NULL;
	}

	Map *map = NewMap(wordSize);
	for (int i = 0; i < wordSize; i++) {
		Put(map, words[i], Get(map, words[i]) + 1);
	}

	int slen = strlen(s);
	int wlen = strlen(words[0]);
	int n = slen - wlen * wordSize;
	char *sub = (char *)malloc((wlen + 1) * sizeof(char));
	sub[wlen] = '\0';

	int size = 0;
	int *result = (int *)malloc(slen * sizeof(int));

	for (int i = 0; i <= n; i++) {
		Map *copy = CopyMap(map);
		int k = wordSize;
		int j = i;

		while (k > 0) {
			strncpy(sub, s + j, wlen);
			int value = Get(copy, sub);
			if (value < 1) {
				break;
			}
			Put(copy, sub, value - 1);
			k--;
			j += wlen;
		}
		if (k == 0) {
			result[size++] = i;
		}
		// FreeMap(copy);
	}

	// FreeMap(map);
	// free(sub);

	*returnSize = size;
	return result;
}

int main() {
	int size;
	char *words[] = {"aa","aa"};
	int wordSize = sizeof(words) / sizeof(words[0]);
	int *result = findSubstring("aaaaaaaaaaaaaa", words, wordSize, &size);
	printf("result = %d\n", size);
	for (int i = 0; i < size; i++) {
		printf("%d ", result[i]);
	}
	printf("\n");
	return 0;
}