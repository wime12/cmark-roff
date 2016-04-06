## cmark-roff

**cmark-roff** is a backend for the CommonMark parsing and rendering
library **cmark**. It transforms CommonMark input to roff macros,
escape sequences and text. No special existing macro package for
roff is the target. Instead the user should write his or her own
macro packages for the intended formats like articles, reports,
books, letters, ... .

The roff family of typesetting systems are fast, do not need many
resources and are very flexible. Together with cmark input they
provide an easy to use system for producing good looking documents
while retaining a readable input.


### Macros

- **Document**

  - **.DB**

    Issued at the start of a document. Can be used for setup.

  - **.DE**

    Cleanup actions after the processing of the document can be
    done in this macro.

- **Block Quotes**

  - **.QB**

    Starts a blockquote.

  - **.QE**

    Ends a blockquote.

- **Bullet Lists**

  - **.BB** *\<tight>*

    Starts a bullet (unordered) list. *\<tight>* can be 't' or 'w'
    for tight or wide lists, respectively.

  - **.BE**

    Ends a bullet list.

- **Ordered Lists**

  - **.OB** *\<delim>* *\<start>* *\<tight>*

    Starts an ordered (numbered) list. *\<delim>* is the delimiter
    ('.' or ')') used after the number and *\<start>* specifies the
    number with which the list will start. If *\<tight>* is 't'
    then a tight list is requested and a wide list for 'w'.

  - **.OE**

    Ends an ordered list.

- **List Items**

  - **.IB**

    Starts a list item.

  - **.IE**

    Ends a list item.

- **Code Blocks**

  - **.CB** *\<info>*

    Starts a code block. The type of code is given by *\<info>*.
    The next line after this macro begins directly with the literal
    text of the code block.

  - **.CE**

    Ends a code block.

- **Paragraph**

  - **.P**

    Starts a paragraph.

  - **.I**

    Sometimes it is necessary to control the indentation of a
    paragraph. If the paragraph text starts with the unicode
    characters U+200B (zero width space, HTML &zwsp;) or U+200C
    (zero width non-joiner, HTML &zwnj;) the **.I** macro is issued
    directly after the **.P** macro and the zero width space or
    zero width non-joiner are deleted from the start of the text
    of the paragraph. This is an extension of the CommonMark
    specification. I chose those two characters because they are
    invisible and do not alter, e.g., the HTML rendering.

- **Headings**

  - **.H**x *\<text>*, x = 1, ..., 5

    Forms a heading. *\<text>* contains the text of the heading.
    All line breaks that may occur in the text of Setext headings
    are removed.

- **Thematic Break**

  - **.T**

    Useful for ornamental breaks or separating straight lines.
