<<<<<<< HEAD
#ifndef COINCONTROL_H
#define COINCONTROL_H
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_COINCONTROL_H
#define BITCOIN_COINCONTROL_H

#include "primitives/transaction.h"
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771

/** Coin Control Features. */
class CCoinControl
{
public:
    CTxDestination destChange;

    CCoinControl()
    {
        SetNull();
    }
<<<<<<< HEAD
        
=======

>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
    void SetNull()
    {
        destChange = CNoDestination();
        setSelected.clear();
    }
<<<<<<< HEAD
    
=======

>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
    bool HasSelected() const
    {
        return (setSelected.size() > 0);
    }
<<<<<<< HEAD
    
=======

>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
    bool IsSelected(const uint256& hash, unsigned int n) const
    {
        COutPoint outpt(hash, n);
        return (setSelected.count(outpt) > 0);
    }
<<<<<<< HEAD
    
    void Select(COutPoint& output)
    {
        setSelected.insert(output);
    }
    
    void UnSelect(COutPoint& output)
    {
        setSelected.erase(output);
    }
    
=======

    void Select(const COutPoint& output)
    {
        setSelected.insert(output);
    }

    void UnSelect(const COutPoint& output)
    {
        setSelected.erase(output);
    }

>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
    void UnSelectAll()
    {
        setSelected.clear();
    }

    void ListSelected(std::vector<COutPoint>& vOutpoints)
    {
        vOutpoints.assign(setSelected.begin(), setSelected.end());
    }
<<<<<<< HEAD
        
private:
    std::set<COutPoint> setSelected;

};

#endif // COINCONTROL_H
=======

private:
    std::set<COutPoint> setSelected;
};

#endif // BITCOIN_COINCONTROL_H
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
