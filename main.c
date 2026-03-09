#include "stdio.h"
#include <string.h>

void compare(FILE* file1, FILE* file2, FILE* temp) {
    char buffer1[100];
    char buffer2[100];
     
    char* ch1 = NULL;
    char* ch2 = NULL;

    int prev1 = ftell(file1);
    int prev2 = ftell(file2);
    
    while (1) {
        prev1 = ftell(file1);
        prev2 = ftell(file2);

        ch1 = fgets(buffer1, 100, file1);
        ch2 = fgets(buffer2, 100, file2);
   
        if (ch1 == NULL && ch2 == NULL) break;
        else if (ch1 == NULL && ch2 != NULL) {
            fputs(buffer2,temp);
            continue;
        }
        else if (ch2 == NULL && ch1 != NULL) {
            fputs(buffer1,temp);
            continue;
        }

        int flag = 0;
        long curr1 = ftell(file1) - prev1;
        long curr2 = ftell(file2) - prev2;
         
        if (curr1 == curr2) {
            for (int i = 0; i < curr1; ++i) {
                if (buffer1[i] != buffer2[i]) flag = 1;
            }

            if (!flag) { 
                fputs(buffer1,temp);
                continue;
            }
        }

        if (flag || curr1 != curr2) {
            int len1 = strcspn(buffer1, "\n");
            buffer1[len1] = 0; 
            int len2 = strcspn(buffer2, "\n");
            buffer2[len2] = 0;

            printf("%s %s\n", buffer1, buffer2);

            buffer1[len1] = '\n'; 
            buffer1[len1 + 1] = '\0';
            buffer2[len2] = '\n';
            buffer2[len2 + 1] = '\0';

            int choice = 0;
            if (scanf("%d", &choice) == 1) {
                switch(choice) {
                    case 1: 
                        fputs(buffer1, temp);
                        fseek(file2, -curr2, SEEK_CUR);
                        break;
                    case 2:
                        fputs(buffer2,temp);
                        fseek(file1, -curr1, SEEK_CUR);
                        break;
                    case 3:
                        fputs(buffer1,temp);
                        break;
                    case 4:
                        fputs(buffer2,temp);
                        break;
                }
            } 
        } 
    }  
}

int main(int argc, char* argv[]) {
    
    if (argc < 3) {
        printf("Not enough file paths. \n");
        return 1;
    }
    
    FILE* file1 = fopen(argv[1], "r");
    FILE* file2 = fopen(argv[2], "r");
    FILE* temp = fopen("temp.txt", "w");
    
    if (file1 == NULL || file2 == NULL || temp == NULL) 
        perror("Couldn't open one of the files./n");
    
    compare(file1, file2, temp);
    
    fclose(file1);
    fclose(file2);
    fclose(temp);

    return 0;
}