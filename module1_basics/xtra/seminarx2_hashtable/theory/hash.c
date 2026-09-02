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


unsigned int naive_hash_function(char* s)
{
    return s[0];
}


unsigned int hash_function(char* s)
{
    unsigned long h = 0;

    for(char* p = s; *p; p++)
        h = h * 97 + *p;

    return h;
}


void hashtable_insert(Hashtable* ht, char* name, char* description)
{
    // Выделить память под Node (Назовём указатель на этот Node - pn)

    
    // Выделить память под pn->name и pn->description и скопировать в них key и value


    // Найти позицию нового элемента в хеш-таблице, используя хеш-функцию


    // Добавить его в хеш-таблицу


    // Увеличить ht->n_elements


    // (в следущей задаче) Если количество элементов в хеш-таблице слишком много (n > size * MAX_LOAD_FACTOR), 
    // то нужно увеличить таблицу в GROWTH_FACTOR раз
    // При этом все элементы будут находиться на новых местах!

}


char* hashtable_get_description(Hashtable* ht, char* name)
{

}



int main()
{
    Hashtable* p = hashtable_create(10);

    /*
    hashtable_insert(p, "Dolgoprudny", "is a town in Moscow Oblast, Russia, located about 20 kilometers (12 mi)"
                                         "north of Moscow city center. The town's name is derived from Russian"
                                         "(dolgy prud, lit. long pond)—a long and narrow pond situated"
                                         "in the northeastern part of the town. The town's name is sometimes"
                                         "colloquially shortened as Dolgopa. ");

    
    hashtable_insert(p, "Seoul", "officially the Seoul Special City, is the capital and largest metropolis of South Korea."
                                       "With surrounding Incheon metropolis and Gyeonggi province, Seoul forms the heart"
                                       " of the Seoul Capital Area, home to roughly half of the country's population. "
                                       "Seoul is ranked as the fourth largest metropolitan economy in the world and is larger than London and Paris.");

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
    
    */





    return 0;
}