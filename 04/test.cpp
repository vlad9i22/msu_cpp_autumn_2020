#include <iostream>
#include "Bigint.h"
#include <assert.h>
using namespace std;
void LowDigitTest() {
    Bigint a(5), b(6);
    assert(a - b == -1);
    assert(b - a == 1);
    assert(-b - a == -11);
    assert(a + b == 11);
    assert(a * b == 30);
}
void HighDigitTest() {
    Bigint a(543), b(612);
    assert(a + b == Bigint("1155"));
    Bigint c(566556), d(111111);
    assert(c + d == Bigint("677667"));
    Bigint e("245724572475472554267"), f("1354635146773541754745");
    assert(e + f == Bigint("1600359719249014309012"));
    assert(a + 1 == 544);
}
void CompTest1() {
    Bigint a("1345613567413567173542547245772547245"), b(343234);
    assert((a < b) == 0);
    assert((a > b) == 1);
    assert((a <= b) == 0);
    assert((a >= b) == 1);
}
void CompTest2() {
    Bigint a("545"), b(545);
    assert((a < b) == 0);
    assert((a > b) == 0);
    assert((a <= b) == 1);
    assert((a >= b) == 1);
    assert((a == b) == 1);
    assert((a != b) == 0);
    Bigint c("1345613567413567173542547245772547245"), d("1345613567413567173542547245772547245");
    assert((c == d) == 1);

}
void ZerosTest() {
    Bigint a("005");
    assert(a == 5);
}
void MultTest1() {
    Bigint c("325325523235253"), d("235325235235235");
    assert(c * d == Bigint("76557305283361821967699739455"));
}
void MultTest2() {
    Bigint c("4575463763756785454678854765467845786567483567856383568"), d("45267254672456724567245724572457245724575474253725472457245724572457245724572457");
    assert(c * d == Bigint("207118683438575777352463344648976660976461208704350842885718331065932242488612244575792967328778758270914754479998290069376225000186576"));
}
int main() {
    LowDigitTest();
    HighDigitTest();
    CompTest1();
    CompTest2();
    ZerosTest();
    MultTest1();
    MultTest2();
    cout << "Program is running correctly" << std::endl;
}