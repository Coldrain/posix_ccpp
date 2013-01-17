Compress.h
#ifndef COMPRESS_H
#define COMPRESS_H

#define E_CANNOT_OPEN_INFILE 1
#define E_CANNOT_OPEN_OUTFILE 2

class CCompress
{
public:
    CCompress();
    ~CCompress();

public:
    int zip(const char *infile, const char *outfile);
    int unzip(const char *infile, const char *outfile);
};

#endif // COMPRESS_H