#include <iostream>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>

class Curl{
public:
  Curl();
  ~Curl();
  char *Get(const char *url, char **data1, char **headers1);

  void Post(const char *p1, const char *url);
  void Delete(const char *p, const char *url);
private:
  static size_t WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data);


  CURL *_curl;
  CURLcode _res;
  char *_URL1;

  struct BufferStruct
  {
    char * buffer;
    size_t size;
  };
};
