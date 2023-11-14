/// Project                            -       ||  MUSIC  PLAYLIST MANAGER  ||

/// Concept Covering               -      Linked List | Queue | Stack | File Handling

/// Team Mates                  -      Sabbir | Shoib | Adnan | Saeem | Maruf

/// Published On                        -       November 14, 2023


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int total_songs = 0;
// Define a structure for a song
typedef struct Song {
    char title[50];
    char artist[50];
    float duration;
} Song;

// Define a structure for a node in the queue
typedef struct QueueNode {
    Song song;
    struct QueueNode* next;
} QueueNode;

// Queue to manage the play queue
QueueNode* tempFront = NULL;
QueueNode* playQueueFront = NULL;
QueueNode* playQueueRear = NULL;

// Define a structure for a node in the stack
typedef struct StackNode {
    Song song;
    struct StackNode* next;
} StackNode;

// Stack to track recently played songs
StackNode* recentlyPlayedStack = NULL;

/// 1. Function to add a song to the play queue (queue)
void addToPlayQueue(Song song) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->song = song;
    newNode->next = NULL;
    total_songs++;

    if (playQueueRear == NULL) {
        playQueueFront=tempFront = playQueueRear = newNode;
    } else {
        playQueueRear->next = newNode;
        playQueueRear = newNode;
    }
}

///2. Function to play a song from the playlist and push it to the recently played stack (stack)
void playNextSong() {
    if (tempFront != NULL) {
        QueueNode* currentSong = tempFront;
        tempFront = tempFront->next;

        StackNode* newStackNode = (StackNode*)malloc(sizeof(StackNode));
        newStackNode->song = currentSong->song;
        newStackNode->next = recentlyPlayedStack;
        recentlyPlayedStack = newStackNode;
        printf("\n ----------------------------------------------------------- ");
        printf("\n|                        NOW PALYING                        |");
        printf("\n ----------------------------------------------------------- \n\n");

        printf("Song: %s\nArtist: %s\n", currentSong->song.title, currentSong->song.artist);
    } else {
        printf("\n ----------------------------------------------------------- ");
        printf("\n|                  THE PLAYLIST IS EMPTY!                   |");
        printf("\n ----------------------------------------------------------- \n\n");
    }
}



/// 3. Function to play n'th  song from the playlist
void play_nthSong(){

    printf("Enter Song position: ");
    int n;
    scanf("%d", &n);
    if(n > total_songs)
    {
        printf("\n ----------------------------------------------------------- ");
    printf("\n|                    %d is not available                    |",n);
    printf("\n ----------------------------------------------------------- \n\n");

        return;
    }

    QueueNode * temp = playQueueFront;
    for(int i=1; i<n; i++)
    {
        temp = temp->next;
    }

    StackNode* newStackNode = (StackNode*)malloc(sizeof(StackNode));
    newStackNode->song = temp->song;
    newStackNode->next = recentlyPlayedStack;
    recentlyPlayedStack = newStackNode;

        printf("\n ----------------------------------------------------------- ");
        printf("\n|                        NOW PALYING                        |");
        printf("\n ----------------------------------------------------------- \n\n");

    printf("Song: %s\nArtist: %s\n", temp->song.title, temp->song.artist);
}
/// 4. Function to search a song to the playlist (queue)
void search_song()
{
    printf("Enter Song title: ");
    char name[50];
    getchar();
    gets(name);
    QueueNode* currentSong = playQueueFront;
    while(currentSong!=NULL)
    {

        if(strcmp(name, currentSong->song.title) == 0)
        {
            printf("\n ----------------------------------------------------------- ");
            printf("\n|                      SONG FOUND !!                        |");
            printf("\n ----------------------------------------------------------- \n\n");

        printf("Song: %s\nArtist: %s\nDuration: %.2f\n", currentSong->song.title, currentSong->song.artist, currentSong->song.duration);
        return;
        }
        currentSong=currentSong->next;
    }
    printf("\n ----------------------------------------------------------- ");
    printf("\n|                    SONG NOT FOUND !!                      |");
    printf("\n ----------------------------------------------------------- \n\n");
}

/// 5. Function to  view and write the recent playlist to a text file (queue)
void viewRecentPlaylist() {
    FILE *fileR = fopen("recentplaylist.txt", "w");
    if (fileR == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    StackNode *currentSong = recentlyPlayedStack;

    printf("\n ----------------------------------------------------------- ");
    printf("\n|                   RECENTLY PLAYED SONGS                   |");
    printf("\n ----------------------------------------------------------- \n\n");

    fprintf(fileR,"\n ----------------------------------------------------------- ");
    fprintf(fileR,"\n|                   RECENTLY PLAYED SONGS                   |");
    fprintf(fileR,"\n ----------------------------------------------------------- \n\n");

    int trackNo=1;
     while (currentSong != NULL) {

        fprintf(fileR, "%d. Song: %s \n    Artist: %s\n", trackNo,currentSong->song.title, currentSong->song.artist);
        printf("%d. Song: %s\n    Artist: %s\n", trackNo,currentSong->song.title, currentSong->song.artist);

        currentSong = currentSong->next;
        trackNo++;
    }
    fclose(fileR);
    printf("\n ----------------------------------------------------------- ");
    printf("\n|           RECENTLY PLAYED SONGS ALSO SAVED TO             |");
    printf("\n|                  'recentplaylist.txt'                     |");
    printf("\n ----------------------------------------------------------- \n\n");
}
/// 6. Function to view and write the playlist to a text file
void viewPlaylist() {
    FILE *file = fopen("playlist.txt", "w");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    QueueNode* currentSong = playQueueFront;
 int trackNo=1;
    fprintf(file, "Playlist:\n");
    printf("\n ----------------------------------------------------------- ");
    printf("\n|                         PLAYLIST                          |");
    printf("\n ----------------------------------------------------------- \n\n");

    fprintf(file,"\n ----------------------------------------------------------- ");
    fprintf(file,"\n|                         PLAYLIST                          |");
    fprintf(file,"\n ----------------------------------------------------------- \n\n");

    while (currentSong != NULL) {
        fprintf(file, "%d. Song: %s\n    Artist: %s\n", trackNo,currentSong->song.title, currentSong->song.artist);
        printf("%d. Song: %s\n    Artist: %s\n", trackNo,currentSong->song.title, currentSong->song.artist);
        currentSong = currentSong->next;
        trackNo++;
    }

    fclose(file);
    printf("\n ----------------------------------------------------------- ");
    printf("\n|            PLYLIST ALSO SAVED TO 'playlist.txt'           |");
    printf("\n ----------------------------------------------------------- \n\n");
}


/// 7. Function to delete a song from the playlist (queue)
void delete_song(){
    int flag = 0;
    printf("Enter Song title: ");
    char name[50];
    getchar();
    gets(name);
    QueueNode* currentSong = playQueueFront;

     //checking found
    while(currentSong != NULL)
    {
        if(strcmp(name, currentSong->song.title) == 0)
        {
            flag = 1;
            break;
        }
        currentSong=currentSong->next;

    }
    //not found
    if (flag==0)
    {
        printf("\n ----------------------------------------------------------- ");
        printf("\n|                    SONG NOT FOUND !!                      |");
        printf("\n|                   OPERATION FAILED !!                     |");
        printf("\n ----------------------------------------------------------- \n\n");
        return;
    }

    ///for front delete
    if(strcmp(name, playQueueFront->song.title) == 0)
    {
        printf("\n ----------------------------------------------------------- ");
        printf("\n|                      SONG DELETED                         |");
        printf("\n ----------------------------------------------------------- \n\n");
        printf("Song: %s\nArtist: %s\nDuration: %.2f\n", playQueueFront->song.title, playQueueFront->song.artist, playQueueFront->song.duration);
        QueueNode* tempD = playQueueFront;
        playQueueFront = playQueueFront->next;
        free(tempD);
        total_songs--;
        return;
    }

    ///for rear delete
    if(strcmp(name, playQueueRear->song.title) == 0)
    {
        while(currentSong->next->next != NULL)
        {
            currentSong=currentSong->next;
        }
        printf("\n ----------------------------------------------------------- ");
        printf("\n|                      SONG DELETED                         |");
        printf("\n ----------------------------------------------------------- \n\n");
        printf("Song: %s\nArtist: %s\nDuration: %.2f\n", playQueueRear->song.title, playQueueRear->song.artist, playQueueRear->song.duration);
        QueueNode* tempD = playQueueRear;
        currentSong->next = NULL;
        playQueueRear = currentSong;
        free(tempD);
        total_songs--;
        return;
    }
        ///for mid song delete
        while(strcmp(name, currentSong->next->song.title) != 0)
        {
            currentSong=currentSong->next;
        }
        printf("\n ----------------------------------------------------------- ");
        printf("\n|                      SONG DELETED                         |");
        printf("\n ----------------------------------------------------------- \n\n");
        printf("Song: %s\nArtist: %s\nDuration: %.2f\n", currentSong->next->song.title, currentSong->next->song.artist, currentSong->next->song.duration);
        QueueNode* tempD = currentSong->next;
        currentSong->next = currentSong->next->next;
        free(tempD);
        total_songs--;
    return;

}

/// Layout Management
void homelayout(){
    printf("\n ----------------------------------------------------------- ");
    printf("\n|                  DATA STRUCTURES PROJECT                  |");
    printf("\n ----------------------------------------------------------- \n\n");

    printf(" Press enter to continue... ");
    getchar();
}
void layout(){
    printf("\n ----------------------------------------------------------- ");
    printf("\n|                       GO TO OPTIONS                       |");
    printf("\n ----------------------------------------------------------- \n");

    printf(" Press enter to continue... ");
    getchar(); getchar();
}
void Slayout(){
    printf("\n ----------------------------------------------------------- ");
    printf("\n|                       GO TO OPTIONS                       |");
    printf("\n ----------------------------------------------------------- \n");

    printf(" Press enter to continue... ");
    getchar();
}

///  ---- *---  Main Function ----*---
int main() {
    int choice;
    homelayout();

    while (1) {

        printf("\n --X--X--X--X--X-- MUSIC  PLAYLIST MANAGER --X--X--X--X--X-- ");
        printf("\n|                                                           |");
        printf("\nX    1. Add a song to playlist                              X");
        printf("\n|    2. Play next song                                      |");
        printf("\nX    3. Play n_th song                                      X");
        printf("\n|    4. Search a  song                                      |");
        printf("\nX    5. View recently played songs and save to file         X");
        printf("\n|    6. View playlist and save to file                      |");
        printf("\nX    7. Delete a song                                       X");
        printf("\n|    8. Exit                                                |");
        printf("\nX                                                           X");
        printf("\n --X--X--X--X--X--X--X--X--X--X--X--X--X--X--X--X--X--X--X-- \n\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        Song song;
        switch (choice) {
            case 1:
                getchar();
                printf("Enter song title: ");
                gets(song.title);
                printf("Enter artist: ");
                gets(song.artist);
                printf("Enter song duration (in munite): ");
                scanf("%f", &song.duration);
                addToPlayQueue(song);
                printf("\n ----------------------------------------------------------- ");
                printf("\n|                     THE SONG IS ADDED                     |");
                printf("\n ----------------------------------------------------------- \n\n");
                getchar();
                break;
            case 2:
                playNextSong();
                layout();
                break;
            case 3:
                play_nthSong();
                layout();
                break;
            case 4:
                search_song();
                Slayout();
                break;
            case 5:
                viewRecentPlaylist();
                layout();
                break;
            case 6:
                viewPlaylist();
                layout();
                break;
            case 7:
                delete_song();
                Slayout();
                break;
            case 8:
                printf("\n ----------------------------------------------------------- ");
                printf("\n|                         THANK YOU                         |");
                printf("\n ----------------------------------------------------------- \n\n");
                return 0;
            default:
                printf("\n ----------------------------------------------------------- ");
                printf("\n|                 INVALID CHOICE! TRY AGAIN                 |");
                printf("\n ----------------------------------------------------------- \n\n");
        }
    }

    return 0;
}
