#include <stdio.h>
#include <cmark.h>
#include "backend.h" 

int in_heading = 0;
int list_item_start = 0;

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
    list_item_start = 1;
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
    if (list_item_start) 
	list_item_start = 0;
    else
	puts(".P");
}

void close_paragraph() {
    puts("");
}

void open_heading(int level) {
    in_heading = 1;
    printf(".H%d \"", level);
}

void close_heading() {
    puts("");
    in_heading = 0;
}

void output_thematic_break() {
    puts(".T");
}

void output_text(const char *text) {
    fputs(text, stdout);
}

void output_softbreak() {
    fputs(in_heading ? " " : "\n", stdout);
}

void output_linebreak() {
    puts("\n.br");
}

void output_code(const char *literal) {
    puts(".TB");
    fputs(literal, stdout);
    puts(".TE");
}

/* TODO: How to deal with that? */
void output_html_inline() {
}

void open_emph() {
    puts(".EB");
}

void close_emph() {
    puts(".EE");
}

void open_strong() {
    puts(".SB");
}

void close_strong() {
    puts(".SE");
}

void open_link(const char *url, const char *title) {
    printf(".RB \"%s\" \"%s\n", url, title);
}

void close_link() {
    puts(".RE");
}

void open_image(const char *url, const char *title) {
    printf(".PB \"%s\" \"%s\n", url, title);
}

void close_image() {
    puts(".PE");
}
