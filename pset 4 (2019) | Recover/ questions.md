# QUESTIONS

## What's `stdint.h`?

Standard input library to allow standardisation and setting of data type size


## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

To ensure parity in data type size as different operating systems can have different default sizes for the same data type
Also to explicitly inform the programmer of the determined data type sizes


## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1, 4, 4, 2


## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

BM or 66 77 or 0x42 0x4d


## What's the difference between `bfSize` and `biSize`?

bfSize = size of the bitmap file
biSize = size of BITMAPINFOHEADER


## What does it mean if `biHeight` is negative?

The bitmap is a top-down DIB and its origin is the upper-left corner.
biCompression must be either BI_RGB or BI_BITFIELDS. 
Top-down DIBs cannot be compressed.


## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount. 

Can only be:
0 (specified by JPEG/PNG format)
1 (monochrome)
4 (16 colours)
8 (256 colours)
16
24
32

1 pixel represented by 4 bits. 
Eg 1 byte = 0x1F, pixel 1 is the first colour in the bmiColors table, pixel 2 is the sixteenth


## Why might `fopen` return `NULL` in `copy.c`?

The input file cannot be opened, and/or an output file cannot be created. 
This in turn can be caused by multiple things such as not having read/write permissions, the file is missing etc


## Why is the third argument to `fread` always `1` in our code?

Third argument is "size_t nmemb" - the number of elements to read, each one with a size of size bytes.
Since each time fread() is called only one header is read in (bf/bi), nmemb is 1


## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

RGBTRIPLE = ¡°encapsulates¡± three bytes: one blue, one green, and one red
padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4
        = (4 - (3 * 3) % 4 ) % 4
        = 3


## What does `fseek` do?

It sets the file position of the stream to the given offset. 
In copy.c, it allows the pointer reading the file stream to skip over the whole padding (the offset)


## What is `SEEK_CUR`?

Current position of the file pointer, inptr.
