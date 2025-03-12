#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>

#define TABLE_SIZE 10

struct HashTable
{
    char key[100]; // untuk Key/Value
    struct HashTable *next;
}ht[TABLE_SIZE];

// fungsi inisialisasi Hash Tabel
void initializationHT()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        strcpy(ht[i].key, ""); // set data kosong
        ht[i].next = NULL;
    }
}

int StoI(char key[])
{
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        sum += key[i]; // sum of ASCII values of charater
    }
    return sum;
}




int midSquareHash(char key[])
{
    int intKey = StoI(key);
    int square = intKey * intKey;
    return (square / 100) % TABLE_SIZE;
}



int foldingHash(char key[])
{
    int intKey = StoI(key);
    int sum = 0;
    while (intKey > 0)
    {
        sum += intKey % 10;
        intKey /= 10;
    }
    return sum % TABLE_SIZE;
}



int digitExtractionHash(char key[])
{
    int intKey = StoI(key);
    return (intKey / 10) % TABLE_SIZE; // mengambil dua digit terakhir
}



int rotatingHash(char key[])
{
    int intKey = StoI(key);
    int result = intKey;
    result = (result >> 4) | (result << (sizeof(result) * 8 - 4)); // rotasi 4 bit
    return result % TABLE_SIZE;
}



int linearProbing(int index)
{
    return (index + 1) % TABLE_SIZE;
}



int rehashing(int index)
{
    return (index + 2) % TABLE_SIZE;
}



void insertChain(int index, char key[])
{
    struct HashTable *newNode = (struct HashTable *)malloc(sizeof(struct HashTable));
    strcpy(newNode->key, key);
    newNode->next = NULL;
    if (ht[index].next == NULL)
    {
        ht[index].next = newNode;
    }
    else
    {
        struct HashTable *temp = ht[index].next;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}



void insert(char key[], int (*hashFunction)(char[]), int (*collisionHandling)(int))
{
    int index = hashFunction(key);
    
    if (strcmp(ht[index].key, "") == 0)
    {
        strcpy(ht[index].key, key);
        printf("Key %s dimasukkan ke index %d.\n", key, index);
    }
    else
    {
        printf("Collision terjadi!\n");
        int newIndex = collisionHandling(index);
        if (strcmp(ht[newIndex].key, "") == 0)
        {
            strcpy(ht[newIndex].key, key);
            printf("Key %s dimasukkan ke index %d setelah penanganan collision.\n", key, newIndex);
        }
        else
        {
            printf("Gagal memasukkan key setelah penanganan collision.\n");
        }
    }
}



void displayHT()
{
    printf("\nHash Table\n");
    for (int i=0;i<TABLE_SIZE;i++)
    {
        if (strcmp(ht[i].key, "") != 0)
        {
            printf("Index %d: %s\n", i, ht[i].key);
        }
        else
        {
            printf("Index %d: Kosong\n", i);
        }
    }

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (ht[i].next != NULL)
        {
            printf("Index %d Chaining:\n", i);
            struct HashTable *temp = ht[i].next;
            while (temp != NULL)
            {
                printf("  %s\n", temp->key);
                temp = temp->next;
            }
        }
    }
}



void clear(){
	for(int i=0;i<50;i++)
	{
		puts("");	
	}
}

int main()
{
    initializationHT();
    char key[100];
    int option, collisionOption;
	
	clear();
    printf("Pilih Hash Function:\n");
    printf("1. Mid-Square\n");
    printf("2. Folding\n");
    printf("3. Digit Extraction\n");
    printf("4. Rotating\n");
    scanf("%d", &option);
    clear();

    int (*hashFunction)(char[]) = NULL;

    switch (option)
    {
    case 1:
        hashFunction = midSquareHash;
        break;
    case 2:
        hashFunction = foldingHash;
        break;
    case 3:
        hashFunction = digitExtractionHash;
        break;
    case 4:
        hashFunction = rotatingHash;
        break;
    default:
        printf("Pilihan tidak valid!\n");
        return 1;
    }

    printf("Pilih Collision Handling:\n");
    printf("1. Linear Probing\n");
    printf("2. Rehashing\n");
    printf("3. Chaining\n");
    scanf("%d", &collisionOption);getchar();
    clear();

    int (*collisionHandling)(int) = NULL;

    switch (collisionOption)
    {
    case 1:
        collisionHandling = linearProbing;
        break;
    case 2:
        collisionHandling = rehashing;
        break;
    case 3:
        break;
    default:
        printf("Pilihan tidak valid!\n");
        return 1;
    }

    while(1)
    {
        printf("-Masukkan key (string) untuk lanjut\n");
        printf("-Masukkan exit untuk berhenti\n");
        
        scanf("%[^\n]", key);getchar();
        clear();
        
        if(strcmp(key, "exit") == 0)break;
		
        if(collisionOption == 3)
        {
            int index = hashFunction(key);
            insertChain(index, key);
        }
        else
        {
            insert(key, hashFunction, collisionHandling);
        }
    }

    // Tampilkan hash table
    displayHT();

    return 0;
}

