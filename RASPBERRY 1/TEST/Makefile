CC=g++
DLIBS=-lbcm2835 -lrt -lpthread
OBJS= /home/pi/TEST/sms.o /home/pi/SIM7600X-4G-HAT-Demo/Raspberry/c/arduPi.o /home/pi/SIM7600X-4G-HAT-Demo/Raspberry/c/sim7x00.o
SMS:$(OBJS) 
	$(CC) -Wall -o sms $(OBJS)  $(DLIBS) 

%.o:%.c
	$(CC) -c -o $@ $<

clean:
	rm -f *.o sms


