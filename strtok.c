// strtok shim provided by Intel technical support 

#define _GNU_SOURCE 1

#include <string.h>
#include <dlfcn.h>
 
typedef char *(*strtok_t) (char *str, const char *delimiters);
static strtok_t strtok_orig_p = NULL;
 
char *strtok(char *str, const char *delimiters)
{
  if (strtok_orig_p == NULL) {
    strtok_orig_p = (strtok_t) dlsym(RTLD_NEXT, "strtok");
    if (strtok_orig_p == NULL) {
      /* Error handling */
      return NULL;
    }
    if (str == NULL) {
      str = "";
    }
  }
  return strtok_orig_p(str, delimiters);
}

