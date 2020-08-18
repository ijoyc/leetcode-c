

int numDecodings(char * s) {
  int len = strlen(s);
  // case "01"
  if (!len || s[0] == '0') {
    return 0;
  }

  int first = 1;
  int second = 1;
  // "case 0" (actually excluded by previous check)
  int res = s[0] >= '1' && s[0] <= '9';
  for (int i = 1; i < len; i++) {
    // if current number is 0, it must be associated with the previous 1 or 2
    // the total number of decoding should go back, too
    if (s[i] == '0') {
      if (s[i - 1] == '0' || s[i - 1] > '2') {
        return 0;
      }
      res = second;
      first = second;
      continue;
    }
    
    if ((s[i - 1] == '1' && s[i] != '0') || (s[i - 1] == '2' && s[i] > '0' && s[i] <= '6')) {
      res = first + second;
    } else {
      res = first;
    }
    second = first;
    first = res;
  }
  return res;
}