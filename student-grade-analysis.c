#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_SUBJECTS 10

// Function Prototypes
char calculateGrade(float avg);
void sortDescending(int n, float avg[], char name[][50], int roll[]);
int searchStudent(int roll[], int n, int targetRoll);

int main() {
    int n, sub, i, j, targetRoll, pos;
    float marks[MAX_STUDENTS][MAX_SUBJECTS];
    float total[MAX_STUDENTS], avg[MAX_STUDENTS];
    char grade[MAX_STUDENTS];
    char name[MAX_STUDENTS][50];
    int roll[MAX_STUDENTS];

    printf("Enter number of students: ");
    scanf("%d", &n);
    printf("Enter number of subjects: ");
    scanf("%d", &sub);

    // Input student data
    for(i = 0; i < n; i++) {
        printf("\nEnter name of student %d: ", i+1);
        scanf("%s", name[i]);
        printf("Enter roll number: ");
        scanf("%d", &roll[i]);

        total[i] = 0;
        for(j = 0; j < sub; j++) {
            printf("Enter marks for Subject %d: ", j+1);
            scanf("%f", &marks[i][j]);
            total[i] += marks[i][j];
        }

        avg[i] = total[i] / sub;
        grade[i] = calculateGrade(avg[i]);
    }

    // Display Report
    printf("\n\n--------- STUDENT GRADE REPORT ---------\n");
    printf("Name\tRoll\tTotal\tAverage\tGrade\n");
    for(i = 0; i < n; i++)
        printf("%s\t%d\t%.2f\t%.2f\t%c\n", name[i], roll[i], total[i], avg[i], grade[i]);

    // Ranking Calculation
    sortDescending(n, avg, name, roll);

    printf("\n--------- RANKING (TOPPER FIRST) ---------\n");
    printf("Rank\tName\tRoll\tAverage\n");
    for(i = 0; i < n; i++)
        printf("%d\t%s\t%d\t%.2f\n", i+1, name[i], roll[i], avg[i]);

    // Search student by roll
    printf("\nEnter roll number to search: ");
    scanf("%d", &targetRoll);

    pos = searchStudent(roll, n, targetRoll);
    if(pos == -1)
        printf("Student NOT FOUND!\n");
    else
        printf("Found: %s (Roll %d) -> Average: %.2f, Grade: %c\n",
               name[pos], roll[pos], avg[pos], grade[pos]);

    return 0;
}

// Grade Calculation
char calculateGrade(float avg) {
    if(avg >= 90) return 'A';
    else if(avg >= 80) return 'B';
    else if(avg >= 70) return 'C';
    else if(avg >= 60) return 'D';
    else if(avg >= 40) return 'E';
    else return 'F';
}

// Sort in descending order based on average marks
void sortDescending(int n, float avg[], char name[][50], int roll[]) {
    int i, j, tempRoll;
    float tempAvg;
    char tempName[50];

    for(i = 0; i < n-1; i++) {
        for(j = i+1; j < n; j++) {
            if(avg[j] > avg[i]) {
                // swap avg
                tempAvg = avg[i];
                avg[i] = avg[j];
                avg[j] = tempAvg;

                // swap name
                strcpy(tempName, name[i]);
                strcpy(name[i], name[j]);
                strcpy(name[j], tempName);

                // swap roll
                tempRoll = roll[i];
                roll[i] = roll[j];
                roll[j] = tempRoll;
            }
        }
    }
}

// Linear Search
int searchStudent(int roll[], int n, int targetRoll) {
    for(int i = 0; i < n; i++)
        if(roll[i] == targetRoll)
            return i;
    return -1;
}
