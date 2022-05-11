#include <stdio.h>
#pragma pack(1)

typedef union ADDR_A {
	unsigned number;
	struct  {
		unsigned a0: 8;
		unsigned a1: 8;
		unsigned a2: 8;
		unsigned a3: 8;
	} byte;
	struct {
		unsigned host: 24;
		unsigned web: 7;
		unsigned type: 1;
	} address;
} address_A;

typedef union ADDR_B {
	unsigned number;
	struct {
		unsigned host: 16;
		unsigned web: 14;
		unsigned type: 2;
	} address;
} address_B;

void printAddress(unsigned address);

unsigned int getAdress();

unsigned A2B(unsigned address);

unsigned B2A(unsigned address);

int main() {
	unsigned uint_address;

	uint_address = getAdress();
	puts("");
	printAddress(uint_address);

	if (uint_address >> 31) {
		/*its B type*/
		puts("Converting B->A");
		uint_address = B2A(uint_address);
	} else {
		/*its A type*/
		puts("Converting A->B");
		uint_address = A2B(uint_address);
	}

	printAddress(uint_address);

	return 0;
}

unsigned int getAdress() {
	address_A address;
	unsigned ubytes[4];
	puts("[ADDRESS_INPUT]");
	puts("[ADDRESS_INPUT]0 octet:");
	scanf("%u", &ubytes[0]);
	puts("[ADDRESS_INPUT]1 octet:");
	scanf("%u", &ubytes[1]);
	puts("[ADDRESS_INPUT]2 octet:");
	scanf("%u", &ubytes[2]);
	puts("[ADDRESS_INPUT]3 octet:");
	scanf("%u", &ubytes[3]);

	address.byte.a0 = ubytes[3];
	address.byte.a1 = ubytes[2];
	address.byte.a2 = ubytes[1];
	address.byte.a3 = ubytes[0];

	return address.number;
}

void printAddress(unsigned int address) {
	int i;
	char type;
	address_A bufferA;
	bufferA.number = address;
	if (bufferA.address.type) {
		type = 'B';
	} else {
		type = 'A';
	}

	printf("Your address(type %c):\n", type);

	printf("%u.%u.%u.%u\n", bufferA.byte.a3, bufferA.byte.a2, bufferA.byte.a1, bufferA.byte.a0);

	for(i=31;i>=0;i--) {
		printf("%d",(bufferA.number>>i)&(0x1));
		if (i % 8 == 0 && i > 0) printf(".");
	}

	puts("");
}

unsigned A2B(unsigned int address) {
	address_A source;
	address_B dest;
	source.number = address;

	dest.address.type = 1<<1; /*10 in binary*/
	dest.address.host = source.address.host;
	dest.address.web = source.address.web;
	return dest.number;
}

unsigned B2A(unsigned int address) {
	address_B source;
	address_A dest;
	source.number = address;

	dest.address.type = 0; /*0 in binary*/
	dest.address.host = source.address.host;
	dest.address.web = source.address.web;
	return dest.number;
}
