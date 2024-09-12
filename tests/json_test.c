#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>

#include "../external/criterion-2.4.2/include/criterion/criterion.h"
#include "../src/json.h"

Test(json_init_object, basic) {
  json_object_t *obj = json_init_object();
  cr_assert_neq(obj, NULL);
  json_free_object(obj);
}

Test(json_add_pair, basic) {
  json_object_t *obj = json_init_object();

  json_add_pair(obj, "hello", "world");
  json_add_pair(obj, "hello", "world");

  char *json_string = json_stringify(obj);
  const char *expected = "{\"hello\": \"world\", "
                         "\"hello\": \"world\"}";
  cr_assert_eq(
      json_string, expected, "Expected %s. Got: %s", expected, json_string);

  json_free_object(obj);
}

// Callback function to write response data into a buffer
static size_t
write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t realsize = size * nmemb;
  char *response = (char *)userp;

  strncat(response, (char *)contents, realsize);

  return realsize;
}

Test(json_from_body, basic) {
  CURL *curl;
  CURLcode res;

  const char *json_data = "{\"name\":\"John Doe\", \"password\":\"1234\"}";
  char response[4096] = {0};

  curl_global_init(CURL_GLOBAL_ALL);

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:6961/");
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      fprintf(
          stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    } else {
      printf("Response from server: %s\n", response);
    }

    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
  }

  curl_global_cleanup();

  cr_assert_eq(
      json_data, response, "Expected %s. Got: %s", json_data, response);
}
