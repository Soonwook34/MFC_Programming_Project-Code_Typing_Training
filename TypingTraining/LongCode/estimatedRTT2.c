#include <stdio.h>
int main() {
int k, n = 1000;
double EstimatedRTT[n], SampleRTT[n], DevRTT[n], TimeoutInterval[n];
int SampleSum = 0;
double MeanRTT[n];
double a = 0.875, b = 0.75;
for(k=1; k<=n; k++) {
if(k<=990)
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
printf("TimeoutInterval[991] = %f\n", TimeoutInterval[991]);
printf("TimeoutInterval[1000] = %f\n", TimeoutInterval[1000]);
printf("EstimatedRTT[991] = %f\n", EstimatedRTT[991]);
printf("EstimatedRTT[1000] = %f\n", EstimatedRTT[1000]);
printf("MeanRTT[991] = %f\n", MeanRTT[991]);
printf("MeanRTT[1000] = %f\n", MeanRTT[1000]);
return 0;
}
