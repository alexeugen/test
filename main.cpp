#include <iostream>
#include "json.h"
#include <cstring>
using namespace std;

int main()
{
  char* json_string = json_get_string("birds_antarctica.json");
  json_value_s* root = json_parse(json_string, strlen(json_string));
  json_object_s* root_object = (json_object_s*)root->payload;

  json_object_element_s* description = root_object->start;
  cout<<description->name->string;
  cout<<((json_string_s*)description->value->payload)->string<<endl;

  json_object_element_s* source = description->next;
  cout<<source->name->string;
  cout<<((json_string_s*)source->value->payload)->string<<endl;

  json_object_element_s* birds = source->next;
  cout<<birds->name->string;

  json_array_s *birds_array = ((json_array_s*)birds->value->payload);
  json_array_element_s* bird1 = birds_array->start;
  json_object_s* bird1_load = (json_object_s*)bird1->value->payload;
  json_object_element_s* bird1_moreload = bird1_load->start;
  cout<<bird1_moreload->name->string;
}
