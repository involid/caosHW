#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

static size_t write_handler(void *ptr, size_t size, size_t nmemb, void *stream)
{
    char* title_start = strstr(ptr, "<title>");
    if (title_start == NULL) {
        return nmemb * size;
    }
    title_start += sizeof("<title>") - 1;
    char* title_end = strstr(title_start, "</title>");
    if (title_end == NULL) {
        return nmemb * size;
    }

    size_t written = fwrite(title_start, title_end - title_start, 1, (FILE *)stream);
    return nmemb * size;
}

int main(int argc, char *argv[]) {
    char* url = argv[1];
    CURLcode res;
    CURL* curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_handler);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return -1;
        }

        curl_easy_cleanup(curl);
    }
    return 0;
}