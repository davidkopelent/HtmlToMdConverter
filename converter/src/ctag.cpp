/**
 * ctag.cpp
 * Title: Parsed tag class implementation
 * Author: David Kopelent
 */

#include "ctag.h"
#include <iostream>
#include <string>
using namespace std;

CTag::CTag(const string &tag, const string &type = "") :
    content(tag),
    atribute(""),
    type(type) {}

string CTag::getContent(void) {
    return content;
}

string CTag::getAtribute(void) {
    return atribute;
}

string CTag::getType(void) {
    return type;
}

string CTag::parseAttribute(string tag, const string &atribute) {
    size_t link = tag.find(atribute + "=\"");
    size_t linkEnd = tag.find('"', link + atribute.length() + 2);

    if (link != string::npos && linkEnd == string::npos)
        return "";

    if (link != string::npos) {
        tag = tag.substr(link + atribute.length() + 2, tag.length());
        size_t linkEnd = tag.find('"');

        if (linkEnd != string::npos) {
            tag = tag.substr(0, linkEnd);
            return tag;
        }
    }
    return "#";
}

void CHtmlTag::initializeTagList(void) {
    ignoredTags =   {{"<!DOCTYPE>"},{"<!doctype>"},{"<html>"},{"</html>"},{"<head>"},{"</head>"},{"<meta>"},
                    {"<link>"},{"<title>"},{"</title>"},{"<body>"},{"</body>"},{"<span>"},{"</span>"},
                    {"<div>"},{"</div>"}};

    supportedTags = {{"<h1>"},{"</h1>"},{"<h2>"},{"</h2>"},{"<h3>"},{"</h3>"},{"<h4>"},{"</h4>"},{"<h5>"},{"</h5>"},
                    {"<h6>"},{"</h6>"},{"<a>"},{"</a>"},{"<p>"},{"</p>"},{"<b>"},{"</b>"},{"<strong>"},{"</strong>"},
                    {"<i>"},{"</i>"},{"<em>"},{"</em>"},{"<br>"},{"<img>"},{"<thead>"},{"</thead>"},{"<tbody>"},{"</tbody>"},{"<ul>"},
                    {"</ul>"},{"<ol>"},{"</ol>"},{"<li>"},{"</li>"},{"<table>"},{"</table>"},{"<tr>"},{"</tr>"},
                    {"<td>"},{"</td>"},{"<th>"},{"</th>"}};
}

CHtmlTag::CHtmlTag(const string &tag) :
    CTag(tag),
    tag(tag) {}

CHtmlTag::CHtmlTag(const string &tag, const string &type) :
    CTag(tag, type),
    tag(tag) {}

bool CHtmlTag::parseTag(int lineNumber) {
    size_t end = tag.find(" ");
    end = (end != string::npos) ? end - 1 : tag.length() - 2;
    content = tag.substr(0, end+1) + ">";

    if (content == "<title>")
        content = "<h1>";
    else if (content == "</title>")
        content = "</h1>";

    initializeTagList();
    if (ignoredTags.find(content) != ignoredTags.end()) {
        content = "";
    } else if (supportedTags.find(content) != supportedTags.end()) {
        if (content == "<a>" || content == "<img>") {
            atribute = parseAttribute(tag, (content == "<a>") ? "href" : "src");

            if (atribute.empty()) {
                warning.printMessage(warning.formatingWarning(lineNumber));
                return false;
            }
        } else if (content.length() >= 4 && content[1] == 'h' && isdigit(content[2])) {
            atribute = content[2];
        }
        type = "tag";
    } else {
        warning.printMessage(warning.formatingNotSupported(tag, lineNumber));
        content = tag;
        if (type != "text") {
            content = tag + "\n";
            type = "unknown";
        }
    }
    return true;
}

CMDTag::CMDTag(const string &tag) :
    CTag(tag),
    tag(tag) {}

bool CMDTag::parseTag(int lineNumber) {
    return true;
}
