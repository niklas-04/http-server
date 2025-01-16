#pragma once
#include "common.h"

Path get_path(char *request);

http_request *parse_request(char *request_str);
