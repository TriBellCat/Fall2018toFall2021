#!/usr/bin/env python3

# Python DNS query client
#
# Example usage:
#   ./dns.py --type=A --name=www.pacific.edu --server=8.8.8.8
#   ./dns.py --type=AAAA --name=www.google.com --server=8.8.8.8

# Should provide equivalent results to:
#   dig www.pacific.edu A @8.8.8.8 +noedns
#   dig www.google.com AAAA @8.8.8.8 +noedns
#   (note that the +noedns option is used to disable the pseduo-OPT
#    header that dig adds. Our Python DNS client does not need
#    to produce that optional, more modern header)


from dns_tools import dns  # Custom module for boilerplate code

import argparse
import ctypes
import random
import socket
import struct
import sys

def main():

    # Setup configuration
    parser = argparse.ArgumentParser(description='DNS client for ECPE 170')
    parser.add_argument('--type', action='store', dest='qtype',
                        required=True, help='Query Type (A or AAAA)')
    parser.add_argument('--name', action='store', dest='qname',
                        required=True, help='Query Name')
    parser.add_argument('--server', action='store', dest='server_ip',
                        required=True, help='DNS Server IP')

    args = parser.parse_args()
    qtype = args.qtype
    qname = args.qname
    server_ip = args.server_ip
    port = 53
    server_address = (server_ip, port)

    if qtype not in ("A", "AAAA"):
        print("Error: Query Type must be 'A' (IPv4) or 'AAAA' (IPv6)")
        sys.exit()

    # Create UDP socket
    # ---------
    # STUDENT TO-DO
    # ---------
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((server_ip, port))

    # Generate DNS request message
    # ---------
    # STUDENT TO-DO
    # ---------
    raw_bytes = bytearray()
    if qtype == "A":
        raw_bytes.append(0x00)
        raw_bytes.append(0x01)
    elif qtype == "AAAA":
        raw_bytes.append(0x00)
        raw_bytes.append(0x1c)
    split = qname.split(".")
    string = ""
    for i in split:
        hexs = hex(len(i))    
        string += str(hexs)+i
    raw_bytes +=bytes(string,'ascii')
    raw_bytes.append(0x08)
    raw_bytes.append(0x08)
    raw_bytes.append(0x08)
    raw_bytes.append(0x08)

    # Send request message to server
    # (Tip: Use sendto() function for UDP)
    # ---------
    # STUDENT TO-DO
    # ---------
    bytes_send = s.sendto(raw_bytes,server_address)

    # Receive message from server
    # (Tip: use recvfrom() function for UDP)
    # ---------
    # STUDENT TO-DO
    # ---------
    max_bytes = 4096
    (raw_bytes2,src_addr) = s.recvfrom(max_bytes)

    print(raw_bytes2)

    # Close socket
    # ---------
    # STUDENT TO-DO
    # ---------
    s.close()

    # Decode DNS message and display to screen
    dns.decode_dns(raw_bytes)
    print(bytes_send)

if __name__ == "__main__":
    sys.exit(main())
