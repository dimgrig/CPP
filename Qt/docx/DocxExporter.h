#ifndef DOCXEXPORTER_H
#define DOCXEXPORTER_H

#include <QTextDocument>
#include <QTextCursor>
#include <QTextTable>
#include <QTextDocumentWriter>
#include <QFileDialog>
#include <QTextCharFormat>
#include <QTextBlockFormat>
#include <QTextTableFormat>

class DocxExporter {
public:
    DocxExporter();

    bool exportToDocx(const QString &fileName, const QString &text, const QVector<QVector<QString>> &tableData);
private:
    void insertTable(QTextCursor &cursor, const QVector<QVector<QString>> &tableData);
};

#endif // DOCXEXPORTER_H
