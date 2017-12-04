#include <fstream>
#include <iostream>
#include <string>

#include "font.hpp"

// clang-format off
const bitmap_t unprintable = {
  {1, 1, 1, 1},
  {1, 0, 0, 1},
  {1, 0, 0, 1},
  {1, 0, 0, 1},
  {1, 0, 0, 1},
  {1, 0, 0, 1},
  {1, 0, 0, 1},
  {1, 0, 0, 1},
  {1, 1, 1, 1},
};

const bitmap_t font[128] = {

  // First the 32 control characters
  unprintable, unprintable, unprintable, unprintable, unprintable,
  unprintable, unprintable, unprintable, unprintable, unprintable,
  unprintable, unprintable, unprintable, unprintable, unprintable,
  unprintable, unprintable, unprintable, unprintable, unprintable,
  unprintable, unprintable, unprintable, unprintable, unprintable,
  unprintable, unprintable, unprintable, unprintable, unprintable,
  unprintable,
  unprintable,

  // Space
  {{0, 0},
   {0, 0},
   {0, 0},
   {0, 0},
   {0, 0},
   {0, 0},
   {0, 0},
   {0, 0},
   {0, 0}},

  // !
  {{0},
   {1},
   {1},
   {1},
   {1},
   {0},
   {1},
   {0},
   {0}},

  // "
  {{0, 0, 0},
   {1, 0, 1},
   {1, 0, 1},
   {0, 0, 0},
   {0, 0, 0},
   {0, 0, 0},
   {0, 0, 0},
   {0, 0, 0},
   {0, 0, 0}},

  // #
  {{0, 1, 0, 1, 0},
   {0, 1, 0, 1, 0},
   {1, 1, 1, 1, 1},
   {0, 1, 0, 1, 0},
   {1, 1, 1, 1, 1},
   {0, 1, 0, 1, 0},
   {0, 1, 0, 1, 0},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}},

  // $
  {{0, 0, 1, 0, 0},
   {0, 1, 1, 1, 0},
   {1, 0, 1, 0, 1},
   {1, 0, 1, 0, 0},
   {0, 1, 1, 1, 0},
   {0, 0, 1, 0, 1},
   {1, 0, 1, 0, 1},
   {0, 1, 1, 1, 0},
   {0, 0, 1, 0, 0}},

  // %
  {{0, 1, 0, 0, 0, 0},
   {1, 0, 1, 0, 1, 0},
   {0, 1, 0, 0, 1, 0},
   {0, 0, 0, 1, 0, 0},
   {0, 0, 1, 0, 0, 0},
   {0, 1, 0, 0, 1, 0},
   {0, 1, 0, 1, 0, 1},
   {0, 0, 0, 0, 1, 0},
   {0, 0, 0, 0, 0, 0}},

  // &
  {{0, 1, 1, 0, 0},
   {1, 0, 0, 1, 0},
   {1, 0, 0, 1, 0},
   {0, 1, 1, 0, 0},
   {1, 0, 0, 1, 1},
   {1, 0, 0, 1, 0},
   {0, 1, 1, 0, 1},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}},

  // '
  {{0},
   {1},
   {1},
   {0},
   {0},
   {0},
   {0},
   {0},
   {0}},

  // (
  {{0, 1},
   {1, 0},
   {1, 0},
   {1, 0},
   {1, 0},
   {1, 0},
   {1, 0},
   {0, 1},
   {0, 0}},

  // )
  {{1, 0},
   {0, 1},
   {0, 1},
   {0, 1},
   {0, 1},
   {0, 1},
   {0, 1},
   {1, 0},
   {0, 0}},

  // *
  {{0, 0, 0},
   {1, 0, 1},
   {0, 1, 0},
   {1, 0, 1},
   {0, 0, 0},
   {0, 0, 0},
   {0, 0, 0},
   {0, 0, 0},
   {0, 0, 0}},

  // +
  {{0, 0, 0},
   {0, 0, 0},
   {0, 0, 0},
   {0, 1, 0},
   {1, 1, 1},
   {0, 1, 0},
   {0, 0, 0},
   {0, 0, 0},
   {0, 0, 0}},

  // ,
  {{0, 0},
   {0, 0},
   {0, 0},
   {0, 0},
   {0, 0},
   {1, 1},
   {0, 1},
   {0, 1},
   {1, 0}},

  // +
  {{0, 0, 0},
   {0, 0, 0},
   {0, 0, 0},
   {0, 0, 0},
   {1, 1, 1},
   {0, 0, 0},
   {0, 0, 0},
   {0, 0, 0},
   {0, 0, 0}},

  // .
  {{0, 0},
   {0, 0},
   {0, 0},
   {0, 0},
   {0, 0},
   {1, 1},
   {1, 1},
   {0, 0},
   {0, 0}},

  // /
  {{0, 0, 0, 0},
   {0, 0, 0, 1},
   {0, 0, 0, 1},
   {0, 0, 1, 0},
   {0, 1, 0, 0},
   {1, 0, 0, 0},
   {1, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // 0
  {{0, 0, 0, 0},
   {0, 1, 1, 0},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {0, 1, 1, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // 1
  {{0, 0, 0},
   {0, 1, 0},
   {1, 1, 0},
   {0, 1, 0},
   {0, 1, 0},
   {0, 1, 0},
   {1, 1, 1},
   {0, 0, 0},
   {0, 0, 0}},

  // 2
  {{0, 0, 0, 0},
   {0, 1, 1, 0},
   {1, 0, 0, 1},
   {0, 0, 0, 1},
   {0, 0, 1, 0},
   {0, 1, 0, 0},
   {1, 1, 1, 1},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // 3
  {{0, 0, 0},
   {1, 1, 1},
   {0, 0, 1},
   {0, 1, 1},
   {0, 0, 1},
   {0, 0, 1},
   {1, 1, 0},
   {0, 0, 0},
   {0, 0, 0}},

  // 4
  {{0, 0, 0, 0, 0},
   {0, 0, 0, 1, 0},
   {0, 0, 1, 1, 0},
   {0, 1, 0, 1, 0},
   {1, 0, 0, 1, 0},
   {1, 1, 1, 1, 1},
   {0, 0, 0, 1, 0},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}},

  // 5
  {{0, 0, 0, 0},
   {1, 1, 1, 1},
   {1, 0, 0, 0},
   {1, 1, 1, 0},
   {0, 0, 0, 1},
   {0, 0, 0, 1},
   {1, 1, 1, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // 6
  {{0, 0, 0, 0},
   {0, 1, 1, 0},
   {1, 0, 0, 0},
   {1, 1, 1, 0},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {0, 1, 1, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // 7
  {{0, 0, 0, 0},
   {1, 1, 1, 1},
   {0, 0, 0, 1},
   {0, 0, 0, 1},
   {0, 0, 1, 0},
   {0, 1, 0, 0},
   {0, 1, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // 8
  {{0, 0, 0, 0},
   {0, 1, 1, 0},
   {1, 0, 0, 1},
   {0, 1, 1, 0},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {0, 1, 1, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // 9
  {{0, 0, 0, 0},
   {0, 1, 1, 0},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {0, 1, 1, 1},
   {0, 0, 0, 1},
   {0, 1, 1, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // :
  {{0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 1, 1, 0},
   {0, 1, 1, 0},
   {0, 0, 0, 0},
   {0, 1, 1, 0},
   {0, 1, 1, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // ;
  {{0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 1, 1, 0},
   {0, 1, 1, 0},
   {0, 0, 0, 0},
   {0, 1, 1, 0},
   {0, 0, 1, 0},
   {0, 0, 1, 0},
   {0, 0, 0, 0}},

  // <
  {{0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 1, 1},
   {0, 1, 1, 0, 0},
   {1, 0, 0, 0, 0},
   {0, 1, 1, 0, 0},
   {0, 0, 0, 1, 1},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}},

  // =
  {{0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {1, 1, 1, 1},
   {0, 0, 0, 0},
   {1, 1, 1, 1},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // >
  {{0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0},
   {1, 1, 0, 0, 0},
   {0, 0, 1, 1, 0},
   {0, 0, 0, 0, 1},
   {0, 0, 1, 1, 0},
   {1, 1, 0, 0, 0},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}},

  // ?
  {{0, 1, 1, 0},
   {1, 0, 0, 1},
   {0, 0, 0, 1},
   {0, 1, 1, 0},
   {0, 1, 0, 0},
   {0, 0, 0, 0},
   {0, 1, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // @
  {{0, 0, 0, 0, 0},
   {0, 1, 1, 1, 0},
   {1, 0, 0, 1, 0},
   {1, 0, 1, 0, 1},
   {1, 0, 1, 1, 0},
   {1, 0, 0, 0, 0},
   {0, 1, 1, 1, 0},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}},

  // A
  {{0, 0, 0, 0, 0},
   {0, 0, 1, 0, 0},
   {0, 1, 0, 1, 0},
   {1, 0, 0, 0, 1},
   {1, 1, 1, 1, 1},
   {1, 0, 0, 0, 1},
   {1, 0, 0, 0, 1},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}},

  // B
  {{0, 0, 0, 0, 0},
   {1, 1, 1, 1, 0},
   {1, 0, 0, 0, 1},
   {1, 1, 1, 1, 0},
   {1, 0, 0, 0, 1},
   {1, 0, 0, 0, 1},
   {1, 1, 1, 1, 0},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}},

  // C
  {{0, 0, 0, 0},
   {0, 1, 1, 0},
   {1, 0, 0, 1},
   {1, 0, 0, 0},
   {1, 0, 0, 0},
   {1, 0, 0, 1},
   {0, 1, 1, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // D
  {{0, 0, 0, 0},
   {1, 1, 1, 0},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {1, 1, 1, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // E
  {{0, 0, 0, 0},
   {1, 1, 1, 1},
   {1, 0, 0, 0},
   {1, 1, 1, 0},
   {1, 0, 0, 0},
   {1, 0, 0, 0},
   {1, 1, 1, 1},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // F
  {{0, 0, 0, 0},
   {1, 1, 1, 1},
   {1, 0, 0, 0},
   {1, 1, 1, 0},
   {1, 0, 0, 0},
   {1, 0, 0, 0},
   {1, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // G
  {{0, 0, 0, 0},
   {0, 1, 1, 0},
   {1, 0, 0, 1},
   {1, 0, 0, 0},
   {1, 0, 1, 1},
   {1, 0, 0, 1},
   {0, 1, 1, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // H
  {{0, 0, 0, 0},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {1, 1, 1, 1},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // I
  {{0, 0, 0},
   {1, 1, 1},
   {0, 1, 0},
   {0, 1, 0},
   {0, 1, 0},
   {0, 1, 0},
   {1, 1, 1},
   {0, 0, 0},
   {0, 0, 0}},

  // J
  {{0, 0, 0, 0, 0},
   {0, 0, 1, 1, 1},
   {0, 0, 0, 1, 0},
   {0, 0, 0, 1, 0},
   {0, 0, 0, 1, 0},
   {1, 0, 0, 1, 0},
   {0, 1, 1, 0, 0},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}},

  // K
  {{0, 0, 0, 0},
   {1, 0, 0, 1},
   {1, 0, 1, 0},
   {1, 1, 0, 0},
   {1, 0, 1, 0},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // L
  {{0, 0, 0, 0},
   {1, 0, 0, 0},
   {1, 0, 0, 0},
   {1, 0, 0, 0},
   {1, 0, 0, 0},
   {1, 0, 0, 0},
   {1, 1, 1, 1},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // M
  {{0, 0, 0, 0, 0},
   {1, 0, 0, 0, 1},
   {1, 1, 0, 1, 1},
   {1, 0, 1, 0, 1},
   {1, 0, 1, 0, 1},
   {1, 0, 0, 0, 1},
   {1, 0, 0, 0, 1},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}},

  // N
  {{0, 0, 0, 0},
   {1, 0, 0, 1},
   {1, 1, 0, 1},
   {1, 0, 1, 1},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // O
  {{0, 0, 0, 0, 0},
   {0, 1, 1, 1, 0},
   {1, 0, 0, 0, 1},
   {1, 0, 0, 0, 1},
   {1, 0, 0, 0, 1},
   {1, 0, 0, 0, 1},
   {0, 1, 1, 1, 0},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}},

  // P
  {{0, 0, 0, 0},
   {1, 1, 1, 0},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {1, 1, 1, 0},
   {1, 0, 0, 0},
   {1, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // Q
  {{0, 0, 0, 0},
   {0, 1, 1, 0},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {1, 1, 0, 1},
   {1, 0, 1, 1},
   {0, 1, 1, 0},
   {0, 0, 0, 1},
   {0, 0, 0, 0}},

  // R
  {{0, 0, 0, 0},
   {1, 1, 1, 0},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {1, 1, 1, 0},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // S
  {{0, 0, 0, 0},
   {0, 1, 1, 0},
   {1, 0, 0, 1},
   {0, 1, 0, 0},
   {0, 0, 1, 0},
   {1, 0, 0, 1},
   {0, 1, 1, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // T
  {{0, 0, 0, 0, 0},
   {1, 1, 1, 1, 1},
   {0, 0, 1, 0, 0},
   {0, 0, 1, 0, 0},
   {0, 0, 1, 0, 0},
   {0, 0, 1, 0, 0},
   {0, 0, 1, 0, 0},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}},

  // U
  {{0, 0, 0, 0},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {0, 1, 1, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // V
  {{0, 0, 0, 0},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {0, 1, 1, 0},
   {0, 1, 1, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // W
  {{0, 0, 0, 0, 0},
   {1, 0, 0, 0, 1},
   {1, 0, 0, 0, 1},
   {1, 0, 1, 0, 1},
   {1, 0, 1, 0, 1},
   {1, 1, 0, 1, 1},
   {1, 0, 0, 0, 1},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}},

  // X
  {{0, 0, 0, 0, 0},
   {1, 0, 0, 0, 1},
   {0, 1, 0, 1, 0},
   {0, 0, 1, 0, 0},
   {0, 0, 1, 0, 0},
   {0, 1, 0, 1, 0},
   {1, 0, 0, 0, 1},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}},

  // Y
  {{0, 0, 0, 0, 0},
   {1, 0, 0, 0, 1},
   {1, 0, 0, 0, 1},
   {0, 1, 0, 1, 0},
   {0, 0, 1, 0, 0},
   {0, 0, 1, 0, 0},
   {0, 0, 1, 0, 0},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}},

  // Z
  {{0, 0, 0, 0},
   {1, 1, 1, 1},
   {0, 0, 0, 1},
   {0, 0, 1, 0},
   {0, 1, 0, 0},
   {1, 0, 0, 0},
   {1, 1, 1, 1},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // [
  {{0, 0, 0},
   {1, 1, 1},
   {1, 0, 0},
   {1, 0, 0},
   {1, 0, 0},
   {1, 0, 0},
   {1, 1, 1},
   {0, 0, 0},
   {0, 0, 0}},

  // backslash
  {{0, 0, 0, 0},
   {1, 0, 0, 0},
   {1, 0, 0, 0},
   {0, 1, 0, 0},
   {0, 0, 1, 0},
   {0, 0, 0, 1},
   {0, 0, 0, 1},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // ]
  {{0, 0, 0},
   {1, 1, 1},
   {0, 0, 1},
   {0, 0, 1},
   {0, 0, 1},
   {0, 0, 1},
   {1, 1, 1},
   {0, 0, 0},
   {0, 0, 0}},

  // ^
  {{0, 0, 0, 0, 0},
   {0, 0, 1, 0, 0},
   {0, 1, 0, 1, 0},
   {1, 0, 0, 0, 1},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}},

  // _
  {{0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {1, 1, 1, 1}},

  // `
  {{0, 0},
   {1, 0},
   {0, 1},
   {0, 0},
   {0, 0},
   {0, 0},
   {0, 0},
   {0, 0},
   {0, 0}},

  // a
  {{0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 1, 1, 1},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {0, 1, 1, 1},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // b
  {{0, 0, 0, 0},
   {1, 0, 0, 0},
   {1, 0, 0, 0},
   {1, 1, 1, 0},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {1, 1, 1, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // c
  {{0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 1, 1, 1},
   {1, 0, 0, 0},
   {1, 0, 0, 0},
   {0, 1, 1, 1},
   {0, 0, 0, 0}},

  // d
  {{0, 0, 0, 0},
   {0, 0, 0, 1},
   {0, 0, 0, 1},
   {0, 1, 1, 1},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {0, 1, 1, 1},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // e
  {{0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 1, 1, 0},
   {1, 0, 1, 1},
   {1, 1, 0, 0},
   {0, 1, 1, 1},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // f
  {{0, 0, 0, 0},
   {0, 0, 1, 0},
   {0, 1, 0, 1},
   {0, 1, 0, 0},
   {1, 1, 1, 0},
   {0, 1, 0, 0},
   {0, 1, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // g
  {{0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 1, 1, 0},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {0, 1, 1, 1},
   {0, 0, 0, 1},
   {0, 1, 1, 0}},

  // h
  {{0, 0, 0, 0},
   {1, 0, 0, 0},
   {1, 0, 0, 0},
   {1, 1, 1, 0},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // i
  {{0, 0, 0},
   {0, 1, 0},
   {0, 0, 0},
   {1, 1, 0},
   {0, 1, 0},
   {0, 1, 0},
   {1, 1, 1},
   {0, 0, 0},
   {0, 0, 0}},

  // j
  {{0, 0, 0},
   {0, 0, 1},
   {0, 0, 0},
   {0, 1, 1},
   {0, 0, 1},
   {0, 0, 1},
   {0, 0, 1},
   {1, 0, 1},
   {0, 1, 0}},

  // k
  {{0, 0, 0, 0},
   {1, 0, 0, 0},
   {1, 0, 0, 0},
   {1, 0, 1, 0},
   {1, 1, 0, 0},
   {1, 0, 1, 0},
   {1, 0, 0, 1},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // l
  {{0, 0, 0},
   {1, 1, 0},
   {0, 1, 0},
   {0, 1, 0},
   {0, 1, 0},
   {0, 1, 0},
   {1, 1, 1},
   {0, 0, 0},
   {0, 0, 0}},

  // m
  {{0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0},
   {1, 1, 0, 1, 0},
   {1, 0, 1, 0, 1},
   {1, 0, 1, 0, 1},
   {1, 0, 0, 0, 1},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}},

  // n
  {{0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {1, 1, 1, 0},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // o
  {{0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 1, 1, 0},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {0, 1, 1, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // p
  {{0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {1, 1, 1, 0},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {1, 1, 1, 0},
   {1, 0, 0, 0},
   {1, 0, 0, 0}},

  // q
  {{0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 1, 1, 0},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {0, 1, 1, 1},
   {0, 0, 0, 1},
   {0, 0, 0, 1}},

  // r
  {{0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {1, 0, 1, 0},
   {1, 1, 0, 1},
   {1, 0, 0, 0},
   {1, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // s
  {{0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 1, 1, 1},
   {1, 1, 0, 0},
   {0, 0, 1, 1},
   {1, 1, 1, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // t
  {{0, 0, 0, 0},
   {0, 1, 0, 0},
   {0, 1, 0, 0},
   {1, 1, 1, 0},
   {0, 1, 0, 0},
   {0, 1, 0, 1},
   {0, 0, 1, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // u
  {{0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {0, 1, 1, 1},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // v
  {{0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {0, 1, 1, 0},
   {0, 1, 1, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // w
  {{0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0},
   {1, 0, 0, 0, 1},
   {1, 0, 1, 0, 1},
   {1, 0, 1, 0, 1},
   {0, 1, 0, 1, 0},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}},

  // x
  {{0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {1, 0, 0, 1},
   {0, 1, 1, 0},
   {0, 1, 1, 0},
   {1, 0, 0, 1},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // y
  {{0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {1, 0, 0, 1},
   {0, 1, 1, 1},
   {1, 0, 0, 1},
   {0, 1, 1, 0}},

  // z
  {{0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {1, 1, 1, 1},
   {0, 0, 1, 0},
   {0, 1, 0, 0},
   {1, 1, 1, 1},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  // {
  {{0, 0, 1},
   {0, 1, 0},
   {0, 1, 0},
   {1, 0, 0},
   {0, 1, 0},
   {0, 1, 0},
   {0, 0, 1},
   {0, 0, 0},
   {0, 0, 0}},

  // |
  {{0},
   {1},
   {1},
   {1},
   {1},
   {1},
   {1},
   {1},
   {0}},

  // }
  {{1, 0, 0},
   {0, 1, 0},
   {0, 1, 0},
   {0, 0, 1},
   {0, 1, 0},
   {0, 1, 0},
   {1, 0, 0},
   {0, 0, 0},
   {0, 0, 0}},

  // ~
  {{0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 1, 0, 1},
   {1, 0, 1, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}},

  unprintable
};

const bitmap_t selector {
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0},
  {0, 0, 0, 1, 0, 0},
  {1, 1, 1, 1, 1, 0},
  {0, 0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
};

const bitmap_t mount_indicator {
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 1, 1, 1, 0},
  {0, 1, 0, 1, 0},
  {0, 1, 1, 1, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
};

// clang-format on

bitmap_t render_text(const std::string &str) {
  bitmap_t bitmap;

  for (unsigned char letter : str) {
    bitmap_t letter_map;
    if (letter > sizeof(font) / sizeof(font[0])) {
      letter_map = unprintable;
    } else {
      letter_map = font[letter];
    }

    // The bitmap must be at least as tall as the letter
    bitmap.resize_height(letter_map.height());

    for (auto row_iter = letter_map.begin(); row_iter != letter_map.end();
         ++row_iter) {
      auto &out_row = bitmap[std::distance(letter_map.begin(), row_iter)];
      out_row.insert(out_row.end(), row_iter->begin(), row_iter->end());
      out_row.push_back(0);
    }
  }

  return bitmap;
}

void gen_pbm(const bitmap_t &map, const std::string &filename) {
  std::ofstream outfile{filename};
  outfile << "P1\n";
  outfile << map.width() << " " << map.height() << std::endl;

  for (const auto &row : map) {
    for (auto bit : row) {
      outfile << (int)bit << " ";
    }
    outfile << std::endl;
  }
}

#ifdef DEBUG
#include <cassert>
static const bool check_font = [] {
  std::cout << "Fonts: ";
  assert(sizeof(font) / sizeof(font[0]) == 128);
  for (std::size_t i = 0; i < sizeof(font) / sizeof(font[0]); ++i) {
    // Each char must be 9 pixels tall
    assert(font[i].height() == 9);

    // And have a consistent width
    for (const auto &row : font[i]) {
      assert(row.size() == font[i][0].size());
    }
  }
  std::cout << "ok\n";
  return true;
}();
#endif