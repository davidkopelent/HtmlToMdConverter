/**
 * ctester.cpp
 * Title: Test class implementation
 * Description: Class to test program units
 * Author: David Kopelent
 */

#include <iostream>
#include <cassert>
#include "cdocument.cpp"
#include "cmessage.cpp"
#include "ctag.cpp"
#include "cmdparser.cpp"
#include "cmdconverter.cpp"
using namespace std;

/**
 * Test class for MD Converter
*/
class CMDConverterTester : public CMDConverter {
public:
    CMDConverterTester(void) = default;

    void testImage(void) {
        atributes.push("image.jpg");
        assert(convertImage("<img src=\"image.jpg\"/>") == "![Image](image.jpg)");
        atributes.push("image.jpg");
        assert(convertImage("<img src=\"image.jpg\" class=\"poster\" id=\"1\"/>") == "![Image](image.jpg)");
    }

    void testHeading(void) {
        assert(convertHeading("<h>", "1") == "\n# ");
        assert(convertHeading("<h>", "2") == "\n## ");
        assert(convertHeading("<h>", "3") == "\n### ");
        assert(convertHeading("<h>", "4") == "\n#### ");
        assert(convertHeading("<h>", "5") == "\n##### ");
        assert(convertHeading("<h>", "6") == "\n###### ");
    }

    void testParagraph(void) {
        assert(convertParagraph("<p>") == "");
        assert(convertParagraph("</p>") == "");
        assert(convertParagraph("<br>") == "\n");
    }

    void testBoldItalic(void) {
        assert(convertBold("<b>") == "**");
        assert(convertItalic("<i>") == "*");
        assert(convertBold("</b>") == "**");
        assert(convertItalic("</i>") == "*");
    }

    void testLink(void) {
        atributes.push("index.html");
        assert(convertLink("<a>") == "[");
        assert(convertLink("</a>") == "](index.html)");

        atributes.push("index.html");
        assert(convertLink("<a>") == "[");
        atributes.push("index.html");
        assert(convertLink("<a>") == "[");
        assert(convertLink("</a>") == "](index.html)");
        assert(convertLink("</a>") == "](index.html)");
    }

    void testUnorderedList(void) {
        assert(convertList("<ul>") == "");
        assert(convertList("<li>") == "\n* ");
        assert(convertList("</li>") == "");
        assert(convertList("<li>") == "\n* ");
        assert(convertList("</li>") == "");
        assert(convertList("</ul>") == "");
    }

    void testOrderedList(void) {
        assert(convertList("<ol>") == "");
        assert(convertList("<li>") == "\n1. ");
        assert(convertList("</li>") == "");
        assert(convertList("<li>") == "\n2. ");
        assert(convertList("</li>") == "");
        assert(convertList("</ol>") == "");
    }

    void testTable(void) { 
        assert(convertTable("<table>") == "\n");
        assert(convertTable("<thead>") == "");
        assert(convertTable("<tr>") == "\n| ");
        assert(convertTable("<td>") == "");
        assert(convertTable("</td>") == " | ");
        assert(convertTable("</tr>") == "");
        assert(convertTable("</thead>") == "");
        assert(convertTable("<tbody>") == "");
        assert(convertTable("<tr>") == "\n| ");
        assert(convertTable("<td>") == "");
        assert(convertTable("</td>") == " | ");
        assert(convertTable("</tr>") == "");
        assert(convertTable("</tbody>") == "");
        assert(convertTable("</table>") == "\n");
    }

    void test(void) {
        testImage();
        testHeading();
        testParagraph();
        testBoldItalic();
        testLink();
        testUnorderedList();
        testOrderedList();
        testTable();
    }
};

/**
 * Test class for MD Parser
*/
class CMDParserTester : public CMDParser {
public:
    CMDParserTester(void) = default;

    void testImage(void) {
        assert(parseImage("![IMAGE](image.jpg)") == "<img src=\"image.jpg\"/>");
        assert(parseImage("![IMAGE](image.png)") == "<img src=\"image.png\"/>");

        // WARNING
        assert(parseImage("IMAGE](image.jpg)") == "IMAGE](image.jpg)");
        assert(parseImage("IMAGE(image.jpg)") == "IMAGE(image.jpg)");
        assert(parseImage("![]()") == "![]()");
        assert(parseImage("![IMAGE]()") == "![IMAGE]()");
    }

    void testHeading(void) {
        assert(parseHeading("# HEADING 1") == "<h1>HEADING 1</h1>");
        assert(parseHeading("## HEADING 2") == "<h2>HEADING 2</h2>");
        assert(parseHeading("### HEADING 3") == "<h3>HEADING 3</h3>");
        assert(parseHeading("#### HEADING 4") == "<h4>HEADING 4</h4>");
        assert(parseHeading("##### HEADING 5") == "<h5>HEADING 5</h5>");
        assert(parseHeading("###### HEADING 6") == "<h6>HEADING 6</h6>");

        // WARNING
        assert(parseHeading("####### HEADING 7") == "####### HEADING 7");
    }

    void testParagraph(void) {
        assert(parseParagraph("Lorem ipsum dolor sit amet, consectetuer adipiscing elit.") == "<p>Lorem ipsum dolor sit amet, consectetuer adipiscing elit.</p>");
        assert(parseParagraph("Lorem ipsum dolor sit amet, [LINK](consectetuer.md) adipiscing elit.") == "<p>Lorem ipsum dolor sit amet, [LINK](consectetuer.md) adipiscing elit.</p>");
    }

    void testBoldItalic(void) {
        assert(parseBold("**BOLD**") == "<b>BOLD</b>");
        assert(parseItalic("*ITALIC*") == "<i>ITALIC</i>");
        assert(parseBoldItalic("***BOLD-ITALIC***") == "<b><i>BOLD-ITALIC</i></b>");

        // WARNING
        assert(parseBold("**BOLD*") == "**BOLD*");
        assert(parseItalic("*ITALIC") == "*ITALIC");
        assert(parseBoldItalic("***BOLD-ITALIC") == "***BOLD-ITALIC");
    }

    void testLink(void) {
        assert(parseLink("[IMAGE](image.jpg)") == "<a href=\"image.jpg\">IMAGE</a>");
        assert(parseLink("[IMAGE](image.png)") == "<a href=\"image.png\">IMAGE</a>");

        // WARNING
        assert(parseLink("IMAGE](image.jpg)") == "IMAGE](image.jpg)");
        assert(parseLink("IMAGE(image.jpg)") == "IMAGE(image.jpg)");
        assert(parseLink("[]()") == "[]()");
        assert(parseLink("[IMAGE]()") == "[IMAGE]()");
    }

    void testUnorderedList(void) {
        assert(parseUnorderedList("* ITEM1") == "<ul>\n<li>ITEM1</li>");
        assert(parseUnorderedList("* ITEM2") == "<li>ITEM2</li>");
        assert(parseUnorderedList("* ITEM3") == "<li>ITEM3</li>");
        assert(parseUnorderedList("") == "</ul>\n");

        // WARNING
        assert(parseUnorderedList("1. ITEM1") == "1. ITEM1");
    }

    void testOrderedList(void) {
        assert(parseOrderedList("1. ITEM1") == "<ol>\n<li>ITEM1</li>");
        assert(parseOrderedList("2. ITEM2") == "<li>ITEM2</li>");
        assert(parseOrderedList("3. ITEM3") == "<li>ITEM3</li>");
        assert(parseOrderedList("") == "</ol>\n");

        // WARNING
        assert(parseOrderedList("* ITEM1") == "* ITEM1");
    }

    void testTable(void) { 
        assert(parseTable("| COLUMN A | COLUMN B |") == "<table>\n<thead>\n<tr>\n<td>COLUMN A</td>\n<td>COLUMN B</td>\n</tr>");
        assert(parseTable("| -------- | -------- |") == "</thead>\n<tbody>");
        assert(parseTable("| CELL 1   | CELL 2   |") == "<tr>\n<td>CELL 1</td>\n<td>CELL 2</td>\n</tr>");
        assert(parseTable("| CELL 3   | CELL 4   |") == "<tr>\n<td>CELL 3</td>\n<td>CELL 4</td>\n</tr>");
        assert(parseTable("") == "</tbody>\n</table>\n");

        // WARNING
        assert(parseTable("[LINK](index.html)") == "[LINK](index.html)");
        assert(parseTable("|") == "|");
    }

    void test(void) {
        testImage();
        testHeading();
        testParagraph();
        testBoldItalic();
        testLink();
        testUnorderedList();
        testOrderedList();
        testTable();
    }
};

int main(void) {
    CMDParserTester tester1;
    tester1.test();

    CMDConverterTester tester2;
    tester2.test();
    return 0;
}