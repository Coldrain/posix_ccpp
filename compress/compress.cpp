#include "Compress.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <zlib.h>

CCompress::CCompress()
{
}

CCompress::~CCompress ()
{
}

int CCompress::zip (const char *infile, const char *outfile)
{
    char buf[512];
    FILE *in;
    gzFile out;
    int len = 0;

    if ((in = fopen(infile, "rb")) == NULL)
    {
        return E_CANNOT_OPEN_INFILE;
    }

    if ((out = gzopen(outfile, "wb")) == NULL)
    {
        return E_CANNOT_OPEN_OUTFILE;
    }

    while ((len = fread(buf, 1, sizeof(buf), in)) > 0)
        gzwrite(out, buf, len);

    fclose(in);
    gzclose(out);

    return 0;
}

int CCompress::unzip (const char *infile, const char *outfile)
{
    char buf[512];
    gzFile in;
    FILE *out;
    int len;

    if ((in = gzopen(infile, "rb")) == NULL)
    {
        return E_CANNOT_OPEN_INFILE;
    }

    if ((out = fopen(outfile, "wb")) == NULL)
    {
        return E_CANNOT_OPEN_OUTFILE;
    }

    while ((len = gzread(in, buf, sizeof(buf))) > 0)
        fwrite(buf, 1, len, out);

    gzclose(in);
    fclose(out);

    return 0;
}