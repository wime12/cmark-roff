#include <stdio.h>
#include <cmark.h>
#include "cmark-roff-backend.h" 

int in_heading = 0;
int list_item_start = 0;

void open_document() {
}

void close_document() {
}

void open_blockquote() {
    puts(".QB");
}

void close_blockquote() {
    puts(".QE");
}

void open_bulleted_list(int tight) {
    puts(".LB");
}

void close_bulleted_list() {
    puts(".LE");
}

void open_ordered_list(cmark_delim_type delim, int start, int tight) {
    fputs(".EB ", stdout);
    fputs(delim == CMARK_PERIOD_DELIM ? ". " : ") ", stdout);
    printf("%d ", start);
    puts(tight ? "t\n" : "w");
}

void close_ordered_list() {
    puts(".EE");
}

void open_item() {
    puts(".I");
    list_item_start = 1;
}

void close_item() {
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
    puts(".IB");
}

void close_emph() {
    puts(".IE");
}

void open_strong() {
    puts(".BB");
}

void close_strong() {
    puts(".BE");
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
