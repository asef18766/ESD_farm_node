import serial
import string
import json

from serial.serialwin32 import Serial

def bytes_filter(by:bytes)->bytes:
    res = b""
    for i in by:
        if i in string.printable.encode():
            res += chr(i).encode()
    return res

def creat_dev_map(cfg:dict)->dict:
    '''
    this segment shall be substitude to other thing in the future
    '''
    map_ct = 3
    devmap = {}
    for d in cfg["input_devices"] + cfg["output_devices"]:
        devmap.update({
            d["hid"]:map_ct
        })
        map_ct+=1
    
    return {
        "success":True,
        "device_map":devmap
    }

def dumpOutput(sio:Serial):
    while True:
        res = sio.readline().strip()
        if res == b"":
            break
        res = bytes_filter(res)
        res = res.decode()
        if res == "":
            break
        print(res)

def conn_serial(dev_port:str, baud_rate:int, timeout:int)->Serial:
    sio = serial.Serial(dev_port, baud_rate, timeout=timeout)

    while True:
        res = sio.readline().strip()
        if res == b"":
            continue
        res = bytes_filter(res)
        res = res.decode()
        if res == "":
            continue
        print(res)
        if (res[0] == "{" and res[-1] == "}"):
            if res == '{"msg":"are you dead?"}':
                sio.write('{"msg":"i am alive"}\n'.encode())
                sio.flush()
        elif (res[0] == "[" and res[-1] == "]"):
            if res == '[register state created]':
                cfg = sio.readline().strip().decode()
                print(f"**receive cfg:{cfg}**")
                cfg = json.loads(cfg)
                dmap = json.dumps(creat_dev_map(cfg), separators=(',', ':'))
                print(f"send cfg {dmap}")
                sio.write((dmap+"\n").encode())
                sio.flush()
                dumpOutput(sio)
                break
    return sio

if __name__ == "__main__":
    sio = conn_serial("COM3", 9600, 1)
    while True:
        dumpOutput(sio)
        sio.write((input("> ")+"\n").encode())
        sio.flush()
        dumpOutput(sio)