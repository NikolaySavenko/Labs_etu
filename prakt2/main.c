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

duck *sortByLexicographicOrder(duck **ducks, int n);

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
		printf("DUCKDUCK badge name (lowercase only and MAX_NAME_LEN=%d):\n", MAX_NAME_LEN);
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
	ducks = sortByLexicographicOrder(&ducks, len);

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
		printf("DUCKDUCK badge name (lowercase only and MAX_NAME_LEN=%d):\n", MAX_NAME_LEN);
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

duck *sortByLexicographicOrder(duck **ducks, int n)
{
	int location;
	duck newElement;
	int i;
	for (i = 1; i < n; i++)
	{
		strcpy(newElement.ownBadge.name, (*ducks[i]).ownBadge.name);
		newElement.ownBadge.rating = (*ducks[i]).ownBadge.rating;
		newElement.ownBadge.color = (*ducks[i]).ownBadge.color;
		newElement.weight = (*ducks[i]).weight;
		newElement.favoriteKey = (*ducks[i]).favoriteKey;
		newElement.gender = (*ducks[i]).gender;
		newElement.pawsCount = (*ducks[i]).pawsCount;
		location = i - 1;
		while(location >= 0 && strcmp((*ducks[location]).ownBadge.name, newElement.ownBadge.name) > 0)
		{
			strcpy((*ducks[location+1]).ownBadge.name, (*ducks[location]).ownBadge.name);
			(*ducks[location+1]).ownBadge.color = (*ducks[location]).ownBadge.color;
			(*ducks[location+1]).ownBadge.rating = (*ducks[location]).ownBadge.rating;
			(*ducks[location+1]).weight = (*ducks[location]).weight;
			(*ducks[location+1]).favoriteKey = (*ducks[location]).favoriteKey;
			(*ducks[location+1]).gender = (*ducks[location]).gender;
			(*ducks[location+1]).pawsCount = (*ducks[location]).pawsCount;
			location = location - 1;
		}
		strcpy((*ducks[location+1]).ownBadge.name, newElement.ownBadge.name);
		(*ducks[location+1]).ownBadge.color = newElement.ownBadge.color;
		(*ducks[location+1]).ownBadge.rating = newElement.ownBadge.rating;
		(*ducks[location+1]).weight = newElement.weight;
		(*ducks[location+1]).favoriteKey = newElement.favoriteKey;
		(*ducks[location+1]).gender = newElement.gender;
		(*ducks[location+1]).pawsCount = newElement.pawsCount;
	}

	return *ducks;
}
