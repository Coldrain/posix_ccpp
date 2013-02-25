unsigned int CountOne(unsigned int x){
	x = (x & 0¡Á55555555) + (x >> 1 & 0¡Á55555555);
	x = (x & 0¡Á33333333) + (x >> 2 & 0¡Á33333333);
	x = (x & 0x0f0f0f0f) + (x >> 4 & 0x0f0f0f0f);
	x = (x & 0x00ff00ff) + (x >> 8 & 0x00ff00ff);
	x = (x & 0x0000ffff) + (x >> 16 & 0x0000ffff);

	return x;
}