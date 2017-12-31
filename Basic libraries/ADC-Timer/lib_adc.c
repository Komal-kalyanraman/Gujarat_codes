
///////////////////////////// 10 bit ADC //////////////////////////////////////////

uint16_t readADC_10bit(int channel)	
{
	
	uint16_t value=0;
	
	ADCSRA |= (1 << ADPS2)| (1 << ADIF);// Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz

	ADMUX = channel;
	
	ADMUX |= (1 << REFS0);//|(0 << REFS1); // Set ADC reference to internal 2.56v
	
	ADCSRA |= (1 << ADEN);  // Enable ADC
	
	for(int i=0;i<3;i++)
	{
	
		ADCSRA |= (1 << ADSC);  // Start A2D Conversions 
		
		while(!(ADCSRA & (1<<ADIF)));
		
		ADCSRA|=(1<<ADIF);	
		
		value = ADCL+(ADCH<<8);	
		
	}
	
	return value;
}

///////////////////////////// 8 bit ADC //////////////////////////////////////////

int readADC_8bit(int channel)	 
{

	ADMUX=channel;
	ADMUX|=(1<<ADLAR)|(1<<REFS0);//|(1<<REFS1);	//supply vcc
	
	ADCSRA|=(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2)|(1<<ADEN)|(1<<ADSC);	//scaling factor=8 ,adc enable,start conversion


	while(!(ADCSRA & (1<<ADIF)));
	
	ADCSRA|=(1<<ADIF);
	
	return ADCH;

}