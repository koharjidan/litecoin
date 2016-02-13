<<<<<<< HEAD
#ifndef COINCONTROLDIALOG_H
#define COINCONTROLDIALOG_H
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_COINCONTROLDIALOG_H
#define BITCOIN_QT_COINCONTROLDIALOG_H

#include "amount.h"
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771

#include <QAbstractButton>
#include <QAction>
#include <QDialog>
#include <QList>
#include <QMenu>
#include <QPoint>
#include <QString>
#include <QTreeWidgetItem>

<<<<<<< HEAD
namespace Ui {
    class CoinControlDialog;
}
class WalletModel;
class CCoinControl;
=======
class WalletModel;

class CCoinControl;
class CTxMemPool;

namespace Ui {
    class CoinControlDialog;
}
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771

class CoinControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CoinControlDialog(QWidget *parent = 0);
    ~CoinControlDialog();

    void setModel(WalletModel *model);
<<<<<<< HEAD
    
    // static because also called from sendcoinsdialog
    static void updateLabels(WalletModel*, QDialog*);
    static QString getPriorityLabel(double);
    
    static QList<qint64> payAmounts;
=======

    // static because also called from sendcoinsdialog
    static void updateLabels(WalletModel*, QDialog*);
    static QString getPriorityLabel(double dPriority, double mempoolEstimatePriority);

    static QList<CAmount> payAmounts;
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
    static CCoinControl *coinControl;

private:
    Ui::CoinControlDialog *ui;
    WalletModel *model;
    int sortColumn;
    Qt::SortOrder sortOrder;
<<<<<<< HEAD
    
=======

>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
    QMenu *contextMenu;
    QTreeWidgetItem *contextMenuItem;
    QAction *copyTransactionHashAction;
    QAction *lockAction;
    QAction *unlockAction;
<<<<<<< HEAD
    
    QString strPad(QString, int, QString);
    void sortView(int, Qt::SortOrder);
    void updateView();
    
=======

    QString strPad(QString, int, QString);
    void sortView(int, Qt::SortOrder);
    void updateView();

>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
    enum
    {
        COLUMN_CHECKBOX,
        COLUMN_AMOUNT,
        COLUMN_LABEL,
        COLUMN_ADDRESS,
        COLUMN_DATE,
        COLUMN_CONFIRMATIONS,
        COLUMN_PRIORITY,
        COLUMN_TXHASH,
        COLUMN_VOUT_INDEX,
        COLUMN_AMOUNT_INT64,
<<<<<<< HEAD
        COLUMN_PRIORITY_INT64
    };
    
=======
        COLUMN_PRIORITY_INT64,
        COLUMN_DATE_INT64
    };

    // some columns have a hidden column containing the value used for sorting
    int getMappedColumn(int column, bool fVisibleColumn = true)
    {
        if (fVisibleColumn)
        {
            if (column == COLUMN_AMOUNT_INT64)
                return COLUMN_AMOUNT;
            else if (column == COLUMN_PRIORITY_INT64)
                return COLUMN_PRIORITY;
            else if (column == COLUMN_DATE_INT64)
                return COLUMN_DATE;
        }
        else
        {
            if (column == COLUMN_AMOUNT)
                return COLUMN_AMOUNT_INT64;
            else if (column == COLUMN_PRIORITY)
                return COLUMN_PRIORITY_INT64;
            else if (column == COLUMN_DATE)
                return COLUMN_DATE_INT64;
        }

        return column;
    }

>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
private slots:
    void showMenu(const QPoint &);
    void copyAmount();
    void copyLabel();
    void copyAddress();
    void copyTransactionHash();
    void lockCoin();
    void unlockCoin();
    void clipboardQuantity();
    void clipboardAmount();
    void clipboardFee();
    void clipboardAfterFee();
    void clipboardBytes();
    void clipboardPriority();
    void clipboardLowOutput();
    void clipboardChange();
    void radioTreeMode(bool);
    void radioListMode(bool);
    void viewItemChanged(QTreeWidgetItem*, int);
    void headerSectionClicked(int);
    void buttonBoxClicked(QAbstractButton*);
    void buttonSelectAllClicked();
    void updateLabelLocked();
};

<<<<<<< HEAD
#endif // COINCONTROLDIALOG_H
=======
#endif // BITCOIN_QT_COINCONTROLDIALOG_H
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
