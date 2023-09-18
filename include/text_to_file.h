#ifndef TEXT_TO_FILE_H
#define TEXT_TO_FILE_H

#include <stdio.h>
#include "text.h"

void fwrite_text_sorted(struct Text *text, int (*cmp_func)(const void *, const void *), FILE *file);

void fwrite_text(const struct Text *text, FILE *file);

#endif //TEXT_TO_FILE_H