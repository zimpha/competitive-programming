#include <cstdio>
#include <cstring>

const int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int year, day, month;

inline bool isLeap() {
	return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
}

inline bool isLegal() {
	if (month <= 0 || month > 12) return false;
	if (month == 2) return day > 0 && day <= 28 + isLeap();
	return day > 0 && day <= days[month - 1];
}

inline int toWeekday() {
	int tm = month >= 3 ? (month - 2) : (month + 10);
	int ty = month >= 3 ? year : (year - 1);
	return (ty + ty / 4 - ty / 100 + ty / 400 + (int)(2.6 * tm - 0.2) + day) % 7;
}

int main() {
	scanf("%d%d", &day, &month); year = 2001;
	int ret = toWeekday(); if (ret == 0) ret = 7;
	if (isLegal()) printf("%d\n", ret);
	else puts("Impossible");
	return 0;
}
