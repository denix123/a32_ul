#include <stdio.h>
#include <io.h>
#include <string.h>

void echo_files(char *, char *);

int
main(int argc, char *argv[])
{
  int i;
  char *prefix;

  prefix = "";

  if (argc < 2) {
    fprintf(stderr, "Usage:  libecho [-p prefix] list...\n");
    return 1;
  }

  for (i = 1 ; i < argc ; i++)
    if (!stricmp(argv[i], "-p"))
      prefix = argv[++i];
    else
      echo_files(prefix, argv[i]);

  return 0;
}

void
echo_files(char *prefix, char *f)
{
  long ff;
  struct _finddata_t fdt;
  char *slash;
  char filepath[256];

  while((slash = strrchr(f, '/')) != NULL)
    *slash = '\\';

  strcpy(filepath, f);

  slash = strrchr(filepath, '\\');

  if (slash) {
    slash++;
    *slash = 0;
  } else {
    filepath[0] = '\0';
  }

  ff = _findfirst(f, &fdt);

  if (ff < 0) {
    printf("%s%s\n", prefix, f);
    return;
  }

  printf("%s%s%s\n", prefix, filepath, fdt.name);

  for (;;) {
    if (_findnext(ff, &fdt) < 0)
      break;
    printf("%s%s%s\n", prefix, filepath, fdt.name);
  }
  _findclose(ff);
}
