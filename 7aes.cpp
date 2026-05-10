from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad
import base64

def encrypt_AES(plaintext, key):
    cipher = AES.new(key, AES.MODE_CBC)
    ciphertext = cipher.encrypt(pad(plaintext.encode(), AES.block_size))

    return {
        "iv": base64.b64encode(cipher.iv).decode(),
        "ciphertext": base64.b64encode(ciphertext).decode()
    }

def decrypt_AES(ciphertext, key, iv):
    cipher = AES.new(key, AES.MODE_CBC, iv=base64.b64decode(iv))
    decrypted = unpad(cipher.decrypt(base64.b64decode(ciphertext)), AES.block_size)

    return decrypted.decode()

if __name__ == "__main__":
    key = get_random_bytes(16)

    plaintext = "Hello i2it, this is AES encryption!"
    print("Original Text:", plaintext)

    encrypted_data = encrypt_AES(plaintext, key)

    print("\nEncrypted:")
    print("IV:", encrypted_data["iv"])
    print("Ciphertext:", encrypted_data["ciphertext"])

    decrypted_text = decrypt_AES(
        encrypted_data["ciphertext"],
        key,
        encrypted_data["iv"]
    )

    print("\nDecrypted Text:", decrypted_text)
