#ifndef DERIVEDMODEL_H
#define DERIVEDMODEL_H

#include <QAbstractTableModel>
#include <QVector>

class DerivedModel : public QAbstractTableModel {
    Q_OBJECT

public:
    DerivedModel(QAbstractTableModel *sourceModel, QObject *parent = nullptr)
        : QAbstractTableModel(parent), m_sourceModel(sourceModel) {
        // Подключаем сигналы к слотам для обновления данных при изменении исходной модели
        connect(m_sourceModel, &QAbstractTableModel::dataChanged, this, &DerivedModel::updateData);
        connect(m_sourceModel, &QAbstractTableModel::modelReset, this, &DerivedModel::updateData);
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return 1; // Одна строка для средних значений
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return m_sourceModel->columnCount();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || role != Qt::DisplayRole)
            return QVariant();

        // Вычисляем среднее значение для столбца
        double sum = 0;
        int rowCount = m_sourceModel->rowCount();
        for (int row = 0; row < rowCount; ++row) {
            QModelIndex sourceIndex = m_sourceModel->index(row, index.column());
            sum += m_sourceModel->data(sourceIndex).toDouble();
        }
        return sum / rowCount;
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal)
            return QString("Avg Column %1").arg(section + 1);
        else
            return QString("Average");
    }

private slots:
    void updateData() {
        // Обновляем данные при изменении исходной модели
        emit dataChanged(index(0, 0), index(0, columnCount() - 1));
    }

private:
    QAbstractTableModel *m_sourceModel;
};

#endif // DERIVEDMODEL_H
