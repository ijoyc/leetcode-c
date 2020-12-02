/*
* @Author: chenyizhuo
* @Date:   2020-12-01 16:36:54
* @Last Modified by:   chenyizhuo.yizhuoc
* @Last Modified time: 2020-12-02 16:47:08
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split(char *s, char c, int *resultSize) {

	char *p = s;
	int slashCount = 0;
	while (*p) {
		if (*p == c) {
			slashCount++;
		}
		p++;
	}

	char **result = (char **)malloc(sizeof(char *) * (slashCount + 1));
	int index = 0;

	p = s;
	while (*p) {
		char *q = p;
		while (*q && *q != c) {
			q++;
		}
		
		if (p != q) {
			int len = q - p + 1;
			char *current = (char *)malloc(sizeof(char) * len);
			strncpy(current, p, len - 1);
			current[len - 1] = '\0';
			result[index++] = current;
		}
		
		if (*q) {
			p = q + 1;
		} else {
			break;
		}
	}

	result = (char **)realloc(result, sizeof(char *) * index);
	*resultSize = index;
	return result;
}

char *join(char **strings, int length, char c) {
	if (length == 0) {
		char *res = (char *)malloc(sizeof(char) * 2);
		res[0] = '/';
		res[1] = '\0';
		return res;
	}

	int *stringLengths = (int *)malloc(sizeof(int) * length);
	int totalLength = 0;
	for (int i = 0; i < length; i++) {
		stringLengths[i] = strlen(strings[i]);
		totalLength += stringLengths[i];
	}

	totalLength += length;
	char *result = (char *)malloc(sizeof(char) * (totalLength + 1));
	int cur = 0;
	for (int i = 0; i < length; i++) {
		result[cur++] = c;
		strncpy(result + cur, strings[i], stringLengths[i]);
		cur += stringLengths[i];
	}
	result[totalLength] = '\0';

	free(stringLengths);
	return result;
}

char *simplifyPath(char *path) {
	int elementCount = 0;
	char **elements = split(path, '/', &elementCount);
	char **components = (char **)malloc(sizeof(char *) * elementCount);

	int i = 0;
	int j = 0;
	for (int i = 0; i < elementCount; i++) {
		if (strcmp(elements[i], ".") == 0) {
			continue;
		} else if (strcmp(elements[i], "..") == 0) {
			j = j == 0 ? 0 : j - 1;
		} else {
			components[j++] = elements[i];
		}
	}
	char *result = join(components, j, '/');
	for (int i = 0; i < elementCount; i++) {
		free(elements[i]);
	}
	free(elements);
	free(components);

	return result;
}

void splitTest(char *str) {
	int length = 0;
	char **result = split(str, '/', &length);
	printf("length = %d\n", length);
	for (int i = 0; i < length; i++) {
		printf("%s\n", result[i]);
	}

	char *joined = join(result, length, '/');
	printf("%s\n", joined);
}

int main() {
	printf("%s\n", simplifyPath("/home/"));
	printf("%s\n", simplifyPath("/../"));
	printf("%s\n", simplifyPath("/home//foo/"));
	printf("%s\n", simplifyPath("/a/./b/../../c/"));
	printf("%s\n", simplifyPath("///e////d/a/./b/../../c/"));

	// splitTest("/home/");
	// splitTest("/../");
	// splitTest("/home//foo/");
	// splitTest("/a/./b/../../c/");
	return 0;
}