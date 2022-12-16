#include <array>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <ostream>
#include <string>
#include <vector>

namespace md5 {

struct MD5 {
  uint32_t A = 0x67452301, B = 0xefcdab89, C = 0x98badcfe, D = 0x10325476;

  static void encode(std::ostream &os, uint32_t word) {
    os << std::setw(2) << std::setfill('0') << (word & 0xff);
    os << std::setw(2) << std::setfill('0') << (word >> 8 & 0xff);
    os << std::setw(2) << std::setfill('0') << (word >> 16 & 0xff);
    os << std::setw(2) << std::setfill('0') << (word >> 24 & 0xff);
  }
  friend std::ostream &operator<<(std::ostream &os, const MD5 &md5) {
    os << std::hex;
    encode(os, md5.A);
    encode(os, md5.B);
    encode(os, md5.C);
    encode(os, md5.D);
    return os;
  }
};

uint32_t rotlFixed(uint32_t x, uint32_t s) {
  return (x << s) | (x >> (-s & 31));
}

MD5 hash(std::string_view message) {
  std::vector<uint8_t> bytes(message.begin(), message.end());
  bytes.push_back(0x80);
  while (bytes.size() % 64 != 0) bytes.push_back(0x00);
  reinterpret_cast<std::size_t &>(bytes[bytes.size() - 8]) = message.size() * 8;

  MD5 state;

  for (int cb = 0; cb < bytes.size(); cb += 64) {
    std::array<uint32_t, 16> data;
    for (int word = 0; word < data.size(); ++word) {
      data[word] = bytes[cb + word * 4] | bytes[cb + word * 4 + 1] << 8 |
                   bytes[cb + word * 4 + 2] << 16 | bytes[cb + word * 4 + 3] << 24;
    }

#define F1(x, y, z) (z ^ (x & (y ^ z)))
#define F2(x, y, z) F1(z, x, y)
#define F3(x, y, z) (x ^ y ^ z)
#define F4(x, y, z) (y ^ (x | ~z))

#define MD5STEP(f, w, x, y, z, data, s) w = rotlFixed(w + f(x, y, z) + data, s) + x

    uint32_t a, b, c, d;

    a = state.A;
    b = state.B;
    c = state.C;
    d = state.D;

    MD5STEP(F1, a, b, c, d, data[0] + 0xd76aa478, 7);
    MD5STEP(F1, d, a, b, c, data[1] + 0xe8c7b756, 12);
    MD5STEP(F1, c, d, a, b, data[2] + 0x242070db, 17);
    MD5STEP(F1, b, c, d, a, data[3] + 0xc1bdceee, 22);
    MD5STEP(F1, a, b, c, d, data[4] + 0xf57c0faf, 7);
    MD5STEP(F1, d, a, b, c, data[5] + 0x4787c62a, 12);
    MD5STEP(F1, c, d, a, b, data[6] + 0xa8304613, 17);
    MD5STEP(F1, b, c, d, a, data[7] + 0xfd469501, 22);
    MD5STEP(F1, a, b, c, d, data[8] + 0x698098d8, 7);
    MD5STEP(F1, d, a, b, c, data[9] + 0x8b44f7af, 12);
    MD5STEP(F1, c, d, a, b, data[10] + 0xffff5bb1, 17);
    MD5STEP(F1, b, c, d, a, data[11] + 0x895cd7be, 22);
    MD5STEP(F1, a, b, c, d, data[12] + 0x6b901122, 7);
    MD5STEP(F1, d, a, b, c, data[13] + 0xfd987193, 12);
    MD5STEP(F1, c, d, a, b, data[14] + 0xa679438e, 17);
    MD5STEP(F1, b, c, d, a, data[15] + 0x49b40821, 22);

    MD5STEP(F2, a, b, c, d, data[1] + 0xf61e2562, 5);
    MD5STEP(F2, d, a, b, c, data[6] + 0xc040b340, 9);
    MD5STEP(F2, c, d, a, b, data[11] + 0x265e5a51, 14);
    MD5STEP(F2, b, c, d, a, data[0] + 0xe9b6c7aa, 20);
    MD5STEP(F2, a, b, c, d, data[5] + 0xd62f105d, 5);
    MD5STEP(F2, d, a, b, c, data[10] + 0x02441453, 9);
    MD5STEP(F2, c, d, a, b, data[15] + 0xd8a1e681, 14);
    MD5STEP(F2, b, c, d, a, data[4] + 0xe7d3fbc8, 20);
    MD5STEP(F2, a, b, c, d, data[9] + 0x21e1cde6, 5);
    MD5STEP(F2, d, a, b, c, data[14] + 0xc33707d6, 9);
    MD5STEP(F2, c, d, a, b, data[3] + 0xf4d50d87, 14);
    MD5STEP(F2, b, c, d, a, data[8] + 0x455a14ed, 20);
    MD5STEP(F2, a, b, c, d, data[13] + 0xa9e3e905, 5);
    MD5STEP(F2, d, a, b, c, data[2] + 0xfcefa3f8, 9);
    MD5STEP(F2, c, d, a, b, data[7] + 0x676f02d9, 14);
    MD5STEP(F2, b, c, d, a, data[12] + 0x8d2a4c8a, 20);

    MD5STEP(F3, a, b, c, d, data[5] + 0xfffa3942, 4);
    MD5STEP(F3, d, a, b, c, data[8] + 0x8771f681, 11);
    MD5STEP(F3, c, d, a, b, data[11] + 0x6d9d6122, 16);
    MD5STEP(F3, b, c, d, a, data[14] + 0xfde5380c, 23);
    MD5STEP(F3, a, b, c, d, data[1] + 0xa4beea44, 4);
    MD5STEP(F3, d, a, b, c, data[4] + 0x4bdecfa9, 11);
    MD5STEP(F3, c, d, a, b, data[7] + 0xf6bb4b60, 16);
    MD5STEP(F3, b, c, d, a, data[10] + 0xbebfbc70, 23);
    MD5STEP(F3, a, b, c, d, data[13] + 0x289b7ec6, 4);
    MD5STEP(F3, d, a, b, c, data[0] + 0xeaa127fa, 11);
    MD5STEP(F3, c, d, a, b, data[3] + 0xd4ef3085, 16);
    MD5STEP(F3, b, c, d, a, data[6] + 0x04881d05, 23);
    MD5STEP(F3, a, b, c, d, data[9] + 0xd9d4d039, 4);
    MD5STEP(F3, d, a, b, c, data[12] + 0xe6db99e5, 11);
    MD5STEP(F3, c, d, a, b, data[15] + 0x1fa27cf8, 16);
    MD5STEP(F3, b, c, d, a, data[2] + 0xc4ac5665, 23);

    MD5STEP(F4, a, b, c, d, data[0] + 0xf4292244, 6);
    MD5STEP(F4, d, a, b, c, data[7] + 0x432aff97, 10);
    MD5STEP(F4, c, d, a, b, data[14] + 0xab9423a7, 15);
    MD5STEP(F4, b, c, d, a, data[5] + 0xfc93a039, 21);
    MD5STEP(F4, a, b, c, d, data[12] + 0x655b59c3, 6);
    MD5STEP(F4, d, a, b, c, data[3] + 0x8f0ccc92, 10);
    MD5STEP(F4, c, d, a, b, data[10] + 0xffeff47d, 15);
    MD5STEP(F4, b, c, d, a, data[1] + 0x85845dd1, 21);
    MD5STEP(F4, a, b, c, d, data[8] + 0x6fa87e4f, 6);
    MD5STEP(F4, d, a, b, c, data[15] + 0xfe2ce6e0, 10);
    MD5STEP(F4, c, d, a, b, data[6] + 0xa3014314, 15);
    MD5STEP(F4, b, c, d, a, data[13] + 0x4e0811a1, 21);
    MD5STEP(F4, a, b, c, d, data[4] + 0xf7537e82, 6);
    MD5STEP(F4, d, a, b, c, data[11] + 0xbd3af235, 10);
    MD5STEP(F4, c, d, a, b, data[2] + 0x2ad7d2bb, 15);
    MD5STEP(F4, b, c, d, a, data[9] + 0xeb86d391, 21);

    state.A += a;
    state.B += b;
    state.C += c;
    state.D += d;
  }

  return state;
}

}  // namespace md5