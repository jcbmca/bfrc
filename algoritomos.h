#ifndef ALGORITOMOS_H
#define ALGORITOMOS_H



unsigned int adler32(unsigned char *data, size_t len);

unsigned int file_get_size(char *file_name);

unsigned int file_get_adler32(char *file_name);


#endif // ALGORITOMOS_H
