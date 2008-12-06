#ifndef SQLSYNTAXHIGHLIGHTER_H
#define SQLSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class SqlSyntaxHighlighter : public QSyntaxHighlighter
{
public:
	SqlSyntaxHighlighter(QTextDocument* parent = 0);
	virtual ~SqlSyntaxHighlighter();
	void setKeywordList(QStringList keywords);

protected:
	void highlightBlock(const QString &text);

private:
	void setRules();

	struct HighlightingRule
	{
		QRegExp pattern;
		QTextCharFormat format;
	};

	QStringList keywords;
	QVector<HighlightingRule> highlightingRules;
	QTextCharFormat keywordFormat;
	QTextCharFormat typeFormat;
	QTextCharFormat operatorFormat;
	QTextCharFormat stringLiteralFormat;
	QTextCharFormat numericLiteralFormat;
};

#endif // SQLSYNTAXHIGHLIGHTER_H
