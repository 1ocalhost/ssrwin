#pragma once

#define dns_ntop inet_ntop
#define dns_pton inet_pton

int inet_pton(int af, const char *src, void *dst);
