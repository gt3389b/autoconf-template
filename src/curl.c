#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <semaphore.h>
#include <curl/curl.h>

#include "b64.h"
//#include "utils.h"
#include "curl.h"

CURL *gCurlCtx = NULL;

typedef struct tCurl_Response {
   char *buf;
   int   buf_len;
   int   buf_size;
} tCurl_Response;

////////////////////////////////////////////////////////////////////////////////
/// \fn size_t write_func( void *ptr, size_t size, size_t nmemb, void *stream)
///
/// \brief Callback function from CURL request upon successful reception of 
///  data.
///
/// This function is a callback function prototyped by the CURL library to 
/// handle the reception of data from HTTP requests.
///
/// \param ptr - A memory pointer to the data
///
/// \param size - The size of each data element passed
///
/// \param nmemb - The number of elements passed
///
/// \param stream - Defined by the WRITE_DATA attribute in the request instance.
/// 
/// \return Number of bytes processed
///
/// \static
////////////////////////////////////////////////////////////////////////////////
static size_t
write_func( void *ptr, size_t size, size_t nmemb, void *user_data)
   {
   char *data = (char *)ptr;
   tCurl_Response *uData = (tCurl_Response *)user_data;
   char *signature;

   if (strstr(data, "SUCCESS"))
      {
      if((signature = strstr(data, "SIGNATURE:")) != NULL)
         signature+=10;
      else if((signature = strstr(data, "PUBLIC_KEY:")) != NULL)
         signature+=11;

      uData->buf_len = decode((unsigned char *)signature, strlen(signature), (unsigned char *)uData->buf, uData->buf_size);
      }
   else
      {
      printf("%s\n",data);
      fflush(stdout);
      uData->buf_len = 0;
      }
   
   return size*nmemb;
   }


////////////////////////////////////////////////////////////////////////////////
/// \fn void make_curl_request(int o_fd, char *postdata)
///
/// \brief Submit a request to the Abraxas server
///
/// This module submits a preassembled post string to the Abraxis server.  It
/// initializes the CURL instance, sets up necessary attributes, and submits
/// the request.
/// 
/// \param o_fd - This is a file descriptor to write resulting data from the 
///               Abraxas server.  If NULL, then it is assumed that the
///               data will be transferred to the result buffer in the master
///               global data structure.
///
/// \param postdata - A string of POST data to send to the URL.
///
/// \note The URL is globally defined
///
/// \static
////////////////////////////////////////////////////////////////////////////////
int
make_curl_request(char *url, char *postdata, char *certFilename, char *outBuf, int outBufLen, char debug)
   {
   CURLcode ccode;
   tCurl_Response uData;
   int retCode = 0;
   
   // initialize cURL library
   curl_global_init(CURL_GLOBAL_ALL);

   gCurlCtx = curl_easy_init();

   // I'd like to allocate this in curl.c
   uData.buf = outBuf;
   uData.buf_size = outBufLen;
   uData.buf_len = 0;

   do {
      // set the write_data function
      if((ccode = curl_easy_setopt(gCurlCtx, CURLOPT_WRITEFUNCTION, write_func)) != CURLE_OK)
         {
         printf("Error (line %d): %s\n", __LINE__, curl_easy_strerror(ccode));
         continue;
         }

      // write_data
      if((ccode = curl_easy_setopt(gCurlCtx, CURLOPT_WRITEDATA, &uData)) != CURLE_OK)
         {
         printf("Error (line %d): %s\n", __LINE__, curl_easy_strerror(ccode));
         continue;
         }

      if((ccode = curl_easy_setopt(gCurlCtx, CURLOPT_URL, url)) != CURLE_OK)
         {
         printf("Error (line %d): %s\n", __LINE__, curl_easy_strerror(ccode));
         continue;
         }

      if((ccode = curl_easy_setopt(gCurlCtx, CURLOPT_POSTFIELDS, postdata)) != CURLE_OK)
         {
         printf("Error (line %d): %s\n", __LINE__, curl_easy_strerror(ccode));
         continue;
         }

      if((ccode = curl_easy_setopt(gCurlCtx, CURLOPT_CAINFO, certFilename)) != CURLE_OK )
         {
         printf("Error (line %d): %s\n", __LINE__, curl_easy_strerror(ccode));
         continue;
         }

      if((ccode = curl_easy_setopt(gCurlCtx, CURLOPT_SSL_VERIFYPEER, 1)) != CURLE_OK)
         {
         printf("Error (line %d): %s\n", __LINE__, curl_easy_strerror(ccode));
         continue;
         }

      // Set cURL to verbose if logging has been turned up
      if(debug)
         if((ccode = curl_easy_setopt(gCurlCtx, CURLOPT_VERBOSE, TRUE)) != CURLE_OK)
            {
            printf("Error (line %d): %s\n", __LINE__, curl_easy_strerror(ccode));
            continue;
            }

      if((ccode = curl_easy_setopt(gCurlCtx, CURLOPT_POST, TRUE)) != CURLE_OK)
         {
         printf("Error (line %d): %s\n", __LINE__, curl_easy_strerror(ccode));
         continue;
         }

      if((ccode = curl_easy_perform(gCurlCtx)) != CURLE_OK)
         {
         printf("Error (line %d): %s\n", __LINE__, curl_easy_strerror(ccode));
         continue;
         }
      
      retCode = uData.buf_len;

      curl_easy_cleanup(gCurlCtx);

      // clean up cURL library
      curl_global_cleanup();
   } while (0);

   return retCode;
}
