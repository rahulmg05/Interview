/************************************STRING************************************/
string reverseString(string s) {
	if (s.length() == 0) {
		return s;
	}

	int start = 0;
	int end = s.length() - 1;

	while (start <= end) {
		char t = s[start];
		s[start] = s[end];
		s[end] = t;

		start++;
		end--;
	}

	return s;
}
/************************************STRING************************************/