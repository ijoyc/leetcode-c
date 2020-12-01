/*
* @Author: chenyizhuo
* @Date:   2020-11-30 20:37:28
* @Last Modified by:   chenyizhuo
* @Last Modified time: 2020-12-01 10:55:42
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void fillBlanks(char *p, int count) {
	for (int i = 0; i < count; i++) {
		// p[i] = '-';
		p[i] = ' ';
	}
}

char **fullJustify(char **words, int wordsSize, int maxWidth, int *returnSize) {
	int capacity = 16;
	int size = 0;
	char **result = (char **)malloc(sizeof(char *) * capacity);

	int *lengths = (int *)malloc(sizeof(int) * wordsSize);
	for (int i = 0;  i< wordsSize; i++) {
		lengths[i] = strlen(words[i]);
	}

	int index = 0;
	while (index < wordsSize) {
		int len = 0;
		int i = index;
		int wordsLength = 0;
		for (; i < wordsSize; i++) {
			if (len + lengths[i] > maxWidth) {
				break;
			}
			len += lengths[i] + 1;
			wordsLength += lengths[i];
		}

		int isLastLine = i == wordsSize;
		int wordCount = i - index;
		int spacesLeft = maxWidth - wordsLength;
		int spacePerWord = wordCount == 1 ? 0 : spacesLeft / (wordCount - 1);
		int extraSpaces = wordCount == 1 ? 0 : spacesLeft % (wordCount - 1);

		char *line = (char *)malloc(sizeof(char) * (maxWidth + 1));
		char *p = line;
		for (int j = index; j < i; j++) {
			strncpy(p, words[j], lengths[j]);
			p += lengths[j];

			int blankCount = 0;
			if (j == i - 1) {
				// last word in this line
				if (isLastLine) {
					// last line
					blankCount = maxWidth - wordsLength - (wordCount - 1);
				} else {
					// index == i - 1: only one word in a line
					blankCount = index == i - 1 ? spacesLeft : 0;
				}
			} else {
				if (isLastLine) {
					blankCount = 1;
				} else {
					blankCount = spacePerWord;
					if (j - index < extraSpaces) {
						blankCount++;
					}
				}
			}
			fillBlanks(p, blankCount);
			p += blankCount;
		}

		line[maxWidth] = '\0';
		if (size == capacity) {
			capacity = 2 * capacity;
			result = (char **)realloc(result, sizeof(char *) * capacity);
		}
		result[size++] = line;

		index = i;
	}

	free(lengths);

	*returnSize = size;
	return result;
}

int main() {
	// char *words[] = {"This", "is", "an", "example", "of", "text", "justification."};
	// char *words[] = {"What","must","be","acknowledgment","shall","be"};
	// char *words[] = {"Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"};
	char *words[] = {"ask","not","what","your","country","can","do","for","you","ask","what","you","can","do","for","your","country"};
	int maxWidth = 16;
	// int maxWidth = 20;
	int len = 0;
	char **result = fullJustify(words, sizeof(words) / sizeof(words[0]), maxWidth, &len);
	printf("count: %d\n", len);
	for (int i = 0; i < len; i++) {
		printf("%s\n", result[i]);
	}
	return 0;
}