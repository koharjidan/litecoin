<<<<<<< HEAD
#ifndef COINCONTROLTREEWIDGET_H
#define COINCONTROLTREEWIDGET_H
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_COINCONTROLTREEWIDGET_H
#define BITCOIN_QT_COINCONTROLTREEWIDGET_H
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771

#include <QKeyEvent>
#include <QTreeWidget>

<<<<<<< HEAD
class CoinControlTreeWidget : public QTreeWidget {
Q_OBJECT

public:
    explicit CoinControlTreeWidget(QWidget *parent = 0);
    
protected:
  virtual void  keyPressEvent(QKeyEvent *event);
};

#endif // COINCONTROLTREEWIDGET_H
=======
class CoinControlTreeWidget : public QTreeWidget
{
    Q_OBJECT

public:
    explicit CoinControlTreeWidget(QWidget *parent = 0);

protected:
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // BITCOIN_QT_COINCONTROLTREEWIDGET_H
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
