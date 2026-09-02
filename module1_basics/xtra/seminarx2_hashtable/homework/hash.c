#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GROWTH_FACTOR 2
#define MAX_LOAD_FACTOR 1


struct node 
{
    char* name;
    char* description;
    struct node* next;
};
typedef struct node Node;

struct hashtable 
{
    int size;                    /* Размер таблицы указателей */
    int n_elements;              /* Число элементов в таблице */
    Node** table;
};
typedef struct hashtable Hashtable;



Hashtable* hashtable_create(int size)
{
    Hashtable* ht = malloc(sizeof(Hashtable));

    ht->size = size;
    ht->n_elements = 0;
    ht->table = malloc(sizeof(struct node *) * ht->size);

    for(int i = 0; i < ht->size; i++) 
        ht->table[i] = NULL;

    return ht;
}


unsigned int hash_function_naive(char* s)
{
    return s[0];
}


unsigned int hash_function(char* s)
{
    unsigned int h = 0;

    for(char* p = s; *p; p++)
        h = h * 97 + *p;

    return h;
}

// Функция, которая ищет город по названию и возвращает указатель на Node
Node* hashtable_find(Hashtable* ht, char* name)
{
    // Находим номер связного списка в котором может содержаться город с именем name 
    unsigned int id = hash_function(name) % ht->size;

    // Ищем город в связном списке
    Node* pn = ht->table[id];
    while (pn != NULL)
    {
        if (strcmp(name, pn->name) == 0)
            return pn;
        pn = pn->next;
    }
    return NULL;
}


void hashtable_insert(Hashtable* ht, char* name, char* description)
{
    // Проверяем есть ли элемент с таким именем в хеш-таблице. Если есть, то выходим из функции.
    if (hashtable_find(ht, name) != NULL)
        return;

    // Выделить память под Node (Назовём указатель на этот Node - pn)
    Node* pn = malloc(sizeof(Node));
    
    // Выделить память под pn->name и pn->description и скопировать в них name и description
    pn->name = malloc(strlen(name) + 1);
    pn->description = malloc(strlen(description) + 1);
    strcpy(pn->name, name);
    strcpy(pn->description, description);

    // Найти позицию нового элемента в хеш-таблице, используя хеш-функцию
    unsigned int id = hash_function(name) % ht->size;

    // Добавить его в хеш-таблицу
    pn->next = ht->table[id];
    ht->table[id] = pn;

    // Увеличить ht->n_elements
    ht->n_elements++;

    // (в следущей задаче) Если количество элементов в хеш-таблице слишком много (n > size * MAX_LOAD_FACTOR), 
    // то нужно увеличить таблицу в GROWTH_FACTOR раз
    // При этом все элементы будут находиться на новых местах!

    // Вам нужно создать новую хеш-таблицу большего размера с помощью hashtable_create
    // и добавить в неё все элементы из текущей таблицы, используя hashtable_insert
    // Затем нужно будет удалить текущую таблицу - hashtable_destroy
    // Так как теперь эта функция будет менять саму таблицу (указатель ht), то нужно будет изменить эту функцию на
    //      void hashtable_insert(Hashtable** pht, char* name, char* description)

}

char* hashtable_get_description(Hashtable* ht, char* name)
{
    Node* pn = hashtable_find(ht, name);
    if (pn == NULL)
        return NULL;
    else
        return pn->description;
}

void print_hashtable(Hashtable* ht)
{
    printf("\n\n\n\tHASHTABLE: size = %d, number of elements = %d\n", ht->size, ht->n_elements);
    for (int i = 0; i < ht->size; i++)
    {
        printf("\tId %u:\n", i);
        Node* pn = ht->table[i];
        while (pn != NULL)
        {
            printf("> %s -- %s\n\n", pn->name, pn->description);
            pn = pn->next;
        }
    }
}


void free_node(Node* node)
{
    free(node->name);
    free(node->description);
    free(node);
}

int hashtable_remove(Hashtable* ht, char* name)
{
    unsigned int id = hash_function(name) % ht->size;
    Node* pn = ht->table[id];

    // Если по этому индексу нет ни одного элемента
    if (pn == NULL)
        return 0;

    // Отдельно проверяем первый элемент в списке
    if (strcmp(name, pn->name) == 0)
    {
        ht->table[id] = pn->next;
        free_node(pn);
        ht->n_elements--;
        return 1;
    }

    // Ищем в оставшейся части списка
    Node* prev = pn;
    Node* curr = pn->next;
    while (curr != NULL)
    {
        if (strcmp(name, curr->name) == 0)
        {
            prev->next = curr->next;
            free_node(curr);
            ht->n_elements--;
            return 1;
        }
        prev = curr;
        curr = curr->next;
    }

    return 0;
}


void hashtable_destroy(Hashtable* ht)
{
    for (int i = 0; i < ht->size; i++)
    {
        Node* pn = ht->table[i];
        while (pn != NULL)
        {
            Node* temp = pn;
            pn = pn->next;
            free_node(temp);
        }
    }
    free(ht->table);
    free(ht);
}


int main()
{
    Hashtable* p = hashtable_create(10);

    
    hashtable_insert(p, "Dolgoprudny", "is a town in Moscow Oblast, Russia, located about 20 kilometers"
                                         "north of Moscow city center.in the northeastern part of the town."
                                         "The town's name is sometimescolloquially shortened as Dolgopa. ");

    
    hashtable_insert(p, "Seoul", "is the capital and largest metropolis of South Korea. Seoul is ranked as the fourth largest metropolitan economy in the world and is larger than London and Paris.");
    hashtable_insert(p, "SaoPaulo", "is a municipality in the Southeast Region of Brazil. The metropolis is an alpha global city and the most populous city in Brazil, the Western Hemisphere and the Southern Hemisphere, besides being the largest Portuguese-speaking city in the world.");
    hashtable_insert(p, "MexicoCity", "is the capital of Mexico and the most populous city in North America. Mexico City is one of the most important cultural and financial centres in the Americas.");
    hashtable_insert(p, "Tokyo", "one of the 47 prefectures of Japan, has served as the Japanese capital since 1869. As of 2014, the Greater Tokyo Area ranked as the most populous metropolitan area in the world. ");
    hashtable_insert(p, "Osaka", "is a designated city in the Kansai region of Japan. It is the capital city of Osaka Prefecture and the largest component of the Keihanshin Metropolitan Area, the second largest metropolitan area in Japan and among the largest in the world with over 19 million inhabitants. Osaka will host Expo 2025. The current mayor of Osaka is Hirohumi Yoshimura.");
    hashtable_insert(p, "Manila", "is the capital of the Philippines. It is the most densely populated city proper in the world.");
    hashtable_insert(p, "Vienna", "is the federal capital and largest city of Austria, and one of the nine states of Austria. Vienna is Austria's primate city, with a population of about 1.9 million, and its cultural, economic, and political centre.");
    hashtable_insert(p, "Paris", "is the capital and most populous city of France. Since the 17th century, Paris has been one of Europe's major centres of finance, commerce, fashion, science, and the arts.");
    hashtable_insert(p, "London", "is a capital of Great Britain.");
    hashtable_insert(p, "Addis Ababa", "is the capital and largest city of Ethiopia. According to the 2007 census, the city has a population of 2,739,551 inhabitants.");
    hashtable_insert(p, "Adelaide", "is the capital city of the state of South Australia, and the fifth-most populous city of Australia. The demonym Adelaidean is used to denote the city and the residents of Adelaide.");
    hashtable_insert(p, "Arkhangelsk", "is a city and the administrative center of Arkhangelsk Oblast, in the north of European Russia. It lies on both banks of the Northern Dvina River near its exit into the White Sea.");
    hashtable_insert(p, "Moscow", "is a major political, economic, cultural, and scientific centre of Russia and Eastern Europe. It is the second-most populous city in Europe, the most populous city entirely within Europe, as well as the largest city (by area) on the European continent.");
    hashtable_insert(p, "Montevideo", " is the capital and largest city of Uruguay. The city was established in 1724 by a Spanish soldier, Bruno Mauricio de Zabala, as a strategic move amidst the Spanish-Portuguese dispute over the platine region.");


    print_hashtable(p);
    hashtable_remove(p, "Seoul");
    hashtable_remove(p, "Adelaide");
    hashtable_remove(p, "SaoPaulo");
    hashtable_remove(p, "Paris");
    hashtable_remove(p, "Seoul");
    hashtable_remove(p, "Vienna");
    print_hashtable(p);

    hashtable_destroy(p);

    return 0;
}