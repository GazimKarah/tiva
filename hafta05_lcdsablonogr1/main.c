#include"inc/tm4c123gh6pm.h"
#include "lcd.h"

int main(void)
{
    // bu kod çalýþmasý gerekecek
    LCDilkayarlar();
    LCDgit(1,7); // satýr 1, sutun 7
    lcdkarakteryaz('A');

	return 0;
}
