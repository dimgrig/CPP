#include "DocxExporter.h"

#include <QTextList>

#include "Logger.h"

DocxExporter::DocxExporter() {

}

bool DocxExporter::exportToDocx(const QString &fileName, const QString &text, const QVector<QVector<QString>> &tableData) {
    QTextDocument document;
    //document.setIndentWidth(1);
    //document.setTextWidth(1);
    //document.setDocumentMargin(10);

    // Добавляем текст в документ
    QTextCursor cursor(&document);
    QTextCharFormat tf;
    tf.setFont(QFont("Arial", 14));
    cursor.insertText(text, tf);

    //блок - по сути абзац, margin - каждого абзаца
    QTextCursor style_cursor(&document);
    do{
        // auto frame = style_cursor.currentFrame();
        // QTextFrameFormat ff = frame->frameFormat();
        // ff.setBottomMargin(200);
        // ff.setTopMargin(15);
        // ff.setLeftMargin(30);
        // ff.setRightMargin(200);
        // frame->setFrameFormat(ff);

        // auto list = style_cursor.currentList();
        // QTextListFormat lf = list->format();
        // lf.setIndent(120);
        // list->setFormat(lf);

        QTextBlockFormat bf = style_cursor.blockFormat();
        bf.setAlignment(Qt::AlignJustify);
        bf.setIndent(0);
        bf.setTextIndent(47.5); // first line in the block (38 - 1 cm???, 47.5 - 1.26cm)
        bf.setLineHeight(10, QTextBlockFormat::LineDistanceHeight); // interval
        // bf.setBottomMargin(0);
        // bf.setTopMargin(15);
        // bf.setLeftMargin(40);
        // bf.setRightMargin(0);
        bf.setNonBreakableLines(true);
        style_cursor.setBlockFormat(bf);
    } while(style_cursor.movePosition(QTextCursor::NextBlock));

    // //Добавляем таблицу в документ
    if (!tableData.isEmpty()) {
        insertTable(cursor, tableData);
    }

    // // Сохраняем документ в формате .odt - works
    // QTextDocumentWriter writer(fileName);
    // writer.setFormat("odt");
    // bool res = writer.write(&document);
    // if (!res) {
    //     qCDebug(logDebug) << writer.device()->errorString();
    // }
    // return res;

    // Сохраняем документ в формате .docx
    QTextDocumentWriter writer(fileName);
    writer.setFormat("ODF");
    bool res = writer.write(&document);
    if (!res) {
        qCDebug(logDebug) << writer.device()->errorString();
    }
    return res;
}

void DocxExporter::insertTable(QTextCursor &cursor, const QVector<QVector<QString>> &tableData) {
    // Создаем таблицу
    QTextTableFormat tf;
    tf.setAlignment(Qt::AlignHCenter);
    tf.setCellPadding(5);
    tf.setCellSpacing(0);
    tf.setBorder(1);

    int rows = tableData.size();
    int columns = tableData.isEmpty() ? 0 : tableData[0].size();

    QTextTable *table = cursor.insertTable(rows, columns, tf);

    // Заполняем таблицу данными
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            QTextTableCell cell = table->cellAt(row, col);
            QTextCursor cellCursor = cell.firstCursorPosition();
            cellCursor.insertText(tableData[row][col]);
        }
    }

    // Перемещаем курсор после таблицы
    cursor.movePosition(QTextCursor::End);
}
