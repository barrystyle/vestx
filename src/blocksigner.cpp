#include <blocksigner.h>
#include <keystore.h>
#include <primitives/block.h>
#include <utilstrencodings.h>
#include <messagesigner.h>

CBlockSigner::CBlockSigner(CBlock &block, const CKeyStore *keystore) :
    refBlock(block),
    refKeystore(keystore)
{

}

bool CBlockSigner::SignBlock()
{
    std::vector<std::vector<unsigned char>> vSolutions;
    txnouttype whichType;

    CKey keySecret;

    if(refBlock.IsProofOfStake())
    {
        const CTxOut& txout = refBlock.vtx[1]->vout[1];

        if (!Solver(txout.scriptPubKey, whichType, vSolutions))
            return false;

        CKeyID keyID;

        if (whichType == TX_PUBKEYHASH)
        {
            keyID = CKeyID(uint160(vSolutions[0]));
        }
        else if(whichType == TX_PUBKEY)
        {
            keyID = CPubKey(vSolutions[0]).GetID();
        }

        if (!refKeystore->GetKey(keyID, keySecret))
            return false;
        }
    else
    {
        const CTxOut& txout = refBlock.vtx[0]->vout[0];

        if (!Solver(txout.scriptPubKey, whichType, vSolutions))
            return false;

        CKeyID keyID;

        if (whichType == TX_PUBKEYHASH)
        {
            keyID = CKeyID(uint160(vSolutions[0]));
        }
        else if(whichType == TX_PUBKEY)
        {
            keyID = CPubKey(vSolutions[0]).GetID();
        }

        if (!refKeystore->GetKey(keyID, keySecret))
            return false;
    }
    return keySecret.SignCompact(refBlock.GetHash(), refBlock.vchBlockSig);
}

bool CBlockSigner::CheckBlockSignature() const
{
    if(refBlock.IsProofOfWork())
        return true;

    if(refBlock.vchBlockSig.empty())
        return false;

    const CTxOut& txout = refBlock.vtx[1]->vout[1];

    CTxDestination destination;

    if(!ExtractDestination(txout.scriptPubKey, destination))
    {
        return false;
    }

    auto hashMessage = refBlock.GetHash();
    if(!refBlock.IsProofOfStake()) {
        return true;
    }

    std::string strError;
    return CHashSigner::VerifyHash(hashMessage, destination, refBlock.vchBlockSig, strError);

}
