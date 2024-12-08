#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char res[100];

void sender() {
int n, i, len;
char frm[100], l[100];
res[0] = '\0';

printf("Enter the number of frames\n");
scanf("%d", &n);
for (i = 0; i < n; i++) {
  printf("Enter the frame %d\n", i + 1);
    scanf("%s", frm);
    len = strlen(frm);
    sprintf(l, "%d", len);
    strcat(l, frm);
    strcat(res, l);
}

printf("The final message is: ");
for (i = 0; i < strlen(res); i++) {
  int frame_len = res[i] - '0';
  printf("[%d: ", frame_len);
  for (int j = i + 1; j <= i + frame_len; j++) {
      printf("%c", res[j]);
  }
  printf("] ");
i += frame_len;
}
printf("\n");
}

void receiver() {
int len, i, j;
printf("Received frames:\n");
for (i = 0; i < strlen(res); i++) {
  len = res[i] - '0';
  for (j = i + 1; j <= i + len; j++) {
     printf("%c", res[j]);
    }
  printf("\n");
   i += len;
  }
}

void main() {
sender();
receiver();
}
