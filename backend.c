#include <stdio.h>
#include <cmark.h>
#include "backend.h"

int in_heading = 0;

int emph = 0;
int strong = 0;

int saved_emph = 0;
int saved_strong = 0;

int new_line = 0;

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
    new_line = 1;
}

void close_document() {
    puts(".DE");
}

void open_blockquote() {
    puts(".QB");
    new_line = 1;
}

void close_blockquote() {
    puts(".QE");
    new_line = 1;
}

void open_bullet_list(int tight) {
    printf(".BB %s\n", tight ? "t" : "w");
    new_line = 1;
}

void close_bullet_list() {
    puts(".BE");
    new_line = 1;
}

void open_ordered_list(cmark_delim_type delim, int start, int tight) {
    printf(".OB %s %d %s\n",
           delim == CMARK_PERIOD_DELIM ? "." : ")",
	   start,
	   tight ? "t" : "w");
    new_line = 1;
}

void close_ordered_list() {
    puts(".OE");
    new_line = 1;
}

void open_item() {
    puts(".IB");
    new_line = 1;
}

void close_item() {
   puts(".IE");
   new_line = 1;
}

void output_code_block(const char *info, const char *literal) {
    printf(".CB \"%s\n", info);
    fputs(literal, stdout);
    puts(".CE");
    new_line = 1;
}

/* Use html_blocks to output literal roff commands
   TODO: remove first and last line of literal */
void output_html_block(const char *literal) {
    fputs(literal, stdout);
    new_line = 1;
}

void open_paragraph() {
    puts(".P");
    new_line = 1;
}

void close_paragraph() {
    switch_font();
    puts("");
    new_line = 1;
}

void open_heading(int level) {
    in_heading = 1;
    printf(".H%d \"", level);
    new_line = 0;
}

void close_heading() {
    switch_font();
    puts("");
    in_heading = 0;
    new_line = 1;
}

void output_thematic_break() {
    puts(".T");
    new_line = 1;
}

void output_text(const char *text) {
    switch_font();
    if (new_line && (text[0] == '.' || text[0] == '\''))
        fputs("\\&", stdout);
    fputs(text, stdout);
    new_line = 0;
}

void output_softbreak() {
    if (in_heading) {
        fputs(" ", stdout);
	new_line = 0;
    }
    else {
        puts("");
	new_line = 1;
    }
}

void output_linebreak() {
    puts("\n.br");
    new_line = 1;
}

void output_code(const char *literal) {
    printf("\\f(CW%s\\fP", literal);
    new_line = 0;
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
    new_line = 1;
}

void close_link() {
    switch_font();
    puts(".RE");
    new_line = 1;
}

void open_image(const char *url, const char *title) {
    printf(".PB \"%s\" \"%s\n", url, title);
    new_line = 1;
}

void close_image() {
    switch_font();
    fputs("\n.PE", stdout);
    new_line = 1;
}
