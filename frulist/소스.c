#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Fruit {
    char name[100];
    struct Fruit* next;
    struct Fruit* prev;
};

struct Fruit* currentFruit = NULL;

void printMenu() {
    printf("\n[메뉴]\n");
    printf("n) 다음 과일\n");
    printf("p) 이전 과일\n");
    printf("d) 현재 과일 삭제\n");
    printf("i) 현재 과일 뒤에 과일 추가\n");
    printf("o) 과일 목록 출력 (현재 선택된 과일은 [O]로 표시)\n");
    printf("e) 프로그램 종료\n");
}

void addFruit() {
    char name[100];
    printf("과일 이름을 입력하세요: ");
    scanf("%s", name);

    struct Fruit* newFruit = (struct Fruit*)malloc(sizeof(struct Fruit));
    strcpy(newFruit->name, name);
    newFruit->next = NULL;
    newFruit->prev = NULL;

    if (currentFruit == NULL) {
        currentFruit = newFruit;
    }
    else {
        newFruit->next = currentFruit->next;
        if (currentFruit->next != NULL) {
            currentFruit->next->prev = newFruit;
        }
        currentFruit->next = newFruit;
        newFruit->prev = currentFruit;
        currentFruit = newFruit;
    }

    printf("과일 '%s'이(가) 추가되었습니다.\n", name);
}

void deleteFruit() {
    if (currentFruit == NULL) {
        printf("현재 선택된 과일이 없습니다.\n");
        return;
    }

    struct Fruit* prevFruit = currentFruit->prev;
    struct Fruit* nextFruit = currentFruit->next;

    if (prevFruit != NULL) {
        prevFruit->next = nextFruit;
    }

    if (nextFruit != NULL) {
        nextFruit->prev = prevFruit;
    }

    printf("과일 '%s'이(가) 삭제되었습니다.\n", currentFruit->name);
    free(currentFruit);

    if (nextFruit != NULL) {
        currentFruit = nextFruit;
    }
    else if (prevFruit != NULL) {
        currentFruit = prevFruit;
    }
    else {
        currentFruit = NULL;
    }
}

void printFruitList() {
    struct Fruit* temp = currentFruit;
    while (temp != NULL) {
        if (temp == currentFruit) {
            printf("[%s] ", temp->name);
        }
        else {
            printf("%s ", temp->name);
        }
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    char choice;

    while (1) {
        printMenu();
        printf("\n원하는 작업을 선택하세요: ");
        scanf(" %c", &choice);

        switch (choice) {
        case 'n':
            if (currentFruit == NULL) {
                printf("과일이 없습니다.\n");
            }
            else if (currentFruit->next == NULL) {
                printf("더 이상 다음 과일이 없습니다.\n");
            }
            else {
                currentFruit = currentFruit->next;
            }
            break;

        case 'p':
            if (currentFruit == NULL) {
                printf("과일이 없습니다.\n");
            }
            else if (currentFruit->prev == NULL) {
                printf("더 이상 이전 과일이 없습니다.\n");
            }
            else {
                currentFruit = currentFruit->prev;
            }
            break;

        case 'd':
            deleteFruit();
            break;

        case 'i':
            addFruit();
            break;

        case 'o':
            printFruitList();
            break;

        case 'e':
            printf("프로그램을 종료합니다.\n");
            exit(0);

        default:
            printf("유효하지 않은 입력입니다. 다시 시도하세요.\n");
            break;
        }
    }

    return 0;
}
