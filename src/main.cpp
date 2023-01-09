#include <iostream>
#include <fmt/core.h>
#include <fmt/format.h>
#include <type_traits>
#include <assert.h>
#include <cmath>

#include <iostream>
#include <iomanip>

template<typename T>
T bitswap(T v)
{
  using UT = std::make_unsigned_t<T>;
  uint8_t highest_bit_num = sizeof(T) * 8 - 1;
  auto uv = static_cast<UT>(v);
  T result = 0;
  for (uint8_t i = 0; i <= highest_bit_num; ++i) {
    UT step1 = uv >> (highest_bit_num - i) & 0b1;
    UT step2 = step1 << i;
    result |= step2;
  }
  return result;
}

void easy_bitswap_check() {
  assert(bitswap(static_cast<uint8_t>(0xAA)) == 0x55);
  assert(bitswap(static_cast<uint8_t>(0x80)) == 0x01);
  assert(bitswap(static_cast<uint8_t>(0xFF)) == 0xFF);
  assert(bitswap(static_cast<uint8_t>(0x00)) == 0x00);
  assert(bitswap(static_cast<uint16_t>(0x80AA)) == 0x5501);
}

void hard_bitswap_check() {  /// is it possible to solve at all??
  assert(bitswap(0xAA) == 0x55);
  assert(bitswap(0x80) == 0x01);
  assert(bitswap(0xFF) == 0xFF);
  assert(bitswap(0x00) == 0x00);
}

struct Phone  { int ext = 0; };
struct Person { Phone phone; };

struct Phone2 {int ext = 0;};
struct Person2 {Phone2 *phone;};

template<typename... Args>
auto FoldExprRef(Args&&... args) {
  return (... .* args);
}

template<typename... Args>
auto FoldExprPtr(Args&&... args) {
  return (... ->* args);
}


int main([[maybe_unused]] int argc, [[maybe_unused]] char const *argv[])
{
  auto phone_p = &Person::phone;
  auto ext_p = &Phone::ext;
  Person p { { 999 } };
  std::cout << FoldExprRef(p, phone_p, ext_p) << std::endl;

  int ext_p2_obj = 998;
  Phone2 phone_p2_obj {ext_p2_obj};
  Person2 p2_obj {&phone_p2_obj};

  auto phone_p2 = &Person2::phone;
  auto ext_p2 = &Phone2::ext;
  auto person_p = &p2_obj;

  std::cout << FoldExprPtr(person_p, phone_p2, ext_p2) << std::endl;

  return 0;
}