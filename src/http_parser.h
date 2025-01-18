#pragma once
#include "common.h"

http_method check_method(char *msg);
Path get_path(char *request);
char *get_version(char *request);
char *get_response_type(char *request);
