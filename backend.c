#include <stdio.h>
#include <cmark.h>
#include "backend.h"

int in_heading = 0;

int emph = 0;
int strong = 0;

int saved_emph = 0;
int saved_strong = 0;

int switch_font() {

    if ((emph != saved_emph) || (strong != saved_strong)) {

        if ((saved_emph > 0) || (saved_strong > 0)) {
	    fputs("\\fP", stdout);
	}

	if ((emph > 0) && (strong == 0)) {
	    fputs("\\*[emph]", stdout);
	}
	else if ((emph == 0) && (strong > 0)) {
	    fputs("\\*[strong]", stdout);
	}
	else if ((emph > 0) && (strong > 0)) {
	    fputs("\\*[strongemph]", stdout);
	}

	saved_emph = emph;
	saved_strong = strong;

	return 1;
    }
    return 0;
}

void open_document() {
    puts(".DB");
}

void close_document() {
    puts(".DE");
}

void open_blockquote() {
    puts(".QB");
}

void close_blockquote() {
    puts(".QE");
}

void open_bullet_list(int tight) {
    printf(".BB %s\n", tight ? "t" : "w");
}

void close_bullet_list() {
    puts(".BE");
}

void open_ordered_list(cmark_delim_type delim, int start, int tight) {
    fputs(".OB ", stdout);
    fputs(delim == CMARK_PERIOD_DELIM ? ". " : ") ", stdout);
    printf("%d ", start);
    puts(tight ? "t" : "w");
}

void close_ordered_list() {
    puts(".OE");
}

void open_item() {
    puts(".IB");
}

void close_item() {
   puts(".IE");
}

void output_code_block(const char *info, const char *literal) {
    fputs(".CB \"", stdout);
    fputs(info, stdout);
    puts("");
    fputs(literal, stdout);
    puts(".CE");
}

/* Use html_blocks to output literal roff commands
   TODO: remove first and last line of literal */
void output_html_block(const char *literal) {
    fputs(literal, stdout);
}

void open_paragraph() {
    puts(".P");
}

void close_paragraph() {
    switch_font();
    puts("");
}

void open_heading(int level) {
    in_heading = 1;
    printf(".H%d \"", level);
}

void close_heading() {
    switch_font();
    puts("");
    in_heading = 0;
}

void output_thematic_break() {
    puts(".T");
}

void output_text(const char *text) {
    switch_font();
    fputs(text, stdout);
}

void output_softbreak() {
    fputs(in_heading ? " " : "\n", stdout);
}

void output_linebreak() {
    puts("\n.br");
}

void output_code(const char *literal) {
    fputs("\\f(CW", stdout);
    fputs(literal, stdout);
    fputs("\\fP", stdout);
}

/* TODO: How to deal with that? */
void output_html_inline() {
}

void open_emph() {
    emph++;
}

void close_emph() {
    emph--;
}

void open_strong() {
    strong++;
}

void close_strong() {
    strong--;
}

void open_link(const char *url, const char *title) {
    printf(".RB \"%s\" \"%s\n", url, title);
}

void close_link() {
    switch_font();
    puts(".RE");
}

void open_image(const char *url, const char *title) {
    printf(".PB \"%s\" \"%s\n", url, title);
}

void close_image() {
    switch_font();
    puts("\n.PE");
}
