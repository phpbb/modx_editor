#include "sqlsyntaxhighlighter.h"

#include <QDebug>

SqlSyntaxHighlighter::SqlSyntaxHighlighter(QTextDocument* parent) : QSyntaxHighlighter(parent)
{
//	setRules();

	QStringList keywords;
	keywords << "CREATE";
	setKeywordList(keywords);
}


void SqlSyntaxHighlighter::setKeywordList(QStringList keywords)
{
	this->keywords = keywords;
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
	types	<< "\\b(?:tiny|small|medium|big)int\\b"
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
	rule.pattern = QRegExp("[-+\\/*<>%;,()]");
	rule.format = operatorFormat;
	highlightingRules.append(rule);

	stringLiteralFormat.setForeground(Qt::darkGreen);
	rule.pattern = QRegExp("(['\"]).*\(\\1)");
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
qDebug() << expression.pattern();
qDebug() << text.mid(index, length);
					setFormat(index, length, rule.format);
					index = text.indexOf(expression, index + length);
				}
			}
			setCurrentBlockState(-1);

		break;
	}

}
