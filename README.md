## cmark-roff

**cmark-roff** is a backend for the CommonMark parsing and rendering
library **cmark**. It transforms CommonMark input to roff macros,
escape sequences and text. **cmar-roff** does not target any of the
existing macro packages for roff. Instead the user should write his
or her own macro packages for the intended formats like articles,
reports, books, letters, ... .

The roff family of typesetting systems are fast, do not need many
resources and are very flexible. Together with cmark input they
provide an easy to use system for producing good looking documents
while retaining a readable input.


### Macros

##### Document

  - `.DB`

    Issued at the start of a document. Can be used for setup.

  - `.DE`

    Cleanup actions after the processing of the document can be
    done in this macro.

##### Block Quotes

  - `.QB`

    Starts a blockquote.

  - `.QE`

    Ends a blockquote.

##### Bullet Lists

  - `.BB` *\<tight>*

    Starts a bullet (unordered) list. *\<tight>* can be 't' or 'w'
    for tight or wide lists, respectively.

  - `.BE`

    Ends a bullet list.

##### Ordered Lists

  - `.OB` *\<delim>* *\<start>* *\<tight>*

    Starts an ordered (numbered) list. *\<delim>* is the delimiter
    ('.' or ')') used after the number and *\<start>* specifies the
    number with which the list will start. If *\<tight>* is 't'
    then a tight list is requested and a wide list for 'w'.

  - `.OE`

    Ends an ordered list.

##### List Items

  - `.IB`

    Starts a list item.

  - `.IE`

    Ends a list item.

##### Code Blocks

  - `.CB` *\<info>*

    Starts a code block. The type of code is given by *\<info>*.
    The next line after this macro begins directly with the literal
    text of the code block.

  - `.CE`

    Ends a code block.

##### Paragraphs

  - `.P`

    Starts a paragraph.

  - `.I`

    Sometimes it is necessary to control the indentation of a
    paragraph. If the paragraph text starts with the Unicode
    characters U+200B (zero width space, HTML \&#x200B;) or U+200C
    (zero width non-joiner, HTML \&zwnj;) the `.I` macro is issued
    directly after the `.P` macro and the zero width space or zero
    width non-joiner are deleted from the start of the text of the
    paragraph. This is an extension of the CommonMark specification.
    I chose those two characters because they are invisible and do
    not alter, e.g., the HTML rendering.

##### Headings

  - `.H`*x* *\<text>* (x = 1, ..., 5)

    Forms a heading. *\<text>* contains the text of the heading.
    All line breaks that may occur in the text of Setext headings
    are replaced by spaces.

##### Thematic Breaks

  - `.T`


### Inline

##### Softbreaks and Linebreaks

  For soft breaks **cmark-roff** just writes the return character
  "\n".  Linebreaks are realized by putting the native roff macro
  `.br` into the text.

##### Inline Code

  For inline code expressed by surrounding text with `` ` `` the escape
  sequence `\f(CW` for switching to the fixed width font is used.
  The inline code is terminated with `\fP` to switch back to the
  previous font.

##### Emph And Strong

  Only three levels of emphasis and strong text are supported:
  emphasis, strong and strong emphasis. More than three levels are
  expressed as strong emphasis, so `****some text****` is the same
  as `***some text***`.

  The backend starts the emphasized or strong text with `\*[emph]`,
  `\*[strong]` and `\*[strongemph]`. Note that these escape sequences
  refer to roff *strings* and not directly to font changes. The
  *strings* should contain the escape sequences for switching the
  fonts. This results in a dynamic font changing scheme. The
  programmer of the roff macros might wish to, e.g., switch to an
  italic font for the normal font of block quotes.  Therefore the
  fonts for emphasized, strong and strongly emphasized text must
  be changed. Usually emphasized text is then set in a roman typeface,
  strong text in bold italic and strongly emphasized text in a bold
  typeface.
  
  When strong, emphasized or strongly emphasized text ends, `\fP` switches
  back to the previous font. **cmark-roff** respects the nesting of
  emphasis and strong emphasis. But within such a nesting
  **cmark-roff** will output a `\fP` before switching to the new style.
  So `\fP` always refers to the normal font of the surrounding
  text.
