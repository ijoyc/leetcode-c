/*
* @Author: chenyizhuo.yizhuoc
* @Date:   2020-12-04 15:27:58
* @Last Modified by:   chenyizhuo.yizhuoc
* @Last Modified time: 2020-12-11 16:51:32
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int key;
	int value;
	struct Node *next;
} Node;

typedef struct Map {
	Node **nodes;
	int size;
	int capacity;
} Map;

int Hash(int key, int capacity) {
	long result = 17;
	if (key < 0) {
		key = -key;
	}

	while (key) {
		result = result * 31 + (key % 10);
		key /= 10;
	}
	return result % capacity;
}

Map *NewMap(int capacity) {
	Map *map = (Map *)malloc(sizeof(Map));
	map->size = 0;
	map->capacity = capacity;
	map->nodes = (Node **)malloc(sizeof(Node *) * capacity);
	for (int i = 0; i < capacity; i++) {
		map->nodes[i] = NULL;
	}
	return map;
}

Node *GetNode(Map *map, int key, int hash) {
	Node *p = map->nodes[hash];
	while (p) {
		if (p->key == key) {
			return p;
		}
		p = p->next;
	}
	return NULL;
}

void Put(Map *map, int key, int value) {
	int hash = Hash(key, map->capacity);

	Node *p = GetNode(map, key, hash);
	if (p) {
		p->value = value;
		return;
	}

	Node *node = (Node *)malloc(sizeof(Node));
	node->value = value;
	node->key = key;
	node->next = map->nodes[hash];
	map->nodes[hash] = node;
}

int Get(Map *map, int key) {
	int hash = Hash(key, map->capacity);
	Node *p = GetNode(map, key, hash);
	return p ? p->value : 0;
}

int *copy(int *current, int currentSize) {
	int *nums = (int *)malloc(sizeof(int) * currentSize);
	for (int i = 0; i < currentSize; i++) {
		nums[i] = current[i];
	}
	return nums;
}

void printMap(Map *map) {
	for (int i = 0; i < map->capacity; i++) {
		Node *p = map->nodes[i];
		while (p) {
			printf("%d-%d ", p->key, p->value);
			p = p->next;
		}
	}
	printf("\n");
}

void backtracking(int numsSize, int *current, int currentSize, Map *map, int **result, int *size, int *columnSizes) {
	if (currentSize == numsSize) {
		result[*size] = copy(current, currentSize);
		columnSizes[*size] = currentSize;
		*size += 1;
		return;
	}

	for (int i = 0; i < map->capacity; i++) {
		Node *p = map->nodes[i];
		while (p) {
			int value = p->value;
			if (value) {
				Put(map, p->key, value - 1);
				current[currentSize++] = p->key;
				backtracking(numsSize, current, currentSize, map, result, size, columnSizes);
				Put(map, p->key, value);
				currentSize--;
			}
			p = p->next;
		}
	}
}

int **permuteUnique(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
	int max = 1;
	for (int i = 2; i <= numsSize; i++) {
		max *= i;
	}

	int *current = (int *)malloc(sizeof(int) * max);
	int **result = (int **)malloc(sizeof(int *) * max);
	int size = 0;
	int *columnSizes = (int *)malloc(sizeof(int) * max);
	Map *map = NewMap(max);

	for (int i = 0; i < numsSize; i++) {
		Put(map, nums[i], Get(map, nums[i]) + 1);
	}

	backtracking(numsSize, current, 0, map, result, &size, columnSizes);

	*returnSize = size;
	*returnColumnSizes = columnSizes;
	return result;
}


int main() {
	int nums[] = {1, 2, 2, 3, 3, 4};
	int size = sizeof(nums) / sizeof(nums[0]);

	int returnSize = 0;
	int *returnColumnSizes;
	int **result = permuteUnique(nums, size, &returnSize, &returnColumnSizes);

	printf("result: %d\n", returnSize);
	for (int i = 0; i < returnSize; i++) {
		if (returnColumnSizes[i] == 0) {
			printf("[]\n");
			continue;
		}

		for (int j = 0; j < returnColumnSizes[i]; j++) {
			printf("%d ", result[i][j]);
		}
		printf("\n");
	}
	return 0;
}



