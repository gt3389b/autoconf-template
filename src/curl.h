/// Server URL for the security system.  Currently this is the Abraxas server
#define SERV_URL "https://abraxas-mtv.cisco.com/SignEngine/sign.jsp"

#define TRUE         1
#define FALSE        0

extern int make_curl_request(char *url, char *postdata, char *certFilename, char *outBuf, int outBufLen, char debug);
