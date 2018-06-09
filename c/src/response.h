#ifndef DQLITE_RESPONSE_H
#define DQLITE_RESPONSE_H

#include <unistd.h>
#include <stdint.h>

#include <capnp_c.h>

#include "error.h"

/* Errors */
#define DQLITE__RESPONSE_ERR_RENDER -1

#define DQLITE__RESPONSE_BUF_SIZE 4096

/*
 * Encoder for outgoing responses.
 */
struct dqlite__response {
	/* read-only */
	dqlite__error  error;

	/* private */
	uint8_t  buf1[DQLITE__RESPONSE_BUF_SIZE]; /* Pre-allocated response buffer, enough for most cases */
	uint8_t *buf2;                            /* Dynamically allocated buffer for large payloads */
	size_t   size;                            /* Number of bytes in the encoded response */
};

void dqlite__response_init(struct dqlite__response* r);
void dqlite__response_close(struct dqlite__response* r);

/* APIs for encoding responses */
int dqlite__response_welcome(
	struct dqlite__response *r,
	const char* leader,
	uint16_t heartbeat_timeout /* In milliseconds */);

int dqlite__response_servers(struct dqlite__response *r, const char** servers);

/* Get the data of an encoded response */
uint8_t *dqlite__response_data(struct dqlite__response *r);

/* Get the size of a encoded response */
size_t dqlite__response_size(struct dqlite__response *r);

#endif /* DQLITE_RESPONSE_H */
