#include <stdio.h>
//메인 함수입니다
int main(void) {
int i, sum = 0, n = 10;
int arr[n];
for(i=0; i<n; i++) {
printf("%d번째 숫자를 입력해주세요 : ", i+1);
scanf("%d", &arr[i]);
sum += arr[i];
}
printf("10개 숫자의 합은 %d입니다.\n", sum);
return 0;
}
