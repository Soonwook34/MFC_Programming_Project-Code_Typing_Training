#include <stdio.h>
int main() {
int k, n = 100;
double EstimatedRTT[n], SampleRTT[n], DevRTT[n], TimeoutInterval[n];
int SampleSum = 0;
double MeanRTT[n];
double a = 0.875, b = 0.75;
for(k=1; k<=n; k++) {
if(k<=90)
SampleRTT[k] = 1;
else
SampleRTT[k] = 2;
}
EstimatedRTT[1] = SampleRTT[1];
DevRTT[1] = 0;
TimeoutInterval[1] = EstimatedRTT[1] + 4 * DevRTT[1];
SampleSum += SampleRTT[1];
MeanRTT[1] = SampleSum/1;
for(k=2; k<=n; k++) {
EstimatedRTT[k] = a * EstimatedRTT[k-1] + (1-a) * SampleRTT[k];
DevRTT[k] = b * DevRTT[k-1] + (1-b) * SampleRTT[k];
TimeoutInterval[k] = EstimatedRTT[k] + 4 * DevRTT[k];
SampleSum += SampleRTT[k];
MeanRTT[k] = (double)SampleSum/(double)k;
}
printf("TimeoutInterval[91] = %f\n", TimeoutInterval[91]);
printf("TimeoutInterval[100] = %f\n", TimeoutInterval[100]);
printf("EstimatedRTT[91] = %f\n", EstimatedRTT[91]);
printf("EstimatedRTT[100] = %f\n", EstimatedRTT[100]);
printf("MeanRTT[91] = %f\n", MeanRTT[91]);
printf("MeanRTT[100] = %f\n", MeanRTT[100]);
return 0;
}
