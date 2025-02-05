	// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>
#include <genesis.h>
#include <consensus/merkle.h>

#include <tinyformat.h>
#include <util.h>
#include <utilstrencodings.h>

#include <assert.h>
#include <memory>

#include <chainparamsseeds.h>
#include <arith_uint256.h>
#include <pthread.h>

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
        consensus.BIP16Height = 0;
        consensus.BIP34Height = 0;
        consensus.powLimit = uint256S("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");

        consensus.nTargetTimespan = 43 * 60 * 60;
        consensus.nStakeTargetSpacing = 1.25 * 60;
        consensus.nTargetSpacingWorkMax = 1.25 * consensus.nStakeTargetSpacing;
        consensus.nPowTargetSpacing = consensus.nStakeTargetSpacing;
        consensus.nStakeMinConfirmations = 6;
        consensus.nCoinbaseMaturity = 40;
        consensus.nDgwPastBlocks = 30;

        consensus.nStartMiningTime = 1605440641;

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00000000000000000000000000000000000000000000000051ba0e7743d8f042");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x71d0dcd63b6dd49e923aeac4a3d596b76d09756109b003e4ef39c25715e1a45d");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xa4;
        pchMessageStart[1] = 0xf1;
        pchMessageStart[2] = 0xc9;
        pchMessageStart[3] = 0xd3;
        vAlertPubKey = ParseHex("040797a85cafdf223783f0e31b7e3554b61f873efb0abaa6fa56632308ae2d7309a8afdf6c221a07f73fc288c7626f3cd97a6121241db0d60e0e375aaa87f4b9a2");
        nDefaultPort = 5995;

        genesis = CreateGenesisBlock(1605440641, 128396, 0x1e0fffff, 1, 0);
//        MineGenesisBlock(genesis, consensus.powLimit);
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("0x19a8a53eaeb38a16b76bad30e70cdb228efafa791b5f2150c2a5934a431a1492"));
        assert(genesis.hashMerkleRoot == uint256S("0x5443b97731232a13f0671d95ba0b3ba59389963d2be7127caf22dfbccdc23aa3"));

        vSeeds.emplace_back("45.63.65.34");
        vSeeds.emplace_back("137.220.60.11");
        vSeeds.emplace_back("103.249.70.51");

        base58Prefixes[PUBKEY_ADDRESS] = {0x37};
        base58Prefixes[SCRIPT_ADDRESS] = {0x38};
        base58Prefixes[SECRET_KEY]     = {0xB0};

        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E}; // xpub
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4}; // xprv

        // human readable prefix to bench32 address
        bech32_hrp = "plsr";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        nMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = {
            {
                {0, uint256S("0x19a8a53eaeb38a16b76bad30e70cdb228efafa791b5f2150c2a5934a431a1492")},
                {1, uint256S("0xccb4587de1142c25a57b13d90a6287c001ce0cf7c9c24d0d16696cc885b2a928")},
                {15, uint256S("0xfb4ca73911e108d6a3a9bfa10fbd9b0e2d2c683dc49866e6cf75f2ca4cc3093a")},
                {45, uint256S("0x80be780f00430bb0988f7b2515f98b4768eb165f73593dbd1516780535b821c3")},
                {132, uint256S("0x1891da0e62ea9fa76146baced9790653b79c3aad8160d97edba61ad824b829bc")},
                {1000, uint256S("0x62e7a25bd5e3b130df3b6841e7c8503f403ea6e1fe1bad7122913ee8c8c9f53e")},
                {10000, uint256S("0x3b93ea64a485b15bd746fb89332d2f68afc5cceed914f5b2a0d3d89659ecfbb8")},
                {30000, uint256S("0x313428907dc75f527bd9faaf0cfe904b3d9a9ced34e482f6cd97e299c536bc79")},
                {68625, uint256S("0x71d0dcd63b6dd49e923aeac4a3d596b76d09756109b003e4ef39c25715e1a45d")},
            }
        };

        chainTxData = ChainTxData{
			// Data from rpc: getchaintxstats 0
			/* nTime    */ 1646267619,
			/* nTxCount */ 112354,
			/* dTxRate  */ 0.03616576107949424
        };
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.BIP16Height = 0;
        consensus.BIP34Height = 0;
        consensus.powLimit = uint256S("000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nTargetTimespan = 24 * 60;  // 24 minutes
        consensus.nStakeTargetSpacing = 1 * 60;  // 1-minute block spacing
        consensus.nTargetSpacingWorkMax = 1 * consensus.nStakeTargetSpacing; // 24-minute
        consensus.nPowTargetSpacing = consensus.nStakeTargetSpacing;
        consensus.nStakeMinConfirmations = 1;
        consensus.nCoinbaseMaturity = 6; // 6 confirmations
        consensus.nDgwPastBlocks = 30;


        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nStartMiningTime = 1605440641;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xc4;
        pchMessageStart[1] = 0xf4;
        pchMessageStart[2] = 0xc1;
        pchMessageStart[3] = 0xe6;
        nDefaultPort = 5998;
        vAlertPubKey = ParseHex("04bef9e37b5da8fb263aff719047b8d148875a4d343f8f093534f6be911b9e7d5b7b678507b24b4b4948f0b8a884da3afd38484a1b37ea33018e32c9bd79e19d9f");

        genesis = CreateGenesisBlock(1605440641, 200008037, 0x1f00ffff, 1, 0);
 
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("0xf035a8cda8f5aaf9592ffcab28c3c08a245fd236adb82432c242b4ad364b9d4e"));
        assert(genesis.hashMerkleRoot == uint256S("0x5443b97731232a13f0671d95ba0b3ba59389963d2be7127caf22dfbccdc23aa3"));

        vFixedSeeds.clear();
        vSeeds.clear();

        // nodes with support for servicebits filtering should be at the top
        vSeeds.emplace_back("23.147.229.244");
        vSeeds.emplace_back("");
        vSeeds.emplace_back("");

        base58Prefixes[PUBKEY_ADDRESS] = {0x80}; // t
        base58Prefixes[SCRIPT_ADDRESS] = {0x7a};
        base58Prefixes[SECRET_KEY]     = {0x2e};
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF}; // tpub
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94}; // tprv

        // human readable prefix to bench32 address
        bech32_hrp = "tplsr";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        nMiningRequiresPeers = 1;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = {
                {
                        {0, uint256S("0xf035a8cda8f5aaf9592ffcab28c3c08a245fd236adb82432c242b4ad364b9d4e")},
            }
        };

        chainTxData = ChainTxData{
                1605440641,
                0,
                0
        };

    }
};

/**
 * Regression test
 */

class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.BIP16Height = 0; // always enforce P2SH BIP16 on regtest
        consensus.BIP34Height = 0; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        consensus.BIP34Hash = uint256();
        consensus.powLimit = uint256S("000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // ~arith_uint256(0) >> 28;
        consensus.nTargetTimespan = 3 * 24 * 60 * 60; // two weeks
        consensus.nStakeTargetSpacing = 1 * 60; // 1-minute block spacing
        consensus.nTargetSpacingWorkMax = 1 * consensus.nStakeTargetSpacing; //
        consensus.nPowTargetSpacing = consensus.nStakeTargetSpacing;
        consensus.nStakeMinConfirmations = 1; //
        consensus.nCoinbaseMaturity = 2;
        consensus.nDgwPastBlocks = 3;


        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nStartMiningTime = 1605440641;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xc5;
        pchMessageStart[1] = 0xfb;
        pchMessageStart[2] = 0xc4;
        pchMessageStart[3] = 0xe6;
        nDefaultPort = 5993;
        vAlertPubKey = ParseHex("04173a381c9a7c0bf2e8f5dd3c71d059b025b6fee42b92224af842bd40ba1c995d4e2e79d2fda539471ffb2cec48f45557c3f34d0269da3b6ae31eb7f48039b719");

        genesis = CreateGenesisBlock(1605440641, 200008037, 0x1f00ffff, 1, 0);

        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0xf035a8cda8f5aaf9592ffcab28c3c08a245fd236adb82432c242b4ad364b9d4e"));
        assert(genesis.hashMerkleRoot == uint256S("0x5443b97731232a13f0671d95ba0b3ba59389963d2be7127caf22dfbccdc23aa3"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        checkpointData = {
            {
                {0, uint256S("0xf035a8cda8f5aaf9592ffcab28c3c08a245fd236adb82432c242b4ad364b9d4e")},
            }
        };

        chainTxData = ChainTxData{
            1605440641,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = {0x80}; // t
        base58Prefixes[SCRIPT_ADDRESS] = {0x7a};
        base58Prefixes[SECRET_KEY]     = {0x2e};
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF}; // tpub
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94}; // tprv

        bech32_hrp = "rtplsr";

        nMiningRequiresPeers = 0;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
    }
};

static std::unique_ptr <CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr <CChainParams> CreateChainParams(const std::string &chain) {
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string &network) {
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}
