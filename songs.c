#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <MMsystem.h>

#define MAX_SONG_LENGTH 100

typedef struct song {
    char title[MAX_SONG_LENGTH];
    struct song *next;
} Song;

void enqueue(Song **head, Song **tail, char *title);
Song *dequeue(Song **head, Song **tail);
void display_queue(Song *head);
void play_song(char *title);

int main() {
    Song *head = NULL;
    Song *tail = NULL;

    int choice;
    char title[MAX_SONG_LENGTH];
    do {
        printf("1. Add song\n");
        printf("2. Delete song\n");
        printf("3. Display queue\n");
        printf("4. Play song\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter song title: ");
                scanf("%s", title);
                enqueue(&head, &tail, title);
                printf("Song added to queue.\n");
                break;

            case 2:
                if (head == NULL) {
                    printf("Queue is empty.\n");
                } else {
                    Song *song = dequeue(&head, &tail);
                    printf("Song \"%s\" deleted from queue.\n", song->title);
                    free(song);
                }
                break;

            case 3:
                if (head == NULL) {
                    printf("Queue is empty.\n");
                } else {
                    printf("Current queue:\n");
                    display_queue(head);
                }
                break;

            case 4:
                if (head == NULL) {
                    printf("Queue is empty.\n");
                } else {
                    printf("Enter song title to play: ");
                    scanf("%s", title);
                    play_song(title);
                }
                break;

            case 5:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 5);

    return 0;
}

void enqueue(Song **head, Song **tail, char *title) {
    Song *new_song = (Song *) malloc(sizeof(Song));
    strncpy(new_song->title, title, MAX_SONG_LENGTH);
    new_song->next = NULL;

    if (*tail == NULL) {
        *head = new_song;
        *tail = new_song;
    } else {
        (*tail)->next = new_song;
        *tail = new_song;
    }
}

Song *dequeue(Song **head, Song **tail) {
    Song *song = *head;

    if (*head == NULL) {
        return NULL;
    }

    if (*head == *tail) {
        *head = NULL;
        *tail = NULL;
    } else {
        *head = (*head)->next;
    }

    return song;
}

void display_queue(Song *head) {
    while (head != NULL) {
        printf("%s\n", head->title);
        head = head->next;
    }
}

void play_song(char *title) {
    printf("Now playing \"%s\".\n", title);
}

