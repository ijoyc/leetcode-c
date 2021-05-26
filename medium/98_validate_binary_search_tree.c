/*
* @Author: chenyizhuo.yizhuoc
* @Date:   2021-05-25 17:09:28
* @Last Modified by:   chenyizhuo.yizhuoc
* @Last Modified time: 2021-05-26 10:35:33
*/

typedef struct {
    int isValid;
    int min;
    int max;
} Result;

Result invalid = { 0, 0, 0 };

Result isValid(struct TreeNode *node) {
    int min = node->val;
    int max = node->val;

    if (node->left) {
        Result left = isValid(node->left);
        if (!left.isValid || left.max >= node->val) {
            return invalid;
        }
        min = left.min;
    }
    if (node->right) {
        Result right = isValid(node->right);
        if (!right.isValid || right.min <= node->val) {
            return invalid;
        }
        max = right.max;
    }

    Result res = { 1, min, max };
    return res;
}

int isValidBST(struct TreeNode *root) {
    if (root == NULL) {
        return 1;
    }

    Result res = isValid(root);
    return res.isValid;
}