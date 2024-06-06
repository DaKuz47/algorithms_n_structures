#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char word[100];
    int key;
} WordEntry;

// Функция сравнения для сортировки
int compareEntries(const void *a, const void *b) {
    WordEntry *entryA = (WordEntry *)a;
    WordEntry *entryB = (WordEntry *)b;
    return entryA->key - entryB->key;
}

int main() {
    // Открываем файл
    FILE *file = fopen("data.txt", "r");
    if (!file) {
        perror("Ошибка открытия файла");
        return 1;
    }

    // Массив для хранения записей
    WordEntry entries[100];
    int count = 0;

    // Считывание данных из файла
    while (fscanf(file, "%99s %d", entries[count].word, &entries[count].key) == 2) {
        count++;
    }
    fclose(file);

    // Сортировка массива
    qsort(entries, count, sizeof(WordEntry), compareEntries);

    // Проверка на дубликаты ключей
    for (int i = 1; i < count; i++) {
        if (entries[i].key == entries[i - 1].key) {
            fprintf(stderr, "Ошибка: дублирующееся ключевое число %d для слов %s и %s\n", 
                    entries[i].key, entries[i - 1].word, entries[i].word);
        }
    }

    // Вывод списка слов и соответствующих им ключевых чисел
    printf("Список слов и соответствующих им ключевых чисел:\n");
    for (int i = 0; i < count; i++) {
        printf("%s %d\n", entries[i].word, entries[i].key);
    }

    // Ввод ключевого числа и проверка наличия соответствующего слова
    int key;
    printf("Введите ключевое число для поиска: ");
    if (scanf("%d", &key) == 1) {
        int found = 0;
        for (int i = 0; i < count; i++) {
            if (entries[i].key == key) {
                printf("Ключевое число %d соответствует слову: %s\n", key, entries[i].word);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Ключевое число %d отсутствует в списке.\n", key);
        }
    } else {
        fprintf(stderr, "Ошибка: некорректный ввод ключевого числа.\n");
    }

    return 0;
}
