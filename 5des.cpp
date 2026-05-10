def hex2bin(s):
    mp = {
        '0': "0000", '1': "0001", '2': "0010", '3': "0011",
        '4': "0100", '5': "0101", '6': "0110", '7': "0111",
        '8': "1000", '9': "1001", 'A': "1010", 'B': "1011",
        'C': "1100", 'D': "1101", 'E': "1110", 'F': "1111"
    }
    return "".join(mp[i] for i in s)

def bin2hex(s):
    return "".join(format(int(s[i:i+4], 2), 'X') for i in range(0, len(s), 4))

def xor(a, b):
    return "".join('0' if i == j else '1' for i, j in zip(a, b))

def permute(k, arr):
    return "".join(k[i - 1] for i in arr)

def shift_left(k, n):
    return k[n:] + k[:n]

initial_perm = [
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
]

final_perm = initial_perm[::-1]

exp_d = [
    32, 1, 2, 3, 4, 5, 4, 5,
    6, 7, 8, 9, 8, 9, 10, 11,
    12, 13, 12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 20, 21,
    22, 23, 24, 25, 24, 25, 26, 27,
    28, 29, 28, 29, 30, 31, 32, 1
]

def encrypt(pt, rkb, rounds=4):
    pt = permute(hex2bin(pt), initial_perm)

    left, right = pt[:32], pt[32:]

    for i in range(rounds):
        right_exp = permute(right, exp_d)
        x = xor(right_exp, rkb[i])

        x = x[:32]

        new_left = xor(left, x)
        left, right = right, new_left

        print(f"Round {i+1}: {bin2hex(left)} {bin2hex(right)}")

    combined = left + right
    return bin2hex(permute(combined, final_perm))

def generate_keys(key, rounds=4):
    key = hex2bin(key)

    left, right = key[:28], key[28:56]
    keys = []

    for i in range(rounds):
        left = shift_left(left, 1)
        right = shift_left(right, 1)

        keys.append((left + right)[:48])

    return keys

pt = "123456ABCD132536"
key = "AABB09182736CCDD"

rkb = generate_keys(key, rounds=4)

print("Encryption:")
cipher = encrypt(pt, rkb, rounds=4)
print("Cipher Text:", cipher)

print("\nDecryption:")
plain = encrypt(cipher, rkb[::-1], rounds=4)
print("Plain Text:", plain)
