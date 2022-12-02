#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "../string/string.h"
#include "io.h"
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "../main.h"

size_t get_file_size(FILE * ptr_file) {
    assert(ptr_file != nullptr);

    struct stat fileinfo = {};
    fstat(fileno(ptr_file), &fileinfo);

    return fileinfo.st_size;
}

size_t get_data_file(char **buff, const char *file_path) {
    assert(buff      != nullptr);
    assert(file_path != nullptr);


    FILE * ptrFile = fopen(file_path, "rb");
    assert(ptrFile != nullptr);

    size_t file_size = get_file_size(ptrFile);

    *buff = (char *)calloc(file_size + 2, sizeof(**buff));

    assert(buff != nullptr);

    fread(*buff, sizeof(char), file_size, ptrFile);
    (*buff)[file_size + 1] = (*buff)[file_size] = 0;

    fclose(ptrFile);

    return file_size;
}

size_t buff_to_text(KR_string **text, char *buff, size_t buff_size) {
    assert(text != nullptr);
    assert(buff != nullptr);

    size_t text_size = 1;

    for (size_t i = 0; i < buff_size; i++) {
        if (buff[i] == '\n') {
            text_size++;
        }
    }
    
    *text = (KR_string *)calloc(text_size + 1, sizeof(**text));
    
    assert(text != nullptr);

    ((*text)[text_size]).ptr = nullptr;

    ((*text)[0]).ptr = buff;
    
    size_t ptr = 1;

    KR_string *ptr_to_last = *text;

    assert(ptr_to_last != nullptr);

    for (size_t i = 0; i < buff_size + 1; i++) {
        if (ptr_to_last != nullptr && (buff[i] == '\r' || buff[i] == '\n' || buff[i] == 0)) {
            (*ptr_to_last).ptr_end = &buff[i];

            ptr_to_last = nullptr;
        }

        if (buff[i] == '\r') {
            buff[i] = 0;
        }
        if (i > 0 && buff[i - 1] == '\n') {
            buff[i - 1] = 0;

            ptr_to_last = &((*text)[ptr]);

            (*text)[ptr++].ptr = &buff[i];
        }
    }
    if (ptr_to_last != nullptr) {
        (*ptr_to_last).ptr_end = &buff[buff_size];
    }

    for (size_t i = 0; i < text_size; i++) {
        assert((*text)[i].ptr     != nullptr);
        assert((*text)[i].ptr_end != nullptr);
    }

    return text_size;
}

void get_file_name_from_flug(const char **file_path, int argc, char *argv[]) {
    //���� ���� �������� ����� ����� �� ���� -f ����� �� ���������, ������ ���������� argc - 1 ������������
    //� ��� �� ��� ������� �������� ������ ���� ���� ������� ���������
    for (size_t i = 0; i < argc - 1; i++) {
        if (!strncmp(argv[i], "-f", 3)) {
            *file_path = argv[i + 1];
            break;
        }
    }
}

void fprintf_buff(FILE *ptrfileout, char *buff, size_t buff_size) {
    assert(ptrfileout != nullptr);
    assert(buff       != nullptr);

    for (size_t i = 0; i < buff_size; i++) {
        if (buff[i] == '\0') {
            if (buff[i + 1] != '\0') {
                fprintf(ptrfileout, "\n");
            }
        }
        else {
            fprintf(ptrfileout, "%c", buff[i]);
        }
    }
}

size_t get_text_file(KR_string **text, char **buff, size_t *buff_size, const char *file_path) {
    assert(text      != nullptr);
    assert(buff      != nullptr);
    assert(buff_size != nullptr);

    *buff_size = get_data_file(buff, file_path);

    assert(buff != nullptr);

    size_t text_size = buff_to_text(text, *buff, *buff_size);

    assert(text != nullptr);

    return text_size;
}

void breaf() {
    printf("Regards, broou. My modes:\n");
    printf("%d\t - akinator\n",           AKINATOR);
    printf("%d\t - wiki\n",               WIKI);
    printf("%d\t - difference\n",         DIFF);
    printf("%d\t - dump\n",               VISUAL);
    printf("%d\t - get data\n",           GET);
    printf("%d\t - save data\n",          SAVE);
    printf("%d\t - exit\n",               EXIT);
    printf("%d\t - help\n",               HELP);
}

void help() {
    printf("My modes:\n");
    printf("%d\t - akinator.      I'm guessing something\n",                 AKINATOR);
    printf("%d\t - wiki.          I tell you about the object\n",            WIKI);
    printf("%d\t - difference.    I telling the difference of 2 objects\n",  DIFF);
    printf("%d\t - visualization. Showing my data tree\n",                   VISUAL);
    printf("%d\t - get data.      Downloading data from a file\n",           GET);
    printf("%d\t - save data.     Uploading data to a file\n",               SAVE);
    printf("%d\t - exit.          shutdown -program -now -rm -rf\n",         EXIT);
    printf("%d\t - help           this\n",                                   HELP);
}

void clear_buffer() {
    char ch = getchar();
    while (!isspace(ch)) {ch = getchar();}
}

bool is_line_end(char ch) {
    if (ch == EOF || ch == '\n' || ch == '\r') {
        return true;
    }
    return false;
}

int get_mode() {
    int ret = 0;

    while (true) {
        printf("chose mode: ");

        if (scanf("%d", &ret) == 1) {
            return ret;
        }

        printf("error, ");
        clear_buffer();
    }
}

void del_line_feed(char *text) {
    assert(text != nullptr);
    while (*text != '\0') {
        if (*text == '\n' || *text == '\r') {
            *text = '\0';
        }
        text++;
    }
}

void get_line_n(char *buf, const size_t max_count) {
    fgets(buf, max_count, stdin);
    del_line_feed(buf);
}