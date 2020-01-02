; Payload configuration constants
.definelabel G_PAYLOAD_VROM,  0x03800000
.definelabel G_PAYLOAD_SIZE,  0x30000
.definelabel G_PAYLOAD_END,   0x80780000
.definelabel G_PAYLOAD_ADDR,  (G_PAYLOAD_END - G_PAYLOAD_SIZE)

; Subset of payload reserved for "C heap"
.definelabel G_C_HEAP_SIZE,   0x8000
.definelabel G_C_HEAP,        (G_PAYLOAD_END - G_C_HEAP_SIZE)
