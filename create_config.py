import hashlib
import json

node_token = "deadbeef"

target_device = [
    ("BH1750"                , True , 5, 57, ""),
    ("DHT"                   , True , 6, 67, ""),
    ("MoistureSensor"        , True , 7, 77, ""),
    ("YF-S201 FlowController", False, 8, 87, "")
]

def create_config():
    device_config = {
        "token":node_token,
        "input_devices":[],
        "output_devices":[]
    }

    for dev in target_device:
        hash = hashlib.md5()
        hash.update(node_token.encode() + dev[0].encode())

        if dev[1]:
            device_config["input_devices"].append({
                "hid":hash.digest().hex()[2:],
                "name":dev[0],
                "min_input":dev[2],
                "max_input":dev[3],
                "unit":dev[4]
            })
        else:
            device_config["output_devices"].append({
                "hid":hash.digest().hex()[2:],
                "name":dev[0],
                "min_output":dev[2],
                "max_output":dev[3],
                "unit":dev[4]
            })

    res = json.dumps(device_config, separators=(',', ':')).replace('"', '\\"')
    print(res)

def create_register_resp():
    dev_map = {
        "success":True,
        "device_map":{}
    }
    for idx, dev in enumerate(target_device):
        hash = hashlib.md5()
        hash.update(node_token.encode() + dev[0].encode())
        dev_map["device_map"].update({hash.digest().hex()[2:]:idx})
    
    print(json.dumps(dev_map, separators=(',', ':')))

cfg = {
    "cfg":
    [
        {
            "dev_hid":"a0dc72230878a4cfc03cb1da52ad8e",
            "condition":"gt",
            "val":8787,
            "sol":
            [
                {
                    "dev_hid":"839bc5bba6a76514868ed84275839c",
                    "operate":True
                },
                {
                    "dev_hid":"839bc5bba6a76514868ed84275839c",
                    "operate":False
                }
            ]
        },
    ],
    "latest_version":87
}
if __name__ == "__main__":
    create_register_resp()
    print(json.dumps(cfg))
    
    #create_config()
    # hash = hashlib.md5()
    # hash.update(node_token.encode() + "water pump".encode())
    # print(hash.digest().hex()[2:])
        