#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 256

#if defined(__linux) || defined(__linux__)
#define CLS system("clear")
#else
#define CLS system("cls")
#endif

typedef struct DUCKBADGE {
	char *name;
	char *type;
} duck_badge;

typedef struct DUCKDUCK {
	duck_badge badge;
	/*char *name;
	char *type;*/
	int position[2];
	float weight;
	float height;
	int paws_count;
	int wings_count;
} duck;

void show_info();

int load_data(duck **ducksDest, char **filename);

void save_data(duck **ducks, int count);

int add_data(duck **ducks, int count, char *templates_file);

char **simple_split(char *str, int length, char sep);

void ClearStringArray(char **str, int n);

int new_gets(char *s, int lim, char endSymbol);

void show_data(duck **ducks, int count);

void edit_data(duck **ducks, int count, char **templates_file);

int delete_data(duck **ducks, int count);

void search_data(duck **ducks, int count);

void sort_data(duck **ducks, int count);

duck *get_new_duck(char **templates_file);

void free_duck(duck *target);

void swap_data(duck **ducks, int count, int index0, int index1);

void print_duck(duck *target_duck);

void free_data(duck **ducks, int count);

int main() {
	duck *ducks = NULL;
	char *database_filename = NULL;
	char *samples_filename = NULL;
	int ducks_count;
	int state;

	database_filename = (char *) malloc(MAX_LEN * sizeof (char));
	samples_filename = (char *) malloc(MAX_LEN * sizeof (char));
	strcpy(database_filename, "data.csv");
	strcpy(samples_filename, "samples.csv");
	ducks_count = load_data(&ducks, &database_filename);
	if (ducks_count >= 0 && database_filename != NULL) {
		do {
			printf("[DATABASE] %s\n", database_filename);
			printf("[SAMPLES] %s\n", samples_filename);
			puts("");
			puts("0: INFO");
			puts("1: ADD");
			puts("2: EDIT");
			puts("3: DELETE");
			puts("4: SHOW");
			puts("5: SEARCH");
			puts("6: SORT");
			puts("7: EXIT");
			puts("---EXTRA---");
			puts("10: load database from file");
			puts("11: save database to file");
			puts("12: load samples from file");
			puts("");
			scanf("%d", &state);

			switch (state) {
				case 0:
					CLS;
					show_info();
					getchar();
					break;
				case 1:
					CLS;
					ducks_count = add_data(&ducks, ducks_count, samples_filename);
					getchar();
					break;
				case 2:
					CLS;
					puts("EDIT");
					edit_data(&ducks, ducks_count, &samples_filename);
					break;
				case 3:
					puts("DELETE");
					ducks_count = delete_data(&ducks, ducks_count);
					getchar();
					break;
				case 4:
					CLS;
					puts("SHOW");
					show_data(&ducks, ducks_count);
					getchar();
					break;
				case 5:
					CLS;
					puts("SEARCH");
					search_data(&ducks, ducks_count);
					break;
				case 6:
					CLS;
					puts("SORT");
					sort_data(&ducks, ducks_count);
					getchar();
					break;
				case 7:
					puts("EXIT");
					break;
				case 10:
					CLS;
					puts("READ");
					printf("Input new database database_filename [MAX_LEN=%d]\n", MAX_LEN);
					getchar();
					new_gets(database_filename, MAX_LEN, '\n');
					ducks_count = load_data(&ducks, &database_filename);
					if (ducks_count > 0) {
						puts("Success");
					}
					break;
				case 11:
					CLS;
					puts("SAVE");
					save_data(&ducks, ducks_count);
					break;
				case 12:
					CLS;
					puts("READ SAMPLES");
					printf("Input new samples database_filename [MAX_LEN=%d]\n", MAX_LEN);
					getchar();
					new_gets(samples_filename, MAX_LEN, '\n');
					break;
				default:
					puts("Incorrect key!");
					getchar();
					break;
			}
			if (ducks_count < 0) {
				state = 7;
				puts("memory error occurs");
			} else {
				puts("Press ENTER to continue");
				getchar();
				CLS;
			}
		} while (state != 7);
	} else puts("Error while file loading");

	free_data(&ducks, ducks_count);

	return 0;
}

void ClearStringArray(char **str, int n) {
	int i;

	for (i = 0; i < n; i++) {
		free(str[i]);
		str[i] = NULL;
	}
	free(str);
	str = NULL;
}

char **simple_split(char *str, int length, char sep) {
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
				if (str[j] != sep) str_array[m][j - k] = str[j];
				else {
					str_array[m][j - k] = '\0';
					k = j + 1;
					m++;
				}
			}
		} else {
			ClearStringArray(str_array, count);
		}
	}
	return str_array;
}

int new_gets(char *s, int lim, char endSymbol) {
	char c;
	int i;
	for (i = 0; ((c = getchar()) != endSymbol) && (i < lim - 1); i++, s++) *s = c;
	*s = '\0';
	return i;
}

int load_data(duck **ducksDest, char **filename) {
	char **s2 = NULL;
	char *string = NULL;
	char sep;
	FILE *df;
	duck *ducks = NULL;
	int slen, i, j;
	int count = 0;
	if ((string = (char *) malloc(MAX_LEN * sizeof(char) + 1)) != NULL) {
		if ((df = fopen(*filename, "r")) != NULL) {
			sep = ';';
			while (fgets(string, MAX_LEN, df)) {
				count++;
			}

			ducks = (duck *) malloc(count * sizeof(duck));
			fseek(df, 0, SEEK_SET);
			if (ducks != NULL) {
				for (i = 0; i < count; i++) {
					fgets(string, MAX_LEN, df);
					slen = strlen(string);
					string[slen - 1] = '\0';
					slen = strlen(string);

					s2 = simple_split(string, slen, sep);
					if (s2 != NULL) {
						for (j = 0; j < 7; j++) {
							if (s2[j] == NULL) {
								for (i = j - 1; j >= 0; j--) free(s2[i]);
								i = count;
								j = 7;
							}
						}
						if (i != count) {
							ducks[i].badge.name = s2[0];
							ducks[i].badge.type = s2[1];
							ducks[i].position[0] = atoi(s2[2]);
							ducks[i].position[1] = atoi(s2[3]);
							ducks[i].weight = atof(s2[4]);
							ducks[i].height = atof(s2[5]);
							ducks[i].paws_count = atoi(s2[6]);
							ducks[i].wings_count = atoi(s2[7]);
							for (j = 2; j < 8; j++) free(s2[j]);
						} else {
							puts("Out if memory! Program terminated");
							count = -1;
						}
					} else {
						puts("Out if memory! Program terminated");
						ClearStringArray(s2, 8);
						count = -1;
					}
				}
				fclose(df);
			} else {
				puts("Out if memory! Program terminated");
				count = -1;
			}
		}
	}
	*ducksDest = ducks;
	return count;
}

int add_data(duck **ducks, int count, char *templates_file) {
	duck *local = NULL;
	duck *samples = NULL;
	int i, samples_count;
	samples_count = load_data(&samples, &templates_file);
	/*if samples not loaded it just not be presented; program can be continued as normal*/
	puts("0 - custom");
	for (i = 0; i < samples_count; i++) {
		printf("%d - ", i + 1);
		print_duck(&samples[i]);
	}
	getchar();
	puts("Choose:");
	scanf("%d", &i);
	*ducks = (duck *) realloc(*ducks, (count + 1) * sizeof(duck));
	if (*ducks != NULL) {
		if (i == 0) {
			getchar();
			local = get_new_duck(&templates_file);
			if (local != NULL) {
				(*ducks)[count] = *local;
				count++;
			} else {
				puts("Memory alloc error");
				count = -1;
			}
		} else if (i > 0 && i - 1 < samples_count) {
			/*from templates*/
			(*ducks)[count] = samples[i - 1];
			count++;
		} else {
			puts("No duck selected");
		}
	} else {
		puts("Memory alloc error");
		count = - 1;
		/*it means error*/
	}
	return count;
}

void show_data(duck **ducks, int count) {
	int i;
	for (i = 0; i < count; i++) {
		printf("Duck# %d name: %s type %s pos: %d:%d w: %f h: %f paws %d wings %d\n ",
			   i,
			   (*ducks)[i].badge.name,
			   (*ducks)[i].badge.type,
			   (*ducks)[i].position[0],
			   (*ducks)[i].position[1],
			   (*ducks)[i].weight,
			   (*ducks)[i].height,
			   (*ducks)[i].paws_count,
			   (*ducks)[i].wings_count
		);
	}
}

void edit_data(duck **ducks, int count, char **templates_file) {
	int choosen;
	duck *new_duck = NULL;
	show_data(ducks, count);
	puts("Input duck index to edit:");
	scanf("%d", &choosen);
	getchar();
	if (choosen < count) {
		new_duck = get_new_duck(templates_file);
		if (new_duck != NULL) {
			(*ducks)[choosen] = *new_duck;
			puts("Edited duck:");
			print_duck(&(*ducks)[choosen]);
		}
	} else puts("i should be < count");
}

duck *get_new_duck(char **templates_file) {
	duck *new_duck = NULL;
	duck *samples = NULL;
	int i, samples_count;
	char *buffer;
	CLS;
	samples_count = load_data(&samples, templates_file);
	new_duck = (duck *) malloc(sizeof (duck));
	buffer = (char *) malloc(MAX_LEN * sizeof(char));
	show_data(&samples, samples_count);
	if (new_duck != NULL) {
		new_duck->badge.name = (char *) malloc(MAX_LEN * sizeof(char));
		new_duck->badge.type = (char *) malloc(MAX_LEN * sizeof(char));

		if (new_duck->badge.name == NULL || new_duck->badge.type == NULL) {
			if (new_duck->badge.name != NULL) free(new_duck->badge.name);
			if (new_duck->badge.type != NULL) free(new_duck->badge.type);
			free(new_duck);
			new_duck = NULL;
			puts("memory allocation error");
		} else {
			puts("[FEATURE TIP] You can input index of sample to insert value from sample");

			printf("Adding new duck with name[MAX_LEN=%d](or index of sample):\n", MAX_LEN);
			new_gets(buffer, MAX_LEN, '\n');
			i = atoi(buffer);
			if (i >= 0 && i < samples_count) {
				new_duck->badge.name = samples[i].badge.name;
			} else {
				new_duck->badge.name = buffer;
			}

			printf("With type[MAX_LEN=%d](or index of sample):\n", MAX_LEN);
			new_gets(buffer, MAX_LEN, '\n');
			i = atoi(buffer);
			if (i > 0 && i <= samples_count) {
				new_duck->badge.type = samples[i].badge.type;
			} else {
				new_duck->badge.type = buffer;
			}

			puts("Pos X of duck: ");
			scanf("%d", &new_duck->position[0]);
			puts("Pos Y of duck: ");
			scanf("%d", &new_duck->position[1]);
			puts("Weight of duck: ");
			scanf("%f", &new_duck->weight);
			puts("Height of duck: ");
			scanf("%f", &new_duck->height);
			puts("Paws count of duck: ");
			scanf("%d", &new_duck->paws_count);
			puts("Wings count of duck: ");
			scanf("%d", &new_duck->wings_count);
		}
	} else {
		puts("memory allocation error");
		free(new_duck);
		new_duck = NULL;
	}
	return new_duck;
}

void print_duck(duck *target_duck) {
	printf("name: %s type %s pos: %d:%d w: %f h: %f paws %d wings %d\n ",
		   target_duck->badge.name,
		   target_duck->badge.type,
		   target_duck->position[0],
		   target_duck->position[1],
		   target_duck->weight,
		   target_duck->height,
		   target_duck->paws_count,
		   target_duck->wings_count
	);
}

int delete_data(duck **ducks, int count) {
	int choosen;
	show_data(ducks, count);
	puts("Input duck index to delete:");
	scanf("%d", &choosen);
	if (choosen < count) {
		puts("Deleting duck...");
		print_duck(&(*ducks)[choosen]);
		while (choosen < count - 1) {
			swap_data(ducks, count, choosen, choosen + 1);
			choosen++;
		}
		free_duck(&(*ducks)[count - 1]);
		count--;
	} else puts("i should be < count");
	return count;
}

void free_duck(duck *target) {
	if (target != NULL) {
		if (target->badge.name != NULL) {
			free(target->badge.name);
		}
		if (target->badge.type != NULL) {
			free(target->badge.type);
		}
	}
}

void swap_data(duck **ducks, int count, int index0, int index1) {
	duck temp;
	if (index0 < count && index1 < count) {
		temp.badge.name = (*ducks)[index0].badge.name;
		temp.badge.type = (*ducks)[index0].badge.type;
		temp.position[0] = (*ducks)[index0].position[0];
		temp.position[1] = (*ducks)[index0].position[1];
		temp.weight = (*ducks)[index0].weight;
		temp.height = (*ducks)[index0].height;
		temp.paws_count = (*ducks)[index0].paws_count;
		temp.wings_count = (*ducks)[index0].wings_count;

		(*ducks)[index0].badge.name = (*ducks)[index1].badge.name;
		(*ducks)[index0].badge.type = (*ducks)[index1].badge.type;
		(*ducks)[index0].position[0] = (*ducks)[index1].position[0];
		(*ducks)[index0].position[1] = (*ducks)[index1].position[1];
		(*ducks)[index0].weight = (*ducks)[index1].weight;
		(*ducks)[index0].height = (*ducks)[index1].height;
		(*ducks)[index0].paws_count = (*ducks)[index1].paws_count;
		(*ducks)[index0].wings_count = (*ducks)[index1].wings_count;

		(*ducks)[index1].badge.name = temp.badge.name;
		(*ducks)[index1].badge.type = temp.badge.type;
		(*ducks)[index1].position[0] = temp.position[0];
		(*ducks)[index1].position[1] = temp.position[1];
		(*ducks)[index1].weight = temp.weight;
		(*ducks)[index1].height = temp.height;
		(*ducks)[index1].paws_count = temp.paws_count;
		(*ducks)[index1].wings_count = temp.wings_count;
	}
}

void search_data(duck **ducks, int count) {
	int choosen;
	int value_int;
	float value_float;
	int i;
	char *string = NULL;
	puts("Choose data type");
	puts("--------------");
	puts("0 - name");
	puts("1 - type");
	puts("2 - position_X");
	puts("3 - position_Y");
	puts("4 - paws_count");
	puts("5 - wings_count");
	puts("6 - weight");
	puts("7 - height");
	puts("any - exit");
	puts("--------------");

	scanf("%d", &choosen);
	getchar();

	string = (char *) malloc(MAX_LEN * sizeof (char));
	if (choosen < 2) {
		if (string != NULL) {
			puts("Input string");
			new_gets(string, MAX_LEN, '\n');
		} else puts("Mem alloc error");
	} else if (choosen < 6) {
		puts("Input int value");
		scanf("%d", &value_int);
	} else if (choosen < 8) {
		puts("Input float value");
		scanf("%f", &value_float);
	}
	puts("");
	for (i = 0; i < count; i++) {
		if ((choosen == 0 && strcmp(string, (*ducks)[i].badge.name) == 0) ||
				(choosen == 1 && strcmp(string, (*ducks)[i].badge.type) == 0) ||
				(choosen == 2 && (*ducks)[i].position[0] == value_int) ||
				(choosen == 3 && (*ducks)[i].position[1] == value_int) ||
				(choosen == 4 && (*ducks)[i].paws_count == value_int) ||
				(choosen == 5 && (*ducks)[i].wings_count == value_int) ||
				(choosen == 6 && (*ducks)[i].weight == value_float) ||
				(choosen == 7 && (*ducks)[i].height == value_float)
		) {
			print_duck(&(*ducks)[i]);
		}
	}
	puts("");
	puts("Done...");
	if (choosen > 1 && choosen < 8) {
		getchar();
	}
}

void sort_data(duck **ducks, int count) {
	int choosen, vector;
	int i, j;
	puts("Choose data type");
	puts("--------------");
	puts("0 - name");
	puts("1 - type");
	puts("2 - position_X");
	puts("3 - position_Y");
	puts("4 - paws_count");
	puts("5 - wings_count");
	puts("6 - weight");
	puts("7 - height");
	puts("any - exit");
	puts("--------------");

	scanf("%d", &choosen);

	puts("Choose sort vector:");
	puts("--------------");
	puts("0 - down");
	puts("1 - up");
	puts("--------------");

	scanf("%d", &vector);
	puts("Sorting...");
	for (i = 0; i < count - 1; ++i) {
		for (j = 0; j < count - i - 1; ++j) {
			if (vector == 0) {
				if ((choosen == 0 && strcmp((*ducks)[j].badge.name, (*ducks)[j + 1].badge.name) > 0) ||
					(choosen == 1 && strcmp((*ducks)[j].badge.type, (*ducks)[j + 1].badge.type) > 0) ||
					(choosen == 2 && (*ducks)[j].position[0] > (*ducks)[j + 1].position[0] > 0) ||
					(choosen == 3 && (*ducks)[j].position[1] > (*ducks)[j + 1].position[1]) ||
					(choosen == 4 && (*ducks)[j].paws_count > (*ducks)[j + 1].paws_count) ||
					(choosen == 5 && (*ducks)[j].wings_count > (*ducks)[j + 1].wings_count) ||
					(choosen == 6 && (*ducks)[j].weight > (*ducks)[j + 1].weight) ||
					(choosen == 7 && (*ducks)[j].height > (*ducks)[j + 1].height)) {
					swap_data(ducks, count, j, j + 1);
					printf("%d<->%d\n", j, j + 1);
				}
			} else {
				if ((choosen == 0 && strcmp((*ducks)[j].badge.name, (*ducks)[j + 1].badge.name) < 0) ||
					(choosen == 1 && strcmp((*ducks)[j].badge.type, (*ducks)[j + 1].badge.type) < 0) ||
					(choosen == 2 && (*ducks)[j].position[0] < (*ducks)[j + 1].position[0] > 0) ||
					(choosen == 3 && (*ducks)[j].position[1] < (*ducks)[j + 1].position[1]) ||
					(choosen == 4 && (*ducks)[j].paws_count < (*ducks)[j + 1].paws_count) ||
					(choosen == 5 && (*ducks)[j].wings_count < (*ducks)[j + 1].wings_count) ||
					(choosen == 6 && (*ducks)[j].weight < (*ducks)[j + 1].weight) ||
					(choosen == 7 && (*ducks)[j].height < (*ducks)[j + 1].height)) {
					swap_data(ducks, count, j, j + 1);
					printf("%d<->%d\n", j, j + 1);
				}
			}
		}
	}
	puts("Done");
}

void free_data(duck **ducks, int count) {
	int i;
	for (i = 0; i < count; i++) {
		free_duck(&(*ducks)[i]);
	}
	if (*ducks != NULL) {
		free(*ducks);
	}
}

void save_data(duck **ducks, int count) {
	char *filename = NULL;
	char *buffer = NULL;
	int buffer_len;
	int i;
	FILE *df;
	filename = (char *) malloc(MAX_LEN * sizeof (char));
	if (filename != NULL) {
		printf("Input filename [MAX_LEN=%d]\n", MAX_LEN);
		getchar();
		new_gets(filename, MAX_LEN, '\n');
		puts("");
		df = fopen(filename, "w");
		if (df != NULL) {
			puts("Opened...");
			for (i = 0; i < count; i++) {
				printf("Writing duck #%d\n", i);
				buffer_len = snprintf (NULL, 0, "%s;%s;%d;%d;%f;%f;%d;%d\n",
						   (*ducks)[i].badge.name,
						   (*ducks)[i].badge.type,
						   (*ducks)[i].position[0],
						   (*ducks)[i].position[1],
						   (*ducks)[i].weight,
						   (*ducks)[i].height,
						   (*ducks)[i].paws_count,
						   (*ducks)[i].wings_count);
				buffer = (char *) malloc(buffer_len * sizeof (char));
				if (buffer != NULL) {
					snprintf (buffer, buffer_len + 1, "%s;%s;%d;%d;%f;%f;%d;%d\n",
							  (*ducks)[i].badge.name,
							  (*ducks)[i].badge.type,
							  (*ducks)[i].position[0],
							  (*ducks)[i].position[1],
							  (*ducks)[i].weight,
							  (*ducks)[i].height,
							  (*ducks)[i].paws_count,
							  (*ducks)[i].wings_count);
					if (fputs(buffer, df) != EOF) {
						puts("Success");
					}
					free(buffer);
				} else {
					puts("Error at memory allocation");
				}
			}
			if (fclose(df) == EOF) {
				puts("Error closing!");
			} else {
				puts("Closing...");
			}
		} else {
			puts("Cannot create file");
		}
		puts("");
		free(filename);
	} else {
		puts("Error at memory allocation");
	}
}

void show_info() {
	puts("                                                /\\\n"
		 "                                               (__)\n"
		 "            /\\\n"
		 "           (__)                  ;;;;;;;\n"
		 "                              ;;;;;;;;;;;;;                      /\\\n"
		 "                             ;;;;;;;;;;;;;;;                    (__)\n"
		 "                            ;;;;;;;;( +);dmmm\n"
		 "                           ;;;;;;;;;;;;;mMMMMMmmmm\n"
		 "                    /\\    ;;;;;;;;;;;;;;;WWwwwwwww\n"
		 "                   (__)   ;;;;;;;;;;;;;;;;;;;");
	puts("                           ;;;;;;;;;;;;;;;;;\n"
		 "                               ;;;;;;;;;;          /\\\n"
		 "    /\\                       ;;;;;;;;;;;;;        (__)\n"
		 "   (__)                    ;;;;;;;;;;;;;;;;;;\n"
		 "                         ;;;;;;;;}};;;;;;;;;;;}\n"
		 "                       ;;;;;;;;;;;}};;;;;;;;;;}}}\n"
		 "           ;         ;;;;;;;;;;;;}}};;;;;;;;;;}}}}}\n"
		 "          ;;;      ;;;;;;;;;;;;}}}};;;;;;;;;;;}}}}}}\n"
		 "         ;;;;;;  ;;;;;{{;;;;}}}}}};;;;;;;;;;;; }}}}}}");
	puts("          ;;;;;;;;;;;;;{}}}}}}}};;;;;;;;/\\;;;                 /\\\n"
		 "         /\\ ;;;;;/\\;;;;;;;;;;;;;;;;;;;;/00\\;   /\\            (__)\n"
		 "        000\\   ;/00\\/\\;;;;;;;;/\\;;;;;;/0000\\/\\/000\n"
		 "        0000\\/\\/000000\\;;/\\;;/00\\/\\/\\/000000000000\n"
		 "        ===============\\/==\\/=====================\n"
		 "         ========================================\n"
		 "          {}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}\n"
		 "     /\\    ++++++++++++++++++++++++++++++++++++\n"
		 "    (__)    ++++++++++++++++++++++++++++++++++         /\\\n");
	puts("              ==============================          (__)\n"
		 "                {{{}{}{}{}{}{}{}{}{}{}{}}}\n"
		 " ))|///|\\))((|\\--==================--////||\\(((|//))\\|///))((//|//\\\n"
		 " \\///|))(((|//|\\/))|//|\\/\\))(//\\/\\||(()(((\\/||///|\\/|\\///||//|\\/))((/");
	puts("");
	puts("Super program to coordinate ducks");
	puts("");
}
