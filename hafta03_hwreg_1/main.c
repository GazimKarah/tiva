#include "stdint.h"
#include "inc/hw_types.h"

int main(void)
{
    HWREG(0x400FE608)|=0x20; // clock portf enerjilendirilir.
    HWREG(0x40025400)|=0x0e; // dir
    HWREG(0x4002551C)|=0x0e; // den

    // HWREG(0x400253FC)=0x02; // data

    // pinlerle iþlem yapýlacaksa arka taraf olan matematik nedir?
    // baseAdres + 4* (2^b)
    // b burada bit yada bitleri ifade eder

    // gpiopinwrite(baseadres, gp0|gp4|gp6, value) == ben oyle bir ram adresi buluyorumki
       // bu adres gp1 gp4 gp7 ile alakalý oluyor
    //                          2  |16 |128

    // ilk amac ben sadece 1. pin ile alakalý registeri bulmak istiyorum

    // 0x40025000 + 4*(2^0)=0x40025004 -- > gpiopinwrite(baseadress,gpi1,2)
    HWREG(0x40025008)=3;//101

    // hem gp1 gp4 gp7
    // 0x40025000+4*(2^1+2^4+2^7)=0x40025248 // bu register sadece 1,4,7 ile alakalý

    // p0|p1|p2....|p7
    //baseadress+4*(2^0+2^1+2^2+.....+2^7)= 0x400253fc

    if (HWREG((0x400253FC)!=1) // pin0 baglý buton topraga cekmiþ ise
    {
        //buradaki
    }
}
