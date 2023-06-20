#! python program to transmit data encrypted with
#  crc-16 algorithm to the virtual uart device
import string
import random
import time
import signal
import sys

# signal handler function to close uart device
# when user interrupts the program to exit
def sig_handler(sig, frame):
    print("signal received closing uartport")
    uartport.close()
    sys.exit(0)

# function to extract payload or add crc-16 to the
# payload when polynomial is given
def crc(data_without_crc: bytes, poly=0x8408):
    '''
    CRC-16-CCITT algorithm
    '''
    data = bytearray(data_without_crc)
    crc = 0xFFFF
    for byte in data:
        cur_byte = 0xFF & byte
        for var in range(0, 8):
            if(crc & 0x0001) ^ (cur_byte & 0x0001):
                crc = (crc >> 1) ^ poly
            else:
                crc >>= 1
            cur_byte >>= 1
    crc = (~crc & 0xFFFF)
    crc = (crc << 8) | ((crc >> 8) & 0xFF)

    return crc & 0xFFFF

# starting the program execution from here
with open("/dev/ttyAB0", "wb") as uartport:
    sequence_num = 0
    signal.signal(signal.SIGINT, sig_handler)
    while True:
        # transmit 12 bytes of alphanumeric string
        payload = ''.join(random.choices(string.ascii_lowercase + string.digits, k=12))
        length = len(payload)
        # create some packet type to add to the data
        packet_type = 0x2654
        sequence_num = sequence_num + 1
        header = packet_type + length + sequence_num
        header_in_bytes = header.to_bytes(4, byteorder='little')
        data_plus_header = header_in_bytes + bytes(payload, 'ascii')
        checksum = crc(data_plus_header)
        checksum_in_bytes = checksum.to_bytes(4, byteorder='little')
        data = data_plus_header + checksum_in_bytes
        uartport.write(data)
        print(data)
        time.sleep(1)

