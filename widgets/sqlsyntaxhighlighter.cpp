/***************************************************************************
 *   Copyright (C) 2009 by the phpBB Group                                 *
 *   phpbb.com                                                             *
 *                                                                         *
 *  This file is part of MODX Editor.                                      *
 *                                                                         *
 *  MODX Editor is free software: you can redistribute it and/or modify    *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  MODX Editor is distributed in the hope that it will be useful,         *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with MODX Editor.  If not, see <http://www.gnu.org/licenses/>.   *
 ***************************************************************************/

#include "sqlsyntaxhighlighter.h"

#include <QDebug>

SqlSyntaxHighlighter::SqlSyntaxHighlighter(QTextDocument* parent) : QSyntaxHighlighter(parent)
{
	setRules();
}


void SqlSyntaxHighlighter::setRules()
{
	HighlightingRule rule;

	highlightingRules.clear();

	keywordFormat.setForeground(Qt::darkBlue);
	keywordFormat.setFontWeight(QFont::Bold);

	foreach (QString pattern, keywords)
	{
		rule.pattern = QRegExp(pattern);
		rule.format = keywordFormat;
		highlightingRules.append(rule);
	}

	QStringList types;
	types	<< "\\b(?:tiny|small|medium|big)?(int|text|blob)\\b"
			<< "\\bvar(:?char|binary)\\b";

	typeFormat.setForeground(Qt::darkYellow);
	typeFormat.setFontWeight(QFont::Bold);

	foreach (QString pattern, types)
	{
		rule.pattern = QRegExp(pattern, Qt::CaseInsensitive);
		rule.format = typeFormat;
		highlightingRules.append(rule);
	}


	numericLiteralFormat.setForeground(Qt::red);
	rule.pattern = QRegExp("0?[1-9][0-9]*(?:\\.[0-9])?|0x[0-9A-Fa-f]+");
	rule.format = numericLiteralFormat;
	highlightingRules.append(rule);

	operatorFormat.setFontWeight(QFont::Bold);
	operatorFormat.setForeground(Qt::darkMagenta);
	rule.pattern = QRegExp("[-+\\/*<>%;,()]|\\b(?:NOT|AND|OR|DIV|XOR)\\b");
	rule.format = operatorFormat;
	highlightingRules.append(rule);

	stringLiteralFormat.setForeground(Qt::darkGreen);
	rule.pattern = QRegExp("(['\"]).*(\\1)");
	rule.format = stringLiteralFormat;
	highlightingRules.append(rule);

	// These two should be highlighted in strings.
	rule.pattern = QRegExp("[%_]");
	rule.format = operatorFormat;
	highlightingRules.append(rule);
}

SqlSyntaxHighlighter::~SqlSyntaxHighlighter()
{
	//dtor
}

void SqlSyntaxHighlighter::highlightBlock(const QString &text)
{
	switch (previousBlockState())
	{
		case -1:
		default:

			foreach (HighlightingRule rule, highlightingRules)
			{
				QRegExp expression(rule.pattern);
				expression.setPatternSyntax(QRegExp::RegExp2);
				int index = text.indexOf(expression);
				while (index >= 0)
				{
					int length = expression.matchedLength();
					setFormat(index, length, rule.format);
					index = text.indexOf(expression, index + length);
				}
			}
			setCurrentBlockState(-1);

		break;
	}

}

const QStringList SqlSyntaxHighlighter::keywords = QStringList() << "ADD" << "ALL" << "ALTER" << "ANALYZE" << "AS"
								 << "ASC" << "BETWEEN" << "BY" << "CALL" << "COLLATE"
								 << "COLUMN" << "CREATE" << "CROSS" << "CURRENT_DATE" << "CURRENT_TIME"
								 << "CURRENT_TIMESTAMP" << "DATABASE" << "DAY_HOUR" << "DECLARE" << "DEFAULT"
								 << "DELETE" << "DESC" << "DISTINCT" << "DROP" << "DUAL"
								 << "EXISTS" << "EXPLAIN" << "FALSE" << "FROM" << "FULLTEXT"
								 << "GRANT" << "GROUP" << "HAVING" << "IN" << "INDEX"
								 << "INNER" << "INSERT" << "INTO" << "IS" << "JOIN"
								 << "KEY" << "KEYS" << "LEFT" << "LIKE" << "LIMIT"
								 << "LOCK" << "MATCH" << "MODIFIES" << "NATURAL" << "NULL"
								 << "ON" << "OPTIMIZE" << "OR" << "ORDER" << "OUTER"
								 << "PRECISION" << "PRIMARY" << "PROCEDURE" << "PURGE" << "RANGE"
								 << "RENAME" << "REPLACE" << "REQUIRE" << "RIGHT" << "SCHEMA"
								 << "SCHEMAS" << "SELECT" << "SEPARATOR" << "SET" << "SHOW"
								 << "SQL" << "TABLE" << "TO" << "TRUE" << "UNION"
								 << "UNIQUE" << "UPDATE" << "USE" << "USING" << "VALUES"
								 << "WHEN" << "WHERE" << "WHILE" << "WITH" << "WRITE";

