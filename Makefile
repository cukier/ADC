CC=ccsc
CFLAGS=+FH +LN -T -A -M -Z +DF +Y=9 +STDOUT
CFLAGS2=+FM +LN -T -A -M -Z +DF +Y=9 +STDOUT

all: ADC

ADC: adc.c
	$(CC) $(CFLAGS) adc.c

clean:
	rm *.cof *.err *.esym *.hex *.lst