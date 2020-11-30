/*
* @Author: chenyizhuo
* @Date:   2020-11-27 21:46:49
* @Last Modified by:   chenyizhuo
* @Last Modified time: 2020-11-30 20:30:41
*/

char *skipBlank(char *s) {
	while (*s == ' ') {
		s++;
	}
	return s;
}

char *skimNumbers(char *s) {
	while (*s >= '0' && *s <= '9') {
		s++;
	}
	return s;
}

int isNumber(char *s) {
	s = skipBlank(s);
	int hasSign = 0;
	if (*s == '+' || *s == '-') {
		s++;
		hasSign = 1;
	}

	char *t = skimNumbers(s);
	int hasInteger = t != s;
	int hasDot = 0;
	if (*t == '.') {
		t++;
		hasDot = 1;
	}

	char *r = skimNumbers(t);
	int hasDecimal = r != t;

	if (!hasInteger && !hasDecimal) {
		return 0;
	}

	int hasE = 0;
	if (*r == 'e') {
		hasE = 1;
		r++;
	}

	if (hasE) {
		int hasESign = 0;
		if (*r == '+' || *r == '-') {
			hasESign = 1;
			r++;
		}

		char *v = skimNumbers(r);
		int hasENumbers = v != r;

		if (hasE && !hasENumbers) {
			return 0;
		}

		r = v;
	}

	r = skipBlank(r);
	int done = *r == '\0';

	return done;
}