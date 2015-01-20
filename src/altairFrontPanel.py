import pexpect
import serial
import struct

# Globals
serialPort = '/dev/ttyACM0'
simh = 0

def step():
	simh.sendline('step')
	simh.expect('PC: ([0-9A-F]+)')
	newPC, = simh.match.groups()
	print('Step: %s' % newPC)
	return int(newPC, 16)

def getPC():
	simh.sendline('e PC')
	simh.expect('PC:\t([0-9A-F]+)')
	PC, = simh.match.groups()
	print('PC: %s' % PC)
	return int(PC, 16)

def setPC(address):
	cmd = "d PC %x" % address
	simh.sendline(cmd)
	simh.expect('sim>')
	print('New PC: %s' % address)
	return

def getData(address):
	cmd = "e %x" % address
	simh.sendline(cmd)
	simh.expect('.+:\t([0-9A-F]+)\r\nsim')
	data, = simh.match.groups()
	print('Get: %04X: %s' % (address, data) )
	return int(data, 16)


def setData(address, data):
	cmd = "d %x %x" % (address, data)
	simh.sendline(cmd)
	simh.expect('sim>')
	print('Set: %04X: %02X' % (address, data) )
	return

def sendSerialData(ser, pc, data):
	print('Send serial: PC: %s, Data: %s' % (pc, data) )
#	serialSendData = struct.pack('H', int(pc, 16) )
#	serialSendData += struct.pack('B', int(data, 16) )
	serialSendData = struct.pack('H', pc )
	serialSendData += struct.pack('B', data )
	ser.write(serialSendData)
	return

# Jump around
def storeProgramJumpAround():
	setData(0x0000, 0xC3)
	setData(0x0001, 0x03)
	setData(0x0002, 0x00)
	setData(0x0003, 0x00)
	setData(0x0004, 0x00)
	setData(0x0005, 0x00)
	setData(0x0006, 0xC3)
	setData(0x0007, 0x00)
	setData(0x0008, 0x00)
	setPC(0);

def storeProgramFibonacci():
	setData(0x0000, 0o061)	#LXI
	setData(0x0001, 0o377)
	setData(0x0002, 0o000)
	setData(0x0003, 0o026)	#MVI 0 D
	setData(0x0004, 0o000)
	setData(0x0005, 0o036)	#MVI 128 E, result address
	setData(0x0006, 0o200)
	setData(0x0007, 0o076)	#MVI 1 A
	setData(0x0008, 0o001)
	setData(0x0009, 0o107)	#MOV A B
	setData(0x000A, 0o022)	#STAX
	setData(0x000B, 0o034)	#INR E
	setData(0x000C, 0o022)	#STAX
	setData(0x000D, 0o034)	#INR E
	setData(0x000E, 0o016)	#MVI 8 C
	setData(0x000F, 0o010)
	setData(0x0010, 0o157)	#MOV A L
	setData(0x0011, 0o345)	#PUSH HL
	setData(0x0012, 0o341)	#POP HL
	setData(0x0013, 0o175)	#MOV L A
	setData(0x0014, 0o150)	#MOV B L
	setData(0x0015, 0o345)	#PUSH HL
	setData(0x0016, 0o200)	#ADD A+B
	setData(0x0017, 0o107)	#MOV A B
	setData(0x0018, 0o022)	#STAX
	setData(0x0019, 0o034)	#INR E
	setData(0x001A, 0o015)	#DCR C
	setData(0x001B, 0o171)	#MOV C A
	setData(0x001C, 0o376)	#CPI A,0
	setData(0x001D, 0o000)
	setData(0x001E, 0o302)	#JNZ
	setData(0x001F, 0o022)
	setData(0x0020, 0o000)
	setData(0x0021, 0o303)	#JMP
	setData(0x0022, 0o000)
	setData(0x0023, 0o000)
	

def main():
	global simh

	simh = pexpect.spawn('./altairz80')
	simh.expect('sim> ')

	simh.sendline('show cpu')
	simh.expect('CPU\r\n(.*)\r\nsim')
	line = simh.match.groups()
	print('CPU Info:\n%s' % line[0])

#	storeProgramJumpAround()
	storeProgramFibonacci()

	ser = serial.Serial(serialPort, 9600)
	# Note: We are still receiving old received reply values here probably due to buffering on Arduino
	# Block until Arduino sketch serial ready
	# TODO: Block not working when Arduino reset and init serial before starting python
	print("Waiting for Arduino serial ready reply")
	while True:
		value = ser.read(1)
		if value == 'S' :
			break

	print("Waiting for Arduino commands...");


	# TODO
	# 
	#	sendSerial: PC(2 bytes),dataAtPC(1 byte)
	# 		struct.pack('H',PC)
	#		struct.pack('B',dataAtPC)
	#       revcSerial: SwitchState(A0-A15 + command switches)
	#	action based on switch state
	while 1:
		command = ser.read(1)
		if (command == '3'): # Step
			print("Command: %s" % command)
			step()
			PC = getPC()
			data = getData(PC)
			sendSerialData(ser, PC, data)
		elif (command == '4'): # Examine
			addressLow = ord(ser.read(1))
			addressHigh = ord(ser.read(1))

			print("Command: %s, Data: %X %X" % (command, addressLow, addressHigh))

			address = (addressHigh << 8) + addressLow
			setPC(address)
			data = getData(address)
			sendSerialData(ser, address, data)
		elif (command == '5'): # Examine next
			print("Command: %s" % command)
			address = getPC() + 1
			setPC(address)
			data = getData(address)
			sendSerialData(ser, address, data)
		elif (command == '6'): # Deposit
			data = ord(ser.read(1))

			print("Command: %s, Data: %X" % (command, data))
			PC = getPC()
			setData(PC, data)
			sendSerialData(ser, PC, data)
		elif (command == '7'): # Deposit next
			data = ord(ser.read(1))

			print("Command: %s, Data: %X" % (command, data))
			PC = getPC() + 1
			setPC(PC)
			setData(PC, data)
			sendSerialData(ser, PC, data)


#		sendSerialData(ser)
#		ser.read(1)
#		step()


	print('Finished')

if __name__ == "__main__":
	main()

