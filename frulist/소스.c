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
    printf("\n[�޴�]\n");
    printf("n) ���� ����\n");
    printf("p) ���� ����\n");
    printf("d) ���� ���� ����\n");
    printf("i) ���� ���� �ڿ� ���� �߰�\n");
    printf("o) ���� ��� ��� (���� ���õ� ������ [O]�� ǥ��)\n");
    printf("e) ���α׷� ����\n");
}

void addFruit() {
    char name[100];
    printf("���� �̸��� �Է��ϼ���: ");
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

    printf("���� '%s'��(��) �߰��Ǿ����ϴ�.\n", name);
}

void deleteFruit() {
    if (currentFruit == NULL) {
        printf("���� ���õ� ������ �����ϴ�.\n");
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

    printf("���� '%s'��(��) �����Ǿ����ϴ�.\n", currentFruit->name);
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
        printf("\n���ϴ� �۾��� �����ϼ���: ");
        scanf(" %c", &choice);

        switch (choice) {
        case 'n':
            if (currentFruit == NULL) {
                printf("������ �����ϴ�.\n");
            }
            else if (currentFruit->next == NULL) {
                printf("�� �̻� ���� ������ �����ϴ�.\n");
            }
            else {
                currentFruit = currentFruit->next;
            }
            break;

        case 'p':
            if (currentFruit == NULL) {
                printf("������ �����ϴ�.\n");
            }
            else if (currentFruit->prev == NULL) {
                printf("�� �̻� ���� ������ �����ϴ�.\n");
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
            printf("���α׷��� �����մϴ�.\n");
            exit(0);

        default:
            printf("��ȿ���� ���� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
            break;
        }
    }

    return 0;
}
