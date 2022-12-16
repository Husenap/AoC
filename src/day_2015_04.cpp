#include "common.hpp"
#include "md5.hpp"

using namespace std;

int main() {
  ifstream    in("day_2015_04");
  std::string secret;
  std::getline(in, secret);

  bool done = false;
#pragma omp parallel for shared(done)
  for (int i = 0; i < 300000; ++i) {
    if (done) continue;
    if (md5::hash(secret + std::to_string(i)).A & 0xf0ffff) continue;
    expectEq(i, 254575);
    done = true;
  }
  done = false;
#pragma omp parallel for shared(done)
  for (int i = 0; i < 1500000; ++i) {
    if (done) continue;
    if (md5::hash(secret + std::to_string(i)).A & 0xffffff) continue;
    expectEq(i, 1038736);
    done = true;
  }

  return 0;
}
