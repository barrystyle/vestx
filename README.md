VESTX integration/staging tree
==============================

- built on bitcoin 0.17.1
- uses components from xsn/fxtc/dash 
- simultaneous pow/pos operation with masternodes
- pow algorithm is x16rt (gincoin-type)
- pos and pow timing is set at 40 seconds
- capable of 250tps peak
- coin schedule set for coinswap from older vestx (2:1 @ 20bn),
  - blocks 1 - 25,000 : 5000 VESTX
  - blocks 25,000 -   : 1000 VESTX
- masternode collateral is 25,000,000 VESTX
- masternode / miner/minting split is 60/40%

migration to bitcoin 0.18 already underway..

