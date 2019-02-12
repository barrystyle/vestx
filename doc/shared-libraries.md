Shared Libraries
================

## vestxconsensus

The purpose of this library is to make the verification functionality that is critical to VESTX's consensus available to other applications, e.g. to language bindings.

### API

The interface is defined in the C header `vestxconsensus.h` located in  `src/script/vestxconsensus.h`.

#### Version

`vestxconsensus_version` returns an `unsigned int` with the API version *(currently at an experimental `0`)*.

#### Script Validation

`vestxconsensus_verify_script` returns an `int` with the status of the verification. It will be `1` if the input script correctly spends the previous output `scriptPubKey`.

##### Parameters
- `const unsigned char *scriptPubKey` - The previous output script that encumbers spending.
- `unsigned int scriptPubKeyLen` - The number of bytes for the `scriptPubKey`.
- `const unsigned char *txTo` - The transaction with the input that is spending the previous output.
- `unsigned int txToLen` - The number of bytes for the `txTo`.
- `unsigned int nIn` - The index of the input in `txTo` that spends the `scriptPubKey`.
- `unsigned int flags` - The script validation flags *(see below)*.
- `vestxconsensus_error* err` - Will have the error/success code for the operation *(see below)*.

##### Script Flags
- `vestxconsensus_SCRIPT_FLAGS_VERIFY_NONE`
- `vestxconsensus_SCRIPT_FLAGS_VERIFY_P2SH` - Evaluate P2SH ([BIP16](https://github.com/vestx/bips/blob/master/bip-0016.mediawiki)) subscripts
- `vestxconsensus_SCRIPT_FLAGS_VERIFY_DERSIG` - Enforce strict DER ([BIP66](https://github.com/vestx/bips/blob/master/bip-0066.mediawiki)) compliance
- `vestxconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY` - Enforce NULLDUMMY ([BIP147](https://github.com/vestx/bips/blob/master/bip-0147.mediawiki))
- `vestxconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY` - Enable CHECKLOCKTIMEVERIFY ([BIP65](https://github.com/vestx/bips/blob/master/bip-0065.mediawiki))
- `vestxconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY` - Enable CHECKSEQUENCEVERIFY ([BIP112](https://github.com/vestx/bips/blob/master/bip-0112.mediawiki))
- `vestxconsensus_SCRIPT_FLAGS_VERIFY_WITNESS` - Enable WITNESS ([BIP141](https://github.com/vestx/bips/blob/master/bip-0141.mediawiki))

##### Errors
- `vestxconsensus_ERR_OK` - No errors with input parameters *(see the return value of `vestxconsensus_verify_script` for the verification status)*
- `vestxconsensus_ERR_TX_INDEX` - An invalid index for `txTo`
- `vestxconsensus_ERR_TX_SIZE_MISMATCH` - `txToLen` did not match with the size of `txTo`
- `vestxconsensus_ERR_DESERIALIZE` - An error deserializing `txTo`
- `vestxconsensus_ERR_AMOUNT_REQUIRED` - Input amount is required if WITNESS is used

### Example Implementations
- [NVESTX](https://github.com/NicolasDorier/NVESTX/blob/master/NVESTX/Script.cs#L814) (.NET Bindings)
- [node-libvestxconsensus](https://github.com/bitpay/node-libvestxconsensus) (Node.js Bindings)
- [java-libvestxconsensus](https://github.com/dexX7/java-libvestxconsensus) (Java Bindings)
- [vestxconsensus-php](https://github.com/Bit-Wasp/vestxconsensus-php) (PHP Bindings)
