// Copyright (c) 2009-2014 The Bitcoin developers
<<<<<<< HEAD
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <openssl/ecdsa.h>
#include <openssl/rand.h>
#include <openssl/obj_mac.h>

#include "key.h"


// anonymous namespace with local implementation code (OpenSSL interaction)
namespace {

// Generate a private key from just the secret parameter
int EC_KEY_regenerate_key(EC_KEY *eckey, BIGNUM *priv_key)
{
    int ok = 0;
    BN_CTX *ctx = NULL;
    EC_POINT *pub_key = NULL;

    if (!eckey) return 0;

    const EC_GROUP *group = EC_KEY_get0_group(eckey);

    if ((ctx = BN_CTX_new()) == NULL)
        goto err;

    pub_key = EC_POINT_new(group);

    if (pub_key == NULL)
        goto err;

    if (!EC_POINT_mul(group, pub_key, priv_key, NULL, NULL, ctx))
        goto err;

    EC_KEY_set_private_key(eckey,priv_key);
    EC_KEY_set_public_key(eckey,pub_key);
=======
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "key.h"

#include "crypto/hmac_sha512.h"
#include "crypto/rfc6979_hmac_sha256.h"
#include "eccryptoverify.h"
#include "pubkey.h"
#include "random.h"
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771

#include <secp256k1.h>
#include "ecwrapper.h"

//! anonymous namespace
namespace {

class CSecp256k1Init {
public:
    CSecp256k1Init() {
        secp256k1_start(SECP256K1_START_SIGN);
    }
    ~CSecp256k1Init() {
        secp256k1_stop();
    }
};
static CSecp256k1Init instance_of_csecp256k1;

<<<<<<< HEAD
// RAII Wrapper around OpenSSL's EC_KEY
class CECKey {
private:
    EC_KEY *pkey;

public:
    CECKey() {
        pkey = EC_KEY_new_by_curve_name(NID_secp256k1);
        assert(pkey != NULL);
    }

    ~CECKey() {
        EC_KEY_free(pkey);
    }

    void GetSecretBytes(unsigned char vch[32]) const {
        const BIGNUM *bn = EC_KEY_get0_private_key(pkey);
        assert(bn);
        int nBytes = BN_num_bytes(bn);
        int n=BN_bn2bin(bn,&vch[32 - nBytes]);
        assert(n == nBytes);
        memset(vch, 0, 32 - nBytes);
    }

    void SetSecretBytes(const unsigned char vch[32]) {
        BIGNUM bn;
        BN_init(&bn);
        assert(BN_bin2bn(vch, 32, &bn));
        assert(EC_KEY_regenerate_key(pkey, &bn));
        BN_clear_free(&bn);
    }

    void GetPrivKey(CPrivKey &privkey, bool fCompressed) {
        EC_KEY_set_conv_form(pkey, fCompressed ? POINT_CONVERSION_COMPRESSED : POINT_CONVERSION_UNCOMPRESSED);
        int nSize = i2d_ECPrivateKey(pkey, NULL);
        assert(nSize);
        privkey.resize(nSize);
        unsigned char* pbegin = &privkey[0];
        int nSize2 = i2d_ECPrivateKey(pkey, &pbegin);
        assert(nSize == nSize2);
    }

    bool SetPrivKey(const CPrivKey &privkey) {
        const unsigned char* pbegin = &privkey[0];
        if (d2i_ECPrivateKey(&pkey, &pbegin, privkey.size())) {
            // d2i_ECPrivateKey returns true if parsing succeeds.
            // This doesn't necessarily mean the key is valid.
            if (EC_KEY_check_key(pkey))
                return true;
        }
        return false;
    }

    void GetPubKey(CPubKey &pubkey, bool fCompressed) {
        EC_KEY_set_conv_form(pkey, fCompressed ? POINT_CONVERSION_COMPRESSED : POINT_CONVERSION_UNCOMPRESSED);
        int nSize = i2o_ECPublicKey(pkey, NULL);
        assert(nSize);
        assert(nSize <= 65);
        unsigned char c[65];
        unsigned char *pbegin = c;
        int nSize2 = i2o_ECPublicKey(pkey, &pbegin);
        assert(nSize == nSize2);
        pubkey.Set(&c[0], &c[nSize]);
    }

    bool SetPubKey(const CPubKey &pubkey) {
        const unsigned char* pbegin = pubkey.begin();
        return o2i_ECPublicKey(&pkey, &pbegin, pubkey.size());
    }

    bool Sign(const uint256 &hash, std::vector<unsigned char>& vchSig) {
        unsigned int nSize = ECDSA_size(pkey);
        vchSig.resize(nSize); // Make sure it is big enough
        assert(ECDSA_sign(0, (unsigned char*)&hash, sizeof(hash), &vchSig[0], &nSize, pkey));
        vchSig.resize(nSize); // Shrink to fit actual size
        return true;
    }

    bool Verify(const uint256 &hash, const std::vector<unsigned char>& vchSig) {
        if (vchSig.empty())
            return false;

        // New versions of OpenSSL will reject non-canonical DER signatures. de/re-serialize first.
        unsigned char *norm_der = NULL;
        ECDSA_SIG *norm_sig = ECDSA_SIG_new();
        const unsigned char* sigptr = &vchSig[0];
        assert(norm_sig);
        if (d2i_ECDSA_SIG(&norm_sig, &sigptr, vchSig.size()) == NULL)
        {
            /* As of OpenSSL 1.0.0p d2i_ECDSA_SIG frees and nulls the pointer on
             * error. But OpenSSL's own use of this function redundantly frees the
             * result. As ECDSA_SIG_free(NULL) is a no-op, and in the absence of a
             * clear contract for the function behaving the same way is more
             * conservative.
             */
            ECDSA_SIG_free(norm_sig);
            return false;
        }
        int derlen = i2d_ECDSA_SIG(norm_sig, &norm_der);
        ECDSA_SIG_free(norm_sig);
        if (derlen <= 0)
            return false;

        // -1 = error, 0 = bad sig, 1 = good
        bool ret = ECDSA_verify(0, (unsigned char*)&hash, sizeof(hash), norm_der, derlen, pkey) == 1;
        OPENSSL_free(norm_der);
        return ret;
    }

    bool SignCompact(const uint256 &hash, unsigned char *p64, int &rec) {
        bool fOk = false;
        ECDSA_SIG *sig = ECDSA_do_sign((unsigned char*)&hash, sizeof(hash), pkey);
        if (sig==NULL)
            return false;
        memset(p64, 0, 64);
        int nBitsR = BN_num_bits(sig->r);
        int nBitsS = BN_num_bits(sig->s);
        if (nBitsR <= 256 && nBitsS <= 256) {
            CPubKey pubkey;
            GetPubKey(pubkey, true);
            for (int i=0; i<4; i++) {
                CECKey keyRec;
                if (ECDSA_SIG_recover_key_GFp(keyRec.pkey, sig, (unsigned char*)&hash, sizeof(hash), i, 1) == 1) {
                    CPubKey pubkeyRec;
                    keyRec.GetPubKey(pubkeyRec, true);
                    if (pubkeyRec == pubkey) {
                        rec = i;
                        fOk = true;
                        break;
                    }
                }
            }
            assert(fOk);
            BN_bn2bin(sig->r,&p64[32-(nBitsR+7)/8]);
            BN_bn2bin(sig->s,&p64[64-(nBitsS+7)/8]);
        }
        ECDSA_SIG_free(sig);
        return fOk;
    }

    // reconstruct public key from a compact signature
    // This is only slightly more CPU intensive than just verifying it.
    // If this function succeeds, the recovered public key is guaranteed to be valid
    // (the signature is a valid signature of the given data for that key)
    bool Recover(const uint256 &hash, const unsigned char *p64, int rec)
    {
        if (rec<0 || rec>=3)
            return false;
        ECDSA_SIG *sig = ECDSA_SIG_new();
        BN_bin2bn(&p64[0],  32, sig->r);
        BN_bin2bn(&p64[32], 32, sig->s);
        bool ret = ECDSA_SIG_recover_key_GFp(pkey, sig, (unsigned char*)&hash, sizeof(hash), rec, 0) == 1;
        ECDSA_SIG_free(sig);
        return ret;
    }
};

}; // end of anonymous namespace

bool CKey::Check(const unsigned char *vch) {
    // Do not convert to OpenSSL's data structures for range-checking keys,
    // it's easy enough to do directly.
    static const unsigned char vchMax[32] = {
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
        0xBA,0xAE,0xDC,0xE6,0xAF,0x48,0xA0,0x3B,
        0xBF,0xD2,0x5E,0x8C,0xD0,0x36,0x41,0x40
    };
    bool fIsZero = true;
    for (int i=0; i<32 && fIsZero; i++)
        if (vch[i] != 0)
            fIsZero = false;
    if (fIsZero)
        return false;
    for (int i=0; i<32; i++) {
        if (vch[i] < vchMax[i])
            return true;
        if (vch[i] > vchMax[i])
            return false;
    }
    return true;
}

void CKey::MakeNewKey(bool fCompressedIn) {
    do {
        RAND_bytes(vch, sizeof(vch));
    } while (!Check(vch));
    fValid = true;
    fCompressed = fCompressedIn;
}

bool CKey::SetPrivKey(const CPrivKey &privkey, bool fCompressedIn) {
    CECKey key;
    if (!key.SetPrivKey(privkey))
        return false;
    key.GetSecretBytes(vch);
    fCompressed = fCompressedIn;
    fValid = true;
    return true;
}

CPrivKey CKey::GetPrivKey() const {
    assert(fValid);
    CECKey key;
    key.SetSecretBytes(vch);
    CPrivKey privkey;
    key.GetPrivKey(privkey, fCompressed);
    return privkey;
}

CPubKey CKey::GetPubKey() const {
    assert(fValid);
    CECKey key;
    key.SetSecretBytes(vch);
    CPubKey pubkey;
    key.GetPubKey(pubkey, fCompressed);
    return pubkey;
}

bool CKey::Sign(const uint256 &hash, std::vector<unsigned char>& vchSig) const {
    if (!fValid)
        return false;
    CECKey key;
    key.SetSecretBytes(vch);
    return key.Sign(hash, vchSig);
}

bool CKey::SignCompact(const uint256 &hash, std::vector<unsigned char>& vchSig) const {
    if (!fValid)
        return false;
    CECKey key;
    key.SetSecretBytes(vch);
    vchSig.resize(65);
    int rec = -1;
    if (!key.SignCompact(hash, &vchSig[1], rec))
        return false;
    assert(rec != -1);
    vchSig[0] = 27 + rec + (fCompressed ? 4 : 0);
    return true;
}

bool CPubKey::Verify(const uint256 &hash, const std::vector<unsigned char>& vchSig) const {
    if (!IsValid())
        return false;
    CECKey key;
    if (!key.SetPubKey(*this))
        return false;
    if (!key.Verify(hash, vchSig))
        return false;
    return true;
}

bool CPubKey::RecoverCompact(const uint256 &hash, const std::vector<unsigned char>& vchSig) {
    if (vchSig.size() != 65)
        return false;
    CECKey key;
    if (!key.Recover(hash, &vchSig[1], (vchSig[0] - 27) & ~4))
        return false;
    key.GetPubKey(*this, (vchSig[0] - 27) & 4);
    return true;
}

bool CPubKey::VerifyCompact(const uint256 &hash, const std::vector<unsigned char>& vchSig) const {
    if (!IsValid())
        return false;
    if (vchSig.size() != 65)
        return false;
    CECKey key;
    if (!key.Recover(hash, &vchSig[1], (vchSig[0] - 27) & ~4))
        return false;
    CPubKey pubkeyRec;
    key.GetPubKey(pubkeyRec, IsCompressed());
    if (*this != pubkeyRec)
        return false;
    return true;
}

bool CPubKey::IsFullyValid() const {
    if (!IsValid())
        return false;
    CECKey key;
    if (!key.SetPubKey(*this))
        return false;
    return true;
}

bool CPubKey::Decompress() {
    if (!IsValid())
        return false;
    CECKey key;
    if (!key.SetPubKey(*this))
        return false;
    key.GetPubKey(*this, false);
    return true;
=======
} // anon namespace

bool CKey::Check(const unsigned char *vch) {
    return eccrypto::Check(vch);
}

void CKey::MakeNewKey(bool fCompressedIn) {
    do {
        GetRandBytes(vch, sizeof(vch));
    } while (!Check(vch));
    fValid = true;
    fCompressed = fCompressedIn;
}

bool CKey::SetPrivKey(const CPrivKey &privkey, bool fCompressedIn) {
    if (!secp256k1_ec_privkey_import((unsigned char*)begin(), &privkey[0], privkey.size()))
        return false;
    fCompressed = fCompressedIn;
    fValid = true;
    return true;
}

CPrivKey CKey::GetPrivKey() const {
    assert(fValid);
    CPrivKey privkey;
    int privkeylen, ret;
    privkey.resize(279);
    privkeylen = 279;
    ret = secp256k1_ec_privkey_export(begin(), (unsigned char*)&privkey[0], &privkeylen, fCompressed);
    assert(ret);
    privkey.resize(privkeylen);
    return privkey;
}

CPubKey CKey::GetPubKey() const {
    assert(fValid);
    CPubKey result;
    int clen = 65;
    int ret = secp256k1_ec_pubkey_create((unsigned char*)result.begin(), &clen, begin(), fCompressed);
    assert((int)result.size() == clen);
    assert(ret);
    assert(result.IsValid());
    return result;
}

bool CKey::Sign(const uint256 &hash, std::vector<unsigned char>& vchSig, uint32_t test_case) const {
    if (!fValid)
        return false;
    vchSig.resize(72);
    RFC6979_HMAC_SHA256 prng(begin(), 32, (unsigned char*)&hash, 32);
    do {
        uint256 nonce;
        prng.Generate((unsigned char*)&nonce, 32);
        nonce += test_case;
        int nSigLen = 72;
        int ret = secp256k1_ecdsa_sign((const unsigned char*)&hash, 32, (unsigned char*)&vchSig[0], &nSigLen, begin(), (unsigned char*)&nonce);
        nonce = 0;
        if (ret) {
            vchSig.resize(nSigLen);
            return true;
        }
    } while(true);
}

bool CKey::VerifyPubKey(const CPubKey& pubkey) const {
    if (pubkey.IsCompressed() != fCompressed) {
        return false;
    }
    unsigned char rnd[8];
    std::string str = "Bitcoin key verification\n";
    GetRandBytes(rnd, sizeof(rnd));
    uint256 hash;
    CHash256().Write((unsigned char*)str.data(), str.size()).Write(rnd, sizeof(rnd)).Finalize((unsigned char*)&hash);
    std::vector<unsigned char> vchSig;
    Sign(hash, vchSig);
    return pubkey.Verify(hash, vchSig);
}

bool CKey::SignCompact(const uint256 &hash, std::vector<unsigned char>& vchSig) const {
    if (!fValid)
        return false;
    vchSig.resize(65);
    int rec = -1;
    RFC6979_HMAC_SHA256 prng(begin(), 32, (unsigned char*)&hash, 32);
    do {
        uint256 nonce;
        prng.Generate((unsigned char*)&nonce, 32);
        int ret = secp256k1_ecdsa_sign_compact((const unsigned char*)&hash, 32, &vchSig[1], begin(), (unsigned char*)&nonce, &rec);
        nonce = 0;
        if (ret)
            break;
    } while(true);
    assert(rec != -1);
    vchSig[0] = 27 + rec + (fCompressed ? 4 : 0);
    return true;
}

bool CKey::Load(CPrivKey &privkey, CPubKey &vchPubKey, bool fSkipCheck=false) {
    if (!secp256k1_ec_privkey_import((unsigned char*)begin(), &privkey[0], privkey.size()))
        return false;
    fCompressed = vchPubKey.IsCompressed();
    fValid = true;

    if (fSkipCheck)
        return true;

    return VerifyPubKey(vchPubKey);
}

bool CKey::Derive(CKey& keyChild, unsigned char ccChild[32], unsigned int nChild, const unsigned char cc[32]) const {
    assert(IsValid());
    assert(IsCompressed());
    unsigned char out[64];
    LockObject(out);
    if ((nChild >> 31) == 0) {
        CPubKey pubkey = GetPubKey();
        assert(pubkey.begin() + 33 == pubkey.end());
        BIP32Hash(cc, nChild, *pubkey.begin(), pubkey.begin()+1, out);
    } else {
        assert(begin() + 32 == end());
        BIP32Hash(cc, nChild, 0, begin(), out);
    }
    memcpy(ccChild, out+32, 32);
    memcpy((unsigned char*)keyChild.begin(), begin(), 32);
    bool ret = secp256k1_ec_privkey_tweak_add((unsigned char*)keyChild.begin(), out);
    UnlockObject(out);
    keyChild.fCompressed = true;
    keyChild.fValid = ret;
    return ret;
}

bool CExtKey::Derive(CExtKey &out, unsigned int nChild) const {
    out.nDepth = nDepth + 1;
    CKeyID id = key.GetPubKey().GetID();
    memcpy(&out.vchFingerprint[0], &id, 4);
    out.nChild = nChild;
    return key.Derive(out.key, out.vchChainCode, nChild, vchChainCode);
}

void CExtKey::SetMaster(const unsigned char *seed, unsigned int nSeedLen) {
    static const unsigned char hashkey[] = {'B','i','t','c','o','i','n',' ','s','e','e','d'};
    unsigned char out[64];
    LockObject(out);
    CHMAC_SHA512(hashkey, sizeof(hashkey)).Write(seed, nSeedLen).Finalize(out);
    key.Set(&out[0], &out[32], true);
    memcpy(vchChainCode, &out[32], 32);
    UnlockObject(out);
    nDepth = 0;
    nChild = 0;
    memset(vchFingerprint, 0, sizeof(vchFingerprint));
}

CExtPubKey CExtKey::Neuter() const {
    CExtPubKey ret;
    ret.nDepth = nDepth;
    memcpy(&ret.vchFingerprint[0], &vchFingerprint[0], 4);
    ret.nChild = nChild;
    ret.pubkey = key.GetPubKey();
    memcpy(&ret.vchChainCode[0], &vchChainCode[0], 32);
    return ret;
}

void CExtKey::Encode(unsigned char code[74]) const {
    code[0] = nDepth;
    memcpy(code+1, vchFingerprint, 4);
    code[5] = (nChild >> 24) & 0xFF; code[6] = (nChild >> 16) & 0xFF;
    code[7] = (nChild >>  8) & 0xFF; code[8] = (nChild >>  0) & 0xFF;
    memcpy(code+9, vchChainCode, 32);
    code[41] = 0;
    assert(key.size() == 32);
    memcpy(code+42, key.begin(), 32);
}

void CExtKey::Decode(const unsigned char code[74]) {
    nDepth = code[0];
    memcpy(vchFingerprint, code+1, 4);
    nChild = (code[5] << 24) | (code[6] << 16) | (code[7] << 8) | code[8];
    memcpy(vchChainCode, code+9, 32);
    key.Set(code+42, code+74, true);
}

bool ECC_InitSanityCheck() {
#if !defined(USE_SECP256K1)
    if (!CECKey::SanityCheck()) {
        return false;
    }
#endif
    CKey key;
    key.MakeNewKey(true);
    CPubKey pubkey = key.GetPubKey();
    return key.VerifyPubKey(pubkey);
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
}
