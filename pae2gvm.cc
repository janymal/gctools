#include <errno.h>
#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include <phosg/Encoding.hh>
#include <phosg/Filesystem.hh>

#include "prs/PRS.hh"

using namespace std;

struct PAEHeader {
  int32_t unknown1;
  int32_t decompressed_size;
  int32_t unknown2[5];
  int32_t gvmoffset;
} __attribute__((packed));

int main(int argc, char* argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  const char* input_filename = argv[1];
  auto pae = fopen_unique(input_filename, "rb");

  PAEHeader header;
  freadx(pae.get(), &header, sizeof(PAEHeader));

  string out_filename = string_printf("%s.dec", input_filename);
  auto dec = fopen_unique(out_filename, "w+b");

  fwritex(dec.get(), &header, sizeof(PAEHeader));
  prs_decompress_stream(pae.get(), dec.get(), 0);
  pae.reset(); // Calls fclose()

  fseek(dec.get(), bswap32(header.gvmoffset) + sizeof(PAEHeader), SEEK_SET);
  save_file(
      string_printf("%s.gvm", input_filename),
      read_all(dec.get()));

  return 0;
}
