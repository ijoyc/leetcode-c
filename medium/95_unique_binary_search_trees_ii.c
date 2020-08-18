
struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

typedef struct {
  int start;
  int end;
  struct TreeNode **list;
  int len;
} Item;

typedef struct {
  int capacity;
  int size;
  Item **list;
} ItemList;

ItemList *newList() {
  ItemList *list = (ItemList *)malloc(sizeof(ItemList));
  list->capacity = 16;
  list->size = 0;
  list->list = (Item **)malloc(sizeof(Item *) * list->capacity);
  return list;
}

Item *newItem(int start, int end, int len, struct TreeNode **list) {
  Item *item = (Item *)malloc(sizeof(Item));
  item->list = list;
  item->start = start;
  item->end = end;
  item->len = len;
  return item;
}

void insertItem(ItemList *list, Item *item) {
  list->list[list->size++] = item;
  if (list->size == list->capacity) {
    list->capacity *= 2;
    list->list = (Item **)realloc(list->list, sizeof(Item *) * list->capacity);
  }
}

struct TreeNode **listWithRange(ItemList *list, int start, int end, int *length) {
  for (int i = 0; i < list->size; i++) {
    Item *item = list->list[i];
    if (item->start == start && item->end == end) {
      *length = item->len;
      return item->list;
    }
  }
  return NULL;
}

struct TreeNode *newNode(int val) {
  struct TreeNode *node = (struct TreeNode *)malloc(sizeof(struct TreeNode));
  node->val = val;
  node->left = node->right = NULL;
  return node;
}

int max(int a, int b) {
  return a > b ? a : b;
}

struct TreeNode **generateSubTrees(ItemList *list, int start, int end, int *returnSize) {
  struct TreeNode **cache = listWithRange(list, start, end, returnSize);
  if (cache) {
    return cache;
  }

  int capacity = 16;
  int size = 0;
  struct TreeNode **result = (struct TreeNode **)malloc(sizeof(struct TreeNode *) * capacity);
  if (start > end) {
    *returnSize = 0;
    return NULL;
  } else if (start == end) {
    *returnSize = 1;
    result[0] = newNode(start);
    return result;
  }

  int totalLength = 0;
  for (int i = start; i <= end; i++) {
    int leftLength = 0;
    struct TreeNode **left = generateSubTrees(list, start, i - 1, &leftLength);
    int rightLength = 0;
    struct TreeNode **right = generateSubTrees(list, i + 1, end, &rightLength);

    int isLeftNull = leftLength == 0;
    int isRightNull = rightLength == 0;
    leftLength = max(1, leftLength);
    rightLength = max(1, rightLength);

    for (int j = 0; j < leftLength; j++) {
      for (int k = 0; k < rightLength; k++) {
        struct TreeNode *root = newNode(i);
        root->left = isLeftNull ? NULL : left[j];
        root->right = isRightNull ? NULL : right[k];
        result[size++] = root;
        if (size == capacity) {
          capacity *= 2;
          result = (struct TreeNode **)realloc(result, sizeof(struct TreeNode *) * capacity);
        }
      }
    }
    totalLength += leftLength * rightLength;
  }

  *returnSize = totalLength;
  insertItem(list, newItem(start, end, totalLength, result));
  return result;
}

struct TreeNode **generateTrees(int n, int *returnSize) {
  ItemList *list = newList();
  return generateSubTrees(list, 1, n, returnSize);
}