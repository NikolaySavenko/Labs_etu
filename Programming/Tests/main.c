#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN 1024
#define MAX_SUBSTRING_LEN 256

/*#define OS_TYPE linux */
#ifdef OS_TYPE
#define CLS system("close")
#else
#define CLS system("cls")
#endif

typedef struct PROCESSOR {
    char *name;
    float clock_speed;
    int tdp;
} PROC;

typedef struct GRAPHICS_CARD {
    char *name;
    int memory;
} GCARD;


typedef struct RANDOM_ACCESS_MEMORY {
    char *name;
    int memory;
    float frequency;
} RANDACCMEM;


typedef struct PC_ACCESSORIES {
    int pc_number;
    PROC cpu;
    GCARD video;
    RANDACCMEM ram;
    float tests[3];
} PC;

PC *addNewPC(PC *pcomps, char *string, int *success, FILE *df, int n);

char *addNewString(char *string, char *manual_input_str);

void outputPC(PC pcomps);

void sortClockSpeed(PC *pc0, int n);

char **simpleSplit(char *str, int length, char sep);

void clearStringArray(char **str, int n);

int newGets(char *s, int lim, char endSymbol);

int hasSubstring(char *str0, char *str1);


int main()
{
    PC *pcomps = NULL;

	char *string = NULL;
	char substring[MAX_LEN];
	char choice_show, choice_add;
	int i, j, count;
	int success;
	int chosen_type;
	FILE *df;
	success = 0;

	if ((string = (char *) malloc(MAX_LEN * sizeof(char) + 1)) != NULL) {
		if ((df = fopen("data.csv", "r")) != NULL) {
			count = 0;
			while (fgets(string, MAX_LEN, df)) {
				count++;
			}

			pcomps = (PC *) malloc(count * sizeof(PC));
			fseek (df, 0, SEEK_SET);
			if (pcomps != NULL) {
				for (i = 0; i < count; i++) {
					pcomps = addNewPC(pcomps, string, &success, df, i);
				}
				fclose(df);
			} else puts("Out if memory! Program terminated");

			printf("Finded %d PC!\n", count);

            printf("\nDo you want add new PC?\n\ny - yes\nn - no\n");
            scanf("%c", &choice_add);
            getchar();

            while (choice_add == 'y') {
                CLS;
                pcomps = (PC*) realloc(pcomps, sizeof(PC) * ++count);
                pcomps = addNewPC(pcomps, string, &success, stdin, count - 1);
                printf("\nDo you want add new PC?\n\ny - yes\nn - no\n");
                scanf("%c", &choice_add);
                getchar();
            }
            puts("");

            printf("Now PC quantity is %d! Would you like to see? \n", count);

            printf("y - yes\nn - no\n\n");
            scanf("%c", &choice_show);
            getchar();

			if (choice_show == 'y') {
                for (i = 0; i < count; i++) {
                    outputPC(pcomps[i]);
                }
            }


            puts("");
			if (success == 1) {
                puts("");
                puts("Search: ");
				puts("1 - cpu name\n2 - video name\n3 - ram name\n");
				scanf("%d", &chosen_type);
				getchar();

				printf("Input substring(MAX_LEN=%d):", MAX_SUBSTRING_LEN);
				newGets(substring, MAX_SUBSTRING_LEN, '\n');
				puts("Output:");
				sortClockSpeed(pcomps, count);
				j = 0;
				for (i = 0; i < count; i++) {
					switch (chosen_type) {
                        case 1:
                            success = hasSubstring(pcomps[i].cpu.name, substring) + 10;
                            break;
                        case 2:
                            success = hasSubstring(pcomps[i].video.name, substring) + 10;
                            break;
                        case 3:
                            success = hasSubstring(pcomps[i].ram.name, substring) + 10;
                            break;
                        default:
                            break;

					}

					if (success > 10) {
                        outputPC(pcomps[i]);
						j++;
					}

					free(pcomps[i].cpu.name);
					free(pcomps[i].video.name);
					free(pcomps[i].ram.name);
				}
				if (j == 0) {
                    puts("No such results");
				}

				free(pcomps);
			}
		}
	}
	free(string);

    return 0;
}


void outputPC(PC pcomps)
{
    puts("");
    printf("PC: %d\n", pcomps.pc_number);
    printf(" %7s | %7s: %15s | %15s: %7.2f | %7s: %5d |\n", "CPU", "name", pcomps.cpu.name, "clock_speed" ,pcomps.cpu.clock_speed, "tdp" ,pcomps.cpu.tdp);
    printf(" %7s | %7s: %15s | %15s: %7d |\n", "VIDEO", "name", pcomps.video.name, "memory", pcomps.video.memory);
    printf(" %7s | %7s: %15s | %15s: %7.2f | %7s: %5d |\n", "RAM", "name", pcomps.ram.name, "frequency" , pcomps.ram.frequency, "memory", pcomps.ram.memory);
    printf(" %7s | %7s: %15.2f | %15s: %7.2f | %7s: %5.2f |", "TESTS", "first", pcomps.tests[0], "second", pcomps.tests[1], "third", pcomps.tests[2]);
}


void clearStringArray(char **str, int n)
{
	int i;

	for (i = 0; i < n; i++) {
		free(str[i]);
		str[i] = NULL;
	}
	free(str);
	str = NULL;
}

PC *addNewPC(PC *pcomps, char *string, int *success, FILE *df, int i)
{
    char **s2;
    char sep;
    char *manual_input_str;
    unsigned int slen;
    unsigned int cpu_name_len, video_name_len, ram_name_len;
    sep = ';';
    if (df == stdin) {
        if ((manual_input_str = (char *) malloc(MAX_SUBSTRING_LEN * sizeof(char) + 1)) != NULL) {
            string[0] = '\0';
            string = addNewString(string, manual_input_str);
        } else {
            puts("Error at memory allocation!\n");
        }
    } else {
        fgets(string, MAX_LEN, df);
        slen = strlen(string);
        string[slen - 1] = '\0';
    }
    free(manual_input_str);
    slen = strlen(string);

    s2 = simpleSplit(string, slen, sep);
    if (s2 != NULL) {

        cpu_name_len = strlen(s2[0]);
        video_name_len = strlen(s2[3]);
        ram_name_len = strlen(s2[5]);

        pcomps[i].cpu.name = (char*) malloc(sizeof(char) * cpu_name_len);
        pcomps[i].video.name = (char*) malloc(sizeof(char) * video_name_len);
        pcomps[i].ram.name = (char*) malloc(sizeof(char) * ram_name_len);

        if (pcomps[i].cpu.name && pcomps[i].video.name && pcomps[i].ram.name) {
            pcomps[i].pc_number = i + 1;
            strcpy(pcomps[i].cpu.name, s2[0]);
            pcomps[i].cpu.clock_speed = atof(s2[1]);
            pcomps[i].cpu.tdp = atoi(s2[2]);
            strcpy(pcomps[i].video.name, s2[3]);
            pcomps[i].video.memory = atoi(s2[4]);
            strcpy(pcomps[i].ram.name, s2[5]);
            pcomps[i].ram.frequency = atof(s2[6]);
            pcomps[i].ram.memory = atoi(s2[7]);
            pcomps[i].tests[0] = atof(s2[8]);
            pcomps[i].tests[1] = atof(s2[9]);
            pcomps[i].tests[2] = atof(s2[10]);

            *success = 1;
        } else puts("Out if memory! Program terminated");
    } else {
        puts("Out if memory! Program terminated");
    }
    return pcomps;
}


char *addNewString(char *string, char *manual_input_str)
{
    unsigned int slen;
    printf("Enter cpu name: ");
    newGets(manual_input_str, MAX_SUBSTRING_LEN, '\n');
    strcat(string, manual_input_str);
    slen = strlen(string);
    string[slen] = ';';
    string[slen + 1] = '\0';
    printf("Enter cpu clock speed: ");
    newGets(manual_input_str, MAX_SUBSTRING_LEN, '\n');
    puts(manual_input_str);
    strcat(string, manual_input_str);
    slen = strlen(string);
    string[slen] = ';';
    string[slen + 1] = '\0';
    printf("Enter cpu tdp: ");
    newGets(manual_input_str, MAX_SUBSTRING_LEN, '\n');
    strcat(string, manual_input_str);
    slen = strlen(string);
    string[slen] = ';';
    string[slen + 1] = '\0';
    printf("Enter video name: ");
    newGets(manual_input_str, MAX_SUBSTRING_LEN, '\n');
    strcat(string, manual_input_str);
    slen = strlen(string);
    string[slen] = ';';
    string[slen + 1] = '\0';
    printf("Enter video memory: ");
    newGets(manual_input_str, MAX_SUBSTRING_LEN, '\n');
    strcat(string, manual_input_str);
    slen = strlen(string);
    string[slen] = ';';
    string[slen + 1] = '\0';
    printf("Enter ram name: ");
    newGets(manual_input_str, MAX_SUBSTRING_LEN, '\n');
    strcat(string, manual_input_str);
    slen = strlen(string);
    string[slen] = ';';
    string[slen + 1] = '\0';
    printf("Enter ram frequency: ");
    newGets(manual_input_str, MAX_SUBSTRING_LEN, '\n');
    strcat(string, manual_input_str);
    slen = strlen(string);
    string[slen] = ';';
    string[slen + 1] = '\0';
    printf("Enter ram memory: ");
    newGets(manual_input_str, MAX_SUBSTRING_LEN, '\n');
    strcat(string, manual_input_str);
    slen = strlen(string);
    string[slen] = ';';
    string[slen + 1] = '\0';
    printf("Enter first test scores: ");
    newGets(manual_input_str, MAX_SUBSTRING_LEN, '\n');
    strcat(string, manual_input_str);
    slen = strlen(string);
    string[slen] = ';';
    string[slen + 1] = '\0';
    printf("Enter second test scores: ");
    newGets(manual_input_str, MAX_SUBSTRING_LEN, '\n');
    strcat(string, manual_input_str);
    slen = strlen(string);
    string[slen] = ';';
    string[slen + 1] = '\0';
    printf("Enter third test scores: ");
    newGets(manual_input_str, MAX_SUBSTRING_LEN, '\n');
    strcat(string, manual_input_str);
    slen = strlen(string);
    string[slen] = ';';
    string[slen + 1] = '\0';
    return string;
}


char **simpleSplit(char *str, int length, char sep)
{
	char **str_array = NULL;
	int i, j, k, m;
	int key, count;
	for (j = 0, m = 0; j < length; j++) {
		if (str[j] == sep) m++;
	}

	key = 0;
	str_array = (char **) malloc((m + 1) * sizeof(char *));
	if (str_array != NULL) {
		for (i = 0, count = 0; i <= m; i++, count++) {
			str_array[i] = (char *) malloc(length * sizeof(char));
			if (str_array[i] != NULL) key = 1;
			else {
				key = 0;
				i = m;
			}
		}
		if (key) {
			k = 0;
			m = 0;
			for (j = 0; j < length; j++) {
				if (str[j] != sep && j != length) str_array[m][j - k] = str[j];
				else {
					str_array[m][j - k] = '\0';
					k = j + 1;
					m++;
				}
			}
		} else {
			clearStringArray(str_array, count);
		}
	}
	return str_array;
}

void sortClockSpeed (PC *pc0, int n) {
	PC tmp_struct;
	int i, j;

	for (i = 0; i < n; i++) {
		tmp_struct = pc0[i];
		for (j = i - 1; j >= 0 && pc0[j].cpu.clock_speed > tmp_struct.cpu.clock_speed; j--) {
			pc0[j + 1] = pc0[j];
		}
		pc0[j + 1] = tmp_struct;
	}
}

int newGets(char *s, int lim, char endSymbol) {
	char c;
	int i;
	for (i = 0; ((c = getchar()) != endSymbol) && (i < lim - 1); i++) *s++ = c;
	*s = '\0';
	return i;
}


int hasSubstring(char *str0, char *str1) {
	char *str0_copy = malloc(sizeof(str0));
	char *str1_copy = malloc(sizeof(str1));
	int i;
	strcpy(str0_copy, str0);
	strcpy(str1_copy, str1);

	for (i = 0; i < strlen(str0_copy); i++) {
		str0_copy[i] = tolower(str0_copy[i]);
	}
	for (i = 0; i < strlen(str1_copy); i++) {
		str1_copy[i] = tolower(str1_copy[i]);
	}
	return strstr(str0_copy, str1_copy) != NULL;
}
