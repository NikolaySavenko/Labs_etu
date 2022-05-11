#include <stdio.h>
#include <stdlib.h>

struct badge {
	char color;
	char rating;
};
typedef struct badge badges;

struct duck {
	badges ownBadge;
	int pawsCount;
	int gender;
	float weight;
	char favoriteKey;
};

typedef struct duck ducks;

ducks *getUserDucks(int *len);

int addDuck(struct duck duckToAdd, ducks *duckArray, int len);

int main() {
	int i, len = 0;
	int shouldContinue = 1;
	struct badge duckBadge;
	struct duck newDuck;
	ducks *duck_list = getUserDucks(&len);

	duckBadge.color = 'g';
	duckBadge.rating = 'A';

	newDuck.ownBadge = duckBadge;
	newDuck.pawsCount = 2;
	newDuck.gender = 0;
	newDuck.weight = 3.1f;
	newDuck.favoriteKey = 'a';

	len = addDuck(newDuck, duck_list, len);
	puts("One duck added by program\nWant to add more? (1 - YES;  0 - NO)");
	scanf("%d", &shouldContinue);
	getchar();

	while (shouldContinue) {
		struct badge duckBadgeNew;
		struct duck newCoolDuck;
		printf("Duck number %d\n", len + 1);
		puts("duck badge color (char):");
		scanf("%c", &duckBadgeNew.color);
		getchar();

		puts("duck badge rating  (char):");
		scanf("%c", &duckBadgeNew.rating);
		getchar();

		newCoolDuck.ownBadge = duckBadgeNew;

		puts("duck paws count (int):");
		scanf("%d", &newCoolDuck.pawsCount);
		getchar();

		puts("duck gender  (int) :");
		scanf("%d", &newCoolDuck.gender);
		getchar();

		puts("duck weight  (float) :");
		scanf("%f", &newCoolDuck.weight);
		getchar();

		puts("duck favorite key  (char) :");
		scanf("%c", &newCoolDuck.favoriteKey);
		getchar();

		puts("1 - to continue;   0 - for exit");
		scanf("%d", &shouldContinue);
		getchar();

		addDuck(newCoolDuck, duck_list, len);
		len++;
	}

	printf("All ducks ready %d\n", len);
	for (i = 0; i < len; i++) {
		printf("rubber %c %c %d %d %f %c\n",
		 duck_list[i].ownBadge.color,
		 duck_list[i].ownBadge.rating,
		 duck_list[i].pawsCount,
		 duck_list[i].gender,
		 duck_list[i].weight,
		 duck_list[i].favoriteKey
		 );
	}
	if(duck_list) free(duck_list);
	return 0;
}

ducks *getUserDucks(int *len) {
	ducks* items = (ducks *)malloc(sizeof (ducks));
	int shouldContinue = 1;
	int length = 0;
	puts("Forming initial array");
	while (shouldContinue) {
		struct badge duckBadge;
		struct duck newDuck;
		printf("Duck number %d\n", length + 1);
		puts("duck badge color (char):");
		scanf("%c", &duckBadge.color);
		getchar();

		puts("duck badge rating  (char):");
		scanf("%c", &duckBadge.rating);
		getchar();

		newDuck.ownBadge = duckBadge;

		puts("duck paws count (int):");
		scanf("%d", &newDuck.pawsCount);
		getchar();

		puts("duck gender  (int) :");
		scanf("%d", &newDuck.gender);
		getchar();

		puts("duck weight  (float) :");
		scanf("%f", &newDuck.weight);
		getchar();

		puts("duck favorite key  (char) :");
		scanf("%c", &newDuck.favoriteKey);
		getchar();

		puts("1 - to continue;   0 - for exit");
		scanf("%d", &shouldContinue);
		getchar();

		items[length] = newDuck;
		length++;
	}
	*len = length;
	return items;
}

int addDuck(struct duck duckToAdd, ducks *duckArray, int len) {
	duckArray = realloc(duckArray, (len + 1) * sizeof(ducks));
	duckArray[len] = duckToAdd;
	return len + 1;
}
