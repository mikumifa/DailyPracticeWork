#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct word_freq {
    char* word;
    int freq;
};
struct word_freq* words = NULL;
int len = 0;

void my_sort() {
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (strcmp(words[j].word, words[j + 1].word) > 0) {

                struct word_freq temp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = temp;
            }
        }
    }
}

void str_trans(char* c) {
    int indexOfdot = -1;
    for (int i = 0; c[i]; i++) {
        if (c[i] >= 'A' && c[i] <= 'Z') {
            c[i] = (c[i] - 'A') + 'a';
        }
        if (c[i] == '\'')
            indexOfdot = i;
    }
    if (indexOfdot > 0) {
        int i;
        for (int i = indexOfdot + 1; c[i];i++) {
            c[i - 1] = c[i];
        }
        c[i - 1] = '\0';
    }
}

int main() {
    char input[1024];
    while (fgets(input, sizeof(input), stdin)) {
        str_trans(input);
        char* word = strtok(input, " ,.?!:\";\t\n");
        while (word) {
            int i;
            for (i = 0; i < len; i++) {
                if (strcmp(words[i].word, word) == 0) {
                    words[i].freq++;
                    break;
                }
            }
            if (i == len) {
                words = realloc(words, (len + 1) * sizeof(*words));
                words[len].word = malloc(strlen(word) + 1);
                strcpy(words[len].word, word);
                words[len].freq = 1;
                len++;
            }
            word = strtok(NULL, " ,.?!:\";\t\n");
        }
    }
    my_sort();
    for (int i = 0; i < len; i++) {
        printf("%s => %d\n", words[i].word, words[i].freq);
    }

}

