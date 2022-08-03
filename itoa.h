char* itoa(long i, char *string)
{
	int power = 0, j = 0;
	j = i;
	for (power = 1; j>10; j /= 10)
		power *= 10;
	for (; power>0; power /= 10)
	{
		*string++ = '0' + i / power;
		i %= power;
	}
	*string = '\0';
	return string;
}

int matoi(char* str){
    int result = 0;
    for (int i = 0; str[i] != '\0'; ++i){
        result = result * 10 + str[i] - '0';
    }
    return result;
}
