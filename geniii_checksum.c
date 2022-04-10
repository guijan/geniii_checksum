/* geniii_checksum: save data section checksum for generation III pokemon games
 *
 * Definition at:
 * https://bulbapedia.bulbagarden.net/wiki/Save_data_structure_(Generation_III)?#Checksum
 *
 * Notice bulbapedia describes an implementation, not the algorithm itself.
 * Here's a definition of the algorithm:
 * 1. Initialize a 16-bit variable to 0.
 * 2. Read a sequence of little-endian 16-bit numbers.
 * 3. 1's complement add with wrap-around each number to the variable.
 *
 * The length of the save data sections is always a multiple of 2, this
 * implementation takes advantage of it.
 */
unsigned short
geniii_checksum(const void *_buf, short len)
{
	const unsigned char *buf = _buf;
	short i;
	unsigned short sum;
	unsigned short tmp;

	sum = 0;
	for (i = 0; i < len;) {
		/* Read 16-bit little-endian word. */
		tmp = buf[i++];
		tmp += buf[i++] << 8;

		/* If there's a carry, add it. */
		if ((tmp + sum & 0xFFFF) < sum)
			sum++;

		sum = sum + tmp & 0xFFFF;
	}
	return (sum);
}
