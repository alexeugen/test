#include "Curl.h"

Curl::Curl()
{

}

Curl::~Curl()
{



}

char *Curl::Get(const char *url, char **data1, char **headers1)
{
  _URL1 = new char[strlen(url)+1];
  strcpy(_URL1, (char*)url);

  struct BufferStruct output;
  output.buffer = NULL;
  output.size = 0;

  struct BufferStruct output_head;
  output_head.buffer = NULL;
  output_head.size = 0;



  _curl = curl_easy_init();
  curl_easy_setopt(_curl, CURLOPT_URL, _URL1);
  curl_easy_setopt(_curl, CURLOPT_NOPROGRESS, 1L);

  curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
  curl_easy_setopt(_curl, CURLOPT_HEADERDATA, (void *)&output_head);
  curl_easy_setopt(_curl, CURLOPT_WRITEDATA, (void *)&output);

  _res = curl_easy_perform(_curl);

  if(_res!= CURLE_OK)
  {
    std::cout<<"curl_easy_perform FAILED\n";

  }
  curl_easy_cleanup(_curl);

  *data1 = new char[output.size + 1];
  strcpy(*data1, output.buffer);


  *headers1 = new char[output_head.size + 1];
  strcpy(*headers1, output_head.buffer);
}

void Curl::Post(const char *p1, const char *url)
{

  struct BufferStruct output;
  output.buffer = NULL;
  output.size = 0;

  curl_global_init(CURL_GLOBAL_ALL);


   _curl = curl_easy_init();
   if(_curl) {

     curl_easy_setopt(_curl, CURLOPT_URL, url);
     curl_easy_setopt(_curl, CURLOPT_NOPROGRESS, 1L);
  //   curl_easy_setopt(_curl, CURLOPT_VERBOSE, 1L);
     curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
     curl_easy_setopt(_curl, CURLOPT_WRITEDATA, (void *)&output);
     curl_easy_setopt(_curl, CURLOPT_POSTFIELDS, p1);


     _res = curl_easy_perform(_curl);

     if(_res != CURLE_OK)
       fprintf(stderr, "curl_easy_perform() failed: %s\n",
               curl_easy_strerror(_res));

     curl_easy_cleanup(_curl);
   }
   curl_global_cleanup();
}

void Curl::Delete(const char *p, const char *url)
{
  char *s = new char[strlen(p)+strlen(url)];
  strcpy(s, url);
  strcat(s, "/");
  strcat(s, p);



  _curl = curl_easy_init();

  curl_easy_setopt(_curl, CURLOPT_URL, s);
  curl_easy_setopt(_curl, CURLOPT_CUSTOMREQUEST, "DELETE");

//  curl_easy_setopt(_curl, CURLOPT_POSTFIELDS, "{\"name\": \"Eugen\"}");
/*  struct curl_slist *headers = NULL;
  headers = curl_slist_append(headers, "content-type: application/json");
  curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);
*/

  _res = curl_easy_perform(_curl);
  if(_res != CURLE_OK)
    std::cout<<"\n\n ****** curl_easy_perform FAILED FAILED FAILED*****\n\n";
  // do something...
//  curl_slist_free_all(headers);
  curl_easy_cleanup(_curl);

}



/*************Private functions*/

size_t Curl::WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data)
{
  int realsize = size * nmemb;

  struct BufferStruct * mem = (struct BufferStruct *) data;

  mem->buffer = (char*)realloc(mem->buffer, mem->size + realsize + 1);

  if (mem->buffer)
  {
    memcpy( &( mem->buffer[ mem->size ] ), ptr, realsize );
    mem->size += realsize;
    mem->buffer[ mem->size ] = 0;
  }
  return realsize;
}
