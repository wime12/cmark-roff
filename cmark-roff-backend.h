#include <stdio.h>

void open_document();

void close_document();

void open_blockquote();

void close_blockquote();

void open_bulleted_list(int tight);

void close_bulleted_list();

void open_ordered_list(cmark_delim_type delim, int start, int tight);

void close_ordered_list();

void open_item();

void close_item();

void output_code_block(const char *info, const char *literal);

void output_html_block(const char *literal);

void open_paragraph();

void close_paragraph();

void open_heading(int level);

void close_heading();

void output_thematic_break();

void output_text(const char *text);

void output_softbreak();

void output_linebreak();

void output_code(const char *literal);

void output_html_inline();

void open_emph();

void close_emph();

void open_strong();

void close_strong();

void open_link(const char *url, const char *title);

void close_link();

void open_image(const char *url, const char *title);

void close_image();
