#include <stdio.h>
#include <curl/curl.h>

#include "curl.h"

int main(int argc, char *argv[]) {
   int outBufLen = 4096;
   char outBuf[outBufLen];

                   //(char *url, char *postdata, char *certFilename, char *outBuf, int outBufLen, char debug);
   make_curl_request("https://api.github.com/users/gt3389b", NULL, NULL, outBuf, outBufLen, FALSE);

   return 0;
}
