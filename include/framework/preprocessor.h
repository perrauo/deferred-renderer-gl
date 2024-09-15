#pragma once
#pragma warning (disable : 5105)

#include <cstring>

#define EXPAND(x) x

#define FOR_EACH_1(what, x, ...) what(x)
#define FOR_EACH_2(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_1(what, __VA_ARGS__))

#define FOR_EACH_3(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_2(what, __VA_ARGS__))
#define FOR_EACH_4(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_3(what, __VA_ARGS__))
#define FOR_EACH_5(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_4(what, __VA_ARGS__))
#define FOR_EACH_6(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_5(what, __VA_ARGS__))
#define FOR_EACH_7(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_6(what, __VA_ARGS__))

#define FOR_EACH_8(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_7(what, __VA_ARGS__))

#define FOR_EACH_9(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_8(what, __VA_ARGS__))

#define FOR_EACH_10(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_9(what, __VA_ARGS__))

#define FOR_EACH_11(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_10(what, __VA_ARGS__))

#define FOR_EACH_12(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_11(what, __VA_ARGS__))

#define FOR_EACH_13(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_12(what, __VA_ARGS__))

#define FOR_EACH_14(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_13(what, __VA_ARGS__))

#define FOR_EACH_15(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_14(what, __VA_ARGS__))

#define FOR_EACH_16(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_15(what, __VA_ARGS__))

//

#define FOR_EACH_17(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_16(what, __VA_ARGS__))

#define FOR_EACH_18(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_17(what, __VA_ARGS__))

#define FOR_EACH_19(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_18(what, __VA_ARGS__))

#define FOR_EACH_20(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_19(what, __VA_ARGS__))

#define FOR_EACH_21(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_20(what, __VA_ARGS__))

#define FOR_EACH_22(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_21(what, __VA_ARGS__))

#define FOR_EACH_23(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_22(what, __VA_ARGS__))

#define FOR_EACH_24(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_23(what, __VA_ARGS__))

#define FOR_EACH_25(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_24(what, __VA_ARGS__))

#define FOR_EACH_26(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_25(what, __VA_ARGS__))

#define FOR_EACH_27(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_26(what, __VA_ARGS__))

#define FOR_EACH_28(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_27(what, __VA_ARGS__))

#define FOR_EACH_29(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_28(what, __VA_ARGS__))

#define FOR_EACH_30(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_29(what, __VA_ARGS__))

#define FOR_EACH_31(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_30(what, __VA_ARGS__))

#define FOR_EACH_32(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_31(what, __VA_ARGS__))

#define FOR_EACH_33(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_32(what, __VA_ARGS__))

#define FOR_EACH_34(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_33(what, __VA_ARGS__))

#define FOR_EACH_35(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_34(what, __VA_ARGS__))

#define FOR_EACH_36(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_35(what, __VA_ARGS__))

#define FOR_EACH_37(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_36(what, __VA_ARGS__))


#define FOR_EACH_38(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_37(what, __VA_ARGS__))


#define FOR_EACH_39(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_38(what, __VA_ARGS__))


#define FOR_EACH_40(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_39(what, __VA_ARGS__))


#define FOR_EACH_41(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_40(what, __VA_ARGS__))


#define FOR_EACH_42(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_41(what, __VA_ARGS__))

#define FOR_EACH_43(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_42(what, __VA_ARGS__))

#define FOR_EACH_44(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_43(what, __VA_ARGS__))

#define FOR_EACH_45(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_44(what, __VA_ARGS__))

#define FOR_EACH_46(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_45(what, __VA_ARGS__))

#define FOR_EACH_47(what, x, ...)\
what(x)\
EXPAND(FOR_EACH_46(what, __VA_ARGS__))

#define FOR_EACH_NARG(...) FOR_EACH_NARG_(__VA_ARGS__, FOR_EACH_RSEQ_N())
#define FOR_EACH_NARG_(...) EXPAND(FOR_EACH_ARG_N(__VA_ARGS__))
#define FOR_EACH_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, N, ...) N
#define FOR_EACH_RSEQ_N()  47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
#define CONCAT(x,y) x##y
#define FOR_EACH_(N, what, ...) EXPAND(CONCAT(FOR_EACH_, N)(what, __VA_ARGS__))
#define FOR_EACH(what, ...) FOR_EACH_(FOR_EACH_NARG(__VA_ARGS__), what, __VA_ARGS__)


//#define FOR_EACH_N_(N, what, ...) EXPAND(CONCAT(FOR_EACH_, N)(what, __VA_ARGS__))
//#define FOR_EACH_N(what, ...) FOR_EACH_N_(FOR_EACH_NARG(__VA_ARGS__), what, __VA_ARGS__)


#define FOR_EACH_LAST_1(what, last, x, ...) last(x)
#define FOR_EACH_LAST_2(what, last, x, ...)\
what(x)\
EXPAND(FOR_EACH_LAST_1(what, last, __VA_ARGS__))

#define FOR_EACH_LAST_3(what, last, x, ...)\
what(x)\
EXPAND(FOR_EACH_LAST_2(what, last, __VA_ARGS__))
#define FOR_EACH_LAST_4(what, last, x, ...)\
what(x)\
EXPAND(FOR_EACH_LAST_3(what, last, __VA_ARGS__))
#define FOR_EACH_LAST_5(what, last, x, ...)\
what(x)\
EXPAND(FOR_EACH_LAST_4(what, last, __VA_ARGS__))
#define FOR_EACH_LAST_6(what, last, x, ...)\
what(x)\
EXPAND(FOR_EACH_LAST_5(what, last, __VA_ARGS__))
#define FOR_EACH_LAST_7(what, last, x, ...)\
what(x)\
EXPAND(FOR_EACH_LAST_6(what, last, __VA_ARGS__))
#define FOR_EACH_LAST_8(what, last, x, ...)\
what(x)\
EXPAND(FOR_EACH_LAST_7(what, last, __VA_ARGS__))
#define FOR_EACH_LAST_9(what, last, x, ...)\
what(x)\
EXPAND(FOR_EACH_LAST_8(what, last, __VA_ARGS__))
#define FOR_EACH_LAST_10(what, last, x, ...)\
what(x)\
EXPAND(FOR_EACH_LAST_9(what, last, __VA_ARGS__))
#define FOR_EACH_LAST_11(what, last, x, ...)\
what(x)\
EXPAND(FOR_EACH_LAST_10(what, last, __VA_ARGS__))
#define FOR_EACH_LAST_12(what, last, x, ...)\
what(x)\
EXPAND(FOR_EACH_LAST_11(what, last, __VA_ARGS__))
#define FOR_EACH_LAST_13(what, last, x, ...)\
what(x)\
EXPAND(FOR_EACH_LAST_12(what, last, __VA_ARGS__))
#define FOR_EACH_LAST_14(what, last, x, ...)\
what(x)\
EXPAND(FOR_EACH_LAST_13(what, last, __VA_ARGS__))
#define FOR_EACH_LAST_15(what, last, x, ...)\
what(x)\
EXPAND(FOR_EACH_LAST_14(what, last, __VA_ARGS__))
#define FOR_EACH_LAST_16(what, last, x, ...)\
what(x)\
EXPAND(FOR_EACH_LAST_15(what, last, __VA_ARGS__))
#define FOR_EACH_LAST_17(what, last, x, ...)\
what(x)\
EXPAND(FOR_EACH_LAST_16(what, last, __VA_ARGS__))
#define FOR_EACH_LAST_18(what, last, x, ...)\
what(x)\
EXPAND(FOR_EACH_LAST_17(what, last, __VA_ARGS__))
#define FOR_EACH_LAST_19(what, last, x, ...)\
what(x)\
EXPAND(FOR_EACH_LAST_18(what, last, __VA_ARGS__))
#define FOR_EACH_LAST_20(what, last, x, ...)\
what(x)\
EXPAND(FOR_EACH_LAST_19(what, last, __VA_ARGS__))
#define FOR_EACH_LAST_21(what, last, x, ...)\
what(x)\
EXPAND(FOR_EACH_LAST_20(what, last, __VA_ARGS__))
#define FOR_EACH_LAST_22(what, last, x, ...)\
what(x)\
EXPAND(FOR_EACH_LAST_21(what, last, __VA_ARGS__))
#define FOR_EACH_LAST_23(what, last, x, ...)\
what(x)\
EXPAND(FOR_EACH_LAST_22(what, last, __VA_ARGS__))


#define FOR_EACH_LAST_(N, what, last, ...) EXPAND(CONCAT(FOR_EACH_LAST_, N)(what, last, __VA_ARGS__))
#define FOR_EACH_LAST(what, last, ...) FOR_EACH_LAST_(FOR_EACH_NARG(__VA_ARGS__), what, last, __VA_ARGS__)

// FOR EACH WITH I

#define FOR_EACH_WITH_I_1(what,  x, ...) what(x, 1)
#define FOR_EACH_WITH_I_2(what,  x, ...)\
  what(x, 2)\
  EXPAND(FOR_EACH_WITH_I_1(what,   __VA_ARGS__))
#define FOR_EACH_WITH_I_3(what,  x, ...)\
  what(x, 3)\
  EXPAND(FOR_EACH_WITH_I_2(what,  __VA_ARGS__))
#define FOR_EACH_WITH_I_4(what,  x, ...)\
  what(x, 4)\
  EXPAND(FOR_EACH_WITH_I_3(what,   __VA_ARGS__))
#define FOR_EACH_WITH_I_5(what,  x, ...)\
  what(x, 5)\
  EXPAND(FOR_EACH_WITH_I_4(what,   __VA_ARGS__))
#define FOR_EACH_WITH_I_6(what,  x, ...)\
  what(x, 6)\
  EXPAND(FOR_EACH_WITH_I_5(what,   __VA_ARGS__))
#define FOR_EACH_WITH_I_7(what,  x, ...)\
  what(x, 7)\
  EXPAND(FOR_EACH_WITH_I_6(what,   __VA_ARGS__))
#define FOR_EACH_WITH_I_8(what,  x, ...)\
  what(x, 8)\
  EXPAND(FOR_EACH_WITH_I_7(what,   __VA_ARGS__))

#define FOR_EACH_WITH_I_9(what,  x, ...)\
  what(x, 9)\
  EXPAND(FOR_EACH_WITH_I_8(what,   __VA_ARGS__))

#define FOR_EACH_WITH_I_10(what,  x, ...)\
  what(x, 10)\
  EXPAND(FOR_EACH_WITH_I_9(what,   __VA_ARGS__))

#define FOR_EACH_WITH_I_11(what,  x, ...)\
  what(x, 11)\
  EXPAND(FOR_EACH_WITH_I_10(what,   __VA_ARGS__))

#define FOR_EACH_WITH_I_12(what,  x, ...)\
  what(x, 12)\
  EXPAND(FOR_EACH_WITH_I_11(what,   __VA_ARGS__))

#define FOR_EACH_WITH_I_13(what,  x, ...)\
  what(x, 13)\
  EXPAND(FOR_EACH_WITH_I_12(what,   __VA_ARGS__))

#define FOR_EACH_WITH_I_14(what,  x, ...)\
  what(x, 14)\
  EXPAND(FOR_EACH_WITH_I_13(what,   __VA_ARGS__))

#define FOR_EACH_WITH_I_15(what,  x, ...)\
  what(x, 15)\
  EXPAND(FOR_EACH_WITH_I_14(what,   __VA_ARGS__))

#define FOR_EACH_WITH_I_16(what,  x, ...)\
  what(x, 16)\
  EXPAND(FOR_EACH_WITH_I_15(what,   __VA_ARGS__))

#define FOR_EACH_WITH_I_(N , what ,...) EXPAND(CONCAT(FOR_EACH_WITH_I_, N)(what ,__VA_ARGS__))
#define FOR_EACH_WITH_I(what ,...) FOR_EACH_WITH_I_(FOR_EACH_NARG(__VA_ARGS__) , what ,__VA_ARGS__)




#define FOR_EACH_TWO_WITH_I_1(what, x1, x2, ...) what(x1, x2, 1, 2)
#define FOR_EACH_TWO_WITH_I_2(what,  x1, x2, ...)\
  what(x1, x2, 3, 4)\
  EXPAND(FOR_EACH_TWO_WITH_I_1(what,   __VA_ARGS__))
#define FOR_EACH_TWO_WITH_I_3(what, x1, x2, ...)\
  what(x1, x2, 5, 6)\
  EXPAND(FOR_EACH_TWO_WITH_I_2(what,  __VA_ARGS__))
#define FOR_EACH_TWO_WITH_I_4(what, x1, x2, ...)\
  what(x1, x2, 7, 8)\
  EXPAND(FOR_EACH_TWO_WITH_I_3(what,   __VA_ARGS__))
#define FOR_EACH_TWO_WITH_I_5(what,  x1, x2, ...)\
  what(x1, x2, 9, 10)\
  EXPAND(FOR_EACH_TWO_WITH_I_4(what,   __VA_ARGS__))
#define FOR_EACH_TWO_WITH_I_6(what, x1, x2, ...)\
  what(x1, x2, 11, 12)\
  EXPAND(FOR_EACH_TWO_WITH_I_5(what,   __VA_ARGS__))
#define FOR_EACH_TWO_WITH_I_7(what, x1, x2, ...)\
  what(x1, x2, 13, 14)\
  EXPAND(FOR_EACH_TWO_WITH_I_6(what,   __VA_ARGS__))
#define FOR_EACH_TWO_WITH_I_8(what, x1, x2, ...)\
  what(x1, x2, 15, 16)\
  EXPAND(FOR_EACH_TWO_WITH_I_7(what,   __VA_ARGS__))

#define FOR_EACH_TWO_WITH_I_9(what, x1, x2, ...)\
  what(x1, x2, 17, 18)\
  EXPAND(FOR_EACH_TWO_WITH_I_8(what,   __VA_ARGS__))

#define FOR_EACH_TWO_WITH_I_10(what, x1, x2, ...)\
  what(x1, x2, 19, 20)\
  EXPAND(FOR_EACH_TWO_WITH_I_9(what, __VA_ARGS__))

#define FOR_EACH_TWO_WITH_I_11(what, x1, x2, ...)\
  what(x1, x2, 21, 22)\
  EXPAND(FOR_EACH_TWO_WITH_I_10(what,   __VA_ARGS__))

#define FOR_EACH_TWO_WITH_I_12(what, x1, x2, ...)\
  what(x1, x2, 23, 24)\
  EXPAND(FOR_EACH_TWO_WITH_I_11(what,   __VA_ARGS__))

#define FOR_EACH_TWO_WITH_I_13(what, x1, x2, ...)\
  what(x1, x2, 25, 26)\
  EXPAND(FOR_EACH_TWO_WITH_I_12(what,   __VA_ARGS__))

#define FOR_EACH_TWO_WITH_I_14(what, x1, x2, ...)\
  what(x1, x2, 27, 28)\
  EXPAND(FOR_EACH_TWO_WITH_I_13(what,   __VA_ARGS__))

#define FOR_EACH_TWO_WITH_I_15(what, x1, x2, ...)\
  what(x1, x2, 29, 30)\
  EXPAND(FOR_EACH_TWO_WITH_I_14(what,   __VA_ARGS__))

#define FOR_EACH_TWO_WITH_I_16(what, x1, x2, ...)\
  what(x1, x2, 31, 32)\
  EXPAND(FOR_EACH_TWO_WITH_I_15(what,   __VA_ARGS__))

#define FOR_EACH_TWO_WITH_I_(N , what ,...) EXPAND(CONCAT(FOR_EACH_WITH_I_, N)(what, __VA_ARGS__))
#define FOR_EACH_TWO_WITH_I(what ,...) FOR_EACH_WITH_I_(FOR_EACH_NARG(__VA_ARGS__), what ,__VA_ARGS__)

//

#define FOR_EACH_WITH_ONE_I_1(what, with, x, ...) what(x, with)
#define FOR_EACH_WITH_ONE_I_2(what, with, x, ...)\
  what(x, with, 2)\
  EXPAND(FOR_EACH_WITH_ONE_I_1(what, with,  __VA_ARGS__))
#define FOR_EACH_WITH_ONE_I_3(what, with, x, ...)\
  what(x, with, 3)\
  EXPAND(FOR_EACH_WITH_ONE_I_2(what, with, __VA_ARGS__))
#define FOR_EACH_WITH_ONE_I_4(what, with, x, ...)\
  what(x, with, 4)\
  EXPAND(FOR_EACH_WITH_ONE_I_3(what, with,  __VA_ARGS__))
#define FOR_EACH_WITH_ONE_I_5(what, with, x, ...)\
  what(x, with, 5)\
  EXPAND(FOR_EACH_WITH_ONE_I_4(what, with,  __VA_ARGS__))
#define FOR_EACH_WITH_ONE_I_6(what, with, x, ...)\
  what(x, with, 6)\
  EXPAND(FOR_EACH_WITH_ONE_I_5(what, with,  __VA_ARGS__))
#define FOR_EACH_WITH_ONE_I_7(what, with, x, ...)\
  what(x, with, 7)\
  EXPAND(FOR_EACH_WITH_ONE_I_6(what, with,  __VA_ARGS__))
#define FOR_EACH_WITH_ONE_I_8(what, with, x, ...)\
  what(x, with, 8)\
  EXPAND(FOR_EACH_WITH_ONE_I_7(what, with,  __VA_ARGS__))

#define FOR_EACH_WITH_ONE_I_9(what, with, x, ...)\
  what(x, with, 9)\
  EXPAND(FOR_EACH_WITH_ONE_I_8(what, with,  __VA_ARGS__))

#define FOR_EACH_WITH_ONE_I_10(what, with, x, ...)\
  what(x, with, 10)\
  EXPAND(FOR_EACH_WITH_ONE_I_9(what, with,  __VA_ARGS__))

#define FOR_EACH_WITH_ONE_I_11(what, with, x, ...)\
  what(x, with, 11)\
  EXPAND(FOR_EACH_WITH_ONE_I_10(what, with,  __VA_ARGS__))

#define FOR_EACH_WITH_ONE_I_12(what, with, x, ...)\
  what(x, with, 12)\
  EXPAND(FOR_EACH_WITH_ONE_I_11(what, with,  __VA_ARGS__))

#define FOR_EACH_WITH_ONE_I_13(what, with, x, ...)\
  what(x, with, 13)\
  EXPAND(FOR_EACH_WITH_ONE_I_12(what, with,  __VA_ARGS__))

#define FOR_EACH_WITH_ONE_I_14(what, with, x, ...)\
  what(x, with, 14)\
  EXPAND(FOR_EACH_WITH_ONE_I_13(what, with,  __VA_ARGS__))

#define FOR_EACH_WITH_ONE_I_15(what, with, x, ...)\
  what(x, with. 15)\
  EXPAND(FOR_EACH_WITH_ONE_I_14(what, with,  __VA_ARGS__))

#define FOR_EACH_WITH_ONE_I_16(what, with, x, ...)\
  what(x, with, 16)\
  EXPAND(FOR_EACH_WITH_ONE_I_15(what, with,  __VA_ARGS__))

#define FOR_EACH_WITH_ONE_I_(N , what ,with ,...) EXPAND(CONCAT(FOR_EACH_WITH_, N)(what ,with ,__VA_ARGS__))
#define FOR_EACH_WITH_ONE_I(what ,with ,...) FOR_EACH_WITH_(FOR_EACH_NARG(__VA_ARGS__) , what ,with ,__VA_ARGS__)

// FOR_EACH_TWO

//#define FOR_EACH_1(what, x, ...) what(x)
//#define FOR_EACH_2(what, x, ...)\
//what(x)\
//EXPAND(FOR_EACH_1(what, __VA_ARGS__))
//
//#define FOR_EACH_3(what, x, ...)\
//what(x)\
//EXPAND(FOR_EACH_2(what, __VA_ARGS__))
//#define FOR_EACH_4(what, x, ...)\
//what(x)\
//EXPAND(FOR_EACH_3(what, __VA_ARGS__))
//#define FOR_EACH_5(what, x, ...)\
//what(x)\
//EXPAND(FOR_EACH_4(what, __VA_ARGS__))
//#define FOR_EACH_6(what, x, ...)\
//what(x)\
//EXPAND(FOR_EACH_5(what, __VA_ARGS__))
//#define FOR_EACH_7(what, x, ...)\
//what(x)\
//EXPAND(FOR_EACH_6(what, __VA_ARGS__))
//
//#define FOR_EACH_8(what, x, ...)\
//what(x)\
//EXPAND(FOR_EACH_7(what, __VA_ARGS__))
//
//#define FOR_EACH_9(what, x, ...)\
//what(x)\
//EXPAND(FOR_EACH_8(what, __VA_ARGS__))
//
//#define FOR_EACH_10(what, x, ...)\
//what(x)\
//EXPAND(FOR_EACH_9(what, __VA_ARGS__))
//
//#define FOR_EACH_11(what, x, ...)\
//what(x)\
//EXPAND(FOR_EACH_10(what, __VA_ARGS__))
//
//#define FOR_EACH_12(what, x, ...)\
//what(x)\
//EXPAND(FOR_EACH_11(what, __VA_ARGS__))
//
//#define FOR_EACH_13(what, x, ...)\
//what(x)\
//EXPAND(FOR_EACH_12(what, __VA_ARGS__))
//
//#define FOR_EACH_14(what, x, ...)\
//what(x)\
//EXPAND(FOR_EACH_13(what, __VA_ARGS__))
//
//#define FOR_EACH_15(what, x, ...)\
//what(x)\
//EXPAND(FOR_EACH_14(what, __VA_ARGS__))
//
//#define FOR_EACH_16(what, x, ...)\
//what(x)\
//EXPAND(FOR_EACH_15(what, __VA_ARGS__))
//
//#define FOR_EACH_NARG(...) FOR_EACH_NARG_(__VA_ARGS__, FOR_EACH_RSEQ_N())
//#define FOR_EACH_NARG_(...) EXPAND(FOR_EACH_ARG_N(__VA_ARGS__))
//#define FOR_EACH_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, N, ...) N
//#define FOR_EACH_RSEQ_N()  16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
//#define CONCAT(x,y) x##y
//#define FOR_EACH_TWO_(N, what, ...) EXPAND(CONCAT(FOR_EACH_, N)(what, __VA_ARGS__))
//#define FOR_EACH_TWO(what, ...) FOR_EACH_(FOR_EACH_NARG(__VA_ARGS__), what, __VA_ARGS__)


// FOR_EACH_WITH

#define FOR_EACH_WITH_1(what, with, x, ...) what(x, with)
#define FOR_EACH_WITH_2(what, with, x, ...)\
  what(x, with)\
  EXPAND(FOR_EACH_WITH_1(what, with,  __VA_ARGS__))
#define FOR_EACH_WITH_3(what, with, x, ...)\
  what(x, with)\
  EXPAND(FOR_EACH_WITH_2(what, with, __VA_ARGS__))
#define FOR_EACH_WITH_4(what, with, x, ...)\
  what(x, with)\
  EXPAND(FOR_EACH_WITH_3(what, with,  __VA_ARGS__))
#define FOR_EACH_WITH_5(what, with, x, ...)\
  what(x, with)\
  EXPAND(FOR_EACH_WITH_4(what, with,  __VA_ARGS__))
#define FOR_EACH_WITH_6(what, with, x, ...)\
  what(x, with)\
  EXPAND(FOR_EACH_WITH_5(what, with,  __VA_ARGS__))
#define FOR_EACH_WITH_7(what, with, x, ...)\
  what(x, with)\
  EXPAND(FOR_EACH_WITH_6(what, with,  __VA_ARGS__))
#define FOR_EACH_WITH_8(what, with, x, ...)\
  what(x, with)\
  EXPAND(FOR_EACH_WITH_7(what, with,  __VA_ARGS__))

#define FOR_EACH_WITH_9(what, with, x, ...)\
  what(x, with)\
  EXPAND(FOR_EACH_WITH_8(what, with,  __VA_ARGS__))

#define FOR_EACH_WITH_10(what, with, x, ...)\
  what(x, with)\
  EXPAND(FOR_EACH_WITH_9(what, with,  __VA_ARGS__))

#define FOR_EACH_WITH_11(what, with, x, ...)\
  what(x, with)\
  EXPAND(FOR_EACH_WITH_10(what, with,  __VA_ARGS__))

#define FOR_EACH_WITH_12(what, with, x, ...)\
  what(x, with)\
  EXPAND(FOR_EACH_WITH_11(what, with,  __VA_ARGS__))

#define FOR_EACH_WITH_13(what, with, x, ...)\
  what(x, with)\
  EXPAND(FOR_EACH_WITH_12(what, with,  __VA_ARGS__))

#define FOR_EACH_WITH_14(what, with, x, ...)\
  what(x, with)\
  EXPAND(FOR_EACH_WITH_13(what, with,  __VA_ARGS__))

#define FOR_EACH_WITH_15(what, with, x, ...)\
  what(x, with)\
  EXPAND(FOR_EACH_WITH_14(what, with,  __VA_ARGS__))

#define FOR_EACH_WITH_16(what, with, x, ...)\
  what(x, with)\
  EXPAND(FOR_EACH_WITH_15(what, with,  __VA_ARGS__))

#define FOR_EACH_WITH_(N , what ,with ,...) EXPAND(CONCAT(FOR_EACH_WITH_, N)(what ,with ,__VA_ARGS__))
#define FOR_EACH_WITH(what ,with ,...) FOR_EACH_WITH_(FOR_EACH_NARG(__VA_ARGS__) , what ,with ,__VA_ARGS__)

// FOR_EACH_WITH_TWO

#define FOR_EACH_WITH_TWO_1(what, with1, with2, x, ...) what(x, with1, with2)
#define FOR_EACH_WITH_TWO_2(what, with1, with2, x, ...)\
  what(x, with1, with2)\
  EXPAND(FOR_EACH_WITH_TWO_1(what, with1, with2,  __VA_ARGS__))
#define FOR_EACH_WITH_TWO_3(what, with1, with2, x, ...)\
  what(x, with1, with2)\
  EXPAND(FOR_EACH_WITH_TWO_2(what, with1, with2, __VA_ARGS__))
#define FOR_EACH_WITH_TWO_4(what, with1, with2, x, ...)\
  what(x, with1, with2)\
  EXPAND(FOR_EACH_WITH_TWO_3(what, with1, with2,  __VA_ARGS__))
#define FOR_EACH_WITH_TWO_5(what, with1, with2, x, ...)\
  what(x, with1, with2)\
  EXPAND(FOR_EACH_WITH_TWO_4(what, with1, with2,  __VA_ARGS__))
#define FOR_EACH_WITH_TWO_6(what, with1, with2, x, ...)\
  what(x, with1, with2)\
  EXPAND(FOR_EACH_WITH_TWO_5(what, with1, with2,  __VA_ARGS__))
#define FOR_EACH_WITH_TWO_7(what, with1, with2, x, ...)\
  what(x, with1, with2)\
  EXPAND(FOR_EACH_WITH_TWO_6(what, with1, with2,  __VA_ARGS__))
#define FOR_EACH_WITH_TWO_8(what, with1, with2, x, ...)\
  what(x, with1, with2)\
  EXPAND(FOR_EACH_WITH_TWO_7(what, with1, with2,  __VA_ARGS__))

#define FOR_EACH_WITH_TWO_9(what, with1, with2, x, ...)\
  what(x, with1, with2)\
  EXPAND(FOR_EACH_WITH_TWO_8(what, with1, with2,  __VA_ARGS__))

#define FOR_EACH_WITH_TWO_10(what, with1, with2, x, ...)\
  what(x, with1, with2)\
  EXPAND(FOR_EACH_WITH_TWO_9(what, with1, with2,  __VA_ARGS__))

#define FOR_EACH_WITH_TWO_11(what, with1, with2, x, ...)\
  what(x, with1, with2)\
  EXPAND(FOR_EACH_WITH_TWO_10(what, with1, with2,  __VA_ARGS__))

#define FOR_EACH_WITH_TWO_12(what, with1, with2, x, ...)\
  what(x, with1, with2)\
  EXPAND(FOR_EACH_WITH_TWO_11(what, with1, with2,  __VA_ARGS__))

#define FOR_EACH_WITH_TWO_13(what, with1, with2, x, ...)\
  what(x, with1, with2)\
  EXPAND(FOR_EACH_WITH_TWO_12(what, with1, with2,  __VA_ARGS__))

#define FOR_EACH_WITH_TWO_14(what, with1, with2, x, ...)\
  what(x, with1, with2)\
  EXPAND(FOR_EACH_WITH_TWO_13(what, with1, with2,  __VA_ARGS__))

#define FOR_EACH_WITH_TWO_15(what, with1, with2, x, ...)\
  what(x, with1, with2)\
  EXPAND(FOR_EACH_WITH_TWO_14(what, with1, with2,  __VA_ARGS__))

#define FOR_EACH_WITH_TWO_16(what, with1, with2, x, ...)\
  what(x, with1, with2)\
  EXPAND(FOR_EACH_WITH_TWO_15(what, with1, with2, __VA_ARGS__))

#define FOR_EACH_WITH_TWO_(N , what ,with1, with2,...) EXPAND(CONCAT(FOR_EACH_WITH_TWO_, N)(what ,with1, with2, __VA_ARGS__))
#define FOR_EACH_WITH_TWO(what ,with1, with2 ,...) FOR_EACH_WITH_TWO_(FOR_EACH_NARG(__VA_ARGS__) , what ,with1, with2 ,__VA_ARGS__)

// FOR_EACH_WITH_THREE

#define FOR_EACH_WITH_THREE_1(what, with1, with2, with3, x, ...) what(x, with1, with2, with3)
#define FOR_EACH_WITH_THREE_2(what, with1, with2, with3, x, ...)\
  what(x, with1, with2, with3)\
  EXPAND(FOR_EACH_WITH_THREE_1(what, with1, with2, with3,  __VA_ARGS__))
#define FOR_EACH_WITH_THREE_3(what, with1, with2, with3, x, ...)\
  what(x, with1, with2, with3)\
  EXPAND(FOR_EACH_WITH_THREE_2(what, with1, with2, with3, __VA_ARGS__))
#define FOR_EACH_WITH_THREE_4(what, with1, with2, with3, x, ...)\
  what(x, with1, with2, with3)\
  EXPAND(FOR_EACH_WITH_THREE_3(what, with1, with2, with3,  __VA_ARGS__))
#define FOR_EACH_WITH_THREE_5(what, with1, with2, with3, x, ...)\
  what(x, with1, with2, with3)\
  EXPAND(FOR_EACH_WITH_THREE_4(what, with1, with2, with3,  __VA_ARGS__))
#define FOR_EACH_WITH_THREE_6(what, with1, with2, with3, x, ...)\
  what(x, with1, with2, with3)\
  EXPAND(FOR_EACH_WITH_THREE_5(what, with1, with2, with3,  __VA_ARGS__))
#define FOR_EACH_WITH_THREE_7(what, with1, with2, with3, x, ...)\
  what(x, with1, with2, with3)\
  EXPAND(FOR_EACH_WITH_THREE_6(what, with1, with2, with3,  __VA_ARGS__))
#define FOR_EACH_WITH_THREE_8(what, with1, with2, with3, x, ...)\
  what(x, with1, with2, with3)\
  EXPAND(FOR_EACH_WITH_THREE_7(what, with1, with2, with3,  __VA_ARGS__))

#define FOR_EACH_WITH_THREE_9(what, with1, with2, with3, x, ...)\
  what(x, with1, with2, with3)\
  EXPAND(FOR_EACH_WITH_THREE_8(what, with1, with2, with3,  __VA_ARGS__))

#define FOR_EACH_WITH_THREE_10(what, with1, with2, with3, x, ...)\
  what(x, with1, with2, with3)\
  EXPAND(FOR_EACH_WITH_THREE_9(what, with1, with2, with3,  __VA_ARGS__))

#define FOR_EACH_WITH_THREE_11(what, with1, with2, with3, x, ...)\
  what(x, with1, with2, with3)\
  EXPAND(FOR_EACH_WITH_THREE_10(what, with1, with2, with3,  __VA_ARGS__))

#define FOR_EACH_WITH_THREE_12(what, with1, with2, with3, x, ...)\
  what(x, with1, with2, with3)\
  EXPAND(FOR_EACH_WITH_THREE_11(what, with1, with2, with3,  __VA_ARGS__))

#define FOR_EACH_WITH_THREE_13(what, with1, with2, with3, x, ...)\
  what(x, with1, with2, with3)\
  EXPAND(FOR_EACH_WITH_THREE_12(what, with1, with2, with3,  __VA_ARGS__))

#define FOR_EACH_WITH_THREE_14(what, with1, with2, with3, x, ...)\
  what(x, with1, with2, with3)\
  EXPAND(FOR_EACH_WITH_THREE_13(what, with1, with2, with3,  __VA_ARGS__))

#define FOR_EACH_WITH_THREE_15(what, with1, with2, with3, x, ...)\
  what(x, with1, with2, with3)\
  EXPAND(FOR_EACH_WITH_THREE_14(what, with1, with2, with3,  __VA_ARGS__))

#define FOR_EACH_WITH_THREE_16(what, with1, with2, with3, x, ...)\
  what(x, with1, with2, with3)\
  EXPAND(FOR_EACH_WITH_THREE_15(what, with1, with2, with3, __VA_ARGS__))

#define FOR_EACH_WITH_THREE_(N, what, with1, with2, with3, ...) EXPAND(CONCAT(FOR_EACH_WITH_THREE_, N)(what, with1, with2, with3, __VA_ARGS__))
#define FOR_EACH_WITH_THREE(what, with1, with2, with3, ...) FOR_EACH_WITH_THREE_(FOR_EACH_NARG(__VA_ARGS__), what, with1, with2, with3 ,__VA_ARGS__)


// FOR_EACH_WITH_FOUR

#define FOR_EACH_WITH_FOUR_1(what, with1, with2, with3, with4, x, ...) what(x, with1, with2, with3, with4)
#define FOR_EACH_WITH_FOUR_2(what, with1, with2, with3, with4, x, ...)\
  what(x, with1, with2, with3, with4)\
  EXPAND(FOR_EACH_WITH_FOUR_1(what, with1, with2, with3, with4,  __VA_ARGS__))
#define FOR_EACH_WITH_FOUR_3(what, with1, with2, with3, with4, x, ...)\
  what(x, with1, with2, with3, with4)\
  EXPAND(FOR_EACH_WITH_FOUR_2(what, with1, with2, with3, with4, __VA_ARGS__))
#define FOR_EACH_WITH_FOUR_4(what, with1, with2, with3, with4, x, ...)\
  what(x, with1, with2, with3, with4)\
  EXPAND(FOR_EACH_WITH_FOUR_3(what, with1, with2, with3, with4,  __VA_ARGS__))
#define FOR_EACH_WITH_FOUR_5(what, with1, with2, with3, with4, x, ...)\
  what(x, with1, with2, with3, with4)\
  EXPAND(FOR_EACH_WITH_FOUR_4(what, with1, with2, with3, with4,  __VA_ARGS__))
#define FOR_EACH_WITH_FOUR_6(what, with1, with2, with3, with4, x, ...)\
  what(x, with1, with2, with3, with4)\
  EXPAND(FOR_EACH_WITH_FOUR_5(what, with1, with2, with3, with4,  __VA_ARGS__))
#define FOR_EACH_WITH_FOUR_7(what, with1, with2, with3, with4, x, ...)\
  what(x, with1, with2, with3, with4)\
  EXPAND(FOR_EACH_WITH_FOUR_6(what, with1, with2, with3, with4,  __VA_ARGS__))
#define FOR_EACH_WITH_FOUR_8(what, with1, with2, with3, with4, x, ...)\
  what(x, with1, with2, with3, with4)\
  EXPAND(FOR_EACH_WITH_FOUR_7(what, with1, with2, with3, with4,  __VA_ARGS__))

#define FOR_EACH_WITH_FOUR_9(what, with1, with2, with3, with4, x, ...)\
  what(x, with1, with2, with3, with4)\
  EXPAND(FOR_EACH_WITH_FOUR_8(what, with1, with2, with3, with4,  __VA_ARGS__))

#define FOR_EACH_WITH_FOUR_10(what, with1, with2, with3, with4, x, ...)\
  what(x, with1, with2, with3, with4)\
  EXPAND(FOR_EACH_WITH_FOUR_9(what, with1, with2, with3, with4,  __VA_ARGS__))

#define FOR_EACH_WITH_FOUR_11(what, with1, with2, with3, with4, x, ...)\
  what(x, with1, with2, with3, with4)\
  EXPAND(FOR_EACH_WITH_FOUR_10(what, with1, with2, with3, with4,  __VA_ARGS__))

#define FOR_EACH_WITH_FOUR_12(what, with1, with2, with3, with4, x, ...)\
  what(x, with1, with2, with3, with4)\
  EXPAND(FOR_EACH_WITH_FOUR_11(what, with1, with2, with3, with4,  __VA_ARGS__))

#define FOR_EACH_WITH_FOUR_13(what, with1, with2, with3, with4, x, ...)\
  what(x, with1, with2, with3, with4)\
  EXPAND(FOR_EACH_WITH_FOUR_12(what, with1, with2, with3, with4,  __VA_ARGS__))

#define FOR_EACH_WITH_FOUR_14(what, with1, with2, with3, with4, x, ...)\
  what(x, with1, with2, with3, with4)\
  EXPAND(FOR_EACH_WITH_FOUR_13(what, with1, with2, with3, with4,  __VA_ARGS__))

#define FOR_EACH_WITH_FOUR_15(what, with1, with2, with3, with4, x, ...)\
  what(x, with1, with2, with3, with4)\
  EXPAND(FOR_EACH_WITH_FOUR_14(what, with1, with2, with3, with4,  __VA_ARGS__))

#define FOR_EACH_WITH_FOUR_16(what, with1, with2, with3, with4, x, ...)\
  what(x, with1, with2, with3, with4)\
  EXPAND(FOR_EACH_WITH_FOUR_15(what, with1, with2, with3, with4, __VA_ARGS__))

#define FOR_EACH_WITH_FOUR_(N , what ,with1, with2, with3, with4,...) EXPAND(CONCAT(FOR_EACH_WITH_FOUR_, N)(what ,with1, with2, with3, with4, __VA_ARGS__))
#define FOR_EACH_WITH_FOUR(what ,with1, with2, with3, with4 ,...) FOR_EACH_WITH_FOUR_(FOR_EACH_NARG(__VA_ARGS__) , what ,with1, with2, with3, with4 ,__VA_ARGS__)

// FOR_EACH_WITH_FIVE

#define FOR_EACH_WITH_FIVE_1(what, with1, with2, with3, with4, with5, x, ...) what(x, with1, with2, with3, with4, with5)
#define FOR_EACH_WITH_FIVE_2(what, with1, with2, with3, with4, with5, x, ...)\
  what(x, with1, with2, with3, with4, with5)\
  EXPAND(FOR_EACH_WITH_FIVE_1(what, with1, with2, with3, with4, with5,  __VA_ARGS__))
#define FOR_EACH_WITH_FIVE_3(what, with1, with2, with3, with4, with5, x, ...)\
  what(x, with1, with2, with3, with4, with5)\
  EXPAND(FOR_EACH_WITH_FIVE_2(what, with1, with2, with3, with4, with5, __VA_ARGS__))
#define FOR_EACH_WITH_FIVE_4(what, with1, with2, with3, with4, with5, x, ...)\
  what(x, with1, with2, with3, with4, with5)\
  EXPAND(FOR_EACH_WITH_FIVE_3(what, with1, with2, with3, with4, with5,  __VA_ARGS__))
#define FOR_EACH_WITH_FIVE_5(what, with1, with2, with3, with4, with5, x, ...)\
  what(x, with1, with2, with3, with4, with5)\
  EXPAND(FOR_EACH_WITH_FIVE_4(what, with1, with2, with3, with4, with5,  __VA_ARGS__))
#define FOR_EACH_WITH_FIVE_6(what, with1, with2, with3, with4, with5, x, ...)\
  what(x, with1, with2, with3, with4, with5)\
  EXPAND(FOR_EACH_WITH_FIVE_5(what, with1, with2, with3, with4, with5,  __VA_ARGS__))
#define FOR_EACH_WITH_FIVE_7(what, with1, with2, with3, with4, with5, x, ...)\
  what(x, with1, with2, with3, with4, with5)\
  EXPAND(FOR_EACH_WITH_FIVE_6(what, with1, with2, with3, with4, with5,  __VA_ARGS__))
#define FOR_EACH_WITH_FIVE_8(what, with1, with2, with3, with4, with5, x, ...)\
  what(x, with1, with2, with3, with4, with5)\
  EXPAND(FOR_EACH_WITH_FIVE_7(what, with1, with2, with3, with4, with5,  __VA_ARGS__))

#define FOR_EACH_WITH_FIVE_9(what, with1, with2, with3, with4, with5, x, ...)\
  what(x, with1, with2, with3, with4, with5)\
  EXPAND(FOR_EACH_WITH_FIVE_8(what, with1, with2, with3, with4, with5,  __VA_ARGS__))

#define FOR_EACH_WITH_FIVE_10(what, with1, with2, with3, with4, with5, x, ...)\
  what(x, with1, with2, with3, with4, with5)\
  EXPAND(FOR_EACH_WITH_FIVE_9(what, with1, with2, with3, with4, with5,  __VA_ARGS__))

#define FOR_EACH_WITH_FIVE_11(what, with1, with2, with3, with4, with5, x, ...)\
  what(x, with1, with2, with3, with4, with5)\
  EXPAND(FOR_EACH_WITH_FIVE_10(what, with1, with2, with3, with4, with5,  __VA_ARGS__))

#define FOR_EACH_WITH_FIVE_12(what, with1, with2, with3, with4, with5, x, ...)\
  what(x, with1, with2, with3, with4, with5)\
  EXPAND(FOR_EACH_WITH_FIVE_11(what, with1, with2, with3, with4, with5,  __VA_ARGS__))

#define FOR_EACH_WITH_FIVE_13(what, with1, with2, with3, with4, with5, x, ...)\
  what(x, with1, with2, with3, with4, with5)\
  EXPAND(FOR_EACH_WITH_FIVE_12(what, with1, with2, with3, with4, with5,  __VA_ARGS__))

#define FOR_EACH_WITH_FIVE_14(what, with1, with2, with3, with4, with5, x, ...)\
  what(x, with1, with2, with3, with4, with5)\
  EXPAND(FOR_EACH_WITH_FIVE_13(what, with1, with2, with3, with4, with5,  __VA_ARGS__))

#define FOR_EACH_WITH_FIVE_15(what, with1, with2, with3, with4, with5, x, ...)\
  what(x, with1, with2, with3, with4, with5)\
  EXPAND(FOR_EACH_WITH_FIVE_14(what, with1, with2, with3, with4, with5,  __VA_ARGS__))

#define FOR_EACH_WITH_FIVE_16(what, with1, with2, with3, with4, with5, x, ...)\
  what(x, with1, with2, with3, with4, with5)\
  EXPAND(FOR_EACH_WITH_FIVE_15(what, with1, with2, with3, with4, with5, __VA_ARGS__))

#define FOR_EACH_WITH_FIVE_(N , what ,with1, with2, with3, with4, with5,...) EXPAND(CONCAT(FOR_EACH_WITH_FIVE_, N)(what ,with1, with2, with3, with4, with5, __VA_ARGS__))
#define FOR_EACH_WITH_FIVE(what ,with1, with2, with3, with4, with5 ,...) FOR_EACH_WITH_FIVE_(FOR_EACH_NARG(__VA_ARGS__) , what ,with1, with2, with3, with4, with5 ,__VA_ARGS__)

// FOR_EACH_WITH_SIX

#define FOR_EACH_WITH_SIX_1(what, with1, with2, with3, with4, with5, with6, x, ...) what(x, with1, with2, with3, with4, with5, with6)
#define FOR_EACH_WITH_SIX_2(what, with1, with2, with3, with4, with5, with6, x, ...)\
  what(x, with1, with2, with3, with4, with5, with6)\
  EXPAND(FOR_EACH_WITH_SIX_1(what, with1, with2, with3, with4, with5, with6,  __VA_ARGS__))
#define FOR_EACH_WITH_SIX_3(what, with1, with2, with3, with4, with5, with6, x, ...)\
  what(x, with1, with2, with3, with4, with5, with6)\
  EXPAND(FOR_EACH_WITH_SIX_2(what, with1, with2, with3, with4, with5, with6, __VA_ARGS__))
#define FOR_EACH_WITH_SIX_4(what, with1, with2, with3, with4, with5, with6, x, ...)\
  what(x, with1, with2, with3, with4, with5, with6)\
  EXPAND(FOR_EACH_WITH_SIX_3(what, with1, with2, with3, with4, with5, with6,  __VA_ARGS__))
#define FOR_EACH_WITH_SIX_5(what, with1, with2, with3, with4, with5, with6, x, ...)\
  what(x, with1, with2, with3, with4, with5, with6)\
  EXPAND(FOR_EACH_WITH_SIX_4(what, with1, with2, with3, with4, with5, with6,  __VA_ARGS__))
#define FOR_EACH_WITH_SIX_6(what, with1, with2, with3, with4, with5, with6, x, ...)\
  what(x, with1, with2, with3, with4, with5, with6)\
  EXPAND(FOR_EACH_WITH_SIX_5(what, with1, with2, with3, with4, with5, with6,  __VA_ARGS__))
#define FOR_EACH_WITH_SIX_7(what, with1, with2, with3, with4, with5, with6, x, ...)\
  what(x, with1, with2, with3, with4, with5, with6)\
  EXPAND(FOR_EACH_WITH_SIX_6(what, with1, with2, with3, with4, with5, with6,  __VA_ARGS__))
#define FOR_EACH_WITH_SIX_8(what, with1, with2, with3, with4, with5, with6, x, ...)\
  what(x, with1, with2, with3, with4, with5, with6)\
  EXPAND(FOR_EACH_WITH_SIX_7(what, with1, with2, with3, with4, with5, with6,  __VA_ARGS__))

#define FOR_EACH_WITH_SIX_9(what, with1, with2, with3, with4, with5, with6, x, ...)\
  what(x, with1, with2, with3, with4, with5, with6)\
  EXPAND(FOR_EACH_WITH_SIX_8(what, with1, with2, with3, with4, with5, with6,  __VA_ARGS__))

#define FOR_EACH_WITH_SIX_10(what, with1, with2, with3, with4, with5, with6, x, ...)\
  what(x, with1, with2, with3, with4, with5, with6)\
  EXPAND(FOR_EACH_WITH_SIX_9(what, with1, with2, with3, with4, with5, with6,  __VA_ARGS__))

#define FOR_EACH_WITH_SIX_11(what, with1, with2, with3, with4, with5, with6, x, ...)\
  what(x, with1, with2, with3, with4, with5, with6)\
  EXPAND(FOR_EACH_WITH_SIX_10(what, with1, with2, with3, with4, with5, with6,  __VA_ARGS__))

#define FOR_EACH_WITH_SIX_12(what, with1, with2, with3, with4, with5, with6, x, ...)\
  what(x, with1, with2, with3, with4, with5, with6)\
  EXPAND(FOR_EACH_WITH_SIX_11(what, with1, with2, with3, with4, with5, with6,  __VA_ARGS__))

#define FOR_EACH_WITH_SIX_13(what, with1, with2, with3, with4, with5, with6, x, ...)\
  what(x, with1, with2, with3, with4, with5, with6)\
  EXPAND(FOR_EACH_WITH_SIX_12(what, with1, with2, with3, with4, with5, with6,  __VA_ARGS__))

#define FOR_EACH_WITH_SIX_14(what, with1, with2, with3, with4, with5, with6, x, ...)\
  what(x, with1, with2, with3, with4, with5, with6)\
  EXPAND(FOR_EACH_WITH_SIX_13(what, with1, with2, with3, with4, with5, with6,  __VA_ARGS__))

#define FOR_EACH_WITH_SIX_15(what, with1, with2, with3, with4, with5, with6, x, ...)\
  what(x, with1, with2, with3, with4, with5, with6)\
  EXPAND(FOR_EACH_WITH_SIX_14(what, with1, with2, with3, with4, with5, with6,  __VA_ARGS__))

#define FOR_EACH_WITH_SIX_16(what, with1, with2, with3, with4, with5, with6, x, ...)\
  what(x, with1, with2, with3, with4, with5, with6)\
  EXPAND(FOR_EACH_WITH_SIX_15(what, with1, with2, with3, with4, with5, with6, __VA_ARGS__))

#define FOR_EACH_WITH_SIX_(N , what ,with1, with2, with3, with4, with5, with6,...) EXPAND(CONCAT(FOR_EACH_WITH_SIX_, N)(what ,with1, with2, with3, with4, with5, with6, __VA_ARGS__))
#define FOR_EACH_WITH_SIX(what ,with1, with2, with3, with4, with5, with6 ,...) FOR_EACH_WITH_SIX_(FOR_EACH_NARG(__VA_ARGS__) , what ,with1, with2, with3, with4, with5, with6 ,__VA_ARGS__)

namespace Experiment
{
	template<typename T>
	inline T& ConstCast(const T& Const) { return const_cast<T&>(Const); }

	template<typename T>
	inline T* ConstCast(const T* Const) { return const_cast<T*>(Const); }
}

#define this_mutable Experiment::ConstCast(this)

#define this_ref_mutable *Experiment::ConstCast(this)

#define this_ref (*this)

#define EXP_CONSTCAST(Type) Experiment::ConstCast(Type)



#define _EXP_IF(Cond)\
	if (Cond)

#define EXP_IF(...)\
	FOR_EACH(_EXP_IF, __VA_ARGS__)

#define EXP_NAMEOF(Name) #Name



#define _EXP_USING_NAMESPACE(NS)\
	using namespace NS;

#define EXP_USING_NAMESPACE(...)\
	FOR_EACH(_EXP_USING_NAMESPACE, __VA_ARGS__)

/*
This allows you to write:

void f() {
	[...]

	EXP_SCOPED(Lock l(&m)) {
		n++;
	}

	[...]
}

*/
//#define _EXP_SCOPED(Variable)\
//	Variable,
//
//#define _EXP_SCOPED_LAST(Variable)\
//	Variable

//#define EXP_SCOPED(...) \
//	for (bool __f = true; __f; ) \
//	for (FOR_EACH_LAST(_EXP_SCOPED, _EXP_SCOPED_LAST, __VA_ARGS__); __f; __f = false)

#define _EXP_SCOPED(Variable, I)\
	for (bool __f##I = true; __f##I; )\
	for (Variable; __f##I; __f##I = false)


#define EXP_SCOPED(...)\
	FOR_EACH_WITH_I(_EXP_SCOPED, __VA_ARGS__)

//
//#define _EXP_FOR_BEGIN(Variable1, Variable2, I1, I2)\
//	auto it##I1 = Variable2.begin();
//
//#define _EXP_FOR_COND_TERM(Variable1, Variable2, I1, I2)\
//	it##I1 != Variable2.end() &&
//
//#define _EXP_FOR_INC(Variable1, Variable2, I1, I2)\
//	it##I1++,
//
//#define _EXP_FOR_ALIAS(Variable1, Variable2, I1, I2)\
//	Variable1 = *it##I1,

#define _EXP_FOR_ELEM(Variable1, Variable2, I1, I2)\
	Variable1 = *it##I1,

//#define _EXP_FOR_PART_1(...)\
//	FOR_EACH_WITH_I(_EXP_FOR_PART_1_INNER, __VA_ARGS__)

#define EXP_FOR(...)\
	for(auto& Collection : {Collection1, Collection2})\
		for (auto& Elem : Collection)\
	
	

	//for (\
	//	FOR_EACH_TWO_WITH_I(_EXP_FOR_BEGIN, __VA_ARGS__);\
	//	FOR_EACH_TWO_WITH_I(_EXP_FOR_COND_TERM, __VA_ARGS__) true;\
	//	FOR_EACH_TWO_WITH_I(_EXP_FOR_INC, __VA_ARGS__))
			


/**
 *
 */
#define _EXP_USING_UCLASS(Nested, Enclosing)\
	using U##Nested = U##Enclosing##Nested;

#define EXP_USING_UCLASS(Enclosing, ...)\
	FOR_EACH_WITH(_EXP_USING_UCLASS, Enclosing, __VA_ARGS__)
 /**
  *
  */
#define _EXP_USING_USTRUCT(Nested, Enclosing)\
	using F##Nested = F##Enclosing##Nested;

#define EXP_USING_USTRUCT(Enclosing, ...)\
	FOR_EACH_WITH(_EXP_USING_USTRUCT, Enclosing, __VA_ARGS__)

  /**
   *
   */
#define _FWD_DECL_CLASS(ClassName) class ClassName;

#define EXP_FWD_DECL_CLASSES(...)\
    FOR_EACH(_FWD_DECL_CLASS, __VA_ARGS__)


   /**
	*
	*/
#define _FWD_DECL_STRUCT(StructName) struct StructName;

#define EXP_FWD_DECL_STRUCTS(...)\
    FOR_EACH(_FWD_DECL_STRUCT, __VA_ARGS__)

	/**
	 *
	 */
#define _DECL_STRUCT(StructName, Api) struct Api StructName {};

	 // Define a custom ensure macro that ends the game gracefully if the condition is false #define CUSTOM_ENSURE(Condition)
#define EXP_DECL_STRUCTS(Api, ...)\
    FOR_EACH_WITH(_DECL_STRUCT, Api, __VA_ARGS__)