#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_PAGES 100

void genrefstr(int refstr[], int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        refstr[i] = rand() % 10;
    }
}

int fifo(int refstr[], int pageFrames[], int numPages, int numFrames) {
    int pageFaults = 0, front = 0;
    for (int i = 0; i < numFrames; i++) pageFrames[i] = -1;

    for (int i = 0; i < numPages; i++) {
        int page = refstr[i];
        bool found = false;
        
        for (int j = 0; j < numFrames; j++) {
            if (pageFrames[j] == page) {
                found = true;
                break;
            }
        }
        
        if (!found) {
            pageFrames[front] = page;
            front = (front + 1) % numFrames;
            pageFaults++;
        }
    }
    return pageFaults;
}

int optimal(int refstr[], int pageFrames[], int numPages, int numFrames) {
    int pageFaults = 0;
    for (int i = 0; i < numFrames; i++) pageFrames[i] = -1;

    for (int i = 0; i < numPages; i++) {
        int page = refstr[i];
        bool found = false;
        
        for (int j = 0; j < numFrames; j++) {
            if (pageFrames[j] == page) {
                found = true;
                break;
            }
        }

        if (!found) {
            if (i < numFrames) pageFrames[i] = page;
            else {
                int farthest = i + 1, replaceIndex = -1;
                for (int j = 0; j < numFrames; j++) {
                    int k;
                    for (k = i + 1; k < numPages; k++) {
                        if (pageFrames[j] == refstr[k]) break;
                    }
                    if (k > farthest) {
                        farthest = k;
                        replaceIndex = j;
                    }
                }
                pageFrames[replaceIndex] = page;
            }
            pageFaults++;
        }
    }
    return pageFaults;
}

int lru_stack(int refstr[], int pageFrames[], int numPages, int numFrames) {
    int pageFaults = 0;
    for (int i = 0; i < numFrames; i++) pageFrames[i] = -1;

    for (int i = 0; i < numPages; i++) {
        int page = refstr[i];
        bool found = false;

        for (int j = 0; j < numFrames; j++) {
            if (pageFrames[j] == page) {
                found = true;
                for (int k = j; k > 0; k--) pageFrames[k] = pageFrames[k - 1];
                pageFrames[0] = page;
                break;
            }
        }
        
        if (!found) {
            for (int j = numFrames - 1; j > 0; j--) pageFrames[j] = pageFrames[j - 1];
            pageFrames[0] = page;
            pageFaults++;
        }
    }
    return pageFaults;
}

int lru_clock(int refstr[], int pageFrames[], int numPages, int numFrames) {
    int pageFaults = 0;
    int useBits[numFrames];
    int pointer = 0;
    for (int i = 0; i < numFrames; i++) pageFrames[i] = -1;

    for (int i = 0; i < numPages; i++) {
        int page = refstr[i];
        bool found = false;

        for (int j = 0; j < numFrames; j++) {
            if (pageFrames[j] == page) {
                useBits[j] = 1;
                found = true;
                break;
            }
        }
        
        if (!found) {
            while (useBits[pointer] == 1) {
                useBits[pointer] = 0;
                pointer = (pointer + 1) % numFrames;
            }
            pageFrames[pointer] = page;
            useBits[pointer] = 1;
            pointer = (pointer + 1) % numFrames;
            pageFaults++;
        }
    }
    return pageFaults;
}

int second_chance(int refstr[], int pageFrames[], int modifyBit[], int numPages, int numFrames) {
    int pageFaults = 0, pointer = 0;
    for (int i = 0; i < numFrames; i++) pageFrames[i] = -1;

    for (int i = 0; i < numPages; i++) {
        int page = refstr[i];
        bool found = false;

        for (int j = 0; j < numFrames; j++) {
            if (pageFrames[j] == page) {
                modifyBit[j] = 1;
                found = true;
                break;
            }
        }
        
        if (!found) {
            while (modifyBit[pointer] == 1) {
                modifyBit[pointer] = 0;
                pointer = (pointer + 1) % numFrames;
            }
            pageFrames[pointer] = page;
            modifyBit[pointer] = 1;
            pointer = (pointer + 1) % numFrames;
            pageFaults++;
        }
    }
    return pageFaults;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_page_frames>\n", argv[0]);
        return 1;
    }

    int numFrames = atoi(argv[1]);
    int refstr[MAX_PAGES];
    int pageFrames[numFrames];
    int modifyBit[MAX_PAGES] = {0}; 
    int numPages = MAX_PAGES;

    genrefstr(refstr, numPages);

    int fifoFaults = fifo(refstr, pageFrames, numPages, numFrames);
    int optFaults = optimal(refstr, pageFrames, numPages, numFrames);
    int lruStackFaults = lru_stack(refstr, pageFrames, numPages, numFrames);
    int lruClockFaults = lru_clock(refstr, pageFrames, numPages, numFrames);
    int secondChanceFaults = second_chance(refstr, pageFrames, modifyBit, numPages, numFrames);

    printf("\nPage Faults Comparison:\n");
    printf("FIFO: %d\n", fifoFaults);
    printf("Optimal: %d\n", optFaults);
    printf("LRU (Stack): %d\n", lruStackFaults);
    printf("LRU (Clock): %d\n", lruClockFaults);
    printf("Second Chance: %d\n", secondChanceFaults);

    return 0;
}