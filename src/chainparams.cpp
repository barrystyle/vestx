// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>
#include <consensus/merkle.h>

#include <tinyformat.h>
#include <util.h>
#include <utilstrencodings.h>
#include <arith_uint256.h>

#include <assert.h>

#include <chainparamsseeds.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "vestx powposmn test 2019";
    const CScript genesisOutputScript = CScript() << ParseHex("03042a235a39a72d7b1296313b0193ba3f93ad1a1fa2d72f1cab4f21d342c9d5b8") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nLastPoWBlock = 75;
        consensus.nFirstBlocksEmpty = 20000;
        consensus.nSubsidyHalvingInterval = 43200;
        consensus.nMasternodePaymentsStartBlock = 100;
        consensus.nMasternodePaymentsIncreaseBlock = 158000;
        consensus.nMasternodePaymentsIncreasePeriod = 576*30;
        consensus.nInstantSendKeepLock = 24;
        consensus.nBudgetPaymentsStartBlock = 0;
        consensus.nBudgetPaymentsCycleBlocks = 16616;
        consensus.nBudgetPaymentsWindowBlocks = 100;
        consensus.nBudgetProposalEstablishingTime = 60*60*24;
        consensus.nSuperblockCycle = 43200;
        consensus.nSuperblockStartBlock = consensus.nSuperblockCycle;
        consensus.nGovernanceMinQuorum = 10;
        consensus.nGovernanceFilterElements = 20000;
        consensus.BIP34Height = consensus.nLastPoWBlock;
        consensus.BIP34Hash = uint256S("0000000000000000000000000000000000000000000000000000000000000000");
        consensus.BIP65Height = consensus.nLastPoWBlock;
        consensus.BIP66Height = consensus.nLastPoWBlock;
        consensus.powLimit = uint256S("0000ffff00000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 15 * 60;
        consensus.nPowTargetSpacing = 3 * 60;
        consensus.nPosTargetSpacing = consensus.nPowTargetSpacing;
        consensus.nPosTargetTimespan = consensus.nPowTargetTimespan;
        consensus.nMerchantnodeMinimumConfirmations = 1;
        consensus.nMasternodeMinimumConfirmations = 15;
        consensus.nStakeMinAge = 10 * 60;
        consensus.nStakeMaxAge = 60 * 60 * 24 * 30;
        consensus.nCoinbaseMaturity = 20;
        consensus.nTPoSContractSignatureDeploymentTime = NEVER;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1080;
        consensus.nMinerConfirmationWindow = 1440;

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999;

        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1533167940;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1564012740;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0000000000000000000000000000000000000000000000000000000000000000");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0000000000000000000000000000000000000000000000000000000000000000");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xb0;
        pchMessageStart[1] = 0xc0;
        pchMessageStart[2] = 0xd0;
        pchMessageStart[3] = 0xe0;
        nDefaultPort = 20000;
        nPruneAfterHeight = 100000;
        nMaxReorganizationDepth = 100;

	// genesis routine
	uint32_t nTime = 1550490000;
	uint32_t nNonce = 0;
	if (nNonce == 0)
	{
	  while (UintToArith256(genesis.GetHash()) > UintToArith256(consensus.powLimit))
	  {
		  nNonce++;
		  if (nNonce % 1024 == 0) printf("\rnonce %08x", nNonce);
		  genesis = CreateGenesisBlock(nTime, nNonce, 0x1f00ffff, 1, 0 * COIN);
	  }
	  printf("\ngenesis is %s\n", genesis.ToString().c_str());
	}
	else
	{
          genesis = CreateGenesisBlock(nTime, nNonce, 0x1f00ffff, 1, 0 * COIN);
	}

        consensus.hashGenesisBlock = genesis.GetHash();
        // vSeeds.emplace_back("autoseeds.vestxseed.xyz");

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,76);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,16);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,204);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};

        bech32_hrp = "xc";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 60*60;
        strSporkPubKey = "030a2b7fdf1f123f3686ebc00f1226a20275bc785570ef069e2c2d81b61d616e91";

        checkpointData = {
            {
                { 0, uint256S("0000000000000000000000000000000000000000000000000000000000000000")},
            }
        };

        chainTxData = ChainTxData{
            // Data as of block 0000000000000000002d6cca6761c99b3c2e936f9a0e304b7c7651a993f461de (height 506081).
            1520274471, // * UNIX timestamp of last known number of transactions
            2000,  // * total number of transactions between genesis and that timestamp
                        //   (the tx=... number in the SetBestChain debug.log lines)
            1.0         // * estimated number of transactions per second after that timestamp
        };

        /* disable fallback fee on mainnet */
        m_fallback_fee_enabled = true;
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nLastPoWBlock = 75;
        consensus.nSubsidyHalvingInterval = 10000;
        consensus.nFirstBlocksEmpty = 20;
        consensus.nMasternodePaymentsStartBlock = 4010; // not true, but it's ok as long as it's less then nMasternodePaymentsIncreaseBlock
        consensus.nMasternodePaymentsIncreaseBlock = 4030;
        consensus.nMasternodePaymentsIncreasePeriod = 10;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 1000;
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 1010; // NOTE: Should satisfy nSuperblockStartBlock > nBudgetPeymentsStartBlock
        consensus.nSuperblockCycle = 24; // Superblocks can be issued hourly on testnet
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 500;
        consensus.BIP34Height = consensus.nLastPoWBlock;
        consensus.BIP34Hash = uint256S("0000000000000000000000000000000000000000000000000000000000000000");
        consensus.BIP65Height = 0;
        consensus.BIP66Height = 0;
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 24 * 60 * 60; // VESTX: 1 day
        consensus.nPowTargetSpacing = 1 * 60; // VESTX: 1 minutes
        consensus.nPosTargetSpacing = 1 * 60; // PoSW: 1 minutes
        consensus.nPosTargetTimespan = 60 * 40;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMerchantnodeMinimumConfirmations = 1;
        consensus.fPowNoRetargeting = false;
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMaxAge = 60 * 60 * 24; // one day
        consensus.nCoinbaseMaturity = 20;
        consensus.nTPoSContractSignatureDeploymentTime = 1522782000;
        consensus.nRuleChangeActivationThreshold = 30; // 75% for testchains
        consensus.nMinerConfirmationWindow = 40; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

//        // Deployment of BIP68, BIP112, and BIP113.
//        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
//        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1456790400; // March 1st, 2016
//        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1493596800; // May 1st, 2017

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1533004200; // June 31 2018 @ 02:30 hours UTC
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1560284399; // June 11 2019

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE; // March 1st, 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT; // May 1st, 2017

//        // Deployment of SegWit (BIP141, BIP143, and BIP147)
//        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
//        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE; // May 1st 2016
//        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT; // May 1st 2017

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x0000000004f5aef732d572ff514af99a995702c92e4452c7af10858231668b1f"); //1135275

        pchMessageStart[0] = 0xce;
        pchMessageStart[1] = 0xe2;
        pchMessageStart[2] = 0xca;
        pchMessageStart[3] = 0xff;
        nDefaultPort = 29999;
        nPruneAfterHeight = 1000;

        // genesis routine
        uint32_t nTime = 1550490001;
        uint32_t nNonce = 0;
        if (nNonce == 0)
        {
          while (UintToArith256(genesis.GetHash()) > UintToArith256(consensus.powLimit))
          {
                  nNonce++;
                  if (nNonce % 1024 == 0) printf("\rnonce %08x", nNonce);
                  genesis = CreateGenesisBlock(nTime, nNonce, 0x1f00ffff, 1, 0 * COIN);
          }
          printf("\ngenesis is %s\n", genesis.ToString().c_str());
        }
        else
        {
          genesis = CreateGenesisBlock(nTime, nNonce, 0x1f00ffff, 1, 0 * COIN);
        }

        consensus.hashGenesisBlock = genesis.GetHash();

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
//        vSeeds.emplace_back("testnet-seed.vestx.jonasschnelli.ch");
//        vSeeds.emplace_back("seed.tvestx.petertodd.org");
//        vSeeds.emplace_back("seed.testnet.vestx.sprovoost.nl");
//        vSeeds.emplace_back("testnet-seed.bluematt.me"); // Just a static list of stable node(s), only supports x9

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,140);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,19);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "tb";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));
    vFixedSeeds.clear();

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes
        strSporkPubKey = "0209c1fb78849b929732cbda125bbb905ffc01aeffb5333badf20a9aef2d539b17";

        checkpointData = {
            {
                {0, uint256S("0000090dda92f4e2f31c0bf7630ff4e15f46b6d1813d64b3ef4f2ea300a0f0cc")},
            }
        };

        chainTxData = ChainTxData{
            // Data as of block 000000000000033cfa3c975eb83ecf2bb4aaedf68e6d279f6ed2b427c64caff9 (height 1260526)
            1516111682,
            0,
            0.09
        };

        /* enable fallback fee on testnet */
        m_fallback_fee_enabled = true;
    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}
