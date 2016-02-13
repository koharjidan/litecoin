<<<<<<< HEAD
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOINADDRESSVALIDATOR_H
#define BITCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator.
   Corrects near-miss characters and refuses characters that are not part of base58.
=======
// Copyright (c) 2011-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_BITCOINADDRESSVALIDATOR_H
#define BITCOIN_QT_BITCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
 */
class BitcoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit BitcoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Bitcoin address widget validator, checks for a valid bitcoin address.
 */
class BitcoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit BitcoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // BITCOIN_QT_BITCOINADDRESSVALIDATOR_H
