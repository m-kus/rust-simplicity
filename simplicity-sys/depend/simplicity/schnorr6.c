#include "schnorr6.h"

/* A length-prefixed encoding of the following Simplicity program:
 *     (scribe (toWord256 0xDFF1D77F2A671C5F36183726DB2341BE58FEAE1DA2DECED843240F7B502BA659) &&&
 *      scribe (toWord256 0x5E2D58D8B3BCDF1ABADEC7829054F90DDA9805AAB56C77333024B9D0A508B75C)) &&&
 *      witness (toWord512 0xFFF97BD5755EEEA420453A14355235D382F6472F8568A18B2F057A14602975563CC27944640AC607CD107AE10923D9EF7A73C643E166BE5EBEAFA34B1AC553E2) >>>
 *     Simplicity.Programs.LibSecp256k1.Lib.bip_0340_verify
 * with jets.
 */
const unsigned char schnorr6[] = {
  0xc6, 0xd5, 0xbf, 0xe3, 0xae, 0xfe, 0x54, 0xce, 0x38, 0xbe, 0x6c, 0x30, 0x6e, 0x4d, 0xb6, 0x46, 0x83, 0x7c, 0xb1, 0xfd,
  0x5c, 0x3b, 0x45, 0xbd, 0x9d, 0xb0, 0x86, 0x48, 0x1e, 0xf6, 0xa0, 0x57, 0x4c, 0xb2, 0xbc, 0x5a, 0xb1, 0xb1, 0x67, 0x79,
  0xbe, 0x35, 0x75, 0xbd, 0x8f, 0x05, 0x20, 0xa9, 0xf2, 0x1b, 0xb5, 0x30, 0x0b, 0x55, 0x6a, 0xd8, 0xee, 0x66, 0x60, 0x49,
  0x73, 0xa1, 0x4a, 0x11, 0x6e, 0xb8, 0xe2, 0x8d, 0x8c, 0x04, 0x00
};

const size_t sizeof_schnorr6 = sizeof(schnorr6);
const unsigned char schnorr6_witness[] = {
  0xff, 0xf9, 0x7b, 0xd5, 0x75, 0x5e, 0xee, 0xa4, 0x20, 0x45, 0x3a, 0x14, 0x35, 0x52, 0x35, 0xd3, 0x82, 0xf6, 0x47, 0x2f,
  0x85, 0x68, 0xa1, 0x8b, 0x2f, 0x05, 0x7a, 0x14, 0x60, 0x29, 0x75, 0x56, 0x3c, 0xc2, 0x79, 0x44, 0x64, 0x0a, 0xc6, 0x07,
  0xcd, 0x10, 0x7a, 0xe1, 0x09, 0x23, 0xd9, 0xef, 0x7a, 0x73, 0xc6, 0x43, 0xe1, 0x66, 0xbe, 0x5e, 0xbe, 0xaf, 0xa3, 0x4b,
  0x1a, 0xc5, 0x53, 0xe2
};

const size_t sizeof_schnorr6_witness = sizeof(schnorr6_witness);

/* The commitment Merkle root of the above schnorr6 Simplicity expression. */
const uint32_t schnorr6_cmr[] = {
  0xc5d4e54fu, 0x4507f3d9u, 0x907e2ac4u, 0x554a8647u, 0x22e2fdd8u, 0x4da0f9eau, 0x9df7b8dau, 0x69f88e45u
};

/* The identity Merkle root of the above schnorr6 Simplicity expression. */
const uint32_t schnorr6_imr[] = {
  0x9cffb490u, 0xbd19d2b0u, 0x0ed557f7u, 0xb4c10527u, 0xa53021d4u, 0x79c607b1u, 0x24f95daau, 0xf8268f9du
};

/* The annotated Merkle root of the above schnorr6 Simplicity expression. */
const uint32_t schnorr6_amr[] = {
  0x30487388u, 0x5e7b26bau, 0x1fb5b6b8u, 0x0557ecddu, 0x27a24599u, 0xdb952e4cu, 0xb9f930fcu, 0x53469638u
};

/* The cost of the above schnorr6 Simplicity expression in milli weight units. */
const ubounded schnorr6_cost = 52219;
