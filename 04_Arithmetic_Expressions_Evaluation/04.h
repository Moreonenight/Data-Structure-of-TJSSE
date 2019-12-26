#ifndef _04_H_
#define _04_H_
#include <iostream>
#include <string>

//in coming priority
int icp(char tmp) {
	switch (tmp) {
	case '=':
		return 0;
		break;
	case '(':
		return 8;
		break;
	case '^':
		return 7;
		break;
	case '*':
	case '/':
	case '%':
		return 4;
		break;
	case '+':
	case '-':
		return 2;
		break;
	case ')':
		return 1;
		break;
	}
	return -1;
}

//in stack priority
int isp(char tmp) {
	switch (tmp) {
	case '=':
		return 0;
		break;
	case '(':
		return 1;
		break;
	case '^':
		return 6;
		break;
	case '*':
	case '/':
	case '%':
		return 5;
		break;
	case '+':
	case '-':
		return 3;
		break;
	case ')':
		return 8;
		break;
	}
	return -1;
}

#endif
