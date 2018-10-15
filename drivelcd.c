//program to drive a single LCD

typedef char byte;

//union representing 8bit output port
union lcdport{
	byte value;
	struct{
		byte gnd : 1;
		byte top: 1;
		byte bottom : 1;
		byte middle : 1;
		byte upleft : 1;
		byte downleft : 1;
		byte upright : 1;
		byte downright : 1;
	};
};


union lcdport getPortValue(byte num){
	union lcdport port;
	switch(num){
		case 0:		port.value=0xFF; port.middle=0; break;
		case 1:		port.value=0x00; port.upright=1; port.downright=0; break;
		case 2:		port.value=0xFF; port.upleft=0; port.downright=0; break;
		case 3:		port.value=0xFF; port.upleft=0; port.downleft=0; break;
		case 4:		port.value=0xFF; port.bottom=0; port.top=0; port.downleft=0; break;
		case 5:		port.value=0xFF; port.downleft=0; port.upright=0; break;
		case 6:		port.value=0xFF; port.upright=0; port.top=0; break;
		case 7:		port.value=0x00; port.top=1; port.upright=1; port.downright=1; break;
		case 8:		port.value=0xFF; break;
		case 9:		port.value=0xFF; port.downleft=0; break;
	}
	port.gnd=0;
	return port;
}

void setup(){
	//write on all pins of DDRC
	DDRC=0xFF;
	//initialize all pins to zero
	PORTC=0x00;
}

int main(int argc,char** argv){
	union lcdport portclow=0x00;	//state of portc during low clock cycle
	union lcdport portchigh=0xFF;	//state of portc during high clock cycle
	for(byte i=0; i<10; i++){
		portclow=getPortValue(i);
		portchigh=!portclow;
		//output current digit for 1s
		for(int j=0; j<500; j++){
			PORTC=portclow;
			delay_ms(1);
			PORTC=portchigh;
			delay_ms(1);
		}
	}
}