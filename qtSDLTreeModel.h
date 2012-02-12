#ifndef QTSDLTREEMODEL_H
#define QTSDLTREEMODEL_H

#include <QVector>
#include <QAbstractItemModel>

class plStateDataRecord;
class plStateVariable;

class qtSDLTreeModel : public QAbstractItemModel
{
    Q_OBJECT
private:
    plStateDataRecord* sdl;
    enum ItemType { kSDR, kVar, kVal };
    struct SDLModelIndex {
        QModelIndex parent;
        ItemType type;
        union {
            plStateDataRecord* sdr;
            plStateVariable* sv;
            void* raw;
        } ptr;
    };
    mutable QVector<SDLModelIndex> indices;

    QModelIndex ICreateIndex(int row, int column, const QModelIndex& parent, void* ptr, ItemType type) const;

public:
    explicit qtSDLTreeModel(plStateDataRecord* sdl);
    QModelIndex index(int row, int column, const QModelIndex& parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

signals:
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);

public slots:

};

#endif // QTSDLTREEMODEL_H
