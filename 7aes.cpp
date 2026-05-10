import base64, time

def enc(t, k):
    e = ''.join(chr(ord(c) ^ ord(k[i % len(k)])) for i, c in enumerate(t))
    return base64.b64encode(k.encode()).decode(), base64.b64encode(e.encode()).decode()

def dec(c, k):
    e = base64.b64decode(c).decode()  
    return ''.join(chr(ord(ch) ^ ord(k[i % len(k)])) for i, ch in enumerate(e))

s = time.time()
k = "AES128KEY"
t = "Hello i2it, this is AES encryption!"

print("Original Text:", t)
iv, c = enc(t, k)

print("\nEncrypted:")
print("IV:", iv)
print("CipherText:", c)

print("\nDecrypted Text:")
print(dec(c, k))

print(f"\nRun completed in {int((time.time() - s) * 1000)}ms")
