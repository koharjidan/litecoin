// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "keystore.h"

#include "crypter.h"
#include "key.h"
#include "script/script.h"
#include "script/standard.h"
#include "util.h"

#include <boost/foreach.hpp>

bool CKeyStore::GetPubKey(const CKeyID &address, CPubKey &vchPubKeyOut) const
{
    CKey key;
    if (!GetKey(address, key))
        return false;
    vchPubKeyOut = key.GetPubKey();
    return true;
}

bool CKeyStore::AddKey(const CKey &key) {
    return AddKeyPubKey(key, key.GetPubKey());
}

bool CBasicKeyStore::AddKeyPubKey(const CKey& key, const CPubKey &pubkey)
{
    LOCK(cs_KeyStore);
    mapKeys[pubkey.GetID()] = key;
    return true;
}

bool CBasicKeyStore::AddCScript(const CScript& redeemScript)
{
<<<<<<< HEAD
    LOCK(cs_KeyStore);
    mapScripts[redeemScript.GetID()] = redeemScript;
=======
    if (redeemScript.size() > MAX_SCRIPT_ELEMENT_SIZE)
        return error("CBasicKeyStore::AddCScript() : redeemScripts > %i bytes are invalid", MAX_SCRIPT_ELEMENT_SIZE);

    LOCK(cs_KeyStore);
    mapScripts[CScriptID(redeemScript)] = redeemScript;
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
    return true;
}

bool CBasicKeyStore::HaveCScript(const CScriptID& hash) const
{
    LOCK(cs_KeyStore);
    return mapScripts.count(hash) > 0;
}

bool CBasicKeyStore::GetCScript(const CScriptID &hash, CScript& redeemScriptOut) const
{
    LOCK(cs_KeyStore);
    ScriptMap::const_iterator mi = mapScripts.find(hash);
    if (mi != mapScripts.end())
    {
        redeemScriptOut = (*mi).second;
        return true;
    }
    return false;
}

<<<<<<< HEAD
bool CCryptoKeyStore::SetCrypted()
{
    LOCK(cs_KeyStore);
    if (fUseCrypto)
        return true;
    if (!mapKeys.empty())
        return false;
    fUseCrypto = true;
    return true;
}

bool CCryptoKeyStore::Lock()
{
    if (!SetCrypted())
        return false;

    {
        LOCK(cs_KeyStore);
        vMasterKey.clear();
    }

    NotifyStatusChanged(this);
    return true;
}

bool CCryptoKeyStore::Unlock(const CKeyingMaterial& vMasterKeyIn)
{
    {
        LOCK(cs_KeyStore);
        if (!SetCrypted())
            return false;

        CryptedKeyMap::const_iterator mi = mapCryptedKeys.begin();
        for (; mi != mapCryptedKeys.end(); ++mi)
        {
            const CPubKey &vchPubKey = (*mi).second.first;
            const std::vector<unsigned char> &vchCryptedSecret = (*mi).second.second;
            CKeyingMaterial vchSecret;
            if(!DecryptSecret(vMasterKeyIn, vchCryptedSecret, vchPubKey.GetHash(), vchSecret))
                return false;
            if (vchSecret.size() != 32)
                return false;
            CKey key;
            key.Set(vchSecret.begin(), vchSecret.end(), vchPubKey.IsCompressed());
            if (key.GetPubKey() == vchPubKey)
                break;
            return false;
        }
        vMasterKey = vMasterKeyIn;
    }
    NotifyStatusChanged(this);
    return true;
}

bool CCryptoKeyStore::AddKeyPubKey(const CKey& key, const CPubKey &pubkey)
{
    {
        LOCK(cs_KeyStore);
        if (!IsCrypted())
            return CBasicKeyStore::AddKeyPubKey(key, pubkey);

        if (IsLocked())
            return false;

        std::vector<unsigned char> vchCryptedSecret;
        CKeyingMaterial vchSecret(key.begin(), key.end());
        if (!EncryptSecret(vMasterKey, vchSecret, pubkey.GetHash(), vchCryptedSecret))
            return false;

        if (!AddCryptedKey(pubkey, vchCryptedSecret))
            return false;
    }
=======
bool CBasicKeyStore::AddWatchOnly(const CScript &dest)
{
    LOCK(cs_KeyStore);
    setWatchOnly.insert(dest);
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
    return true;
}

bool CBasicKeyStore::RemoveWatchOnly(const CScript &dest)
{
    LOCK(cs_KeyStore);
    setWatchOnly.erase(dest);
    return true;
}

bool CBasicKeyStore::HaveWatchOnly(const CScript &dest) const
{
<<<<<<< HEAD
    {
        LOCK(cs_KeyStore);
        if (!IsCrypted())
            return CBasicKeyStore::GetKey(address, keyOut);

        CryptedKeyMap::const_iterator mi = mapCryptedKeys.find(address);
        if (mi != mapCryptedKeys.end())
        {
            const CPubKey &vchPubKey = (*mi).second.first;
            const std::vector<unsigned char> &vchCryptedSecret = (*mi).second.second;
            CKeyingMaterial vchSecret;
            if (!DecryptSecret(vMasterKey, vchCryptedSecret, vchPubKey.GetHash(), vchSecret))
                return false;
            if (vchSecret.size() != 32)
                return false;
            keyOut.Set(vchSecret.begin(), vchSecret.end(), vchPubKey.IsCompressed());
            return true;
        }
    }
    return false;
}

bool CCryptoKeyStore::GetPubKey(const CKeyID &address, CPubKey& vchPubKeyOut) const
{
    {
        LOCK(cs_KeyStore);
        if (!IsCrypted())
            return CKeyStore::GetPubKey(address, vchPubKeyOut);

        CryptedKeyMap::const_iterator mi = mapCryptedKeys.find(address);
        if (mi != mapCryptedKeys.end())
        {
            vchPubKeyOut = (*mi).second.first;
            return true;
        }
    }
    return false;
=======
    LOCK(cs_KeyStore);
    return setWatchOnly.count(dest) > 0;
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
}

bool CBasicKeyStore::HaveWatchOnly() const
{
<<<<<<< HEAD
    {
        LOCK(cs_KeyStore);
        if (!mapCryptedKeys.empty() || IsCrypted())
            return false;

        fUseCrypto = true;
        BOOST_FOREACH(KeyMap::value_type& mKey, mapKeys)
        {
            const CKey &key = mKey.second;
            CPubKey vchPubKey = key.GetPubKey();
            CKeyingMaterial vchSecret(key.begin(), key.end());
            std::vector<unsigned char> vchCryptedSecret;
            if (!EncryptSecret(vMasterKeyIn, vchSecret, vchPubKey.GetHash(), vchCryptedSecret))
                return false;
            if (!AddCryptedKey(vchPubKey, vchCryptedSecret))
                return false;
        }
        mapKeys.clear();
    }
    return true;
=======
    LOCK(cs_KeyStore);
    return (!setWatchOnly.empty());
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
}
