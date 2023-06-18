import string
import random
import time
import signal
import sys

def sig_handler(sig, frame):
    print("signal received closing uartport")
    close(uartport)
    sys.exit(0)

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

with open("/dev/ttyAB0", "wb") as uartport:
    sequence_num = 0
    signal.signal(signal.SIGINT, sig_handler)
    while True:
        payload = ''.join(random.choices(string.ascii_lowercase + string.digits, k=12))
        length = len(payload)
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


