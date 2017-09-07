#include <sys/types.h>
#include <time.h>
#include <stdio.h>
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

// 2017-09-07T07:00:58Z.867840
int iso_timestamp(char s[TIMESTAMP])
{
  int len;
  struct tm *tm;
  
  struct timeval now;
  gettimeofday(&now,(struct timezone *) 0);
  
  tm = gmtime(&now.tv_sec);
  
  // 2013-11-15T03:00:28Z.000000
  len = strftime(s, TIMESTAMP, "%Y-%m-%dT%H:%M:%SZ", tm);
  len += sprintf(s + len, ".%06d ", now.tv_usec);
  
  return len;
}
