#include<stdio.h>
#define MAX_LENGTH 100
void bitStuffing(char *input, char *stuffed) {
int count = 0;
int j = 0;
for (int i = 0; i < strlen(input); i++) {
stuffed[j++] = input[i];

if (input[i] == '1') {
count++;
if (count == 3) {
stuffed[j++] = '0';
count = 0;
}
} else {
count = 0;
}
}
stuffed[j] = '\0';
}

void bitDestuffing(char *stuffed, char *destuffed) {
int count = 0;
int j = 0;
for (int i = 0; i < strlen(stuffed); i++) {
destuffed[j++] = stuffed[i];
if (stuffed[i] == '1') {
count++;
} else {
count = 0;
}
if (count == 3 && stuffed[i + 1] == '0') {
i++;
}
}
destuffed[j] = '\0';
}

int main() 
{
char input[MAX_LENGTH], stuffed[MAX_LENGTH], destuffed[MAX_LENGTH];
printf("The flag which defines the beginning or the end of a frame is 111.\nBitstuffing takes place when this sequence of numbers are found.\n");
printf("Enter a binary string (only 0s and 1s): ");
scanf("%s", input);
bitStuffing(input, stuffed);
printf("Stuffed/Encoded String: %s\n", stuffed);
bitDestuffing(stuffed, destuffed);
printf("Destuffed/Decoded String: %s\n", destuffed);
return 0;
}
