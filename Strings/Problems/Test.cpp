#include<stdio.h>
#include<string.h>
#include <iostream>
using namespace std;
#define MaxL 1000001
	int P[MaxL];
int KMP_init(char *B) {
	int i, j;

	P[0] = -1, i = 1, j = -1;
	while(B[i]) {
		while(j >= 0 && B[j+1] != B[i])
			j = P[j];
		if(B[j+1] == B[i])
			++j;
		P[i] = j, ++i;
	}
	return j;
}
main() {
	char s[MaxL];
	while(cin>>s) {
		if(s[0] == '.' && s[1] == '\0')
			break;
		int n = strlen(s), t = KMP_init(s);

		for(int i = 0 ; i < n+1; i++) cout<<P[i]<<' ';
			cout<<endl;
		cout<<t<<endl;
		if(n%(n-t-1) == 0)
			printf("%d\n", n/(n-t-1));
		else
			puts("1");
	}
	return 0;
}