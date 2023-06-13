#define BUFFER_SIZE 10

typedef struct
{
	/* data */
}	item;

item	buffer[BUFFER_SIZE];
int		in = 0;
int		out = 0;

int main(void) // 이 방법은 최대 BUFFER_SIZE - 1 만큼 버퍼에 수용 가능하다.
{
	item	next_produced;

	while (1)
	{
		/* produce an item in next_produced */
		while ((in + 1) % BUFFER_SIZE == out)
			; // do nothing
		buffer[in] = next_produced;
		in = (in + 1) % BUFFER_SIZE;
	}

	item	next_consumed;

	while (1)
	{
		while (in == out)
			; // do nothing
		next_consumed = buffer[out];
		out = (out + 1) % BUFFER_SIZE;
		/* consume the item in next_consumed */
	}

	return 0;
}

