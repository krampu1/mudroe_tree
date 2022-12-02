#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "speak.h"


void _speak(const char *text) {
    char *post_question = (char *)calloc(sizeof(char), MAX_POST_QUESTION_SIZE);
    assert(post_question != nullptr);

    sprintf(post_question, "%s%s%s%s%s", 
        "curl --request POST '",
        SPEAK_SERVER_ADRESS,
        "' --header 'Content-Type: application/json' --data-raw '{\"text\": \"",
        text,
        "\",\"voice\": \"Ruslan\"}\' -s >/dev/null");

    system(post_question);

    free(post_question);
}