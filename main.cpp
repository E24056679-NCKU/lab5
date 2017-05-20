#include "HugeInt.h"

using namespace std;

int main()
{
    HugeInt a(1000);
    HugeInt b("891374918347148973041412341874136498712364");
    cout << a << endl;
    cout << b << endl;
    cout << a + b << endl;
    return 0;
}
