#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <curl/curl.h>
#include <sys/time.h>
 
#define HANDLECOUNT 10   /* Number of simultaneous transfers */

CURLM *initMultiHandle(char *location){
  CURL *handles[HANDLECOUNT];
  
 
  int still_running = 1; /* keep number of running handles */
  int i;
 
  CURLMsg *msg; /* for picking up messages with the transfer status */
  int msgs_left; /* how many messages are left */
 
  /* Allocate one CURL handle per transfer */
  for(i = 0; i<HANDLECOUNT; i++)
    handles[i] = curl_easy_init();
    curl_easy_setopt(handles[i], CURLOPT_URL, location);
    curl_easy_setopt(handles[i], CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(handles[i], CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(handles[i], CURLOPT_VERBOSE, 0L);
    curl_easy_setopt(handles[i], CURLOPT_COOKIEJAR, "cookie.txt");
    curl_easy_setopt(handles[i], CURLOPT_COOKIEFILE, "");
    curl_easy_setopt(handles[i], CURLOPT_FOLLOWLOCATION, 1L);
 
  /* init a multi stack */
  return curl_multi_init();
}
 
int main(void)
{
  CURLM *multi_handle;
  initMultiHandle()
 
  /* add the individual transfers */
  for(i = 0; i<HANDLECOUNT; i++)
    curl_multi_add_handle(multi_handle, handles[i]);
 
  while(still_running) {
    CURLMcode mc = curl_multi_perform(multi_handle, &still_running);
 
    if(still_running)
      /* wait for activity, timeout or "nothing" */
      mc = curl_multi_poll(multi_handle, NULL, 0, 1000, NULL);
 
    if(mc)
      break;
  }
  /* See how the transfers went */
  while((msg = curl_multi_info_read(multi_handle, &msgs_left))) {
    if(msg->msg == CURLMSG_DONE) {
      int idx;
 
      /* Find out which handle this message is about */
      for(idx = 0; idx<HANDLECOUNT; idx++) {
        int found = (msg->easy_handle == handles[idx]);
        if(found)
          break;
      }
 
      switch(idx) {
      case HTTP_HANDLE:
        printf("HTTP transfer completed with status %d\n", msg->data.result);
        break;
      case FTP_HANDLE:
        printf("FTP transfer completed with status %d\n", msg->data.result);
        break;
      }
    }
  }
 
  curl_multi_cleanup(multi_handle);
 
  /* Free the CURL handles */
  for(i = 0; i<HANDLECOUNT; i++)
    curl_easy_cleanup(handles[i]);
 
  return 0;
}