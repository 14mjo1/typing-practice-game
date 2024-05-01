#define _CRT_SECURE_NO_WARNINGS

// �ʿ��� ��� ����
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

// �ִ� �ܾ� ����, �ִ� ���, �ִ� �÷��̾� ���� ����� ����
#define MAX_WORD_LENGTH 30
#define MAX_LIVES 5
#define MAX_PLAYERS 10

// ������ ���̵��� ��Ÿ���� ������ ����
typedef enum { EASY, MEDIUM, HARD } Difficulty;

// �÷��̾� ������ ��� ����ü ����
typedef struct {
    char name[50];
    int score;
    Difficulty difficulty;
} Player;

// �� ���̵��� ���� �ð� �� ������ �迭�� ����
int difficulty_times[] = { 10, 15, 20 };
int difficulty_scores[] = { 1, 2, 3 };

// ����, �߰�, ����� ���̵��� �ܾ� ����� �ʱ�ȭ�ϴ� �Լ�
char* easy_words[MAX_WORD_LENGTH];
char* medium_words[MAX_WORD_LENGTH];
char* hard_words[MAX_WORD_LENGTH];
Player* ranking;

// ���ӿ� ���� �ܾ� ����� �ʱ�ȭ�ϴ� �Լ�
void initialize_word_list(char** word_list, char* words[]) {
    // �ܾ� ����Ʈ �ʱ�ȭ
    for (int i = 0; i < MAX_WORD_LENGTH; i++) {
        word_list[i] = words[i];
    }
}
// ���ӿ� ���� �ܾ� ����� �ʱ�ȭ�ϴ� �Լ�
void initialize_words() {
    // �� ���̵��� �ش��ϴ� �ܾ� ��� ����
    char* easy_word_list[MAX_WORD_LENGTH] = {
        "cat", "dog", "book", "tree", "ball", "sun", "moon", "star", "fire", "water",
        "apple", "banana", "orange", "flower", "music"
    };
    char* medium_word_list[MAX_WORD_LENGTH] = {
        "computer", "university", "restaurant", "championship", "environment", "keyboard",
        "internet", "programming", "mountain", "river", "elephant", "tiger", "lion",
        "giraffe", "ocean"
    };
    char* hard_word_list[MAX_WORD_LENGTH] = {
        "concatenation", "philosophy", "architecture", "microprocessor", "biotechnology",
        "telecommunication", "psychoanalysis", "interdisciplinary", "responsibility",
        "misinterpretation", "extraterrestrial", "quantum", "paradox", "phenomenon", "catastrophe"
    };

    // �ܾ� ��� �ʱ�ȭ
    initialize_word_list(easy_words, easy_word_list);
    initialize_word_list(medium_words, medium_word_list);
    initialize_word_list(hard_words, hard_word_list);
}

// ��ŷ �迭�� �ʱ�ȭ�ϴ� �Լ�
void initialize_ranking() {
    // ��ŷ �迭 ���� �Ҵ�
    ranking = (Player*)malloc(MAX_PLAYERS * sizeof(Player));
    // �� �÷��̾��� ���� �ʱ�ȭ
    for (int i = 0; i < MAX_PLAYERS; i++) {
        ranking[i].score = 0;
    }
}

// ��ŷ�� �÷��̾ �߰��ϴ� �Լ�
void add_to_ranking(char* name, int score, Difficulty difficulty) {
    // ������ ���� ��ŷ�� �߰�
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (ranking[i].score < score) {
            // ���ο� �÷��̾� ������ ��ŷ�� ����
            for (int j = MAX_PLAYERS - 1; j > i; j--) {
                ranking[j] = ranking[j - 1];
            }
            // �÷��̾� ���� ������Ʈ
            strcpy(ranking[i].name, name);
            ranking[i].score = score;
            ranking[i].difficulty = difficulty;
            break;
        }
    }
}

// ��ŷ �迭�� �޸𸮿��� ��ü�ϴ� �Լ�
void free_ranking() {
    // ��ŷ �迭 �޸� ��ü
    free(ranking);
}

// ���� ���� �� ȭ�鿡 ��µǴ� ���� ȭ���� ����ϴ� �Լ�
void print_intro() {
    // ȭ�� �ʱ�ȭ
    system("cls");
    // ���� ȭ�� ���
    printf("\033[1;36m");
    printf("\n\t\t\t\t\t\t�ѤѤѤѤѤѤѤѤѤѤ�\n");
    printf("\t\t\t\t\t\t|   Ÿ�� ���� ����   |\n");
    printf("\t\t\t\t\t\t�ѤѤѤѤѤѤѤѤѤѤ�\n");
    printf("\033[0m");
    printf("\n\n\t\t\t\t�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n\n");
    printf("\t\t\t\t\t\t    1. ���� ����\n\n\n\n");
    printf("\t\t\t\t\t\t    2. ���� ���\n\n\n\n");
    printf("\t\t\t\t\t\t    3. ��ŷ ����\n\n\n\n");
    printf("\t\t\t\t\t\t    4. ���� ����\n\n");
    printf("\t\t\t\t�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n\n\n");
}

// ���� ����� ����ϴ� �Լ�
void print_instructions() {
    // ȭ�� �ʱ�ȭ
    system("cls");
    // ���� ��� ���
    printf("\033[1;36m");
    printf("\n\t\t\t���� ���\n\n");
    printf("\033[0m");
    printf("1. ���� ������ �����ϸ� �÷��̾� �̸��� �Է��ϰ�, ���̵��� ������ �� �ֽ��ϴ�.\n");
    printf("2. �ܾ ȭ�鿡 ǥ�õǰ�, ��Ȯ�ϰ� �Է��ؾ� �մϴ�.\n");
    printf("3. ���� �ð� ���� ��Ȯ�ϰ� �Է��ϸ� ������ �����ϰ�, Ʋ���� ����� �����մϴ�.\n");
    printf("4. ����� ��� �����ǰų� ��� �ܾ �Ϸ��ϸ� ������ ����˴ϴ�.\n");
    printf("5. ���� ���� �� ȹ���� ������ ���� ��ŷ�� ������Ʈ�˴ϴ�.\n");
    printf("6. ���� �߿� 'item'�� �Է��ϸ� �������� ����� �� �ֽ��ϴ�.\n");
    printf("\n�����ۿ� ���� ��������:\n");
    printf("- ��� 1���� �߰��մϴ�.\n");
    printf("- ���� 2�踦 ����ϴ�.\n");
    printf("\n���̵��� ���� ���� ����:\n");
    printf("- ���� ���̵�: ��� 5��, ���� �ð� 10��, ���� 1��\n");
    printf("- ���� ���̵�: ��� 4��, ���� �ð� 15��, ���� 2��\n");
    printf("- ����� ���̵�: ��� 3��, ���� �ð� 20��, ���� 3��\n");
    printf("\nEnter Ű�� ������ �޴��� ���ư��ϴ�...");
    getchar();
}

// ��� ������ ȭ�鿡 ����ϴ� �Լ�
void print_hearts(int lives) {
    // ��� ���� ���
    printf("���: ");
    for (int i = 0; i < lives; i++) {
        printf("\033[1;31m�� \033[0m");
    }
    printf("\n");
}

// ������ �����ϴ� �Լ�
void game_start() {
    // �ʿ��� ������ �ʱ�ȭ
    int difficulty_index, lives, word_count;
    char** word_list;

    // ���̵� ����
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t���̵� ���� (1: ����, 2: ����, 3: �����) 1 ~ 3�� �Է��ϼ���.\n\t\t\t\t: ");
    scanf("%d", &difficulty_index);

    // ������ ���̵��� ���� ����
    Difficulty difficulty;
    switch (difficulty_index) {
    case 1:
        word_list = easy_words;
        lives = MAX_LIVES;
        word_count = 15;
        difficulty = EASY;
        break;
    case 2:
        word_list = medium_words;
        lives = MAX_LIVES - 1;
        word_count = 15;
        difficulty = MEDIUM;
        break;
    case 3:
        word_list = hard_words;
        lives = MAX_LIVES - 2;
        word_count = 15;
        difficulty = HARD;
        break;
    default:
        printf("\t\t\t�߸��� �Է��Դϴ�. ���� ���̵��� �����մϴ�.\n");
        word_list = easy_words;
        lives = MAX_LIVES;
        word_count = 15;
        difficulty = EASY;
    }

    // �÷��̾� �̸� �Է�
    char player_name[50];
    printf("\n\t\t\t\t�÷��̾� �̸��� �Է��ϼ���: ");
    scanf("%49s", player_name);

    // ����, �ð�, ������ ����
    int score = 0;
    double total_time = 0;
    int has_item = 1;

    // �õ� �� ����
    srand(time(NULL));

    // ���� ����
    for (int i = 0; i < word_count && lives > 0; i++) {
        // ���� �ܾ� ����
        int random_index = rand() % word_count;
        char* word = word_list[random_index];

        // ȭ�� �ʱ�ȭ
        system("cls");
        // ���� ȭ�� ���
        printf("\033[1;36m");
        printf("\n\n\t\t\t\t\t\tŸ�� ���� ����\n\n\n\t\t\t");
        printf("\033[0m");
        printf("���� ���̵�: %s\n\t\t\t", (difficulty == EASY) ? "����" : ((difficulty == MEDIUM) ? "����" : "�����"));
        print_hearts(lives);
        printf("\t\t\t���� �ð�: %ds\n", difficulty_times[difficulty_index - 1]);
        printf("\t\t\t�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n\n");
        printf("\t\t\t\t\t\t    %s\t\t\t   \n", word);
        printf("\n\t\t\t�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n");
        printf("\t\t\t������(��� +1 �Ǵ� ���� 2��) ��� ���� ����: %s\n", has_item ? "����" : "�Ұ���");
        printf("\t\t\t���� ����: %d\n", score);
        printf("\n\n\t\t\t\t\t\t�Է�: ");

        // ���� �ð� ���
        clock_t start_time = clock();
        char input[MAX_WORD_LENGTH];
        scanf("%s", input);
        double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
        total_time += elapsed_time;

        // �ð� �ʰ� ���� Ȯ��
        if (elapsed_time > difficulty_times[difficulty_index - 1]) {
            printf("\t\t\t�ð��ʰ�!");
            double time_difference = -(15.00 - elapsed_time);
            printf("\t\t\t\t    �ʰ� �ð�: %.2f��\n", time_difference);
            lives--;
            printf("\n\t\t\tEnter Ű�� ������ ����մϴ�...");
            getchar();
            getchar();
            continue;
        }

        // ������ ��� ���� Ȯ��
        if (strcmp(input, "item") == 0 && has_item) {
            if (lives < MAX_LIVES) {
                printf("\t\t\t������ ���: ����� 1�� �߰��մϴ�!\n");
                lives++;
            }
            else {
                printf("\t\t\t������ ���: ������ 2��� �޽��ϴ�!\n");
                score += 2;
            }
            has_item = 0;
        }
        // �ܾ� �Է� Ȯ��
        else if (strcmp(input, word) == 0) {
            printf("\n\n\t\t\t��Ȯ�մϴ�!");
            score += difficulty_scores[difficulty_index - 1];
        }
        // Ʋ�� �Է� ó��
        else {
            printf("\n\n\t\t\tƲ�Ƚ��ϴ�!");
            lives--;
        }
        printf("\t\t\t\t     �ҿ� �ð�: %.2f��", elapsed_time);
        printf("\n\n\t\t\tEnter Ű�� ������ ����մϴ�...\n");
        getchar();
        getchar();
    }

    // ȭ�� �ʱ�ȭ
    system("cls");
    // ���� ���� ȭ�� ���
    printf("\033[1;36m");
    printf("\n\n\t\t\t\t\t\t���� ����\n\n\n");
    printf("\033[0m");
    // ��ŷ�� �÷��̾� �߰�
    printf("\t\t\t\t\t���� ����: %d, �� �ҿ� �ð�: %.2f��\n\n", score, total_time);
    add_to_ranking(player_name, score, difficulty);
    printf("\t\t\t\t\tEnter Ű�� ������ �޴��� ���ư��ϴ�...\n");
    getchar();
}

// ��ŷ�� ȭ�鿡 ����ϴ� �Լ�
void show_ranking() {
    // ȭ�� �ʱ�ȭ
    system("cls");
    printf("\033[1;36m");
    printf("\n\t\t\t��ŷ\n\n");
    printf("\033[0m");

    printf("\033[1;33m");
    printf("%-5s %-20s %-10s %s\n", "����", "�̸�", "����", "���̵�");
    printf("\033[0m");

    int empty = 1;

    // ��ŷ �迭�� �����Ͽ� ����
    Player sorted_ranking[MAX_PLAYERS];
    memcpy(sorted_ranking, ranking, MAX_PLAYERS * sizeof(Player));

    // ������ ���� ������ ����
    for (int i = 0; i < MAX_PLAYERS - 1; i++) {
        for (int j = i + 1; j < MAX_PLAYERS; j++) {
            if (sorted_ranking[i].score < sorted_ranking[j].score) {
                Player temp = sorted_ranking[i];
                sorted_ranking[i] = sorted_ranking[j];
                sorted_ranking[j] = temp;
            }
        }
    }

    // ���̵��� ������ ��쿡�� �����, ����, ���� ������ ����
    for (int i = 0; i < MAX_PLAYERS - 1; i++) {
        for (int j = i + 1; j < MAX_PLAYERS; j++) {
            if (sorted_ranking[i].score == sorted_ranking[j].score && sorted_ranking[i].difficulty < sorted_ranking[j].difficulty) {
                Player temp = sorted_ranking[i];
                sorted_ranking[i] = sorted_ranking[j];
                sorted_ranking[j] = temp;
            }
        }
    }

    // ���ĵ� ��ŷ ���
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (sorted_ranking[i].score != 0) {
            printf("%-5d %-20s %-10d ", i + 1, sorted_ranking[i].name, sorted_ranking[i].score);
            switch (sorted_ranking[i].difficulty) {
            case HARD:
                printf("�����\n");
                break;
            case MEDIUM:
                printf("����\n");
                break;
            case EASY:
                printf("����\n");
                break;
            }
            empty = 0;
        }
    }

    if (empty) {
        printf("����� �����ϴ�.\n");
    }

    printf("\nEnter Ű�� ������ �޴��� ���ư��ϴ�...");
    getchar();
}

// Ŀ�� ����� �����ϴ� �Լ�
void setcursortype(int c) {
    // Ŀ�� ���� ����
    CONSOLE_CURSOR_INFO CurInfo;
    switch (c)
    {
    case 0:
        CurInfo.dwSize = 1;
        CurInfo.bVisible = FALSE;
        break;
    case 1:
        CurInfo.dwSize = 100;
        CurInfo.bVisible = TRUE;
        break;
    case 2:
        CurInfo.dwSize = 20;
        CurInfo.bVisible = TRUE;
        break;
    default:
        break;
    }
    // Ŀ�� ��� ����
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

// ��ǥ�� �̵��ϴ� �Լ�
void gotoxy(int x, int y) {
    COORD CursorPosition = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

// ���� �Լ�
int main() {
    // ��ŷ, �ܾ� �ʱ�ȭ
    initialize_words();
    initialize_ranking();

    // Ŀ�� ����
    setcursortype(0);

    int x = 70, y = 8;
    int key;
    print_intro();

    gotoxy(x, y);
    printf("��");

    while (1) {
        key = _getch();
        gotoxy(x, y);
        printf(" ");

        if (key == 224) {
            key = _getch();
        }

        switch (key) {
        case (int)'w': case 72:
            if (y > 11) y -= 4;
            break;
        case (int)'s': case 80:
            if (y < 17) y += 4;
            break;
        case 13:
            if (y == 12) {
                print_instructions();
                print_intro();
                gotoxy(x, y);
                printf("��");
            }
            else if (y == 8) {
                game_start();
                print_intro();
                gotoxy(x, y);
                printf("��");
            }
            else if (y == 16) {
                show_ranking();
                print_intro();
                gotoxy(x, y);
                printf("��");
            }
            else {
                printf("\n\n\n\t\t\t\t������ �����մϴ�.\n");
                free_ranking();
                return 0;
            }
        }

        gotoxy(x, y);
        printf("��");
    }
    free_ranking();
    return 0;
}