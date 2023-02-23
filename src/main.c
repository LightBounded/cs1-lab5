#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct person_t person_t;
typedef struct arraylist_t arraylist_t;

struct arraylist_t
{
  person_t **array;
  int capacity, size;
};

struct person_t
{
  char name[20 + 1];
  person_t *likes;
  person_t *dislikes;
  arraylist_t people_who_like_me;
};

void init_array_list(arraylist_t *list)
{
  list->capacity = 5;
  list->size = 0;
  list->array = (person_t **)malloc(list->capacity * sizeof(person_t *));
}

void append_array_list(arraylist_t *list, person_t *person)
{
  if (list->size == list->capacity)
  {
    list->capacity *= 2;
    list->array = realloc(list->array, list->capacity * sizeof(person_t *));
  }
  list->array[list->size] = person;
  list->size++;
}

person_t *create_person(char *name)
{
  person_t *person = (person_t *)malloc(sizeof(person_t));

  strcpy(person->name, name);
  person->likes = NULL;
  person->dislikes = NULL;

  init_array_list(&person->people_who_like_me);

  return person;
}

void print_person(person_t *person)
{
  printf("%s likes", person->name);
  if (person->likes)
    printf(" %s", person->likes->name);
  else
    printf(" nobody");

  printf(" and dislikes");
  if (person->dislikes)
    printf(" %s", person->dislikes->name);
  else
    printf(" nobody");
  printf("\n");

  if (person->people_who_like_me.size == 0)
    printf("Nobody likes me :(\n");
  else
  {
    for (int i = 0; i < person->people_who_like_me.size; i++)
    {
      printf("%s ", person->people_who_like_me.array[i]->name);
    }
    printf("\n");
  }
}

int main()
{
  person_t *steve = create_person("Steve");
  person_t *greg = create_person("Greg");
  person_t *matt = create_person("Matt");

  steve->likes = matt;
  append_array_list(&matt->people_who_like_me, steve);
  matt->likes = greg;
  append_array_list(&greg->people_who_like_me, matt);
  greg->likes = matt;
  append_array_list(&matt->people_who_like_me, greg);

  // Greg dislikes Steve
  steve->likes->likes->dislikes = steve;

  print_person(steve);
  print_person(greg);
  print_person(matt);
  return 0;
}
