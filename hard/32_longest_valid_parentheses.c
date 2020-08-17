

int longestValidParentheses(char *s) {
  int len = strlen(s);
  // dp[i] = max length of valid parentheses ending at i
  int *dp = (int *)calloc(len, sizeof(int));

  int res = 0;
  for (int i = 1; i < len; i++) {
    if (s[i] == ')') {
      if (s[i - 1] == '(') {
        dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
      } else if (i - dp[i - 1] > 0 && 
        s[i - dp[i - 1] - 1] == '(') {
        int last = i - dp[i - 1] >= 2 ? dp[i - dp[i - 1] - 2] : 0;
        dp[i] = dp[i - 1] + last + 2;
      }
      res = res > dp[i] ? res : dp[i];
    }
  }

  free(dp);

  return res;
}

int max(int a, int b) {
  return a > b ? a : b;
}

int longestValidParentheses2(char *s) {
  int left = 0;
  int right = 0;
  int res = 0;

  int len = strlen(s);
  for (int i = 0; i < len; i++) {
    if (s[i] == '(') {
      left++;
    } else {
      right++;
    }
    if (left == right) {
      res = max(left + right, res);
    } else if (right > left) {
      left = right = 0;
    }
  }

  if (left == right) {
    return res;
  }

  left = right = 0;
  for (int i = len - 1; i >= 0; i--) {
    if (s[i] == '(') {
      left++;
    } else {
      right++;
    }
    if (left == right) {
      res = max(left + right, res);
    } else if (right < left) {
      left = right = 0;
    }
  }

  return res;
}



