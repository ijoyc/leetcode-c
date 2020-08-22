/*
* @Author: yizhuoc
* @Date:   2020-08-21 16:12:14
* @Last Modified by:   cyz
* @Last Modified time: 2020-08-22 11:41:01
*/

int helper_tle(char *s, char **wordDict, int *lengths, int wordDictSize) {
  if (!*s) {
    return 1;
  }
  for (int i = 0; i < wordDictSize; i++) {
    if (strncmp(wordDict[i], s, lengths[i]) == 0 && helper(s + lengths[i], wordDict, lengths, wordDictSize)) {
      return 1;
    }
  }
  return 0;
}

int isWordInDict(char *s, int i, int j, char **wordDict, int *lengths, int wordDictSize) {
  int len = j - i + 1;
  for (int k = 0; k < wordDictSize; k++) {
    if (lengths[k] == len && strncmp(s + i, wordDict[k], len) == 0) {
      return 1;
    }
  }
  return 0;
}

int helper(char *s, char **wordDict, int *lengths, int wordDictSize) {
  int sLength = strlen(s);
  int dp[sLength][sLength];

  memset(dp, 0, sLength * sLength * sizeof(int));
  
  for (int l = 1; l <= sLength; l++) {
    for (int i = 0; i < sLength - l + 1; i++) {
      int j = i + l - 1;
      int inDict = isWordInDict(s, i, j, wordDict, lengths, wordDictSize);
      if (inDict) {
        dp[i][j] = 1;
      } else {
        for (int k = i; k < j; k++) {
          if (dp[i][k] && dp[k + 1][j]) {
            dp[i][j] = 1;
            break;
          }
        }
      }
    }
  }

  return dp[0][sLength - 1];
}

int wordBreak(char *s, char **wordDict, int wordDictSize) {
  if (!wordDictSize) {
    return 0;
  }
  int lengths[wordDictSize];
  for (int i = 0; i < wordDictSize; i++) {
    lengths[i] = strlen(wordDict[i]);
  }
  return helper(s, wordDict, lengths, wordDictSize);
}