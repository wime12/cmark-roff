## cmark-roff

**cmark-roff** is a backend for the CommonMark parsing and rendering
library *cmark*. It transforms CommonMark input to roff macros,
escape sequences and text. No special existing macro package for
roff is the target. Instead the user should write her own macro
packages for the intended formats like articles, reports, books,
letters ... .

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

  - **.BB** *<tight>*

    Starts a bullet (unordered) list. *<tight>* can be 't' or 'w'
    for tight or wide lists, respectively.

  - **.BE**

    Ends a bullet list.

- **Ordered Lists**

  - **.OB** *<delim>* *<start>* *<tight>*

    Starts an ordered (numbered) list. *<delim>* is the delimiter
    ('.' or ')') used after the number and *<start>* specifies the
    number with which the list will start. If *<tight>* is 't' then
    a tight list is requested and a wide list for 'w'.  Like with
    bullet lists *<tight>*

  - **.OE**

    Ends an ordered list.

- **List Items**

  - **.IB**

    Starts a list item.

  - **.IE**

    Ends a list item.

- **Code Blocks**

  - **.CB** *<info>*

    Starts a code block. The type of code is given by *<info>*. The
    next line after this macro begins directly with the literal
    text of the code block.

  - **.CE**

    Ends a code block.
