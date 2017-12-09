#include <iostream>
using namespace std;
//합병 정렬 함수
void mergeSort3(int *, int);
//합병 함수
void merge3(int *, int, int, int);
//배열 출력 함수
void printArray(int *, int);
//메인 함수
int main() {
int n;
//정렬할 원소의 수 받기
cout<<"원소의 수 : ";
cin>>n;
//정렬할 배열 생성
int a[n] = {0};
//정렬할 원소 받기
cout<<"원소 : ";
for(int i=0; i<n; i++) {
cin>>a[i];
}
//합병 정렬
mergeSort3(a, n);
cout<<"정렬 : ";
//정렬된 배열 출력
printArray(a, n);
return 0;
}
//합병 정렬 함수
void mergeSort3(int a[], int n) {
//합병할 크기
int size;
//합병할 부분 배열의 low, middle, high
int low, mid, high;
//2개, 4개, ...씩 합병하면서 정렬
for(size=1; size<n; size*=2) {
//low, middle, high 설정 후 합병
for(low=0; low<n; low+=size*2) {
high = min(low+(size*2)-1, n-1);
mid = min(low+size-1, n-1);
merge3(a, low, mid, high);
}
}
}
//합병 함수
void merge3(int a[], int low, int mid, int high) {
int i, j, k;
int temp[high-low+1] = {0};
//i는 왼쪽, j는 오른쪽 부분 배열의 index, k는 임시 배열의 index
i = low;
j = mid+1;
k = 0;
//오름차순으로 합병하기
while(i<=mid && j<=high) {
if(a[i]<a[j]) {
temp[k] = a[i];
i++;
}
else {
temp[k] = a[j];
j++;
}
k++;
}
while(i<=mid) {
temp[k] = a[i];
i++;
k++;
}
while(j<=high) {
temp[k] = a[j];
j++;
k++;
}
//임시 배열에서 기존 배열로 복사
for(i=low, k=0; k<high-low+1; i++, k++) {
a[i] = temp[k];
}
}
//배열 출력 함수
void printArray(int a[], int n) {
for(int i=0; i<n; i++) {
cout<<a[i]<<" ";
}
cout<<endl;
}
