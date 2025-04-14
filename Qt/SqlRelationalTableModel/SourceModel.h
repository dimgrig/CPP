#ifndef SOURCEMODEL_H
#define SOURCEMODEL_H

#include <QAbstractTableModel>
#include <QVector>

class SourceModel : public QAbstractTableModel {
    Q_OBJECT

public:
    SourceModel(QObject *parent = nullptr) : QAbstractTableModel(parent) {
        // Пример данных: 3 строки, 3 столбца
        m_data = {
            {10, 22, 33},
            {11, 23, 35},
            {9, 21, 34}
        };
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return m_data.size();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return m_data.isEmpty() ? 0 : m_data[0].size();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || role != Qt::DisplayRole)
            return QVariant();

        return m_data[index.row()][index.column()];
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal)
            return QString("Column %1").arg(section + 1);
        else
            return QString("Row %1").arg(section + 1);
    }

private:
    QVector<QVector<int>> m_data;
};

#endif // SOURCEMODEL_H
