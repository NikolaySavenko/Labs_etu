#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 128

struct badge {
	char name[MAX_NAME_LEN];
	char color;
	char rating;
};
typedef struct badge badges;

typedef struct DUCKDUCK {
	badges ownBadge;
	int pawsCount;
	int gender;
	float weight;
	char favoriteKey;
} duck;

duck *getUserDucks(int *len);

int addDuck(struct DUCKDUCK duckToAdd, duck **duckArray, int len);

int main() {
	int i, len = 0;
	int shouldContinue = 1;
	char buffer[MAX_NAME_LEN];
	int bufLen;
	struct badge duckBadge;
	struct DUCKDUCK newDuck;
	duck *ducks = getUserDucks(&len);

	strcpy(duckBadge.name, "program duck");
	duckBadge.color = 'g';
	duckBadge.rating = 'A';

	newDuck.ownBadge = duckBadge;
	newDuck.pawsCount = 2;
	newDuck.gender = 0;
	newDuck.weight = 3.1f;
	newDuck.favoriteKey = 'a';

	len = addDuck(newDuck, &ducks, len);
	puts("Duck added by program\nWant to add more? (1 - YES;  0 - NO)");
	scanf("%d", &shouldContinue);
	getchar();

	while (shouldContinue) {
		struct badge duckBadgeNew;
		struct DUCKDUCK newCoolDuck;
		printf("Duck number %d\n", len + 1);

		/*new field: name*/
		printf("DUCKDUCK badge name (max=%d):\n", MAX_NAME_LEN);
		fgets(buffer, MAX_NAME_LEN, stdin);
		bufLen = strlen(buffer);
		buffer[bufLen - 1] = '\0';
		strcpy(duckBadgeNew.name, buffer);

		puts("DUCKDUCK badge color (char):");
		scanf("%c", &duckBadgeNew.color);
		getchar();

		puts("DUCKDUCK badge rating  (char):");
		scanf("%c", &duckBadgeNew.rating);
		getchar();

		newCoolDuck.ownBadge = duckBadgeNew;

		puts("DUCKDUCK paws count (int):");
		scanf("%d", &newCoolDuck.pawsCount);
		getchar();

		puts("DUCKDUCK gender  (int) :");
		scanf("%d", &newCoolDuck.gender);
		getchar();

		puts("DUCKDUCK weight  (float) :");
		scanf("%f", &newCoolDuck.weight);
		getchar();

		puts("DUCKDUCK favorite key  (char) :");
		scanf("%c", &newCoolDuck.favoriteKey);
		getchar();

		puts("1 - to continue;   0 - for exit");
		scanf("%d", &shouldContinue);
		getchar();

		len = addDuck(newCoolDuck, &ducks, len);
	}

	printf("All duck ready %d\n", len);
	for (i = 0; i < len; i++) {
		printf("rubber %c %c %s %d %d %f %c\n",
			   ducks[i].ownBadge.color,
			   ducks[i].ownBadge.rating,
			   ducks[i].ownBadge.name,
			   ducks[i].pawsCount,
			   ducks[i].gender,
			   ducks[i].weight,
			   ducks[i].favoriteKey
		);
	}

	return 0;
}

duck *getUserDucks(int *len) {
	duck *items = NULL;/*(duck *)malloc(sizeof (duck));*/
	int shouldContinue = 1;
	puts("Forming initial array");
	while (shouldContinue) {
		struct badge duckBadge;
		struct DUCKDUCK newDuck;
		char buffer[MAX_NAME_LEN];
		int bufLen;
		printf("Duck number %d\n", *len + 1);

		/*new field: name*/
		printf("DUCKDUCK badge name (max=%d):\n", MAX_NAME_LEN);
		fgets(buffer, MAX_NAME_LEN, stdin);
		bufLen=strlen(buffer);
		buffer[bufLen-1]='\0';
		strcpy(duckBadge.name, buffer);

		puts("DUCKDUCK badge color (char):");
		scanf("%c", &duckBadge.color);
		getchar();

		puts("DUCKDUCK badge rating  (char):");
		scanf("%c", &duckBadge.rating);
		getchar();

		newDuck.ownBadge = duckBadge;

		puts("DUCKDUCK paws count (int):");
		scanf("%d", &newDuck.pawsCount);
		getchar();

		puts("DUCKDUCK gender  (int) :");
		scanf("%d", &newDuck.gender);
		getchar();

		puts("DUCKDUCK weight  (float) :");
		scanf("%f", &newDuck.weight);
		getchar();

		puts("DUCKDUCK favorite key  (char) :");
		scanf("%c", &newDuck.favoriteKey);
		getchar();

		puts("1 - to continue;   0 - for exit");
		scanf("%d", &shouldContinue);
		getchar();

		*len = addDuck(newDuck, &items, *len);
	}
	return items;
}

int addDuck(struct DUCKDUCK duckToAdd, duck **duckArray, int len) {
	*duckArray = (duck *) realloc(*duckArray, (len + 1) * sizeof(duck));
	/*duckArray[len] = &duckToAdd;*/
	strcpy((*duckArray)[len].ownBadge.name, duckToAdd.ownBadge.name);
	(*duckArray)[len].ownBadge.color = duckToAdd.ownBadge.color;
	(*duckArray)[len].ownBadge.rating = duckToAdd.ownBadge.rating;
	(*duckArray)[len].weight = duckToAdd.weight;
	(*duckArray)[len].favoriteKey = duckToAdd.favoriteKey;
	(*duckArray)[len].gender = duckToAdd.gender;
	(*duckArray)[len].pawsCount = duckToAdd.pawsCount;
	return len + 1;
}
