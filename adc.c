/*
 * adc.c
 *
 *  Created on: 19/04/2013
 *      Author: cuki
 */

#include <18F252.h>
#DEVICE ADC=10

#FUSES HS
#USE delay(clock=15MHz)
#USE rs232(xmit=PIN_C6, baud=9600)

#define buff 10

int i;

long buffer[buff];

float volt;
float voltAux;

void rotate(long *p) {
	long *pri;
	long *seg;
	int cont;

	pri = p;
	seg = p + 1;

	for (cont = 0; cont < (buff - 1); cont++, pri++, seg++) {
		*pri = *seg;
	}
}

float media(long in) {
	float media = 0;
	long *p;
	int cont;

	if (i < buff)
		buffer[i++] = in;
	else {
		rotate(buffer);
		buffer[buff - 1] = in;
	}

	p = buffer;

	for (cont = 0; cont < buff; cont++, p++)
		media += (float) *p;

	return media / i;
}

#zero_ram
int main(void) {

	setup_adc_ports(AN0);
	setup_adc(ADC_CLOCK_INTERNAL);
	set_adc_channel(0);
	delay_us(100);

	while (TRUE) {
		volt = media(read_adc());

		if (volt != voltAux) {
			printf("%f %f\n\r", volt, voltAux);
			voltAux = volt;
			delay_ms(10);
		}
	}
	return 0;
}
