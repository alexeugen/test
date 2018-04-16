#include <iostream>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "Curl.h"

using namespace std;

#define URL1 "http://localhost:3000/xmlpost"

void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap(*(str+start), *(str+end));
        start++;
        end--;
    }
}

char* my_itoa(int num)  //itoa code was shamefully coppied from geeksforgeeks
{                                         // and a little modified
    char *str = new char [20];
    int i = 0;
    bool isNegative = false;

    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    if (num < 0)
    {
        isNegative = true;
        num = -num;
    }

    while (num != 0)
    {
        int rem = num % 10;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/10;
    }


    if (isNegative)
        str[i++] = '-';

    str[i] = '\0';


    reverse(str, i);

    return str;
}

int is_leaf(xmlNode *nod)
{
  xmlNode *child = nod->children;
  while(child)
  {
    if(child->type == XML_ELEMENT_NODE)
      return 0;
    child = child->next;
  }
  return 1;
}

void print_xml(xmlNode *nod)
{
  xmlNode *temp = NULL;
  temp = nod;

  while(temp)
  {
    if(temp->type == XML_ELEMENT_NODE)
      printf("%s: %s\n", temp->name, is_leaf(temp)?xmlNodeGetContent(temp):xmlGetProp(temp, (xmlChar*)"id"));
    print_xml(temp->children);
    temp = temp->next;
  }
}

void post_xml(xmlNode *nod, Curl &curl)
{
  xmlNode *temp = NULL;
  temp = nod;

  while(temp)
  {
    if(temp->type == XML_ELEMENT_NODE)
    {

      char *s2 = new char[1000];
      if(is_leaf(temp))
      {
        strcpy(s2,(char*)xmlNodeGetContent(temp));
        int x = sizeof(s2);

        char *s = new char[1000];
        strcpy(s, (char*)temp->name);
        strcat(s, "=");
        strcat(s, s2);
      
        curl.Post(s, URL1);
      }
    }

      //printf("%s: %s\n", temp->name, is_leaf(temp)?xmlNodeGetContent(temp):xmlGetProp(temp, (xmlChar*)"id"));
    post_xml(temp->children, curl);
    temp = temp->next;
  }
}

int main()
{
  xmlDoc *doc;
  xmlNode *nod;
  doc = xmlReadFile("books.xml", NULL, 0);
  nod = xmlDocGetRootElement(doc);


  Curl curl;
   post_xml(nod, curl);

}
