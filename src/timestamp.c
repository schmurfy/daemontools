#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "taia.h"
#include "timestamp.h"

static char hex[16] = "0123456789abcdef";

void timestamp(char s[TIMESTAMP])
{
  struct taia now;
  char nowpack[TAIA_PACK];
  int i;

  taia_now(&now);
  taia_pack(nowpack,&now);

  s[0] = '@';
  for (i = 0;i < 12;++i) {
    s[i * 2 + 1] = hex[(nowpack[i] >> 4) & 15];
    s[i * 2 + 2] = hex[nowpack[i] & 15];
  }
}

void iso_timestamp(char s[TIMESTAMP])
{
  int len;
  time_t now = time(NULL);
  struct tm *tm = gmtime(&now);
  // the string has to be 24 characters
  len = strftime(s, TIMESTAMP, "%Y-%m-%dT%H:%M:%SZ    ", tm);
  s[len] = ' ';
}
