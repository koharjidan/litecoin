// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

<<<<<<< HEAD
#ifndef WALLETFRAME_H
#define WALLETFRAME_H
=======
#ifndef BITCOIN_QT_WALLETFRAME_H
#define BITCOIN_QT_WALLETFRAME_H
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771

#include <QFrame>
#include <QMap>

class BitcoinGUI;
class ClientModel;
class SendCoinsRecipient;
class WalletModel;
<<<<<<< HEAD
class WalletStack;
class WalletView;
=======
class WalletView;

QT_BEGIN_NAMESPACE
class QStackedWidget;
QT_END_NAMESPACE
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771

class WalletFrame : public QFrame
{
    Q_OBJECT

public:
    explicit WalletFrame(BitcoinGUI *_gui = 0);
    ~WalletFrame();

    void setClientModel(ClientModel *clientModel);

    bool addWallet(const QString& name, WalletModel *walletModel);
    bool setCurrentWallet(const QString& name);
    bool removeWallet(const QString &name);
    void removeAllWallets();

    bool handlePaymentRequest(const SendCoinsRecipient& recipient);

    void showOutOfSyncWarning(bool fShow);

private:
    QStackedWidget *walletStack;
    BitcoinGUI *gui;
    ClientModel *clientModel;
    QMap<QString, WalletView*> mapWalletViews;

    bool bOutOfSync;

    WalletView *currentWalletView();

    WalletView *currentWalletView();

public slots:
    /** Switch to overview (home) page */
    void gotoOverviewPage();
    /** Switch to history (transactions) page */
    void gotoHistoryPage();
    /** Switch to receive coins page */
    void gotoReceiveCoinsPage();
    /** Switch to send coins page */
    void gotoSendCoinsPage(QString addr = "");

    /** Show Sign/Verify Message dialog and switch to sign message tab */
    void gotoSignMessageTab(QString addr = "");
    /** Show Sign/Verify Message dialog and switch to verify message tab */
    void gotoVerifyMessageTab(QString addr = "");

    /** Encrypt the wallet */
    void encryptWallet(bool status);
    /** Backup the wallet */
    void backupWallet();
    /** Change encrypted wallet passphrase */
    void changePassphrase();
    /** Ask for passphrase to unlock wallet temporarily */
    void unlockWallet();

    /** Show used sending addresses */
    void usedSendingAddresses();
    /** Show used receiving addresses */
    void usedReceivingAddresses();
};

<<<<<<< HEAD
#endif // WALLETFRAME_H
=======
#endif // BITCOIN_QT_WALLETFRAME_H
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
