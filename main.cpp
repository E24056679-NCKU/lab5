#include "HugeInt.h"

using namespace std;

int main()
{
#ifdef TEST
    HugeInt x(100);
    HugeInt y(999);
    cout << x - y << endl;
#endif

#ifndef TEST
    HugeInt x;
    HugeInt y(28825252);
    HugeInt z("314159265358979323846");
    HugeInt result;

    cin >> x;
    result = x + y;
    cout << x << '+' << y << " = " << result << endl;

    result = z - x;
    cout << result << endl;
#endif
    return 0;
}
