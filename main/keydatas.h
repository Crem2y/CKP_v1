#define KEYSET_MAX 16 // number of key sets
#define KEYS_H 4  // number of horiznal keys
#define KEYS_V 5  // number of vertical keys

// -- Key arrangement (physical) --
//     [  LCD   ]
//  V  a  b  c  d
//  |  e  f  g  h
//  v  i  j  k  l
//     m  n  o  p
//     q  r  s  t
//     H ->
// * a is mode change key (hold about 3sec)

// -- Key arrangement (list) --
// {{a,b,c,d},{e,f,g,h},{i,j,k,l},{m,n,o,p},{q,r,s,t}}

// -- How to set the mode-code --
// set bit 7~0, if key is {1,2,3,4}
// bit 7 : key 1 toggle mode?
// bit 6 : key 1 repeat mode?
// bit 5 : key 2 toggle mode?
// bit 4 : key 2 repeat mode?
// bit 3 : key 3 toggle mode?
// bit 2 : key 3 repeat mode?
// bit 1 : key 4 toggle mode?
// bit 0 : key 4 repeat mode? 

// -- special keycode(0x00 ~ 0x1F) mapping --
// at "customcode.h"

byte keySets[KEYSET_MAX][KEYS_V][KEYS_H+1] = { // V, H + 1byte(mode-code)
  {{0xDB,0xDC,0xDD,0xDE,0x00},
   {0xE7,0xE8,0xE9,0xDF,0x00},
   {0xE4,0xE5,0xE6,0xDF,0x00},
   {0xE1,0xE2,0xE3,0xE0,0x00},
   {0xEA,F_S1,0xEB,0xB2,0x00}},// 0

  {{L_CN,M_LB,M_MB,M_RB,0x00},
   {M_UL,M_U ,M_UR,MH_U,0x54},
   {M_L ,M_LB,M_R ,MH_D,0x54},
   {M_DL,M_D ,M_DR,R_F ,0x55},
   {M_F ,M_S ,0X00,R_S ,0x01}},// 1

  {{0xB1,0xD8,0xD7,0xB0,0x00},
   { 't', 'g', 'h', 'y',0x00},
   { 'e', 'r', 'u', 'i',0x00},
   { 'd', 'f', 'j', 'k',0x00},
   { 'a', 's', 'k', 'l',0x00}},// 2

  {{0xDB,0xDC,0xDD,0xDE,0x00},
   {0xE7,0xE8,0xE9,0xDF,0x00},
   {0xE4,0xE5,0xE6,0xDF,0x00},
   {0xE1,0xE2,0xE3,0xE0,0x00},
   {0xEA,F_S1,0xEB,0xB2,0x00}},// 3

  {{0x00,0xD8,0xD7,0xD9,0x00},
   { '7', '8', '9',0xDA,0x00},
   { '4', '5', '6',0xDA,0x00},
   { '1', '2', '3', 'f',0x00},
   { '0',0xEA, ' ',0xC6,0x00}},// 4

  {{ 'q', 'e', 'r', 'f',0x00},
   { 'a',0xDA, 'w', 'd',0x00},
   {0xD8,0xD9, 's',0xD7,0x00},
   { 'y', 'u', 'i', 'o',0x00},
   { 'h', 'j', 'k', 'l',0x00}},// 5

  {{ 'q', 'e',0x81,0x80,0x00},
   { 'a',0xDA, 'w', 'd',0x00},
   {0xD8,0xD9, 's',0xD7,0x00},
   { 'y', 'u', 'i', 'o',0x00},
   { 'h', 'j', 'k', 'l',0x00}},// 6

  {{0x00, 'b', 'c', 'd',0x00},
   { 'e', 'f', 'g', 'h',0x00},
   { 'i', 'j', 'k', 'l',0x00},
   { 'm', 'n', 'o', 'p',0x00},
   { 'q', 'r', 's', 't',0x00}},// 7

  {{0x00, 'b', 'c', 'd',0x00},
   { 'e', 'f', 'g', 'h',0x00},
   { 'i', 'j', 'k', 'l',0x00},
   { 'm', 'n', 'o', 'p',0x00},
   { 'q', 'r', 's', 't',0x00}},// 8

  {{0x00, 'b', 'c', 'd',0x00},
   { 'e', 'f', 'g', 'h',0x00},
   { 'i', 'j', 'k', 'l',0x00},
   { 'm', 'n', 'o', 'p',0x00},
   { 'q', 'r', 's', 't',0x00}},// 9

  {{0x00,M_LB,M_MB,M_RB,0x00},
   {M_UL,M_U ,M_UR,MH_U,0x54},
   {M_L ,M_LB,M_R ,MH_D,0x74},
   {M_DL,M_D ,M_DR,R_F ,0x55},
   {M_F ,M_S ,0X00,R_S ,0x01}},// 10

  {{0x00,G_DL,G_DU,G_DR,0x00},
   {G_LU,G_LR,G_RU,G_RR,0x00},
   {G_LL,G_LD,G_RL,G_RD,0x00},
   {G_01,G_02,G_03,G_04,0x00},
   {G_05,G_06,G_07,G_08,0x00}},// 11

  {{0x00,G_21,G_22,G_23,0x00},
   {G_ZU,G_ZR,G_09,G_10,0x00},
   {G_ZL,G_ZD,G_11,G_12,0x00},
   {G_13,G_14,G_15,G_16,0x00},
   {G_17,G_18,G_19,G_20,0x00}},// 12

  {{0x00, 'b', 'c', 'd',0x00},
   { 'e', 'f', 'g', 'h',0x00},
   { 'i', 'j', 'k', 'l',0x00},
   { 'm', 'n', 'o', 'p',0x00},
   { 'q', 'r', 's', 't',0x00}},// 13

  {{0x00,S_CC,S_B ,S_CW,0x11},
   { 'e', 'f',R_F ,R_S ,0x05},
   { 'i', 'j', 'k', 'l',0x00},
   { 'm', 'n', 'o', 'p',0x00},
   { 'q', 'r', 's', 't',0x00}},// 14

  {{0x00,C_VM,C_VU,C_VD,0x00},
   {C_MP,C_MS,C_MN,C_MR,0x00},
   {C_CA,C_EM,C_BH,C_BB,0x00},
   {C_BF,C_FI,0x00,0x00,0x00},
   {M_4B,M_5B,M_6B,M_7B,0x00}} // 15
}; // keyset end

char modeString[KEYSET_MAX][17] = { // char*16 + 0x00(null)
  "  keypad mode   ", "   mouse mode   ", "  Rhythm mode\7  ", "clip studio mode", // 0~3
  "  youtube mode  ", " complex game 1 ", " complex game 2 ", "  mode num 07   ", // 4~7
  "  mode num 08   ", "  mode num 09   ", "  macro mouse!  ", "  Gamepad mode  ", // 8~11
  " Gamepad mode2  ", "  mode num 13   ", "  Surface mode  ", " Consumer mode  "  // 12~15
}; // end

/*
  {{0x00,0x00,0x00,0x00,0x00},
   {0x00,0x00,0x00,0x00,0x00},
   {0x00,0x00,0x00,0x00,0x00},
   {0x00,0x00,0x00,0x00,0x00},
   {0x00,0x00,0x00,0x00,0x00}},
*/