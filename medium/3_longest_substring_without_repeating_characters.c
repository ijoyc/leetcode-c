/*
* @Author: yizhuoc
* @Date:   2020-11-25 16:18:03
* @Last Modified by:   chenyizhuo
* @Last Modified time: 2020-11-26 12:07:08
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

float LOAD_FACTOR = 0.75;

typedef struct Node {
	char key;
	int value;
	struct Node *next;
} Node;

typedef struct Map {
	Node **nodes;
	int size;
	int capacity;
} Map;

int Hash(char key, int capacity) {
	float t = (key * 0.17);
	return floorf(capacity * (t - (int)t));
}

Map *NewMap() {
	int initial = 16;
	Map *map = (Map *)malloc(sizeof(Map));
	map->capacity = initial;
	map->size = 0;
	map->nodes = (Node **)malloc(initial * sizeof(Node *));
	for (int i = 0; i < initial; i++) {
		map->nodes[i] = NULL;
	}
	return map;
}

void PutValue(Node **nodes, int capacity, char key, int value) {
	int index = Hash(key, capacity);
	Node *p = (Node *)malloc(sizeof(Node));
	p->key = key;
	p->value = value;
	p->next = nodes[index];
	nodes[index] = p;
}

void EnlargeIfNeeded(Map *map) {
	if (map->capacity * LOAD_FACTOR > map->size) {
		return;
	}
	int newCapacity = 2 * map->capacity;
	Node **newNodes = (Node **)malloc(newCapacity * sizeof(Node *));
	for (int i = 0; i < newCapacity; i++) {
		newNodes[i] = NULL;
	}
	for (int i = 0; i < map->capacity; i++) {
		Node *p = map->nodes[i];
		while (p != NULL) {
			PutValue(newNodes, newCapacity, p->key, p->value);
			p = p->next;
		}
	}
	map->nodes = newNodes;
	map->capacity = newCapacity;
}

Node *GetNode(Map *map, char key) {
	int index = Hash(key, map->capacity);
	Node *p = map->nodes[index];
	while (p != NULL) {
		if (p->key == key) {
			return p;
		}
		p = p->next;
	}
	return NULL;
}

void Put(Map *map, char key, int value) {
	Node *p = GetNode(map, key);
	if (p) {
		p->value = value;
		return;
	}

	EnlargeIfNeeded(map);
	PutValue(map->nodes, map->capacity, key, value);
	map->size++;
}

int Get(Map *map, char key) {
	Node *p = GetNode(map, key);
	return p == NULL ? -1 : p->value;
}

void Remove(Map *map, char key) {
	int index = Hash(key, map->capacity);
	Node *p = map->nodes[index];
	if (p == NULL) {
		return;
	} else if (p->key == key) {
		map->nodes[index] = p->next;
		free(p);
		return;
	}

	while (p->next != NULL) {
		if (p->next->key == key) {
			Node *q = p->next;
			p->next = q->next;
			free(q);
			break;
		}
		p = p->next;
	}
}

int lengthOfLongestSubstring(char *s) {
	Map *map = NewMap();
	int len = strlen(s);
	int max = 0;
	int i = 0;
	for (int j = 0; j < len; j++) {
		i = MAX(i, Get(map, s[j]));
		max = MAX(max, j - i + 1);
		Put(map, s[j], j + 1);
	}
	return max;
}

int main() {
	printf("%d\n", lengthOfLongestSubstring("abcabcbb"));
	return 0;
}