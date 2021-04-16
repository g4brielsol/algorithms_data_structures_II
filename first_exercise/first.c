#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main()
{
    int a = 0;
    printf("%d\n", a);
    return 0;
}

// unsigned char buf[4];

// FILE *fp = fopen("reg2.dat", "rb");

// while(!feof(fp)) {
//     fread(buf, 4, 1, fp); // read 4 bytes
//     int throw_away = do_some_magic_to_get_the_number(buf);
//     fseek(fp, throw_away, SEEK_CUR); // skip the given number of bytes
//     fread(buf, 1, 1, fp); // read one byte
//     // your character is now in buf[0]
// }