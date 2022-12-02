#ifndef SPEAKH
#define SPEAKH

static const char *SPEAK_SERVER_ADRESS = "http://172.19.224.1:5000/synthesize/";

const size_t MAX_POST_QUESTION_SIZE = 1000;

const size_t MAX_PHRASE_SIZE        = 1000;

#define speak(...)  {char *phrase = (char *)calloc(1, MAX_PHRASE_SIZE);\
                    assert(phrase != nullptr);                         \
                    sprintf(phrase, __VA_ARGS__);                      \
                    _speak(phrase);                                    \
                    free(phrase);}   

void _speak(const char *text);

#endif