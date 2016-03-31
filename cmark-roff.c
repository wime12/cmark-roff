#include <cmark.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "backend.h"

#define BUFFER_SIZE 2048

void output_node(cmark_node *cur, cmark_event_type ev);

cmark_node *get_root(FILE *fp) {
    cmark_node *root;
    char buffer[BUFFER_SIZE];
    int bytes;
    cmark_parser *parser = cmark_parser_new(CMARK_OPT_DEFAULT);
 
    while ((bytes = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) {
	cmark_parser_feed(parser, buffer, bytes);
	if (bytes < BUFFER_SIZE) {
	    break;
	}
    }

    root = cmark_parser_finish(parser);
    cmark_parser_free(parser);

    return root;
}

void output_nodes(cmark_node *root) {
    cmark_event_type ev_type;
    cmark_iter *iter = cmark_iter_new(root);

    while((ev_type = cmark_iter_next(iter)) != CMARK_EVENT_DONE) {
	output_node(cmark_iter_get_node(iter), ev_type);
    }

    cmark_iter_free(iter);
}

void output_node(cmark_node *node, cmark_event_type ev) {
    switch (cmark_node_get_type(node)) {
	case CMARK_NODE_DOCUMENT:
	    if (ev == CMARK_EVENT_ENTER)
		open_document();
	    else
		close_document();
	    break;
	case CMARK_NODE_BLOCK_QUOTE:
	    if (ev == CMARK_EVENT_ENTER)
		open_blockquote();
	    else
		close_blockquote();
	    break;
	case CMARK_NODE_LIST:
	    if (cmark_node_get_list_type(node) == CMARK_BULLET_LIST) {
		if (ev == CMARK_EVENT_ENTER) 
		    open_bullet_list(cmark_node_get_list_tight(node));
		else
		    close_bullet_list();
	    }
	    else {
		if (ev == CMARK_EVENT_ENTER)
		    open_ordered_list(cmark_node_get_list_delim(node),
				      cmark_node_get_list_start(node),
				      cmark_node_get_list_tight(node));
		else
		    close_ordered_list();
	    }
	    break;
	case CMARK_NODE_ITEM:
	    if (ev == CMARK_EVENT_ENTER)
		open_item();
	    else
		close_item();
	    break;
	case CMARK_NODE_CODE_BLOCK:
	    output_code_block(cmark_node_get_fence_info(node),
			      cmark_node_get_literal(node));
	    break;
	case CMARK_NODE_HTML_BLOCK:
	    output_html_block(cmark_node_get_literal(node));
	    break;
	case CMARK_NODE_PARAGRAPH:
	    if (ev == CMARK_EVENT_ENTER)
		open_paragraph();
	    else
		close_paragraph();
	    break;
	case CMARK_NODE_HEADING:
	    if (ev == CMARK_EVENT_ENTER)
		open_heading(cmark_node_get_heading_level(node));
	    else
		close_heading();
	    break;
	case CMARK_NODE_THEMATIC_BREAK:
	    output_thematic_break();
	    break;
	case CMARK_NODE_TEXT:
	    output_text(cmark_node_get_literal(node));
	    break;
	case CMARK_NODE_SOFTBREAK:
	    output_softbreak();
	    break;
	case CMARK_NODE_LINEBREAK:
	    output_linebreak();
	    break;
	case CMARK_NODE_CODE:
	    output_code(cmark_node_get_literal(node));
	    break;
	case CMARK_NODE_HTML_INLINE:
	    output_html_inline(cmark_node_get_literal(node));
	    break;
	case CMARK_NODE_EMPH:
	    if (ev == CMARK_EVENT_ENTER)
		open_emph();
	    else
		close_emph();
	    break;
	case CMARK_NODE_STRONG:
	    if (ev == CMARK_EVENT_ENTER)
		open_strong();
	    else
		close_strong();
	    break;
	case CMARK_NODE_LINK:
	    if (ev == CMARK_EVENT_ENTER)
		open_link(cmark_node_get_url(node),
			  cmark_node_get_title(node));
	    else
		close_link();
	    break;
	case CMARK_NODE_IMAGE:
	    if (ev == CMARK_EVENT_ENTER)
		open_image(cmark_node_get_url(node),
			   cmark_node_get_title(node));
	    else
		close_image();
	    break;
	default:
	    fputs("Warning: Unknown node type.\n", stderr);
    }
}

void usage(char *cmd) {
    printf("USAGE: %s [filename|-]\n", cmd);
}

int main(int argc, char *argv[]) {
    FILE *fp = NULL;
    struct stat statbuf;

    if (argc > 2) {
	usage(argv[0]);
	return 1;
    }

    if (argc == 2) {
	if (strcmp(argv[1], "-") == 0) fp = stdin;
	else {
	    lstat(argv[1], &statbuf);
	    if (! S_ISDIR(statbuf.st_mode)) fp = fopen(argv[1], "r");
	}
    }
    else {
	fp = stdin;
    }

    if (fp) {
	output_nodes(get_root(fp));
    }
    else {
	fprintf(stderr, "%s: Could not open file \"%s\"!\n", argv[0], argv[1]);
	return 1;
    }

    return 0;
}
